#ifndef HEAP_H
#define HEAP_H

#include <bits/stdc++.h>

const int MAX_ITEMS = 10;
typedef int Itemtype;

class Heap
{
     void ReheapDown(int root, int last);
     void ReheapUp(int root, int last);
     Itemtype* heap_array;
     int length;
public:
     Heap();
     ~Heap();
     void Insert(const Itemtype& It);
     Itemtype Retrieve();
     bool IsEmpty() const;
     bool IsFull() const;
};

#endif
