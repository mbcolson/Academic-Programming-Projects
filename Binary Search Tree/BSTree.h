#include <iostream>
using namespace std;

typedef int InfoType;
typedef int KeyType;

struct Data
{
     InfoType i;
     KeyType k;        
};

class BSTree
{
     struct node
     {
          Data info;
          node* LC;
          node* RC;
     }; 
     
     node* root;
     friend Data _retrieve(const node*, const KeyType&);
     friend void _insert(node*&, const Data&);
     friend void _delete(node*&, const KeyType&);
     friend void _inorder(const node*, void(*)(const Data&));
     friend void _preorder(const node*, void(*)(const Data&));
     friend void _postorder(const node*, void(*)(const Data&));
     friend unsigned _depth(const node*);
     friend void _destruct(node*&);
     friend void GetPredecessor(const node* n, KeyType& data);
public:
     
     //PRE: None
     //POST: An empty BSTree is created
     BSTree () {root = NULL;}
     //PRE: None
     //POST: The BSTree is destroyed and all allocated memory is released
     ~BSTree ();
     //PRE: None
     //POST: FCTVAL == (tree is empty)
     bool IsEmpty() const {return (root == NULL);}
     //PRE: NOT IsEmpty()
     //POST: FCTVAL == data item with this key
     Data Retrieve(const KeyType&) const;
     //PRE: NOT IsFull()
     //POST: Item and k are inserted into BSTree
     void Insert(const Data& );
     //PRE: NOT IsEmpty()
     //POST: Item with this key is deleted
     void Delete(const KeyType&);
     //PRE: NOT IsEmpty()
     //POST: BSTree is traversed and fun is applied to each node.
     void InOrder(void (*)(const Data&));
     void PreOrder(void (*)(const Data&));
     void PostOrder(void (*)(const Data&));
     //PRE: NOT IsEmpty()
     //POST: FCTVAL == depth of the tree
     unsigned depth( ) const;
};
