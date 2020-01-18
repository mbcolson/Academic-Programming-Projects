#ifndef BSTREE_H_
#define BSTREE_H_

#include <bits/stdc++.h>

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
        node *left;
        node *right;
    };
	
    node* root;
	
    friend Data _retrieve(const node*, const KeyType&);
    friend bool _insert(node*&, const Data&);
    friend bool _delete(node*&, const KeyType&);
    friend void _inorder(const node*, void(*)(const Data&));
    friend void _preorder(const node*, void(*)(const Data&));
    friend void _postorder(const node*, void(*)(const Data&));
    friend int _depth(const node*);
    friend void _destruct(node*&);
    friend node* _findMin(node*);

  public:
    //PRE: None
    //POST: An empty BSTree is created
    BSTree() {root = NULL;}
	
    //PRE: None
    //POST: The BSTree is destroyed and all allocated memory is released
    ~BSTree();
	
    //PRE: None
    //POST: FCTVAL == (tree is empty)
    bool IsEmpty() const { return root == NULL; }
	
    //PRE: None
    //POST: FCTVAL == data item with this key returned
    Data Retrieve(const KeyType&) const;

    //PRE: Item with key is not already in the tree
    //POST: Item and k are inserted into the BSTree
    bool Insert(const Data&);
	
    //PRE: Item with key is in the tree
    //POST: Item with this key is deleted from the BSTree
    bool Delete(const KeyType&);
	
    //PRE: None
    //POST: BSTree is traversed and fun is applied to each node
    void InOrder(void (*)(const Data&));
	
    void PreOrder(void (*)(const Data&));
	
    void PostOrder(void (*)(const Data&));
	
    //PRE: None
    //POST: FCTVAL == depth of the tree
    int depth() const;
};

#endif
