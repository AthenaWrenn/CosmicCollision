#pragma once
#include <string> 
#include <iostream>
#include <cmath>
#include <map>
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

    map<string, string> getNodeInfo() {
        map<string, string> nodeInfo;
        nodeInfo["Score"] = to_string(score);
        nodeInfo["Name"] = name;
        nodeInfo["ID"] = to_string(id);
        nodeInfo["Class"] = recClass;
        nodeInfo["Mass"] = to_string(mass) + "g";
        nodeInfo["Year"] = to_string(year);
        nodeInfo["Latitude"] = to_string(recLat);
        nodeInfo["Longitude"] = to_string(recLon);
        return nodeInfo;
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