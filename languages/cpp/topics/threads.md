# threads and any other related topics :loop:

## threads

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

## mutex and locks

* don't forget about `std::mutex` and `std::unique_lock<std::mutex>` for shared memory across threads

* avoid using `std::lock<std::mutex>`, because it will rely on lock and unlock pairs, use `std::unique_lock<std::mutex>` instead

* for non-critical operations that could be skipped (for example, printing stuff out), if the shared memory is alreedy locked, use `std::defer_lock`

```cpp
std::unique_lock<std::mutex> non_critical_lock(mutex, std::defer_lock);
if (!non_critical_lock.try_lock())
{
  // continue without performing the non-critical operation
  return;
}
// otherwise, lock was acquired, continue with operations on shared memory
```

* try to keep the operations after `lock`s as small as possible, use scopes if necessary

```cpp
if (someBool)
{
  {
    std::unique_lock<std::mutex> mem_lock(mem_mutex);
    foo.tiny_operation(); // small operation that reads or writes the shared memory
  }
  foo.bigger_operation(); // other operations that don't need it
}
```
