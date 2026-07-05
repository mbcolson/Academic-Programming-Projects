# Matrix

A C++ matrix class that supports common matrix operations, including addition, multiplication, transpose, and determinant calculation.

## Features

* Create matrices with custom row and column sizes
* Set and get matrix values
* Add matrices using `+=` and `+`
* Multiply matrices using `*=` and `*`
* Transpose a matrix
* Calculate the determinant of a square matrix
* Print matrix contents

## Files

```text id="kz41em"
Matrix.h        # Matrix class definition
Matrix.cpp      # Matrix implementation
Matrix_Main.cpp # Test driver
README.md       # Project documentation
```

## Notes

* Matrix values are stored as `long long` integers.
* Matrices are stored using a two-dimensional `vector`.
* Addition requires matrices with the same dimensions.
* Multiplication requires the first matrix’s column count to match the second matrix’s row count.
* Determinants can only be calculated for square matrices.
