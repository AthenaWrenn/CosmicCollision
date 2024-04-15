#pragma once
#include <string> 
#include <iostream>
using namespace std;

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
};

class binaryMaxHeap{
    private:
        Node *hArray; //heap array
        int capacity;
        int currentSize;

    public:
        //constructor
        binaryMaxHeap(int capacity);

        //destructor
        ~binaryMaxHeap();

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