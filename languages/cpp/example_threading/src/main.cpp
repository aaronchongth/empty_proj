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

  std::chrono::high_resolution_clock::time_point running_time_now_;
  std::thread running_thread_;

public:
  BaseClass()
  {
    std::cout << "BaseClass(): entered" << std::endl;
    running_time_now_ = std::chrono::high_resolution_clock::now();
    running_thread_ = std::thread(&std::bind(BaseClass::running_thread_fn, this));
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

  // template<typename... Args>
  // ReturnType spawn_thread(Args... _arguments)
  // {

  // }

  // ReturnType spawn_thread()
  // {

  // }

  void running_thread_fn()
  {

  }

};

class DerivedClass
{
private:
  int seconds_per_task_;

public:
  DerivedClass()
  {
    seconds_per_task_ = 5;
  }

  bool blocking_fn_simple()
  {
    auto t_0 = std::chrono::high_resolution_clock::now();
    auto t_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::high_resolution_clock::now() - t_0);
    while (t_elapsed < seconds_per_task_)
    {
      t_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::high_resolution_clock::now() - t_0);
    }
    std::cout << "blocking_fn_simple(): ended" << std::endl;
  }

};

int main(int argc, char** argv)
{
  std::cout << "all done" << std::endl;
  return 0;
}
