# C++ topics and mini optimizations :rocket:

## Contents

- Code
  - [emplace_back](#emplace_back)
  - [explicit](#explicit)
  - [template](#template)
  - [thread](#thread)
- Tools
  - [bazel](#bazel)
  - [cmake](#cmake)
  - [cxxopts](#cxxopts)
  - [doxygen](#doxygen)
  - [gtest](#gtest)
  - [protobuf](#protobuf)
- TODO
  - [Entity-component system](https://github.com/skypjack/entt)
  - [libuv wrapper](https://github.com/skypjack/uvw)
  - [Python bindings, Pybind11](https://github.com/pybind/pybind11)
  - [Algorithm in C++](https://github.com/TheAlgorithms/C-Plus-Plus)
  - [GUI in C++, imgui](https://github.com/ocornut/imgui)
  - [Rule of zero](http://scottmeyers.blogspot.com/2014/03/a-concern-about-rule-of-zero.html)
  - [Rule of zero - 2](https://cpppatterns.com/patterns/rule-of-zero.html#line7)
  - [Pimpl pattern](https://dzone.com/articles/the-pimpl-pattern-what-you-should-know)
  - [Pimpl and rule of zero](http://oliora.github.io/2015/12/29/pimpl-and-rule-of-zero.html)
  - [Most vexing parse](https://en.wikipedia.org/wiki/Most_vexing_parse), [example](https://stackoverflow.com/questions/19615659/c-default-constructor-not-being-called)

## emplace_back

This is for `emplace_back` that is a member function of `std::vector`. It can be used as a tiny optimization for vectorizing objects, [reference](https://en.cppreference.com/w/cpp/container/vector/emplace_back), [example](https://stackoverflow.com/questions/48630349/how-do-i-create-multiple-c-threads-without-blocking-the-main-thread-using-join),

```cpp
std::thread single_thread;
single_thread = std::thread(thread_fn);

std::vector<std::thread> bunch_of_threads;
bunch_of_threads.emplace_back(thread_fn);
```

instead of using `.push_back()`, which calls the copy constructor of objects.

## explicit

The compiler allows constructors and functions that have one single parameter to be implicitly converted to another type to suit the call. 

```cpp
class Foo
{
public:
  // single parameter constructor, can be used as an implicit conversion
  Foo (int foo) : m_foo (foo) 
  {
  }

  int GetFoo () { return m_foo; }

private:
  int m_foo;
};

void DoBar (Foo foo)
{
  int i = foo.GetFoo ();
}

int main ()
{
  DoBar (42);
  return 0;
}
```

The `explicit` keyword prevents such implicit conversions, [reference](https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean)

```cpp
class Foo
{
public:
  // the previous situation will not compile
  explicit Foo (int foo) : m_foo (foo) 
  {
  }

  int GetFoo () { return m_foo; }

private:
  int m_foo;
};
```

## template

[References](https://en.cppreference.com/w/cpp/language/templates) online should be good enough for most applications, here are some random A-ha moment notes I found useful,

* templates are implemented in header files, in order for the compiler to generate and compose type-named instructions in your code before compilation and linking happens

* templates are one of the reasons why most libraries can be header-only libraries :eyes:

* compilation errors get pretty difficult to debug when templates are involved, so if walls of compilation error text is thrown out, it is likely an error due to a template somewhere

### Variadic templates :feet:

Allows templates to handle varying number of arguments in a type-safe way. A nice example was given [here](https://eli.thegreenplace.net/2014/variadic-templates-in-c/)

```cpp
template<typename T>
T adder(T v) {
  return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args) {
  return first + adder(args...);
}
```

Note the use of `...` which is called a `parameter pack`, a template parameter that packs and unpacks varying number of parameters. References [here](https://en.cppreference.com/w/cpp/language/parameter_pack) and [here](https://stackoverflow.com/questions/39792417/what-does-this-three-dots-means-in-c)

### Example

`std::thread` constructor that handles varying number of arguments is a pretty good example of variadic templates, luckily for us, the STL has just been open sourced. (Yay!) So let's take a look

```cpp
template <class _Fn, class... _Args, class = enable_if_t<!is_same_v<_Remove_cvref_t<_Fn>, thread>>>
    explicit thread(_Fn&& _Fx, _Args&&... _Ax) {
        using _Tuple                 = tuple<decay_t<_Fn>, decay_t<_Args>...>;
        auto _Decay_copied           = _STD make_unique<_Tuple>(_STD forward<_Fn>(_Fx), _STD forward<_Args>(_Ax)...);
        constexpr auto _Invoker_proc = _Get_invoke<_Tuple>(make_index_sequence<1 + sizeof...(_Args)>{});
```

A more comprehensive example can be seen in the `example_threading` project, [here](example_threading/main.cpp).

## thread

`std::thread` can be used to handle multithreading operations, however lots of care will need to be taken for shared access memory safety.

```cpp
std::vector<std::thread> threads;
threads.emplace_back(threadFunction);

for (auto& t : threads)
  t.join();
```

* `.join()` is blocking until the `thread` function returns

* `.joinable()` lets you check if the `thread` has already started, note that it is not for checking if the `thread` function has already returned, for that check out `std::packaged_task`, `std::future` or `std::promise`

* `std::packaged_task`, [reference](https://stackoverflow.com/questions/9094422/how-to-check-if-a-stdthread-is-still-running)

```cpp
// create a packaged_task using some task and get its future
std::packaged_task<void()> task([]
{
  // replace below with any function that is supposed to run in a new thread
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(3s);
});
auto future = task.get_future();

// run task on new thread
std::thread t(std::move(task));

// get thread status using wait_for as before
auto status = future.wait_for(0ms);
if (status == std::future_status::ready)
{
  // the thread function is returned, join it without blocking now!
  t.join();
}

// or just wait to join, this blocks though D:
t.join();
```

For a more comprehensive example on spawning threads, packaging tasks and getting the return values of the thread function, check out [here](../example_threading/), and its [source code](../example_threading/src/main.cpp).

### mutex and locks :lock

* don't forget about `std::mutex` and `std::unique_lock<std::mutex>` for shared memory across threads

* avoid using `std::lock<std::mutex>`, because it will rely on lock and unlock pairs, use `std::unique_lock<std::mutex>` instead

* for non-critical operations that could be skipped (for example, printing stuff out), if the shared memory is alreedy locked, use `std::defer_lock`

```cpp
std::unique_lock<std::mutex> non_critical_lock(mutex, std::defer_lock);
if (!non_critical_lock.try_lock())
{
  // continue without performing the non-critical operation
  return;
}
// otherwise, lock was acquired, continue with operations on shared memory
```

* try to keep the operations after `lock`s as small as possible, use scopes if necessary

```cpp
if (someBool)
{
  {
    std::unique_lock<std::mutex> mem_lock(mem_mutex);
    foo.tiny_operation(); // small operation that reads or writes the shared memory
  }
  foo.bigger_operation(); // other operations that don't need it
}
```

---

## Tools :wrench:

* `cmake` - everyone's favorite build tool, [notes](topics/cmake.md) :hammer:

* `cxxopts` - light-weight C++ options and arguments handler, [reference](https://github.com/jarro2783/cxxopts) and [notes](topics/cxxopts.md) :hammer:

* `bazel` - build tool that Google released, [notes](topics/bazel.md) :hammer:

* `gtest` - test tool for unit testing, sometimes also known as Google Test, [introduction](https://www.youtube.com/watch?v=16FI1-d2P4E) and [notes](topics/gtest.md)

* `doxygen` - for documentation, can be used for other languages as well, [wholesome introduction](https://www.youtube.com/watch?v=TtRn3HsOm1s), [reference](http://www.doxygen.nl/index.html), [wiki example](https://en.wikipedia.org/wiki/Doxygen)

* `protobuf` - stands for protocol buffers, great alternative to JSONs for storing and compressing data. [Reference](https://developers.google.com/protocol-buffers/docs/cpptutorial) and [basic example](https://github.com/shaochuan/cmake-protobuf-example), a [fix](https://github.com/shaochuan/cmake-protobuf-example/issues/3) for now. A better example with CMake will be featured here soon :hammer:

## upcoming references :hammer:

* [Entity-component system](https://github.com/skypjack/entt)

* [libuv wrapper](https://github.com/skypjack/uvw)

* [Python bindings, Pybind11](https://github.com/pybind/pybind11)

* [Algorithm in C++](https://github.com/TheAlgorithms/C-Plus-Plus)

* [GUI in C++, imgui](https://github.com/ocornut/imgui)

* [Rule of zero](http://scottmeyers.blogspot.com/2014/03/a-concern-about-rule-of-zero.html)

* [Rule of zero - 2](https://cpppatterns.com/patterns/rule-of-zero.html#line7)

* [Pimpl pattern](https://dzone.com/articles/the-pimpl-pattern-what-you-should-know)

* [Pimpl and rule of zero](http://oliora.github.io/2015/12/29/pimpl-and-rule-of-zero.html)

* [Most vexing parse](https://en.wikipedia.org/wiki/Most_vexing_parse), [example](https://stackoverflow.com/questions/19615659/c-default-constructor-not-being-called)

## Protobuf

`Protobuf`, also known as Protocol Buffers, was introduced by Google. It has a lot of different uses, but I mainly learnt it for its message serialization and IO related functionalities. However I would also like to point out other gotchas.

* [guides and references](https://developers.google.com/protocol-buffers/docs/cpptutorial) - there are plenty of these online, the official one is best IMO

* [installation](example_protobuf) - some installation instructions and setup

* [example](example_protobuf) - diving in, here is an example `cmake` project, mainly following the guides given online, but with some tweaks for styling and safety.

* [syntax](https://www.crankuptheamps.com/blog/posts/2017/10/12/protobuf-battle-of-the-syntaxes/#) - note that there are major differences between syntax `proto2` and `proto3`.
