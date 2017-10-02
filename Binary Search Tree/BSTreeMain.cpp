#include "BSTree.h"
using namespace std;

void fun(const Data& item)
{
	cout << item.k << " ";
}

int main()
{
	BSTree bstree;
	cout << "BSTree bstree;" << endl << endl;
    srand(time(NULL));
    int cnt = 0;
	while(cnt < 15)
	{
        Data d;
        d.i = rand() % 100;
        d.k = rand() % 30;
        if(bstree.Insert(d))
        {
        	cout << "Insert of d.i = " << d.i << ", d.k = " << d.k
        		 << " completed successfully" << endl;
        	cnt++;
        }
        else
        {
            cout << "Insert of d.i = " << d.i << ", d.k = " << d.k
            	 << " failed" << endl;
        }
	}
	cout << endl << "bstree.InOrder(fun);" << endl;
    bstree.InOrder(fun);
    cout << endl << endl << "bstree.PreOrder(fun);" << endl;
    bstree.PreOrder(fun);
    cout << endl << endl << "bstree.PostOrder(fun);" << endl;
    bstree.PostOrder(fun);
    cout << endl << endl << "bstree.depth() = ";
    cout << bstree.depth() << endl << endl;

    cout << "bstree.Delete(5)" << endl;
    if(bstree.Delete(5))
    	cout << "Delete of key 5 was successful" << endl;
    else
    	cout << "Delete of key 5 failed" << endl;

    cout << endl << "bstree.Delete(10)" << endl;
    if(bstree.Delete(10))
       	cout << "Delete of key 10 was successful" << endl;
    else
       	cout << "Delete of key 10 failed" << endl;

    cout << endl << "bstree.Delete(13)" << endl;
    if(bstree.Delete(13))
      	cout << "Delete of key 13 was successful" << endl;
    else
       	cout << "Delete of key 13 failed" << endl;

    cout << endl << "bstree.InOrder(fun);" << endl;
    bstree.InOrder(fun);
    cout << endl << endl;

    cnt = 0;
    while(cnt < 5)
    {
        int key = rand() % 30;
        cout << "d = bstree.Retrieve(" << key << ")" << endl;
        Data d = bstree.Retrieve(key);
        if(d.k != -1)
        {
         	cout << "Data item with key = " << key << " and info = "
         	     << d.i << " retrieved successfully" << endl;
           	cnt++;
        }
        else
            cout << "Data item with key = " << key << " failed" << endl;
    }
	return 0;
}
