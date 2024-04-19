#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Partition function for Quick Sort
int partition(vector<Node>& arr, int low, int high) {
    float pivot = arr[high].getScore();
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].getScore() >= pivot) { // Change comparison to >= for descending order
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort function
void quickSort(vector<Node>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to sort the vector of Nodes based on their scores in descending order
void sortNodesByScore(vector<Node>& nodes) {
    quickSort(nodes, 0, nodes.size() - 1);
}
