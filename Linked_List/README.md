# Linked List

A C++ implementation of a singly linked list with cursor-based navigation.

## Features

* Insert integer values into the list
* Delete the current list item
* Check if the list is empty
* Reset the cursor to the front of the list
* Advance the cursor through the list
* Check if the cursor has reached the end
* Retrieve the current item
* Display the list contents for debugging

## Files

```text id="m7yq9a"
List.h        # List class definition
List.cpp      # List implementation
ListMain.cpp  # Test driver
README.md     # Project documentation
```

## Notes

* The list stores integer values.
* The implementation uses dynamically allocated nodes.
* Inserted items are placed before the current cursor position.
* `Delete()` removes the item at the current cursor position.
* The destructor removes all nodes when the list is destroyed.
