// Sample driver
// EE 312 Fall 2018
//
// The BST should work for any data type or object.
// Other user created objects must have the << operator overloaded for 
// output.
//

#include <iostream>
#include <fstream>
#include "BST312.h"

using namespace std;

template <typename T>
void print(vector<T> vec){
    for(int i = 0 ; i < vec.size() ; i++){
        cout << vec[i] << endl;;
    }
}

int main() {


    ifstream inFile;
    inFile.open("test.txt");

    BST_312<int> bst;
   
    string s;
    inFile >> s;
    /*while (inFile) {;
        cout << "inserting ... " << s << endl;
        bst.insertItem(s);
        inFile >> s;
    }*/
    for(int i=0; i<10; i++){
        bst.insertItem(i);
    }


//traversal test
    cout << "postorder traversal is " << endl;

    print(bst.postOrderTraversal());
    cout << endl;

    cout << "preorder traversal is " << endl;
    print(bst.preOrderTraversal());
    cout << endl;

    cout << "inorder traversal is " << endl;
    print(bst.inOrderTraversal());
    cout << endl;

    //countNodes test
    cout << "countNodes Test " << endl << "Number of nodes is: ";
    cout << bst.countNodes() << endl;
    cout << endl;

    //isItemInTree test
    cout << "isItemInTree Test " << endl;
    cout << "Looking for: 1" << endl;
    if(bst.isItemInTree(1)){
        cout << "Yes! It is in the tree" << endl;
    }else{
        cout << "No, it is not in the tree" << endl;
    }
    cout << endl;

//makeEmpty test
    cout << "makeEmpty Test " << endl;
    bst.makeEmpty();
    cout << "preorder traversal is " << endl;
    vector<int> testVector = bst.preOrderTraversal();
    if(testVector.empty()){
        cout << "returned an empty vector" << endl;
    }else {
        print(bst.preOrderTraversal());
        cout << endl;
    }


}

