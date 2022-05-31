// allows hierarchical composistion of types
// for example Foo<Bar<Bax>> x; to declare a variable of a type that implements
// the traits of all three classes, without having to actually construct a brand
// new FooBarBaz type.

template<typename T> struct Mixin : T
{
  // ...
}
