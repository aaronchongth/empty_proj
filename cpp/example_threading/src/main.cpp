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

#include <future>
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>

template<typename ReturnType>
class BaseClass
{
private:
  std::thread blocking_thread_;
  std::future<ReturnType> blocking_thread_future_;

  std::thread running_thread_;

  virtual void running_thread_fn() = 0;

public:
  BaseClass()
  {
    std::cout << "BaseClass(): entered" << std::endl;
    running_thread_ = std::thread(
        std::bind(&BaseClass::running_thread_fn, this));
    std::cout << "BaseClass(): completed" << std::endl;
  }

  ~BaseClass()
  {
    if (blocking_thread_.joinable())
      blocking_thread_.join();
    if (running_thread_.joinable())
      running_thread_.join();
    std::cout << "~BaseClass(): called" << std::endl;
  }

  template<typename... Args>
  bool execute_blocking_fn(
      std::function<ReturnType(Args...)> _blocking_fn, Args... _arguments)
  {
    if (blocking_thread_.joinable())
      return false;

    std::packaged_task<ReturnType(Args...)> 
        blocking_task([_blocking_fn](Args... _packaged_arguments)
    {
      return _blocking_fn(_packaged_arguments...);
    });
    blocking_thread_future_ = blocking_task.get_future();
    blocking_thread_ = std::thread(std::move(blocking_task), _arguments...);
    return true;
  }

  bool execute_blocking_fn(std::function<ReturnType()> _blocking_fn)
  {
    if (blocking_thread_.joinable())
      return false;

    std::packaged_task<ReturnType()> blocking_task([_blocking_fn]()
    {
      return _blocking_fn();
    });
    blocking_thread_future_ = blocking_task.get_future();
    blocking_thread_ = std::thread(std::move(blocking_task));
    return true;
  }

};

struct CustomReturn
{
  std::string name;
  int int_param;
  double double_param;
};

class DerivedClass : public BaseClass<CustomReturn>
{
private:
  int seconds_per_task_;

  std::chrono::high_resolution_clock::time_point running_time_now_;
  bool blocking_fn_with_param_called_;

  void running_thread_fn() override
  {
    auto t_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::high_resolution_clock::now() - running_time_now_);
    if (t_elapsed.count() >= 2)
    {
      if (blocking_fn_with_param_called_)
      {
        std::function<CustomReturn()> blocking_fn = 
            std::bind(&DerivedClass::blocking_fn_simple, this);
        this->execute_blocking_fn(blocking_fn);
        blocking_fn_with_param_called_ = false;
      }
      else
      {
        using namespace std::placeholders;
        std::function<CustomReturn(int, double, CustomReturn)> blocking_fn =
            std::bind(&DerivedClass::blocking_fn_with_param, this, _1, _2, _3);

        CustomReturn p3;
        p3.name = "custom_return";
        this->execute_blocking_fn(blocking_fn, 123, 43221.234, p3);
        blocking_fn_with_param_called_ = true;
      }
      
      std::cout << "running_thread_fn(): called" << std::endl;
      running_time_now_ = std::chrono::high_resolution_clock::now();
    }
  }

public:
  DerivedClass()
  {
    seconds_per_task_ = 5;
    blocking_fn_with_param_called_ = false;
    running_time_now_ = std::chrono::high_resolution_clock::now();
  }

  CustomReturn blocking_fn_simple()
  {
    auto t_0 = std::chrono::high_resolution_clock::now();
    auto t_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::high_resolution_clock::now() - t_0);
    while (t_elapsed.count() < seconds_per_task_)
    {
      t_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::high_resolution_clock::now() - t_0);
    }
    std::cout << "blocking_fn_simple(): ended" << std::endl;
    return CustomReturn();
  }

  CustomReturn blocking_fn_with_param(
      int p1, const double& p2, const CustomReturn& p3)
  {
    auto t_0 = std::chrono::high_resolution_clock::now();
    auto t_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::high_resolution_clock::now() - t_0);
    while (t_elapsed.count() < seconds_per_task_)
    {
      t_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::high_resolution_clock::now() - t_0);
    }
    std::cout << "blocking_fn_with_param(): ended" << std::endl;
    CustomReturn tmp_p = p3;
    tmp_p.double_param = p2;
    tmp_p.int_param = p1;
    return tmp_p;
  }

};

int main(int argc, char** argv)
{
  DerivedClass();
  std::cout << "all done" << std::endl;
  return 0;
}
