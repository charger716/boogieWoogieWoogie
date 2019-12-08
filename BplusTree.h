/*
 * Authors: Joseph Perez, Nicholas Prater
 * Assignment Title: Group Project
 * Assignment Description: This is the header file for the B+ Tree
 *                          visualization
 * Date Created: 12/1/19
 * Due Date: 12/9/19
 * Date Last Modified: 12/1/19
 */

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>

using namespace std;

struct Node{
    int *data, size, max;
    Node **children;
    Node *nextLeaf;
    bool isKey;

    // Constructor
    explicit Node(int m){
        max = m;
        size = 0;
        data = new int[max];
        children = new Node*[max];
        isKey = false;
        nextLeaf = nullptr;
    }

    // Destructor
    ~Node(){
        delete [] data;
        for (int i = 0; i < this->max; i++){
            delete children[i];
        }
        delete children;
    }
};

class BPlusTree {
private:

//    void split(Node*& p, Node*& n);
    void InsertionSort (int data[], int size, int d);
    void split(Node*& n, Node*& p);

    int m;
    Node* root;

public:
    BPlusTree(int max = 3);
    ~BPlusTree();
    void find(int d);
    void insert(int d);
    void remove(int d);
};


#endif //BPLUSTREE_H
