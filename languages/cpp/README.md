# C++ topics and mini optimizations :rocket:

* `cxxopts` - light-weight C++ options and arguments handler, [reference](https://github.com/jarro2783/cxxopts) and [notes](topics/cxxopts.md) :hammer:

* `emplace_back` for `std::vector` - tiny optimization of vectorized objects, [reference](https://en.cppreference.com/w/cpp/container/vector/emplace_back), [example](https://stackoverflow.com/questions/48630349/how-do-i-create-multiple-c-threads-without-blocking-the-main-thread-using-join)

* `explicit` keyword - for class constructors when to use it, and why, [reference](https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean)

* `std::thread` - multithreading operations and shared access memory safety, [notes](topics/threads.md)

* `template` - writing code that handles varying interfaces, and how to write great libraries, [notes](topics/template.md)

## Tools :wrench:

* `cmake` - everyone's favorite build tool, [notes](topics/cmake.md) :hammer:

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
