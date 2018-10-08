// Starting with a 1-indexed array of zeros and a list of operations,
// for each operation add a value to each of the array element between two given
// indices, inclusive. Once all operations have been performed, return the
// maximum value in your array.

// 1 2 100, index 1 and 2 add 100
// 2 5 100, index 2 to 5 add 100
// max is 200

#include <vector>

long arrayManipulation(int n, std::vector<std::vector<int>> queries) {
  int n_queries = queries.size();
  long curr_val = 0;
  long curr_max = 0;

  // slow way
  // vector<int> values(n, 0);
  // for (int i = 0; i < n_queries; i++){
  //     for (int j = queries[i][0]; j <= queries[i][1]; j++){
  //         values[j] += queries[i][2];
  //         if (values[j] > curr_max){
  //             curr_max = values[j];
  //         }
  //     }
  // }

  // algorithmic way, store the differences only
  std::vector<int> values(n, 0);
  for (int i = 0; i < n_queries; i++) {
    int start_ind = queries[i][0] - 1;
    int end_ind = queries[i][1] - 1;
    int sum = queries[i][2];

    values[start_ind] += sum;
    if (end_ind + 1 < n) values[end_ind + 1] -= sum;
  }
  for (int i = 0; i < n; i++) {
    curr_val += values[i];
    if (curr_val > curr_max) curr_max = curr_val;
  }
  return curr_max;
}