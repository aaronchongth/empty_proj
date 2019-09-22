# threads :loop:

* keeping a bunch of threads alive, 

```cpp
std::vector<std::thread> threads;
threads.emplace_back(threadFunction);

for (auto& t : threads)
  t.join();
```

* `.join()` is blocking until the `thread` function returns

* `.joinable()` lets you check if the `thread` has already started, note that it is not for checking if the `thread` function has already returned, for that check out `std::packaged_task`, `std::future` or `std::promise`

* `std::packaged_task`, [reference](https://stackoverflow.com/questions/9094422/how-to-check-if-a-stdthread-is-still-running)

```cpp
// create a packaged_task using some task and get its future
std::packaged_task<void()> task([]
{
  // replace below with any function that is supposed to run in a new thread
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(3s);
});
auto future = task.get_future();

// run task on new thread
std::thread t(std::move(task));

// get thread status using wait_for as before
auto status = future.wait_for(0ms);
if (status == std::future_status::ready)
{
  // the thread function is returned, join it without blocking now!
  t.join();
}

// or just wait to join, this blocks though D:
t.join();
```
