#include <cstdlib>
#include <iostream>
#include "List.h"

using namespace std;

int main()
{
    List l1;
    cout << "The list is currently: " << (l1.IsEmpty() ? "empty" : "not empty") << endl;
    l1.Insert(4);
    cout << "l1.Insert(4)" << endl;
    cout << "The list is currently: " << (l1.IsEmpty() ? "empty" : "not empty") << endl;
    l1.Insert(6);
    l1.Insert(2);
    l1.Insert(3);
    l1.Insert(8);
    cout << "l1.Insert(6)" << endl;
    cout << "l1.Insert(2)" << endl;
    cout << "l1.Insert(8)" << endl;
    cout << "l1.Insert(2)" << endl;
    l1.Display();
    l1.Delete();
    cout << "l1.Delete()" << endl;
    l1.Display();
    l1.Advance();
    l1.Advance();
    cout << "l1.Advance()" << endl;
    cout << "l1.Advance()" << endl;
    l1.Display();
    cout << "The cursur is pointing: " << (l1.EndOfList() ? 
         "at the end of list" : "somewhere other than the end of the list")
         << endl << endl; 
    
    return 0;
}
