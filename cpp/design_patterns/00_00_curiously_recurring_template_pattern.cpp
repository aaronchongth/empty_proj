// Inheritor passes itself as a template argument to its base class
struct Foo : SomeBase<Foo>
{
  // ...
  // implements begin() and end() iterator pair
}

// Can be useful if the inheritor implements iterators
template<typename Derived>
struct SomeBase
{
  void foo()
  {
    for (auto& item : *static_cast<Derived*>(this))
    {
      // ...
    }
  }
}
