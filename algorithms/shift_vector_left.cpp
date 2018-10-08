// given a vector, shift it left d times, have circularity

#include <vector>

std::vector<int> rotLeft(std::vector<int> a, int d) {
  for (int i = 0; i < d; i++) {
    int first = a[0];
    a.erase(a.begin());
    a.push_back(first);
  }
  return a;
}