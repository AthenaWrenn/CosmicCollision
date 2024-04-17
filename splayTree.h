#pragma once
#include <iostream>
#include <string>
#include <map>
using namespace std;

struct SplayNode {
    float score;
    string name;
    int id;
    string recClass;
    float mass;
    int year;
    float recLat;
    float recLon;

    SplayNode* left;
    SplayNode* right;
    SplayNode* parent;
    SplayNode(float s, string n, int i, string c, float m, int y, float lat, float lon)
        : score(s), name(n), id(i), recClass(c), mass(m), year(y), recLat(lat), recLon(lon),
          left(nullptr), right(nullptr), parent(nullptr) {}

    //assign a new score to the Splaynode
    void SplaynodeScore(float s){
        score = s;
    }

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
};

class SplayTree {
private:
    SplayNode* root;

    SplayNode* splay(SplayNode* Splaynode);
    SplayNode* findMax(SplayNode* Splaynode);
    void rotateLeft(SplayNode* Splaynode);
    void rotateRight(SplayNode* Splaynode);

public:
    SplayTree() : root(nullptr) {}
    ~SplayTree();

    void insert(SplayNode* Splaynode);
    SplayNode* search(int id);
    void remove(int id);
    void printInOrder();
    void printInOrder(SplayNode* Splaynode); // Helper function for printing in-order traversal
};

SplayTree::~SplayTree() {
    // Implement destructor to delete Splaynodes
}

// Splays the given Splaynode to the root
SplayNode* SplayTree::splay(SplayNode* Splaynode) {
    while (Splaynode->parent) {
        if (!Splaynode->parent->parent) {
            if (Splaynode->parent->left == Splaynode)
                rotateRight(Splaynode->parent);
            else
                rotateLeft(Splaynode->parent);
        } else if (Splaynode->parent->left == Splaynode && Splaynode->parent->parent->left == Splaynode->parent) {
            rotateRight(Splaynode->parent->parent);
            rotateRight(Splaynode->parent);
        } else if (Splaynode->parent->right == Splaynode && Splaynode->parent->parent->right == Splaynode->parent) {
            rotateLeft(Splaynode->parent->parent);
            rotateLeft(Splaynode->parent);
        } else if (Splaynode->parent->left == Splaynode && Splaynode->parent->parent->right == Splaynode->parent) {
            rotateRight(Splaynode->parent);
            rotateLeft(Splaynode->parent);
        } else {
            rotateLeft(Splaynode->parent);
            rotateRight(Splaynode->parent);
        }
    }
    return Splaynode;
}

// Finds the Splaynode with maximum key in the subtree rooted at the given Splaynode
SplayNode* SplayTree::findMax(SplayNode* Splaynode) {
    if (!Splaynode)
        return nullptr;
    while (Splaynode->right)
        Splaynode = Splaynode->right;
    return Splaynode;
}

// Rotates the given Splaynode to the left
void SplayTree::rotateLeft(SplayNode* Splaynode) {
    if (!Splaynode || !Splaynode->right)
        return;
    SplayNode* pivot = Splaynode->right;
    Splaynode->right = pivot->left;
    if (pivot->left)
        pivot->left->parent = Splaynode;
    pivot->parent = Splaynode->parent;
    if (!Splaynode->parent)
        root = pivot;
    else if (Splaynode == Splaynode->parent->left)
        Splaynode->parent->left = pivot;
    else
        Splaynode->parent->right = pivot;
    pivot->left = Splaynode;
    Splaynode->parent = pivot;
}

// Rotates the given Splaynode to the right
void SplayTree::rotateRight(SplayNode* Splaynode) {
    if (!Splaynode || !Splaynode->left)
        return;
    SplayNode* pivot = Splaynode->left;
    Splaynode->left = pivot->right;
    if (pivot->right)
        pivot->right->parent = Splaynode;
    pivot->parent = Splaynode->parent;
    if (!Splaynode->parent)
        root = pivot;
    else if (Splaynode == Splaynode->parent->left)
        Splaynode->parent->left = pivot;
    else
        Splaynode->parent->right = pivot;
    pivot->right = Splaynode;
    Splaynode->parent = pivot;
}

// Inserts a Splaynode into the splay tree
void SplayTree::insert(SplayNode* Splaynode) {
    if (!root) {
        root = Splaynode;
        return;
    }
    SplayNode* current = root;
    SplayNode* parent = nullptr;
    while (current) {
        parent = current;
        if (Splaynode->id < current->id)
            current = current->left;
        else
            current = current->right;
    }
    Splaynode->parent = parent;
    if (Splaynode->id < parent->id)
        parent->left = Splaynode;
    else
        parent->right = Splaynode;
    root = splay(Splaynode);
}

// Searches for a Splaynode with the given key and splays it to the root if found
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

// Removes a Splaynode with the given key from the splay tree
void SplayTree::remove(int id) {
    SplayNode* Splaynode = search(id);
    if (!Splaynode)
        return;
    if (!Splaynode->left) {
        root = Splaynode->right;
    } else if (!Splaynode->right) {
        root = Splaynode->left;
    } else {
        SplayNode* maxLeft = findMax(Splaynode->left);
        if (maxLeft->parent != Splaynode) {
            maxLeft->parent->right = maxLeft->left;
            if (maxLeft->left)
                maxLeft->left->parent = maxLeft->parent;
            maxLeft->left = Splaynode->left;
            Splaynode->left->parent = maxLeft;
        }
        maxLeft->right = Splaynode->right;
        if (Splaynode->right)
            Splaynode->right->parent = maxLeft;
        root = maxLeft;
    }
    delete Splaynode;
}

// Prints the elements of the splay tree in-order
void SplayTree::printInOrder() {
    printInOrder(root);
}

// Helper function to print the elements of the subtree rooted at the given Splaynode in-order
void SplayTree::printInOrder(SplayNode* Splaynode) {
    if (Splaynode) {
        printInOrder(Splaynode->left);
        cout << "Score: " << Splaynode->score << ", Name: " << Splaynode->name << ", ID: " << Splaynode->id << endl;
        printInOrder(Splaynode->right);
    }
}



