//
//  BPlusTree.cpp
//  B+Tree
//
//  Created by Zach Coon on 12/7/19.
//  Copyright © 2019 Zach Coon. All rights reserved.
//

#include "BplusTree.h"

void BPlusTree::InsertionSort(int data[], int size, int d){
    for (int i = 1; i < size; i++){
        int temp = data[i];
        int j;
        for (j = i ; j > 0 && temp < data[j -1]; --j){
            data[j] = data[j-1];
        }
        data[j] = temp;
    }
}

// public functions
BPlusTree::BPlusTree(int max) {
    m = max;
    root = nullptr;
}

BPlusTree::~BPlusTree() {
    delete root;
}

// Nick, Joseph Insert, split
void BPlusTree::insert(int d) {
    if (!root){
        root = new Node(m);
        root->data[0] = d;
        root->size++;
    } else {
        Node* cur = root;
        Node* par = nullptr;

        // index for child pointer
        int j = 0;

        // find possible leaf node
        while (cur->isKey){
            for (int i = 0; i < cur->size; i++){
                if (d > cur->data[i]){
                    j = i+1;
                }
            }
            par = cur;
            cur = cur->children[j];
        }

        // insert value if space
        if (cur->size < m){

            this->InsertionSort(cur->data,cur->size, d);
            cur->size++;
            
            if (cur->size == m){
                split(cur,par);
            }

        }
    }
}


// n = parent
// p = current
void BPlusTree::split(Node*& n, Node*& p) {
    int mid = n->data[n->size/2];
    int ndx = n->size/2;
    int j = 0;

    // root case
    if (p == nullptr) {
        // create new parent node with middle value as key
        p = new Node(m);
        p->data[p->size++] = mid;
        p->isKey = true;
        p->children[j] = new Node(m);

        // copy all values smaller than middle value to left
        // child.
        for(int i = 0; i < ndx; i++){
            p->children[j]->data[i] = n->data[i];
        }

        // shift values of right child
        for(int i = 0; i < n->size; i++){
            n->data[i] = n->data[i+1];
        }
        n->size--;

        // attach child
        p->children[j+1] = n;

        //update root
        root = p;

    } else {
        this->InsertionSort(n->data, n->size, mid);
        // recursion call somewhere in here

        for (int i = 0; i < ndx; i++) {
            this->InsertionSort(n->children[j]->data, n->children[j]->size, p->data[i]);
            n->children[j]->size++;

        }

        // move the pointers???
        // shift values in current node

        j++;

        for (int i = 0; i < p->size; i++) {
            p->data[i] = p->data[i + 1];
        }
        p->size--;

    }
}

// Thomas and Zach find, remove
void BPlusTree::find(int d) {
    if (!root){
        return;
    } else {
        //CODE
    }
}

void BPlusTree::remove(int d) {
    if(!root){
        return;
    } else {
        // CODE
    }
}

void BPlusTree::mergeRight(Node*& curr, Node*& LeftChild, Node*& RightChild){
    //allways merge with curr being the parent
   //LeftChild->size++;
    
    LeftChild->data[1] = curr->data[0];
    
    //LeftChild->children[2] = RightChild->children[0];
    int i = 0;
    
    if(LeftChild->children[1] == nullptr){
        while(i < curr->max-1){
            if(RightChild->children[i] != nullptr){
                LeftChild->size++;
                LeftChild->children[i+1] = RightChild->children[i];
                i++;
            }
        }
    }else{
        while(i < curr->max-2){
            if(RightChild->children[i] != nullptr){
                LeftChild->size++;
                LeftChild->children[i+2] = RightChild->children[i];
                i++;
            }
        }
    }
    
    delete RightChild;
    
   // curr->data[i] =
    
}


void BPlusTree::shiftR(Node*& curr, Node*& Neighbor){
    //only use if your node is too small
    int i = Neighbor->size;
    curr->data[0] = Neighbor->data[i-1];
    Neighbor->size--;
    
}
void BPlusTree::shiftL(Node*& curr, Node*& Neighbor){
    int i = Neighbor->size;
    curr->data[0] = Neighbor->data[0];
    for(int j = 0; j < i-1; j++){
        Neighbor->data[j] = Neighbor->data[j+1];
    }
    Neighbor->size--;
}
/*
search

if node not leaf
for i<size
search(child(i))
if this is equal to key it is a key value delte and replace appropriately
}
if(child->data[0])
 */
