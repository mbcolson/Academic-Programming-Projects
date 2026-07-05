# String Class

A C++ implementation of a custom string class with common string manipulation and operator overloading features.

## Features

* Create strings from characters or C-style strings
* Copy and assign string objects
* Concatenate strings using `+` and `+=`
* Access and modify characters by index
* Compare strings using relational operators
* Convert strings to:

  * `char*`
  * `int`
  * `float`
* Find the position of a character
* Change letter casing:

  * Uppercase
  * Lowercase
  * Toggle case
* Supports input and output using `>>` and `<<`

## Files

```text id="f7m2qx"
STRING.h        # STRING class definition
STRING.cpp      # STRING class implementation
STRINGMain.cpp  # Test driver
README.md       # Project documentation
```

## Notes

* Strings are stored using dynamically allocated character arrays.
* The class includes constructors, a copy constructor, and a destructor.
* Comparison and concatenation operators are overloaded for `STRING`, `char*`, and `char` values.
* The demo program tests input, output, concatenation, comparison, case conversion, indexing, and type casting.
