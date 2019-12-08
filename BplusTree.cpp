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

        // copy all values smaller than middle value to left
        // child.
        for(int i = 0; i < ndx; i++){
            p->children[j]->data[i] = n->data[i];
            p->children[j]->size++;
        }

        // shift values of right child
        for(int i = 0; i < n->size; i++){
            n->data[i] = n->data[i+1];
        }
        n->size--;

        // attach leaf nodes
        p->children[j]->nextLeaf = n;

        // attach child
        p->children[j+1] = n;

        //update root
        root = p;

    } else {

        // insert into parent
        if (p->size < m) {
            this->InsertionSort(p->data, p->size, mid);
            p->size++;
            // split parent if full
            if(p->size == m){
                split(p,root);
            }
        }

        // after recursion move pointers
        for(int i = 0; i < p->size; i++){

        }

        for (int i = 0; i < p->size; i++) {
            this->InsertionSort(n->children[j]->data, n->children[j]->size, p->data[i]);
            n->children[j]->size++;
        }

        j++;

        for (int i = 0; i < p->size; i++) {
            p->data[i] = p->data[i + 1];
        }
        p->size--;

    }
}

// Tomas and Zach find, remove
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

void BPlusTree::remove(int d) {
    if(!root){
        return;
    } else {
        // CODE
    }
}