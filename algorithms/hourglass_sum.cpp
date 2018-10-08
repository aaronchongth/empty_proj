// 2D vectors
// convolve with an hour glass shape, find largest hourglass sum

#include <vector>

int hourglassSum(std::vector<std::vector<int>> arr) {
  int curr_max = 0;

  for (int i = 1; i < arr.size() - 1; i++) {
    for (int j = 1; j < arr[0].size() - 1; j++) {
      int curr_sum = arr[i - 1][j - 1] + arr[i - 1][j] + arr[i - 1][j + 1] +
                     arr[i][j] + arr[i + 1][j - 1] + arr[i + 1][j] +
                     arr[i + 1][j + 1];
      if (curr_sum > curr_max) curr_max = curr_sum;
    }
  }
  return curr_max;
}