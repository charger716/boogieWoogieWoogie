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
// do we just want to find the value at the leaf or both the parent and the leaf (if it's a parent?)
// is find really just a void or do we want to return a where the data is stored (if it is at all)

void BPlusTree::find(int d) {
    if (!root){
        cout << "No such value!" << endl;
        return;
    } else {
        BPlusTree test;
        // how to find the size of children (both x and y component)?
        for(int i = 0; i < test.root->max; i++){ // go through x component of children (this is incorrect)
            for(int j = 0; j < test.root->max; j++){    // go through y component of children (this is incorrect)
                for(int k = 0; k < test.root->(max+2); k++){
                    if(test.root->data[k] == d && !test.root->data[k]->isKey){  // how to check for if it is key
                        cout << "Element is within the B+ tree" << endl;
                        return;
                    }
                }
            }
        }

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