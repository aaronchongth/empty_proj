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

template<typename... Features>
class X : public Features...
{
public:
  void basicMethod() {}

  void init() override
  {
    cout << "x init called." << endl;
    (static_cast<void>(Features::init()), ...);
  }
};

//==============================================================================
int main()
{
  using IntX = X<IntFeature>;
  IntX int_x;
  int_x.init();
  int int_val = int_x.get_int_value();
  cout << "int_val: " << int_val << endl;

  using AllX = X<IntFeature, DoubleFeature, StringFeature>;
  AllX all_x;
  all_x.init();
  int all_int_val = all_x.get_int_value();
  double all_double_val = all_x.get_double_value();
  string all_string_val = all_x.get_string_value();

  cout << "all_int_val: " << all_int_val << endl;
  cout << "all_double_val: " << all_double_val << endl;
  cout << "all_string_val: " << all_string_val << endl;

  cout << "all done" << endl;
  return 0;
}
