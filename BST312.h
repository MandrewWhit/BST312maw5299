
/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree


  Michael Whitaker maw5299


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);

};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();

}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)
        t = t->right;

    data = t->data;

}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    //YOUR CODE GOES HERE
    /*
    if((t->left==NULL)||(t->right==NULL)){
        deleteNode(t);
        return;
    }
    if(t->left!=NULL) {
        makeEmpty(t->left);
    }
    if(t->right!=NULL) {
        makeEmpty(t->right);
    }
    */

    if(t==NULL){ // if gone past a leaf return to previous node
        return;
    }

    makeEmpty(t->left);   // post order traversal delete leaves first
    makeEmpty(t->right);
    deleteNode(t);

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root); // pass the root of the tree to makeEmpty
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}


template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{

    //YOUR CODE GOES HERE
    if(t==NULL){ // check if there is nothing in the tree
        t = new TreeNode;
        t->data = newItem;
        t->left = NULL;
        t->right = NULL;
    }
    if(t->data<newItem){     //move to the right of the tree
        insertItem(t->right, newItem);
    }
    if(t->data>newItem){     //move to the left of the tree
        insertItem(t->left, newItem);
    }
    if(t->right==NULL) {      // if nothing exists to the right of the tree create a node
        if (t->data < newItem) {
            t->right = new TreeNode;
            (t->right)->data = newItem;
            (t->right)->left = NULL;
            (t->right)->right = NULL;
        }
    }
    if(t->left==NULL) {     // if nothing exists to the left of the tree create a node
        if (t->data > newItem) {
            t->left = new TreeNode;
            (t->left)->data = newItem;
            (t->left)->left = NULL;
            (t->left)->right = NULL;
        }
    }

}

template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    //YOUR CODE GOES HERE
    insertItem(root, newItem);  //call the insert function
}



template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    //YOUR CODE GOES HERE
    if(t==NULL){
        return 0;        //check if at a leaf
    }else{
        int result = 1;  //count for the current node
        int sum = countNodes(t->left);   //traverse the tree
        int sum2 = countNodes(t->right);
        result = result + sum; //add the results
        result = result + sum2;
        return result;
    }
}


template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    //YOUR CODE GOES HERE
    return countNodes(root);  //call the countnodes function
}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const {
    //YOUR CODE GOES HERE
    if(t==NULL){       //if gone past a leaf, return
        return;
    }
    result.push_back(t->data);   // preorder traversal, do action before recursion
    preOrderTraversal(t->left, result); // traverse left side of tree
    preOrderTraversal(t->right, result); // traverse right side of tree
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> myVector;         //declare vector
    preOrderTraversal(root, myVector);  // pass root of tree and empty vector
    return myVector;

}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if(t==NULL){  //if gone past a leaf, return
        return;
    }

    inOrderTraversal(t->left, result);     //go to left subtree first
    result.push_back(t->data);            // perform action on node before right subtree
    inOrderTraversal(t->right, result);    //visit right subtree


}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> result;     // declare an empty vector
    inOrderTraversal(root, result);   // pass the root of the tree and empty vector
    return result;
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if(t==NULL) {       // if gone ast a leaf, return
        return;
    }

    postOrderTraversal(t->left, result); // visit left subtree
    postOrderTraversal(t->right, result); // visit right subtree
    result.push_back(t->data); // perform action
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> result;  // declare vector
    postOrderTraversal(root, result);  // pass root of tree and empty vector
    return result;
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{
  //YOUR CODE GOES HERE
  vector<ItemType> result;         // declare empty vector
  result = postOrderTraversal();   // traverse the tree, fill a vector
  bool isInTree = false;

  for(typename vector<ItemType>::iterator itr = result.begin(); itr != result.end(); itr++){ //iterate through vector
        if((*itr)==item){                 // if item is found in the tree, set true
            isInTree = true;
        }
  }
  return isInTree;

}
#endif

