# Dual - Automatic Differentiation Library

## Overview
This C++ library provides an implementation of dual numbers for automatic differentiation. It enables computation of function values and their derivatives simultaneously using template metaprogramming. The library supports various mathematical operations, including addition, multiplication, and exponentiation, ..., while automatically tracking derivatives.

## Features
- **Automatic Differentiation**: Computes function derivatives alongside function values.
- **Template Metaprogramming**: Uses C++ templates for compile-time type safety.
- **Custom Operator Overloading**: Supports arithmetic operations and derivatives tracking.
- **Mathematical Functions Support**: Implements standard mathematical functions such as `exp`.
- **Flexible Indexing**: Allows defining differentials with multiple indices for higher-order derivatives.

## Installation
This library is a header-only implementation. To use it, simply include the `dual` namespace in your C++ project.

```cpp
#include "dual.h" // Ensure this file is included in your project
```

## Usage

### Defining Dual Numbers
```cpp
#include <iostream>
#include "dual.h"

int main() {
    dual::number<double, 0> x{2};  // Define variable x with index 0
    dual::number<double, 1> y{3};  // Define variable y with index 1

    auto f = x * y + 3.0 * std::exp(y);  // Compute function f = x*y + 3*exp(y)

    std::cout << "f = " << f.value() << "\n";
    std::cout << "df/dx = " << f.dvalue<0>() << "\n";
    std::cout << "df/dy = " << f.dvalue<1>() << "\n";
    return 0;
}
```

### Output
```
f = 32.0855,
df/dx = 3,
df/dy = 26.0855
```

## Supported Operations
The library provides:
- **Addition (`+`)**
- **Multiplication (`*`)**
- **Exponentiation (`std::exp`)**
- **Custom Operations** can be added via template specialization.

## How It Works
This library represents a number and its derivatives using template-based type indexing. Each operation propagates derivatives according to differentiation rules. The primary classes and methods include:

- `number<T, Dn...>`: Represents a number with derivatives.
- `binary_operation<T, Derived>`: Implements binary operations like `+` and `*`.
- `unary_operation<T, Derived>`: Implements unary operations like `exp`.
- `indices<Dn...>`: Manages derivative indices for tracking differentiation.

## Steps to Build and Run Tests

1. Install GoogleTest (if not installed):

``` sh
sudo apt-get install libgtest-dev  # Ubuntu/Debian
sudo yum install gtest-devel       # Fedora
brew install googletest            # macOS (Homebrew)
Create a Build Directory and Compile:
```
2. Create a Build Directory and Compile:
``` sh
mkdir build && cd build
cmake ..
make
```
3.Run the Tests:
``` sh
./run_tests
```
4. Run with CTest:
``` sh
ctest --verbose
```



## License
This library is open-source and available under the MIT License.

## Contributions
Contributions and improvements are welcome! Feel free to fork the repository and submit pull requests.

## Author
Developed by Luis Monteiro.

## References
- [Automatic Differentiation](https://en.wikipedia.org/wiki/Automatic_differentiation)
- [Dual Numbers](https://en.wikipedia.org/wiki/Dual_number)

Happy coding!

