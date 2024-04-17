#include <iostream>
#include <string>
using namespace std;

struct Node {
    float score;
    string name;
    int id;
    string recClass;
    float mass;
    int year;
    float recLat;
    float recLon;

    Node* left;
    Node* right;
    Node* parent;
    Node(float s, string n, int i, string c, float m, int y, float lat, float lon)
        : score(s), name(n), id(i), recClass(c), mass(m), year(y), recLat(lat), recLon(lon),
          left(nullptr), right(nullptr), parent(nullptr) {}

    //assign a new score to the node
    void nodeScore(float s){
        score = s;
    }

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

class SplayTree {
private:
    Node* root;

    Node* splay(Node* node);
    Node* findMax(Node* node);
    void rotateLeft(Node* node);
    void rotateRight(Node* node);

public:
    SplayTree() : root(nullptr) {}
    ~SplayTree();

    void insert(Node* node);
    Node* search(int id);
    void remove(int id);
    void printInOrder();
    void printInOrder(Node* node); // Helper function for printing in-order traversal
};

SplayTree::~SplayTree() {
    // Implement destructor to delete nodes
}

// Splays the given node to the root
Node* SplayTree::splay(Node* node) {
    while (node->parent) {
        if (!node->parent->parent) {
            if (node->parent->left == node)
                rotateRight(node->parent);
            else
                rotateLeft(node->parent);
        } else if (node->parent->left == node && node->parent->parent->left == node->parent) {
            rotateRight(node->parent->parent);
            rotateRight(node->parent);
        } else if (node->parent->right == node && node->parent->parent->right == node->parent) {
            rotateLeft(node->parent->parent);
            rotateLeft(node->parent);
        } else if (node->parent->left == node && node->parent->parent->right == node->parent) {
            rotateRight(node->parent);
            rotateLeft(node->parent);
        } else {
            rotateLeft(node->parent);
            rotateRight(node->parent);
        }
    }
    return node;
}

// Finds the node with maximum key in the subtree rooted at the given node
Node* SplayTree::findMax(Node* node) {
    if (!node)
        return nullptr;
    while (node->right)
        node = node->right;
    return node;
}

// Rotates the given node to the left
void SplayTree::rotateLeft(Node* node) {
    if (!node || !node->right)
        return;
    Node* pivot = node->right;
    node->right = pivot->left;
    if (pivot->left)
        pivot->left->parent = node;
    pivot->parent = node->parent;
    if (!node->parent)
        root = pivot;
    else if (node == node->parent->left)
        node->parent->left = pivot;
    else
        node->parent->right = pivot;
    pivot->left = node;
    node->parent = pivot;
}

// Rotates the given node to the right
void SplayTree::rotateRight(Node* node) {
    if (!node || !node->left)
        return;
    Node* pivot = node->left;
    node->left = pivot->right;
    if (pivot->right)
        pivot->right->parent = node;
    pivot->parent = node->parent;
    if (!node->parent)
        root = pivot;
    else if (node == node->parent->left)
        node->parent->left = pivot;
    else
        node->parent->right = pivot;
    pivot->right = node;
    node->parent = pivot;
}

// Inserts a node into the splay tree
void SplayTree::insert(Node* node) {
    if (!root) {
        root = node;
        return;
    }
    Node* current = root;
    Node* parent = nullptr;
    while (current) {
        parent = current;
        if (node->id < current->id)
            current = current->left;
        else
            current = current->right;
    }
    node->parent = parent;
    if (node->id < parent->id)
        parent->left = node;
    else
        parent->right = node;
    root = splay(node);
}

// Searches for a node with the given key and splays it to the root if found
Node* SplayTree::search(int id) {
    Node* current = root;
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

// Removes a node with the given key from the splay tree
void SplayTree::remove(int id) {
    Node* node = search(id);
    if (!node)
        return;
    if (!node->left) {
        root = node->right;
    } else if (!node->right) {
        root = node->left;
    } else {
        Node* maxLeft = findMax(node->left);
        if (maxLeft->parent != node) {
            maxLeft->parent->right = maxLeft->left;
            if (maxLeft->left)
                maxLeft->left->parent = maxLeft->parent;
            maxLeft->left = node->left;
            node->left->parent = maxLeft;
        }
        maxLeft->right = node->right;
        if (node->right)
            node->right->parent = maxLeft;
        root = maxLeft;
    }
    delete node;
}

// Prints the elements of the splay tree in-order
void SplayTree::printInOrder() {
    printInOrder(root);
}

// Helper function to print the elements of the subtree rooted at the given node in-order
void SplayTree::printInOrder(Node* node) {
    if (node) {
        printInOrder(node->left);
        cout << "Score: " << node->score << ", Name: " << node->name << ", ID: " << node->id << endl;
        printInOrder(node->right);
    }
}


