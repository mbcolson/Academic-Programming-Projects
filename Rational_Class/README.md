# Rational Class

A C++ class for representing rational numbers as reduced fractions.

## Features

* Stores fractions as numerator/denominator pairs
* Automatically reduces fractions to lowest terms
* Supports arithmetic operations:

  * Addition
  * Subtraction
  * Multiplication
  * Division
* Supports comparison operators
* Supports increment and decrement operators
* Finds reciprocals
* Raises rational numbers to integer powers
* Supports input and output using `>>` and `<<`

## Files

```text id="r8xz21"
Rational.h         # Rational class definition
Rational.cpp       # Rational class implementation
Rational_Main.cpp  # Test driver
README.md          # Project documentation
```

## Notes

* Rational numbers are stored using `long` values.
* A denominator of `0` is reset to `1`.
* Negative denominators are converted so the negative sign is stored in the numerator.
* The class includes overloaded operators for working with both rational numbers and integers.
