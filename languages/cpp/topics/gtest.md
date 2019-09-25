# gtest - Google Test :traffic_light:

`gtest` is an intuitive tool used for unit testing in C++ projects. There are multiple ways of integrating `gtest` with new or existing `cmake` projects, however the most robust way would be to have the project clone and build `gtest` from source before running the tests. These instructions are highlighted [here](https://github.com/google/googletest/blob/master/googletest/README.md).

Fun fact, `gtest` is also included in the `ROS` and `ROS2` ecosystem for unit testing, and open source packages could be tested automatically within its buildfarm if the right configurations are present.

## Examples

A simple example program was written [here](../example_gtest/) that gets tested with `gtest` for simple initializations and functional tests of objects called `BankAccount`.

The project directory structure looks like this

```bash
<path-to-repo>/languages/cpp/example_gtest/
├── CMakeLists.txt
├── include
│   └── bank_account
│       └── bank_account.hpp
├── src
│   └── main.cpp
└── test
    ├── bank_account_init_test.cpp
    ├── CMakeLists.txt
    └── CMakeLists.txt.in
```

Here are the build instructions,

```bash
git clone https://github.com/aaronchongth/coding
cd coding/languages/cpp/example_gtest

mkdir build
cd build
cmake -Dtest=ON ..
make

# this launches the minimal executable defined in src/main.cpp
./bank_account

# this launches the test that was defined in test/bank_account_init_test.cpp
./test/bank_account_init_test
```

## References

* [source code](https://github.com/google/googletest/tree/master/googletest)

* [integration instructions](https://github.com/google/googletest/blob/master/googletest/README.md)
