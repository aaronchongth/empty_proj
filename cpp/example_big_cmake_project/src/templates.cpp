#include <iostream>
#include <string>

template <typename T>
inline const T& Max(const T& _a, const T& _b)
{
  return _a < _b ? _b : _a;
}

int main(int argc, char** argv)
{
  int i = 39;
  int j = 20;
  std::cout << "Max(i, j): " << Max(i, j) << std::endl;

  return 0;
}
