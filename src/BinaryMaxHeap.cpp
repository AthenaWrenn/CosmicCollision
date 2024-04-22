#include "binaryMaxHeap.h"

//constructor
binaryMaxHeap::binaryMaxHeap(int c) {
    capacity = c;
    currentSize = 0;
    hArray = new Node[c];
}

//destructor
binaryMaxHeap::~binaryMaxHeap() {
    delete[] hArray;
}

//given index i, get parent index
int binaryMaxHeap::getParentIndex(int p) {
    int parentIndex = (p - 1) / 2;
    return parentIndex;
}

//swap two nodes
void binaryMaxHeap::swapNodes(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

//insert a new node
void binaryMaxHeap::insert(Node k) {
    //check that there is room
    if (currentSize == capacity) {
        cout << "\nError: Heap Full\n";
        return;
    }

    //tack the new node on the end
    int i = currentSize;
    currentSize++;
    hArray[i] = k;

    //the parent should be the node with the bigger score
    while ((i > 0) && (hArray[getParentIndex(i)].score < hArray[i].score)) {
        swapNodes(&hArray[i], &hArray[getParentIndex(i)]);
        i = getParentIndex(i);
    }
}

//heapify subtree with root r
void binaryMaxHeap::heapify(int r) {

    int leftChild = (2 * r) + 1;
    int rightChild = (2 * r) + 2;
    int largest = r;

    // Check if left child is larger than root
    if (leftChild < currentSize && hArray[leftChild].score > hArray[largest].score) {
        largest = leftChild;
    }

    // Check if right child is larger than largest so far
    if (rightChild < currentSize && hArray[rightChild].score > hArray[largest].score) {
        largest = rightChild;
    }

    // If largest is not root
    if (largest != r) {
        swapNodes(&hArray[r], &hArray[largest]);

        // Recursively heapify the affected sub-tree
        heapify(largest);
    }
}

//get max from top of heap
Node binaryMaxHeap::extractMax() {

    //check edge cases first
    if (currentSize <= 0) {

        cout << "\nError: Heap Empty\n";
        Node emptyNode;
        return emptyNode;
    }
    else if (currentSize == 1) {

        currentSize--;
        return hArray[0];
    }

    //usual case

    Node max = hArray[0];
    hArray[0] = hArray[currentSize - 1];
    currentSize--;
    heapify(0);

    return max;
}

//access heapsize
int binaryMaxHeap::size() {
    return currentSize;
}
