# Vector Class

A C++ implementation of a three-dimensional vector class. This project demonstrates basic class design, operator overloading, and common vector operations.

## Overview

The `VECTOR` class represents a vector in 3D space using `x`, `y`, and `z` coordinates. The included driver program, `VECTORMain.cpp`, demonstrates the class functionality with several sample vectors.

## Features

* Create 3D vectors
* Add and subtract vectors
* Calculate dot products
* Calculate cross products
* Multiply vectors by a scalar
* Find vector magnitude
* Find the angle between two vectors
* Print vectors using an overloaded output operator

## Project Files

| File             | Description                                  |
| ---------------- | -------------------------------------------- |
| `VECTOR.h`       | Declares the `VECTOR` class                  |
| `VECTOR.cpp`     | Implements the class methods                 |
| `VECTORMain.cpp` | Demonstrates and tests the vector operations |

## Class Functionality

The `VECTOR` class includes methods for calculating vector length, dot product, cross product, scalar multiplication, and the angle between two vectors. It also overloads the `+`, `-`, and `<<` operators to make vector operations and output more intuitive.

## Note

The `angle()` method returns the result in radians. The driver program converts these values to degrees for display.
