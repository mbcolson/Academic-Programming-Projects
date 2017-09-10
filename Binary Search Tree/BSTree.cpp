#include "BSTree.h"

void _destruct(BSTree::node*& n)
{
     if(n != NULL)
     {
          _destruct(n->LC);
          _destruct(n->RC);
          delete n;
     }    
}

BSTree::~BSTree()
{
     _destruct(root);
}

Data _retrieve(const BSTree::node* n, const KeyType& key) 
{
    if (n == NULL)
    {
         Data d;
         d.i =- 1;
         d.k =- 1;
         return d;
    }
    else
    {
         if(n->info.k == key)
              return n->info;
         else if(n->info.k > key)
              return _retrieve(n->LC, key);
         else
              return _retrieve(n->RC, key);
    }
}

//PRE: NOT IsEmpty()
//POST: FCTVAL == data item with this key
Data BSTree::Retrieve(const KeyType& item) const
{
     return _retrieve(root, item);      
}  

void _insert(BSTree::node*& n, const Data& item)
{
     if (n == NULL)
     {
          n = new BSTree::node;
          n->LC = NULL;
          n->RC = NULL;
          n->info = item;
     }
     else if(item.k < n->info.k)
          _insert(n->LC, item);
     else 
          _insert(n->RC, item); 
}
       
//PRE: NOT IsFull()
//POST: Item and k are inserted into BSTree
void BSTree::Insert(const Data& item)
{
    _insert(root, item); 
}

void _delete(BSTree::node*& n, const KeyType& key)
{
     BSTree::node* tempPtr;
     KeyType data;
     
     if(key < n->info.k)
          _delete(n->LC, key);
     else if(key > n->info.k)
          _delete(n->RC, key);
     else 
     {
          tempPtr = n;
          if(n->LC == NULL)
          {
               n = n->RC;
               delete tempPtr;
          }
          else if(n->RC == NULL)
          {
               n = n->LC;
               delete tempPtr;
          }
          else
          { 
               GetPredecessor(n->LC, data); 
               n->info.k = data;
               _delete(n->LC, data);
          }
     }
}     

void GetPredecessor(const BSTree::node* n, KeyType& data)
{
     while(n->RC != NULL)
          n = n->RC;
     data = n->info.k;
}
     
//PRE: NOT IsEmpty()
//POST: Item with this key is deleted
void BSTree::Delete(const KeyType& key)
{
     _delete(root, key);
}

void _inorder(const BSTree::node* n, void(*f)(const Data&))
{
     if(n != NULL)
     {
          if(n->LC != NULL)
               _inorder(n->LC, f);
          f(n->info);
          if(n->RC != NULL)
               _inorder(n->RC, f);
     }
}
//PRE: NOT IsEmpty()
//POST: BSTree is traversed and fun is applied to each node.
void BSTree::InOrder(void(*f)(const Data&))
{
     _inorder(root, f);
}

void _preorder(const BSTree::node* n, void(*f)(const Data&))
{
     if(n != NULL)
     {
          f(n->info);
          if(n->LC != NULL)
               _preorder(n->LC, f);
          if(n->RC != NULL)
               _preorder(n->RC, f);
     }
}

void BSTree::PreOrder(void(*f)(const Data&))
{
     _preorder(root, f);
}

void _postorder(const BSTree::node* n, void(*f)(const Data&))
{
     if(n != NULL)
     {
          if(n->LC != NULL)
               _postorder(n->LC, f);
          if(n->RC != NULL)
               _postorder(n->RC, f);
          f(n->info);
     }
}

void BSTree::PostOrder(void(*f)(const Data&))
{
     _postorder(root, f);
}

unsigned _depth(const BSTree::node* n)
{
     unsigned left_height, right_height;    
     
     if(n == NULL || n->RC == NULL && n->LC == NULL)
          return 0;
     else 
     {
          left_height = 1 + _depth(n->LC);
          right_height = 1 + _depth(n->RC);
          if(left_height > right_height)
               return left_height;
          else
               return right_height;
     }
}
//PRE: NOT IsEmpty()
//POST: FCTVAL == depth of the tree
unsigned BSTree::depth() const
{
     _depth(root);
}
