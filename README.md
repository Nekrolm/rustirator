# Rustirator: Rust Iterator Combinators for C++20 Ranges

Rustirator brings the expressive power of Rust's iterator combinators to C++20 ranges. It enables concise, functional-style transformations and processing of standard C++ containers, inspired by Rust's iterator API.

## Overview

Rustirator provides:

- Iterator combinators such as `filter`, `map`, `take`, `drop`, and `take_while`
- Expressive, chainable functional-style range processing for C++20
- Simple conversion from standard containers into iterator pipelines
- Easy collection of results back into standard containers

## Example Usage

Suppose you want to process a vector of integers by:
- Filtering only even numbers
- Mapping each number to its square divided by 2.0
- Collecting the results into a new vector

With Rustirator, this becomes:

```c++
#include "rustirator.h"
#include <vector>
#include <iostream>

auto process(std::vector<int> v) -> std::vector<float>
{
    return rustirator::into_iter(v)
        .filter([](int x) { return x % 2 == 0; })
        .map([](int x) { return x * x / 2.0; })
        .collect();
}

int main()
{
    for (auto x : process({1, 2, 3, 4, 5}))
    {
        std::cout << x << "\n";
    }
    return 0;
}
```

**Output:**
```
2
8
```

## Features

### Core Iterator Combinators

- **into_iter(container):** Start an iterator chain from a container.
- **iter(container):** Like `into_iter`, but always adapts the range for chaining (ensures "view" semantics).
- **filter(predicate):** Select elements based on a unary predicate.
- **map(function):** Transform each element with a function or lambda.
- **take(n):** Yield only the first `n` elements from the range.
- **drop(n):** Skip the first `n` elements, yield the rest.
- **take_while(predicate):** Take elements while the predicate returns `true`.
- **collect():** Gather the results into a standard C++ container (e.g., `std::vector`, `std::map`). `.collect()` uses auto-deduction based on the output type in assignment.

### Example: Using `take`, `drop`, and `take_while`

```c++
#include "rustirator.h"
#include <vector>
#include <iostream>

int main()
{
    auto result = rustirator::into_iter(std::vector<int>{1, 2, 3, 4, 5, 6})
        .drop(1) // Skip the first element (1)
        .take(3) // Take the next three elements (2, 3, 4)
        .take_while([](int x) { return x < 4; }) // Take while element < 4
        .collect<std::vector<int>>();

    for (auto x : result)
        std::cout << x << " "; // Output: 2 3
    std::cout << std::endl;
}
```

### Example: Custom Collection

```c++
#include "rustirator.h"
#include <vector>
#include <set>
#include <iostream>

int main()
{
    auto s = rustirator::into_iter(std::vector<int>{1,2,2,3,4,4,5})
        .filter([](int x) { return x % 2 == 0; })
        .collect<std::set<int>>();
    // s contains: 2, 4
}
```

## Getting Started

1. Add `#include "rustirator.h"` to your project.
2. Use `rustirator::into_iter(your_container)` or `rustirator::iter(your_container)` to start chaining.
3. Chain combinators (`filter`, `map`, `take`, etc.).
4. Call `.collect()` at the end to materialize the results.

## Requirements

- C++20 compatible compiler (for concepts and ranges support)

## License

MIT

---

For more advanced usage and available combinators, see the source and test files.