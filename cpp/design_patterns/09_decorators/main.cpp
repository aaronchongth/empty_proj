#include <string>
#include <sstream>
#include <iostream>

using namespace std;


//==============================================================================
struct Feature
{
  virtual void init() = 0;
};

struct IntFeature : Feature
{
  int value;

  int get_int_value()
  {
    return value;
  }

  void init() override 
  {
    cout << "int init called." << endl;
    value = 50;
  }
};

struct DoubleFeature : Feature
{
  double value;

  double get_double_value()
  {
    return value;
  }

  void init() override
  {
    cout << "double init called." << endl;
    value = 40.0;
  }
};

struct StringFeature : Feature
{
  string value;

  string get_string_value()
  {
    return value;
  }

  void init() override
  {
    cout << "string init called." << endl;
    value = "thirty";
  }
};

template <typename... List>
struct FeatureList;

template <typename Head, typename... Tail>
struct FeatureList<Head, Tail...> : FeatureList<Tail...>
{};

template <>
struct FeatureList<>
{};

struct God : FeatureList<IntFeature, DoubleFeature, StringFeature>
{
};

//==============================================================================
// IsContained checks whether a type appears in a type list.
template <typename T, typename... List>
struct IsContained;

template <typename T, typename Head, typename... Tail>
struct IsContained<T, Head, Tail...>
{
  enum {value = std::is_same<T, Head>::value || IsContained<T, Tail...>::value};
};

template <typename T>
struct IsContained<T>
{
  enum {value = false};
};

//==============================================================================
// IsUnique checks whether a type list contains no duplicates.
// It uses IsContained to check all element combinations.
template <typename... List>
struct IsUnique;

template <typename Head, typename... Tail>
struct IsUnique<Head, Tail...>
{
  enum {value = !IsContained<Head, Tail...>::value && IsUnique<Tail...>::value};
};

template <>
struct IsUnique<>
{
  enum {value = true};
};

//==============================================================================
// With the above tools, the static assertion is then very simple.
template <typename... Ts>
struct NoDuplicates
{
  static_assert(IsUnique<Ts...>::value, "No duplicate types allowed");
};

//==============================================================================
// Basic types
struct Shape
{
  virtual string str() const = 0;
};

struct Circle : Shape
{
  float radius;

  explicit Circle(const float radius)
  : radius{radius}
  {}

  void resize(float factor)
  {
    radius *= factor;
  }

  string str() const override
  {
    ostringstream oss;
    oss << "A circle of radius " << radius;
    return oss.str();
  }
};

struct Square : Shape
{
  float side;

  explicit Square(const float side)
  : side{side}
  {}

  void resize(float factor)
  {
    side *= factor;
  }

  string str() const override
  {
    ostringstream oss;
    oss << "A square of side " << side;
    return oss.str();
  }
};

//==============================================================================
template <typename T>
struct ColoredShape : T
{
  static_assert(
    is_base_of<Shape, T>::value,
    "Template argument must be a Shape");

  string color;

  template <typename... Args>
  ColoredShape(const string color, Args ...args)
  : T(std::forward<Args>(args)...),
    color{color}
  {}

  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has the color " << color;
    return oss.str();
  }
};

//==============================================================================
template <typename T>
struct TransparentShape : T
{
  static_assert(
    is_base_of<Shape, T>::value,
    "Template argument must be a Shape");

  uint8_t transparency;

  template <typename... Args>
  TransparentShape(const uint8_t transparency, Args ...args)
  : T(std::forward<Args>(args)...),
    transparency{transparency}
  {}

  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has transparency " << transparency;
    return oss.str();
  }
};

//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
int main()
{
  ColoredShape<TransparentShape<Square>> sq = {"red", 51, 5};
  cout << sq.str() << endl;

  God god;
  god.init();
  // cout << "int: " << god.get_int_value() << endl;
  // cout << "double: " << god.get_double_value() << endl;
  // cout << "string: " << god.get_string_value() << endl;

  cout << "all done" << endl;
  return 0;
}
