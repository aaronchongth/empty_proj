enum class Color { Red, Green Blue };
enum class Size { Small, Medium, Large };

struct Product
{
  string name;
  Color color;
  Size size;
};

// now we want filtering
struct ProductFilter
{
  typedef vector<Product*> Items;
};

// filter by color
ProductFilter::Items ProductFilter::by_color(Items items, Color color)
{
  Items result;
  for (auto& i : items)
    if (i->color == color)
      result.push_back(i);
  retrun result;
}

// but what if by size?
// what if by size AND color?

// we should separate conceptually our filtering process into 2 parts
// a filter, and a specification

template <typename T> struct Specification
{
  virtual bool is_satisfied(T* item) = 0;
};

template <typename T> struct Filter
{
  virtual vector<T*> filter(vector<T*> items, Specificatin<T>& spec) = 0;
};

// the improved filter will look like this
struct BetterFilter : Filter<Product>
{
  vector<Product*> filter(
    vector<Product*> items, Specification<Product>& spec) override
  {
    vector<Product*> result;
    for (auto& p : items)
      if (spec.is_satisfied(p))
        result.push_back(p);
    return result;
  }
};

// our specs can look like this
struct ColorSpecification : Specification<Product>
{
  Color color;
  
  explicit ColorSpecification(const Color color)
  : color{color}
  {}

  bool is_satisfied(Product* item) override
  {
    return item->color == color;
  }
};

// now we can do this
Product apple{ "Apple", Color::Green, Size::Small };
Product tree{ "Tree", Color::Green, Size::Large };
Product house{ "House", Color::Blue, Size::Large };

vector<Product*> all {&apple, &tree, &house};

BetterFilter bf;
ColorSpecification green(Color::Green);

auto green_things = bf.filter(all, green);
for (auto& x : green_things)
  cout << x->name << " is green" << endl;

// what about AND specifications?
template <typename T> struct AndSpecification : Specification<T>
{
  Specification<T>& first;
  Specification<T>& second;

  AndSpecification(Specification<T>& first, Specification<T>& second)
  : first{first}, second{second}
  {}

  bool is_satisfied(T* item) override
  {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

// now we can do more specs!
SizeSpecification large(Size::Large);
COlorSpecification green(Color::Green);
AndSpecification<Product> green_and_large{large, green};

auto big_green_things = bf.filter(all, green_and_large);
for (auto& x : big_green_things)
  cout << x->name << " is large and green" << endl;

// we can also implement the && operator
template <typename T> struct Specification
{
  virtual bool is_satisfied(T* item) = 0;

  AndSpecification<T> operator&&(Specification&& other)
  {
    return AndSpecification<T>(*this, other);
  }
};

auto green_and_big =
  ColorSpecification(Color::Green) && SizeSpecification(Size::Large);

