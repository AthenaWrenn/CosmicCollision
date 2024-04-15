
#include <string> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "binaryMaxHeap.h"

using namespace std;
//Team Name: Cosmic Collision
//Team Members:  Thomas Chavarria, Joseph Molina, and Athena Wrenn
//Project Title: Meteorite Landing Finder

//reference: geeksforgeeks.org/csv-file-management-using-c
//reference: gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp

//read the csv file into the binary heap
void importFile(binaryMaxHeap &bH){
 
    string fileName = "Meteorite_Landings.csv";
    ifstream myFile(fileName);

    if(!myFile.is_open()){
        throw runtime_error("Could not open csv file");
    }

    //the first line is headers
    string line;
    if(myFile.good()){
        getline(myFile, line);
    }

    //the rest of the lines are each nodes
    while(getline(myFile, line)){
        stringstream s(line);
        string word;
        vector<string> row;

        while (getline(s, word, ',')) { 
            row.push_back(word);
        } 

        //remove rows of incomplete data
        if(row[0].empty() || row[1].empty() || row[3].empty() || row[4].empty() || row[6].empty() || row[7].empty() || row[8].empty()){
            cout << "Skipping incomplete tuple..." << endl;
        } else{
            //file is setup: name, id, nametype, recclass, mass (g), fall, year, reclat, reclong, GeoLocation
            cout << row[0] << endl;
            string name = row[0];
            int id = stoi(row[1]);
            string recClass = row[3];
            float mass = stof(row[4]);
            int year = stoi(row[6]);
            float recLat = stof(row[7]);
            float recLon = stof(row[8]);

            Node currentNode = Node(name, id, recClass, mass, year, recLat, recLon);
            bH.insert(currentNode);
        }

        
    }

}

int main()
{
    //import the meteorite data into the 2 data structures
    int defaultHeapSize = 45717;
    binaryMaxHeap binaryHeap(defaultHeapSize);
    importFile(binaryHeap);

    // Prints hello world
    cout << "Hello World";
 
    return 0;
}