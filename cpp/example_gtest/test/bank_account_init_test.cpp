#include <iostream>
#include <gtest/gtest.h>

#include "bank_account/bank_account.hpp"

TEST(BankAccount, BankAccountStartsEmpty)
{
  BankAccount account_default;
  EXPECT_EQ(true, account_default.get_balance().empty());

  BankAccount account_currency("Ringgit");
  EXPECT_EQ(false, account_currency.get_balance().empty());
  EXPECT_EQ(1, account_currency.get_balance().size());
  EXPECT_EQ("Ringgit", account_currency.get_balance()[0].first);
  EXPECT_EQ(0, account_currency.get_balance()[0].second.dollars);
  EXPECT_EQ(0, account_currency.get_balance()[0].second.cents);

  BankAccount account_single_currency("SGD", CurrencyValue(1000, 20));
  EXPECT_EQ(false, account_single_currency.get_balance().empty());
  EXPECT_EQ(1, account_single_currency.get_balance().size());
  EXPECT_EQ("SGD", account_single_currency.get_balance()[0].first);
  EXPECT_EQ(1000, account_single_currency.get_balance()[0].second.dollars);
  EXPECT_EQ(20, account_single_currency.get_balance()[0].second.cents);
}

TEST(BankAccount, BankAccountFullWithdraw)
{
  BankAccount account("SGD", CurrencyValue(1000, 20));
  EXPECT_EQ(false, account.withdraw("Ringgit", CurrencyValue(100, 0)));
  EXPECT_EQ(true, account.withdraw("SGD", CurrencyValue(100, 0)));
  EXPECT_EQ(1, account.get_balance().size());
  EXPECT_EQ("SGD", account.get_balance()[0].first);
  EXPECT_EQ(900, account.get_balance()[0].second.dollars);
  EXPECT_EQ(20, account.get_balance()[0].second.cents);
  EXPECT_EQ(true, account.withdraw("SGD", CurrencyValue(900, 20)));
  EXPECT_EQ(1, account.get_balance().size());
  EXPECT_EQ("SGD", account.get_balance()[0].first);
  EXPECT_EQ(0, account.get_balance()[0].second.dollars);
  EXPECT_EQ(0, account.get_balance()[0].second.cents);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
