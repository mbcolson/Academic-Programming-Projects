#include "List.h"

using namespace std;

int main()
{
    List l1;
    
    cout << "The list is currently: " << (l1.IsEmpty() ? "empty" : "not empty") << endl;
    
    cout << "l1.Insert(4)" << endl;
    l1.Insert(4);
    
    cout << "The list is currently: " << (l1.IsEmpty() ? "empty" : "not empty") << endl;
    
    cout << "l1.Insert(6)" << endl;
    cout << "l1.Insert(2)" << endl;
    cout << "l1.Insert(3)" << endl;
    cout << "l1.Insert(8)" << endl;
    l1.Insert(6);
    l1.Insert(2);
    l1.Insert(3);
    l1.Insert(8);
    
    l1.Display();
    
    cout << "l1.Delete()" << endl;
    l1.Delete();
    
    l1.Display();
    
    cout << "l1.Advance()" << endl;
    cout << "l1.Advance()" << endl;
    l1.Advance();
    l1.Advance();
    
    l1.Display();
    
    cout << "The cursur is pointing: " << (l1.EndOfList() ?
         "at the end of list" : "somewhere other than the end of the list")
         << endl;
    
    cout << "l1.Delete()" << endl;
    l1.Delete();
    
    l1.Display();
    
    cout << "l1.Delete()" << endl;
    l1.Delete();
    
    l1.Display();
    
    cout << "l1.Delete()" << endl;
    l1.Delete();
    
    l1.Display();
    
    cout << "l1.Delete()" << endl;
    l1.Delete();
    
    l1.Display();
    
    cout << "l1.Delete()" << endl;
    l1.Delete();
    
    l1.Display();
    
    cout << "The list is currently: " << (l1.IsEmpty() ? "empty" : "not empty") << endl;
    
    cout << "l1.Insert(5)" << endl;
    cout << "l1.Insert(1)" << endl;
    cout << "l1.Insert(9)" << endl;
    cout << "l1.Insert(11)" << endl;
    l1.Insert(5);
    l1.Insert(1);
    l1.Insert(9);
    l1.Insert(11);
    
    l1.Display();
    
    cout << "l1.Delete()" << endl;
    l1.Delete();
    
    l1.Display();

    return 0;
}
