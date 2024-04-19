#pragma once
#include <string> 
#include <iostream>
#include <cmath>
using namespace std;

//reference: geeksforgeeks.org/binary-heap
//reference: www.cs.usfca.edu/~galles/visualization/Heap

struct Node{
    float score; //how wll does this meteorite match, default 0
    string name;
    int id;
    string recClass;
    float mass; //in g
    int year;
    float recLat; //latitude
    float recLon; //longitude
    
public:
    Node() : name(""), id(0), recClass(""), mass(0), year(0), recLat(0), recLon(0){}
    Node(string n, int id, string c, float g, int y, float lat, float lon) : name(n), id(id), recClass(c), mass(g), year(y), recLat(lat), recLon(lon){}

    //assign a new score to the node
    void nodeScore(float s){
        score = s;
    }

    float getScore(){
        return score;
    }

    //print out the information for this node
    void printNode(){
        cout << "Score: " << score;
        cout << " Name: " << name;
        cout << " ID: " << id;
        cout << " Class: " << recClass;
        cout << " Mass: " << mass << "g";
        cout << " Year: " << year;
        cout << " Latitude: " << recLat;
        cout << " Longitude: " << recLon;
        cout << endl;
    }

};

class binaryMaxHeap{
    private:
        Node *hArray; //heap array
        int capacity;
        int currentSize;

    public:
        //constructor
        binaryMaxHeap(int capacity = 45717);

        //destructor
        ~binaryMaxHeap();

        //given position p, get parent index
        int getParentIndex(int p);

        //swap two nodes
        void swapNodes(Node *a, Node *b);

        // Insert a new node
        void insert(Node k);

        //heapify subtree with root r
        void heapify(int r);

        //get max from top of heap
        Node extractMax();

        //access heapsize
        int size();


};

//constructor
binaryMaxHeap::binaryMaxHeap(int c){
    capacity = c;
    currentSize = 0;
    hArray = new Node[c];
}

//destructor
binaryMaxHeap::~binaryMaxHeap() {
    delete[] hArray;
}

//given index i, get parent index
int binaryMaxHeap::getParentIndex(int p){
    int parentIndex = (p-1)/2;
    return parentIndex;
}

//swap two nodes
void binaryMaxHeap::swapNodes(Node *a, Node *b){
    Node temp = *a; 
    *a = *b; 
    *b = temp; 
}

//insert a new node
void binaryMaxHeap::insert(Node k){
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
void binaryMaxHeap::heapify(int r){

    int leftChild = (2*r) + 1; 
    int rightChild = (2*r) + 2; 
    int largest = r; 

    if ((rightChild < currentSize) && (hArray[rightChild].score > hArray[largest].score)){
        //the right child is the largest 
        largest = rightChild; 
    }
        
    if ((r < currentSize) && (hArray[leftChild].score > hArray[largest].score)){
        //the left child is the largest 
        largest = leftChild; 
    } 
       
    if (largest  != r) { 
        swapNodes(&hArray[r], &hArray[largest]); 
        heapify(largest); //recurse
    } 
}

//get max from top of heap
Node binaryMaxHeap::extractMax(){
    //check edge cases first
    if (currentSize <= 0){
        cout << "\nError: Heap Empty\n";
        Node emptyNode;
        return emptyNode; 
    } else if (currentSize == 1) { 
        currentSize--; 
        return hArray[0]; 
    } 

    //usual case
    Node max = hArray[0];
    hArray[0] = hArray[currentSize-1]; 
    currentSize--; 
    heapify(0);
    return max;
}

//access heapsize
int binaryMaxHeap::size(){
    return currentSize;
}
