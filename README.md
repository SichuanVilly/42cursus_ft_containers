# 42Cursus ft_containers

This project is part of the **42cursus** curriculum and focuses on implementing a set of container classes in C++ that mimic the behavior of the standard library containers. The goal is to understand the inner workings of C++ containers, iterators, and memory management, as well as to practice object-oriented programming principles.

## Table of Contents

- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Built With](#built-with)

## Description

**ft_containers** is a collection of container classes in C++ that replicate the functionality of standard library containers such as `vector`, `map`, `stack`, `set`, and its iterators. This project is designed to help you better understand data structures, iterators, and memory allocation strategies.

### Key Concepts:

- **Custom Implementations** of standard containers like `vector`, `map`, `stack`, `set`.
- **Memory Management** using pointers and dynamic memory allocation.
- **Iterators** and **const_iterators** for traversing through containers.
- **Exception Handling** when the container's bounds are violated.

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/SichuanVilly/42cursus_ft_containers.git
    ```

2. Navigate to the project directory:

    ```bash
    cd 42cursus_ft_containers
    ```

3. Compile the project using `make`:

    ```bash
    make
    ```

    This will generate the necessary executables for testing the containers.

## Usage

To run the tests or use the containers, compile the main program and test different functionalities of each container implementation. Example:

```bash
make run
```
### Example Usage:

Here is an example of using the `vector` container:

```cpp
#include "vector.hpp"

int main() {
    ft::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << std::endl;

    return 0;
}
```
## Built With

- **C++** – The programming language used for the container implementations.
- **Make** – The build automation tool used to compile the project.

