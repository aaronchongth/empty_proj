# template and related topics :busts_in_silhouette:

[References](https://en.cppreference.com/w/cpp/language/templates) online should be good enough for most applications, here are some random A-ha moment notes I found useful,

* templates are implemented in header files, in order for the compiler to generate and compose type-named instructions in your code before compilation and linking happens

* templates are one of the reasons why most libraries can be header-only libraries :eyes:

* compilation errors get pretty difficult to debug when templates are involved, so if walls of compilation error text is thrown out, it is likely an error due to a template somewhere

## Variadic templates :feet:

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

[Reference](https://github.com/microsoft/STL/blob/master/stl/inc/thread)
