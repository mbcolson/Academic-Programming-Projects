#include "Heap.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
     Itemtype i1;
     Heap h;
     
     h.Insert(4);
     h.Insert(1);
     h.Insert(7);
     h.Insert(3);
     h.Insert(9);
     h.Insert(2);
     h.Insert(8);
     h.Insert(5);
     
     cout << "Heap is full: " << (h.IsFull() ? "true" : "false") << endl;
     cout << "Heap is empty: " << (h.IsEmpty() ? "true" : "false") << endl;
     i1 = h.Retrieve();
     cout << "h.Retrieve: " << i1 << endl;
     
     system("pause");
     return 0;
}
