#pragma once
#include <iostream>
#include <string>
#include <map>
using namespace std;

struct SplayNode {
    float score; //how well does this meteorite match, default 0
    string name;
    int id;
    string recClass;
    float mass; //in g
    int year;
    float recLat; //latitude
    float recLon; //longitude

    SplayNode* left;
    SplayNode* right;
    SplayNode* parent;
    SplayNode(float s, string n, int i, string c, float m, int y, float lat, float lon)
        : score(s), name(n), id(i), recClass(c), mass(m), year(y), recLat(lat), recLon(lon),
          left(nullptr), right(nullptr), parent(nullptr) {}

    //assign a new score to the SplayNode
    void SplayNodeScore(float s){
        score = s;
    }

    //print out the information for this SplayNode
    void printSplayNode(){
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
    //return the information of the SplayNode as a dictionary
    map<string, string> getSplayNodeInfo() {
        map<string, string> SplayNodeInfo;
        SplayNodeInfo["Score"] = to_string(score);
        SplayNodeInfo["Name"] = name;
        SplayNodeInfo["ID"] = to_string(id);
        SplayNodeInfo["Class"] = recClass;
        SplayNodeInfo["Mass"] = to_string(mass) + "g";
        SplayNodeInfo["Year"] = to_string(year);
        SplayNodeInfo["Latitude"] = to_string(recLat);
        SplayNodeInfo["Longitude"] = to_string(recLon);
        return SplayNodeInfo;
    }
};

class SplayTree {
private:
    SplayNode* root;

    SplayNode* splay(SplayNode* SplayNode);
    SplayNode* findMax(SplayNode* SplayNode);
    void rotateLeft(SplayNode* SplayNode);
    void rotateRight(SplayNode* SplayNode);

public:
    SplayTree() : root(nullptr) {}
    ~SplayTree();

    void insert(SplayNode* SplayNode);
    SplayNode* search(int id);
    void remove(int id);
    void printInOrder();
    void printInOrder(SplayNode* SplayNode); //helper function for printing in-order traversal
};

SplayTree::~SplayTree() {
    while (root) {
        remove(root->id);
    }
}

//splays the given SplayNode to the root
SplayNode* SplayTree::splay(SplayNode* SplayNode) {
    while (SplayNode->parent) {
        if (!SplayNode->parent->parent) {
            if (SplayNode->parent->left == SplayNode)
                rotateRight(SplayNode->parent);
            else
                rotateLeft(SplayNode->parent);
        } else if (SplayNode->parent->left == SplayNode && SplayNode->parent->parent->left == SplayNode->parent) {
            rotateRight(SplayNode->parent->parent);
            rotateRight(SplayNode->parent);
        } else if (SplayNode->parent->right == SplayNode && SplayNode->parent->parent->right == SplayNode->parent) {
            rotateLeft(SplayNode->parent->parent);
            rotateLeft(SplayNode->parent);
        } else if (SplayNode->parent->left == SplayNode && SplayNode->parent->parent->right == SplayNode->parent) {
            rotateRight(SplayNode->parent);
            rotateLeft(SplayNode->parent);
        } else {
            rotateLeft(SplayNode->parent);
            rotateRight(SplayNode->parent);
        }
    }
    return SplayNode;
}

//finds the SplayNode with maximum key in the subtree rooted at the given SplayNode
SplayNode* SplayTree::findMax(SplayNode* SplayNode) {
    if (!SplayNode)
        return nullptr;
    while (SplayNode->right)
        SplayNode = SplayNode->right;
    return SplayNode;
}

//rotates the given SplayNode to the left
void SplayTree::rotateLeft(SplayNode* current) {
    if (!current || !current->right) {
        return;
    }
    SplayNode* pivot = current->right; // Declare the 'pivot' variable
    current->right = pivot->left;
    if (pivot->left) {
        pivot->left->parent = current;
    }
    pivot->parent = current->parent;
    if (!current->parent) {
        root = pivot;
    } else if (current == current->parent->left) {
        current->parent->left = pivot;
    } else {
        current->parent->right = pivot;
    }
    pivot->left = current;
    current->parent = pivot;
}

//rotates the given SplayNode to the right
void SplayTree::rotateRight(SplayNode* current) {
    if (!current || !current->left)
        return;
    SplayNode* pivot = current->left;
    current->left = pivot->right;
    if (pivot->right)
        pivot->right->parent = current;
    pivot->parent = current->parent;
    if (!current->parent)
        root = pivot;
    else if (current == current->parent->left)
        current->parent->left = pivot;
    else
        current->parent->right = pivot;
    pivot->right = current;
    current->parent = pivot;
}

//inserts a SplayNode into the splay tree
void SplayTree::insert(SplayNode* current) {
    if (!root) {
        root = current;
        return;
    }
    SplayNode* current = root;
    SplayNode* parent = nullptr;
    while (current) {
        parent = current;
        if (current->id < current->id)
            current = current->left;
        else
            current = current->right;
    }
    current->parent = parent;
    if (current->id < parent->id)
        parent->left = current;
    else
        parent->right = current;
    root = splay(current);
}

//searches for a SplayNode with the given key and splays it to the root if found
SplayNode* SplayTree::search(int id) {
    SplayNode* current = root;
    while (current) {
        if (current->id == id) {
            root = splay(current);
            return current;
        } else if (id < current->id)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}



