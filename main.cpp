
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
    int countSkipped = 0;
    int countProcessed = 0;
    while(getline(myFile, line)){
        stringstream s(line);
        string word;
        vector<string> row;

        while (getline(s, word, ',')) { 
            //if the , is in "" it isn't a new column
            if(word[0] == '"'){
                string secondHalf;
                getline(s, secondHalf, ',');
                word = word + secondHalf;
            }

            row.push_back(word);
        } 

        //remove rows of incomplete data
        if(row[0].empty() || row[1].empty() || row[3].empty() || row[4].empty() || row[6].empty() || row[7].empty() || row[8].empty()){
            countSkipped++;
            //cout << "Skipping incomplete tuple..." <<  countSkipped << endl;
        } else{
            //file is setup: name, id, nametype, recclass, mass (g), fall, year, reclat, reclong, GeoLocation
            string name = row[0];
            int id = stoi(row[1]);
            string recClass = row[3];
            float mass = stof(row[4]);
            int year = stoi(row[6]);
            float recLat = stof(row[7]);
            float recLon = stof(row[8]);

            Node currentNode = Node(name, id, recClass, mass, year, recLat, recLon);
            bH.insert(currentNode);
            countProcessed++;
        }  
    }

    cout << "Skipped " <<  countSkipped << " invalid tuples." << endl;
    cout << "Processed " <<  countProcessed << " valid tuples." << endl;

}

int main()
{
    //import the meteorite data into the 2 data structures
    int defaultHeapSize = 45717;
    binaryMaxHeap binaryHeap(defaultHeapSize);
    importFile(binaryHeap);
    cout << "Size of the binary heap: " << binaryHeap.size() << endl;

    //testing geting the max off the top
    Node max = binaryHeap.extractMax();
    max.printNode();
    cout << "Size of the binary heap: " << binaryHeap.size() << endl;

    return 0;
}

// CURRENT RETURN STRUCTURE!!
// Map with keys as shown below and strings representing the values

// map<string, string> getNodeInfo() {
//     map<string, string> nodeInfo;
//     nodeInfo["Score"] = to_string(score);
//     nodeInfo["Name"] = name;
//     nodeInfo["ID"] = to_string(id);
//     nodeInfo["Class"] = recClass;
//     nodeInfo["Mass"] = to_string(mass) + "g";
//     nodeInfo["Year"] = to_string(year);
//     nodeInfo["Latitude"] = to_string(recLat);
//     nodeInfo["Longitude"] = to_string(recLon);
//     return nodeInfo;
// }