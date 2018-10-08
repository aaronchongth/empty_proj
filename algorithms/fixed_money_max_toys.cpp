// some dude has a set amount of money
// vector of toy prices
// max number of toys?

#include <algorithm>
#include <vector>

int maximumToys(const std::vector<int>& prices, int k) {
  std::sort(prices.begin(), prices.end());
  int n_toys = 0;
  int money_left = k;

  for (int i = 0; i < prices.size(); i++) {
    if (money_left == 0) {
      return n_toys;
    }

    if (money_left >= prices[i]) {
      n_toys++;
      money_left -= prices[i];
    }
  }
  return n_toys;
}