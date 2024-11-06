# Algorithm Study

Welcome to my personal collection of algorithmic solutions. This repository is organized by algorithm type to help you easily find and study different algorithms.

This project primarily implements these algorithms using C++ 20 language features.

## Table of Contents

- [Array Algorithms](#array-algorithms)
- [Sorting Algorithms](#sorting-algorithms)
- [Search Algorithms](#search-algorithms)
- [Graph Algorithms](#graph-algorithms)
- [Backtracking Algorithms](#backtracking-algorithms)
- [Dynamic Programming](#dynamic-programming)
- [Other Algorithms](#other-algorithms)

## Array Algorithms

A collection of various array traversal based algorithms
See [Array Algorithms](./src/array/)

## Sorting Algorithms

A collection of various sorting algorithms.
See [Sorting Algorithms](./src/sorting/)

## Search Algorithms

A collection of various search algorithms.
See [Search Algorithms](./src/search/)

## Graph Algorithms

A collection of various graph algorithms.
See [Graph Algorithms](./src/graph/)

## Backtracking Algorithms

A collection of various backtracking algorithms.
See [Backtracking Algorithms](./src/backtracking/)

## Dynamic Programming

A collection of dynamic programming solutions. 
See [Dynamic Programming](./src/dynamicProgramming/)

## Other Algorithms

A collection of other miscellaneous algorithms.
See [Other Algorithms](./src/otherAlgorithms/)

## Compilation
This project utilizes CMake for build configuration. To build this project is it recommended to create a build directory in a subfolder, and execute `cmake`. It is reccomended to use `ninja` as your build tool, but this project should build with most standard CMake compatible build tools.

Ex:
```
mkdir build
cmake -GNinja ..
ninja
```

## Contributing

Feel free to contribute by submitting a pull request. Please ensure your code is well-documented and tested.

## License

This project is licensed under the MIT License.