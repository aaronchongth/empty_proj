// input a vector, sort using bubble sort
// count number of swaps needed

#include <algorithm>
#include <iostream>
#include <vector>

// slow n^2 bubble sort
void bubble_sort(std::vector<int>& arr) {
  for (int i = 0; i < arr.size(); i++) {
    for (int j = 0; j < arr.size() - 1; j++) {
      // Swap adjacent elements if they are in decreasing order
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void count_swaps(std::vector<int> a) {
  int swaps = 0;

  // bubble sort implementation
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a.size() - 1; j++) {
      // Swap adjacent elements if they are in decreasing order
      if (a[j] > a[j + 1]) {
        std::swap(a[j], a[j + 1]);
        swaps++;
      }
    }
  }

  std::cout << "Array is sorted in " << swaps << " swaps." << std::endl;
  std::cout << "First Element: " << a[0] << std::endl;
  std::cout << "Last Element: " << a[a.size() - 1] << std::endl;
  return;
}