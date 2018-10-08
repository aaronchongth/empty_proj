// also known as New Years Chaos
// a queue of people, in a vector, 1,2,3,4,5,6
// can bribe 2 people at most to get ahead

#include <algorithm>
#include <iostream>
#include <vector>

void minimum_bribes(std::vector<int> q) {
  int n_bribes = 0;
  for (int i = q.size() - 1; i >= 0; i--) {
    // if this person is more than 2 from this position, fail
    if (q[i] - (i + 1) > 2) {
      std::cout << "Too chaotic" << std::endl;
      return;
    }

    int curr_num = q[i];
    // check all the people from 1 in front of this person's original position
    // all the way to before his current position
    int curr_index = curr_num - 1;
    for (int j = std::max(0, curr_index - 1); j < i; j++) {
      if (q[j] > curr_num) n_bribes++;
    }
  }
  std::cout << n_bribes << std::endl;
  return;
}