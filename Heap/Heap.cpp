#include "Heap.h"
using namespace std;

Heap::Heap()
{
     heap_array = new Itemtype[MAX_ITEMS];
     length = 0;
}

Heap::~Heap()
{
     delete [] heap_array;
}

void Heap::Insert(const Itemtype& It)
{
     if(IsFull())
          cout << "Heap is full" << endl;
     else
     {
          length++;
          heap_array[length - 1] = It;
          ReheapUp(0, length - 1);
     }
}

Itemtype Heap::Retrieve() 
{
     Itemtype It;    
         
     if(IsEmpty())
          cout << "Heap is empty" << endl;
     else
     {
          It = heap_array[0];
          heap_array[0] = heap_array[length - 1];
          length--;
          ReheapDown(0, length - 1);
     }
     return It;
}

bool Heap::IsEmpty() const
{
     return length == 0;
}

bool Heap::IsFull() const
{
     return length == MAX_ITEMS;
}

void Heap::ReheapDown(int root, int last)
{
     int maxChild, RC, LC;
     Itemtype temp;
     
     LC = (root * 2) + 1;
     RC = (root * 2) + 2;
     
     if(LC <= last)
     {
          if(LC == last)
               maxChild = LC;
          else
          {
               if(heap_array[LC] <= heap_array[RC])
                    maxChild = RC;
               else
                    maxChild = LC;
          }
          if(heap_array[root] < heap_array[maxChild])
          {
               temp = heap_array[root];
               heap_array[root] = heap_array[maxChild];
               heap_array[maxChild] = temp;             
               ReheapDown(maxChild, last);
          }
     }
}

void Heap::ReheapUp(int root, int last)
{
     int parent;
     Itemtype temp;
     
     if(last > root)
     {
          parent = (last - 1) / 2;
          
          if(heap_array[parent] < heap_array[last])
          {
               temp = heap_array[parent];
               heap_array[parent] = heap_array[last];
               heap_array[last] = temp;               
               ReheapUp(root, parent);
          }
     }
}
