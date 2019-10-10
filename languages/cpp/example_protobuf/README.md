<h1 align="center">
  Protocol Buffers example
</h1>

<p align="center">
  <a href="https://opensource.org/licenses/Apache-2.0" alt="Apache-2.0">
    <img src="https://img.shields.io/badge/License-Apache%202.0-blue.svg">
  </a>
</p>

This example is written mainly based on the example given on official `protobuf` C++ references, however I added some tweaks to it for styling and safety preferences. Namely avoiding the use of raw pointers as much as possible, while passing ownership using `set_allocated_<>(...)`.

## Project Structure

```
example_protobuf
├── CMakeLists.txt
├── main.cpp
├── proto
│   ├── CMakeLists.txt
│   └── example_msg.proto
```

## Installation

These instructions are written for and tested on Ubuntu 18.04

```bash
sudo apt update
sudo apt upgrade
sudo apt install protobuf-c-compiler
```

For building the project,

```bash
git clone https://github.com/aaronchongth/coding
cd coding/languages/cpp/example_protobuf

mkdir build
cd build
cmake ..
make

# running the project
./main
```
