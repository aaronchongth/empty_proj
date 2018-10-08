// given a vector that is sequential but unordered
// find minimum number of swaps to sort

#include <vector>

int minimumSwaps(std::vector<int> arr) {
  int swaps = 0;
  for (int i = 0; i < arr.size(); i++) {
    // since it is sequential, we just check if it is in correct pos
    if (arr[i] == i + 1) continue;

    // otherwise swap to its correct pos, check current pos again
    std::swap(arr[i], arr[arr[i] - 1]);
    swaps++;
    i--;
  }
  return swaps;
}