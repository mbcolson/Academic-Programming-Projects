#include <cstdlib>
#include <iostream>
#include "BSTree.h"
using namespace std;

void fun(const Data& item){cout << item.k << " ";}

int main()
{
     BSTree bs;
     for(unsigned i = 0; i < 15; i++)
     {
          Data d;
          d.i = rand() % 15;
          d.k = d.i;
          bs.Insert(d);
     } 
     Data d1;
     d1.i = 5;
     d1.k = 7;
     cout << "d1.k = 7" << endl;
     bs.Delete(d1.k);
     cout << "bs.Delete(d1.k)" << endl;
     Data d2, d3;
     d2.i = 26;
     d2.k = 6;
     cout << "d2.i = 26" << endl;
     cout << "d2.k = 6" << endl;
     bs.Insert(d2);
     cout << "bs.Insert(d2)" << endl;
     d3 = bs.Retrieve(d2.k);
     cout << "bs.Retrieve(d2.k): " << d3.i << endl;
     cout << "depth is: " << bs.depth() << endl;
     cout << "In Order Traversal: ";
     bs.InOrder(fun);
     cout << endl << "Pre Order Traversal: ";
     bs.PreOrder(fun);
     cout << endl << "Post Order Traversal: ";
     bs.PostOrder(fun);
     cout << endl << endl;
     
     return 0;
}
