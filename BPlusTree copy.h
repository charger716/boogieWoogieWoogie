//
//  BPlusTree.h
//  B+Tree
//
//  Created by Zach Coon on 12/7/19.
//  Copyright © 2019 Zach Coon. All rights reserved.
//

#ifndef BPlusTree_h
#define BPlusTree_h
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

        // assign all children to null
        for(int i = 0; i < max; i++){
            children[i] = nullptr;
        }

        isKey = false;
        nextLeaf = nullptr;
    }

    // Destructor
    ~Node(){
        for (int i = 0; i < size; i++){
            delete children[i];
        }
        delete children;
        delete [] data;
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
    void shiftR(Node*& curr, Node*& Neighbor);
    void shiftL(Node*& curr, Node*& Neighbor);
    void merge(Node*& curr, Node*& LeftChild, Node*& RightChild);
    void mergeLeft(Node*& curr, Node*& LeftChild, Node*& RightChild);
    void Balance(Node*& curr);
};

#endif /* BPlusTree_h */
