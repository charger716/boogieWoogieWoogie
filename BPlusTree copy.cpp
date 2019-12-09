//
//  BPlusTree.cpp
//  B+Tree
//
//  Created by Zach Coon on 12/7/19.
//  Copyright © 2019 Zach Coon. All rights reserved.
//

#include "BplusTree.h"

void BPlusTree::InsertionSort(int data[], int size, int d){
    data[size++] = d;
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
        root->data[root->size++] = d;
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
    if (p == nullptr || p == n) {
        // create new parent node with middle value as key
        p = new Node(m);
        p->data[p->size++] = mid;
        p->isKey = true;
        p->children[j] = new Node(m);

        if (n->isKey){

        } else {
            // copy all values smaller than middle value to left
            // child.
            for (int i = 0; i < ndx; i++) {
                p->children[j]->data[i] = n->data[i];
                p->children[j]->size++;
            }

            // shift values of right child
            for (int i = 0; i < n->size; i++) {
                n->data[i] = n->data[i + 1];
            }
            n->size--;

            // attach leaf nodes
            p->children[j]->nextLeaf = n;

            // attach child
            p->children[j + 1] = n;

            //update root
            root = p;
        }
    } else {

        bool lT = false;
        // insert into parent
        if (p->size < m) {
            if(mid < p->data[0])
            {
                lT = true;
            }
            this->InsertionSort(p->data, p->size, mid);
            p->size++;
            // split parent if full
            if(p->size == m){
                split(p,root);
            }
        }

        if(lT) {
            // shift pointers
            for (int i = m-1; i > 0; i--) {
                p->children[i] = p->children[i-1];
            }

            p->children[0] = new Node(m);
            p->children[0]->data[p->children[0]->size++] = p->children[1]->data[0];

            for(int i = 0; i < n->size; i++) {
                n->data[i] = n->data[i+1];
                p->children[0]->nextLeaf = p->children[1];
            }
            n->size--;
        } else{
            int k = 0;
            // find next available child
            while(p->children[j]){
                    k++;
            }

            p->children[k] = new Node(m);

            // copy values over to next node
            for (int i = ndx; i < n->size; i++ ) {
                p->children[k]->data[p->children[k]->size++] = n->data[i];
            }
            n->size -= p->children[k]->size;

            // attach leaf nodes
            p->children[k-1]->nextLeaf = p->children[k];

        }

    }
}


void BPlusTree::remove(int d) {
    if (!root){
        cout << "No such value!" << endl;
        return;
    } else {
        Node* cur = root;
        Node* par = nullptr;
        int size_of_child;
        bool flag = false;
        
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
        size_of_child = par->size + 1;

        // traverse through all the leaf nodes
        for(int i = 0; i < size_of_child; i++){
            cur = par->children[i];
            for(int j = 0; j < cur->size; j++){
                cout << cur->data[j] << " ";
                if(cur->data[j] == d){
                    
                    flag = true;
                    break;
                }
            }
            cout << endl;
            if(flag){
                for(int k = j; k < cur->size-1; k++){
                    cur->data[k] = cur->data[k+1];
                }
                cur->size--;
                
                //If the cur node is the root?
                
                if(cur->size < 1){
                    if(par->children[i+1]){
                        if(par->children[i+1]->size > 1){
                            cur->data[0] = par->children[i+1]->data[0];
                            cur->size++;
                            par->children[i+1]->data[0] = par->children[i+1]->data[1];
                            par->children[i+1]->size--;
                            par->data[0] = par->children[i+1]->data[0];
                        }
                        
                    }else if(par->children[i-1]){
                        if(par->children[i-1]->size > 1){
                            cur->data[0] = par->children[i-1]->data[1];
                            cur->size++;
                            par->children[i+1]->size--;
                            par->data[0] = cur->data[0];
                    }
                }
                }else{
                    if(i > 0){
                        par->data[0] = par->children[i]->data[0];
                    }
                }
        
                      
                
                
                cout << "value found!" << endl;
                break;
            }
        }

        if(!flag){
            cout << "value not found :^(" << endl;
        }

        //CODE
    }
}

void BPlusTree::Balance(Node*& top){
    Node* cur = top;
    Node* par = nullptr;
   // int childsize = 0;
    int j = 0;
    while (cur->isKey){
              for (int i = 0; i < cur->size; i++){
                  if(cur->size != cur->max){
                      if(cur->children[cur->size + 1] != NULL){//This will make sure that the child is there when it shouldn't be
                          //Handle for when size is now 0
                          if(i == 0){
                              merge(cur, cur->children[0], cur->children[1]);
                          }else{
                          //handle for when size is now 1
                             // merge(cur, cur->children, )
                          }
                        
                      }
                    }
              }
            j++;
            par = cur;
            cur = cur->children[j];
          }
}

void BPlusTree::merge(Node*& curr, Node*& LeftChild, Node*& RightChild){
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
    cout << "Shifted Right" << endl;
    
}
void BPlusTree::shiftL(Node*& curr, Node*& Neighbor){
    int i = Neighbor->size;
    curr->data[0] = Neighbor->data[0];
    for(int j = 0; j < i-1; j++){
        Neighbor->data[j] = Neighbor->data[j+1];
    }
    Neighbor->size--;
    cout << "Shifted Right" << endl;
}

void BPlusTree::find(int d) {
    if (!root){
        cout << "No such value!" << endl;
        return;
    } else {
        Node* cur = root;
        Node* par = nullptr;
        int size_of_child;
        bool flag = false;

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
        size_of_child = par->size + 1;

        // traverse through all the leaf nodes
        for(int i = 0; i < size_of_child; i++){
            cur = par->children[i];
            for(int j = 0; j < cur->size; j++){
                cout << cur->data[j] << " ";
                if(cur->data[j] == d){
                    flag = true;
                }
            }
            cout << endl;
            if(flag){
                cout << "value found!" << endl;
                break;
            }
        }

        if(!flag){
            cout << "value not found :^(" << endl;
        }

        //CODE
    }
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
