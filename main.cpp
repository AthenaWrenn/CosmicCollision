
#include <string> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

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

//calculate the accuracy of each specification; how close a match?
vector<float> findAccuracies(int idealYear, float idealLat, float idealLon, float idealSize, string idealClass, Node &max){
    vector<float> matchVector;

    //find how close the specified year is (between 0 and 1.0)
    //100 years off scores a 0
    float yearAccuracy = 1.0 - (abs(max.year - idealYear) / 100.0);
    //cout << yearAccuracy << endl;
    matchVector.push_back(yearAccuracy);

    //find how close the specified location is (between 0 and 1.0)
    //100 miles off scores a 0
    float locAccuracy;
    float latDiff = max.recLat - idealLat;
    float lonDiff = max.recLon - idealLon;
    float locDiff = sqrt((latDiff * latDiff) + (lonDiff * lonDiff));
    locAccuracy = 1.0 - (locDiff / 100.0);
    //cout << locAccuracy  << endl;
    matchVector.push_back(locAccuracy);

    //find how close the specified size is (between 0 and 1.0)
    //100g off scores a 0
    float sizeAccuracy = 1.0 - (abs(max.mass - idealSize) / 100.0);
    //cout << sizeAccuracy << endl;
    matchVector.push_back(sizeAccuracy);

    //Does the specified class match?
    float classAccuracy;
    if(max.recClass == idealClass){
        classAccuracy = 1.0;
    } else{
        classAccuracy = 0.0;
    }
    //cout << classAccuracy << endl;
    matchVector.push_back(classAccuracy);

    return matchVector;
}



int main()
{
    //import the meteorite data into the 2 data structures
    int defaultHeapSize = 45717;
    binaryMaxHeap binaryHeap(defaultHeapSize);
    importFile(binaryHeap);
    cout << "Size of the binary heap: " << binaryHeap.size() << endl;

    //take in meteorite specifications
    int idealYear;
    cout << "Specify year: ";
    cin >> idealYear;

    float idealLat;
    cout << "Specify latitude: ";
    cin >> idealLat;

    float idealLon;
    cout << "Specify longitude: ";
    cin >> idealLon;

    float idealSize;
    cout << "Specify size: ";
    cin >> idealSize;

    string idealClass;
    cout << "Specify class: ";
    cin >> idealClass;

    //take in priority
    int yearRank;
    cout << "Rank importance of year(1-4): ";
    cin >> yearRank;

    int locRank;
    cout << "Rank importance of location(1-4): ";
    cin >> locRank;

    int sizeRank;
    cout << "Rank importance of size(1-4): ";
    cin >> sizeRank;

    int clRank;
    cout << "Rank importance of class(1-4): ";
    cin >> clRank;

    //testing geting the max off the top
    Node max = binaryHeap.extractMax();
    max.printNode();
    cout << "Size of the binary heap: " << binaryHeap.size() << endl;


    //score a crash
    vector<float> accuracies; // 0: year, 1: location, 2: size, 3: class
    accuracies = findAccuracies(idealYear, idealLat, idealLon, idealSize, idealClass, max);

    float currentScore = 0;
    currentScore = (yearRank * 10 * accuracies[0]) + (locRank * 10 * accuracies[1]) + (sizeRank * 10 * accuracies[2]) + (clRank * 10 * accuracies[3]);

    //testing updating the score of this node
    max.nodeScore(currentScore);
    max.printNode();

    cout << "THE END" << endl;

    return 0;
}