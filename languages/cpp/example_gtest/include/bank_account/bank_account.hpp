/*
Copyright (c) 2019 Aaron Chong. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

struct CurrencyValue
{
  int dollars;
  int cents;

  CurrencyValue() : dollars(0), cents(0) {}

  explicit CurrencyValue(const int& _dollars, const int& _cents)
    : dollars(_dollars), cents(_cents)
  {
    if (cents > 99)
    {
      dollars += cents % 100;
      cents /= 100;
    }
  }
};

class BankAccount
{
private:
  std::unordered_map<std::string, CurrencyValue> balance_;

  void empty_account()
  {
    balance_.clear();
  }

  bool check_enough(const std::string& _type, const CurrencyValue& _value)
  {
    auto it = balance_.find(_type);

    if (it == balance_.end())
      return false;

    if (it->second.dollars < _value.dollars)
      return false;

    if (it->second.dollars == _value.dollars && 
        it->second.cents < _value.cents)
      return false;

    return true;
  }

public:
  BankAccount()
  {
    empty_account();
  }

  BankAccount(const std::string& _type, const CurrencyValue& _value)
  {
    empty_account();
    balance_[_type] = _value;
  }

  BankAccount(
      const std::unordered_map<std::string, CurrencyValue>& _init_sum)
  {
    empty_account();
    balance_ = _init_sum;
  }

  BankAccount(
      const std::vector<std::pair<std::string, CurrencyValue>>& _init_sum)
  {
    empty_account();
    for (const auto& it : _init_sum)
    {
      balance_[it.first] = it.second;
    }
  }

  BankAccount(const std::string& _designated_currency)
  {
    empty_account();
    balance_[_designated_currency] = CurrencyValue();
  }

  bool withdraw(const std::string& _type, const CurrencyValue& _amount)
  {
    if (check_enough(_type, _amount))
    {
      balance_[_type].dollars -= _amount.dollars;
      balance_[_type].cents -= _amount.cents;
      if (balance_[_type].cents < 0)
      {
        --balance_[_type].dollars;
        balance_[_type].cents += 100;
      }
      return true;
    }
    return false;
  }

  bool deposit(const std::string& _type, const CurrencyValue& _amount)
  {
    auto it = balance_.find(_type);
    if (it == balance_.end())
      balance_[_type] = _amount;
    else
    {
      balance_[_type].dollars += _amount.dollars + (_amount.cents % 100);
      balance_[_type].cents += (_amount.cents / 100);
    }
    return true;
  }

  std::vector<std::pair<std::string, CurrencyValue>> get_balance()
  {
    std::vector<std::pair<std::string, CurrencyValue>> result;
    result.clear();
    for (const auto& it : balance_)
    {
      result.emplace_back(it.first, it.second);
    }
    return result;
  }
};
