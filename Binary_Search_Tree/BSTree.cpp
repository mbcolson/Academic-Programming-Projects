#include "BSTree.h"
using namespace std;

//PRE: None
//POST: The BSTree is destroyed and all allocated memory is released
BSTree::~BSTree() {
    _destruct(root);
}

//PRE: None
//POST: FCTVAL == data item with this key returned
Data BSTree::Retrieve(const KeyType& key) const {
     return _retrieve(root, key);
}

//PRE: Item with key is not already in the tree
//POST: Item and k are inserted into the BSTree
bool BSTree::Insert(const Data& item) {
    return _insert(root, item);
}

//PRE: Item with key is in the tree
//POST: Item with this key is deleted from the BSTree
bool BSTree::Delete(const KeyType& key) {
    return _delete(root, key);
}

//PRE: None
//POST: BSTree is traversed and fun is applied to each node
void BSTree::InOrder(void (*f)(const Data&)) {
    _inorder(root, f);
}

void BSTree::PreOrder(void (*f)(const Data&)) {
    _preorder(root, f);
}

void BSTree::PostOrder(void (*f)(const Data&)) {
    _postorder(root, f);
}

//PRE: None
//POST: FCTVAL == depth of the tree
int BSTree::depth() const {
    return _depth(root);
}

Data _retrieve(const BSTree::node* node, const KeyType& key) {
    if (node == NULL) {
        Data d;
        d.i = -1;
        d.k = -1;
        return d;
    }

    if (node->info.k == key)
        return node->info;
    else if (node->info.k > key)
        _retrieve(node->left, key);
    else
        _retrieve(node->right, key);
}

bool _insert(BSTree::node*& node, const Data& item) {
    if (node == NULL) {
        node = new BSTree::node;
        node->left = node->right = NULL;
        node->info = item;
        return true;
    }
    if (node->info.k < item.k)
        _insert(node->right, item);
    else if (node->info.k > item.k)
    	_insert(node->left, item);
    else
    	return false;
}

BSTree::node* _findMin(BSTree::node* node) {
    if (node == NULL)
        return NULL;
	
    if (node->left == NULL)
        return node;
	
    return _findMin(node->left);
}

bool _delete(BSTree::node*& node, const KeyType& key) {
    if (node == NULL)
        return false;
    if (node->info.k < key)
    	return _delete(node->right, key);
    else if (node->info.k > key)
    	return _delete(node->left, key);
    else if (node->left != NULL and node->right != NULL) {
        node->info = _findMin(node->right)->info;
        return _delete(node->right, node->info.k);
    } else {
    	BSTree::node *n = node;
	    
    	if (node->left != NULL)
    	    node = node->left;
    	else
    	    node = node->right;
	
    	delete n;
    }
    return true;
}

void _inorder(const BSTree::node* node, void(*f)(const Data&)) {
    if (node == NULL)
        return;

    _inorder(node->left, f);
    f(node->info);
    _inorder(node->right, f);
}

void _preorder(const BSTree::node* node, void(*f)(const Data&)) {
    if (node == NULL)
	return;
	
    f(node->info);
    _preorder(node->left, f);
    _preorder(node->right, f);
}

void _postorder(const BSTree::node* node, void(*f)(const Data&)) {
    if (node == NULL)
        return;
	
    _postorder(node->left, f);
    _postorder(node->right, f);
    f(node->info);
}

int _depth(const BSTree::node* node) {
    if (node == NULL)
        return 0;
	
    return 1 + max(_depth(node->left), _depth(node->right));
}

void _destruct(BSTree::node*& node) {
    if (node != NULL) {
    	_destruct(node->left);
    	_destruct(node->right);
    	delete node;
    }
}
