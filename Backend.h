#include <string> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <chrono>

#include "binaryMaxHeap.h"
#include "quickSort.h"
using namespace std;

//Team Name: Cosmic Collision
//Team Members:  Tomas Chavarria, Joseph Molina, and Athena Wrenn
//Project Title: Meteorite Landing Finder

//reference: geeksforgeeks.org/csv-file-management-using-c
//reference: gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp

class Backend {

    //calculate the accuracy of each specification; how close a match?
    vector<float> findAccuracies(int idealYear, float idealLat, float idealLon, float idealSize, Node& max) {
        vector<float> matchVector;

        //find how close the specified year is (between 0 and 1.0)
        //100 years off scores a 0
        float yearAccuracy = 1.0 - (abs(max.year - idealYear) / 100.0);
        matchVector.push_back(yearAccuracy);

        //find how close the specified location is (between 0 and 1.0)
        //100 miles off scores a 0
        float locAccuracy;
        float latDiff = max.recLat - idealLat;
        float lonDiff = max.recLon - idealLon;
        float locDiff = sqrt((latDiff * latDiff) + (lonDiff * lonDiff));
        locAccuracy = 1.0 - (locDiff / 100.0);

        matchVector.push_back(locAccuracy);

        //find how close the specified size is (between 0 and 1.0)
        //100g off scores a 0
        float sizeAccuracy = 1.0 - (abs(max.mass - idealSize) / 100.0);
        //cout << sizeAccuracy << endl;
        matchVector.push_back(sizeAccuracy);

        return matchVector;
    }

    //read the csv file into the binary heap
    void importFile(vector<Node>& needsSort, int idealYear, float idealLat, float idealLon, float idealSize, int yearRank, int locRank, int sizeRank) {

        string fileName = "Meteorite_Landings.csv";
        ifstream myFile(fileName);

        if (!myFile.is_open()) {
            throw runtime_error("Could not open csv file");
        }

        //the first line is headers
        string line;
        if (myFile.good()) {
            getline(myFile, line);
        }

        //the rest of the lines are each nodes
        int countSkipped = 0;
        int countProcessed = 0;


        while (getline(myFile, line)) {
            stringstream s(line);
            string word;
            vector<string> row;

            while (getline(s, word, ',')) {
                //if the , is in "" it isn't a new column
                if (word[0] == '"') {
                    string secondHalf;
                    getline(s, secondHalf, ',');
                    word = word + secondHalf;
                }

                row.push_back(word);
            }

            //remove rows of incomplete data
            if (row[0].empty() || row[1].empty() || row[3].empty() || row[4].empty() || row[6].empty() || row[7].empty() || row[8].empty()) {
                countSkipped++;
            }
            else {
                //file is setup: name, id, nametype, recclass, mass (g), fall, year, reclat, reclong, GeoLocation
                string name = row[0];
                int id = stoi(row[1]);
                string recClass = row[3];
                float mass = stof(row[4]);
                int year = stoi(row[6]);
                float recLat = stof(row[7]);
                float recLon = stof(row[8]);

                Node currentNode = Node(name, id, recClass, mass, year, recLat, recLon);

                //score a crash
                vector<float> accuracies; // 0: year, 1: location, 2: size, 3: class
                accuracies = findAccuracies(idealYear, idealLat, idealLon, idealSize, currentNode);

                float currentScore = 0;
                currentScore = (yearRank * 10 * accuracies[0]) + (locRank * 10 * accuracies[1]) + (sizeRank * 10 * accuracies[2]);

                //testing updating the score of this node
                currentNode.nodeScore(currentScore);

                needsSort.push_back(currentNode);
                countProcessed++;


            }
        }

        cout << endl << "Skipped " << countSkipped << " invalid tuples." << endl;
        cout << "Processed " << countProcessed << " valid tuples." << endl;

    }


    public:
    vector<Node> algorithm(int idealYear, float idealLat, float idealLon, float idealSize, int yearRank, int locRank, int sizeRank) {
        //import the meteorite data into the 2 data structures
        binaryMaxHeap binaryHeap;
        vector<Node> needsSort;
        vector<Node> results;

        importFile(needsSort, idealYear, idealLat, idealLon, idealSize, yearRank, locRank, sizeRank);

        cout << "Size of the data: " << needsSort.size() << endl;

        auto startHeapTime = std::chrono::high_resolution_clock::now();

        //testing the binary heap
        for (auto& node : needsSort) {
            binaryHeap.insert(node);
        }
        for (int i = 0; i < 10; i++) {//store into vector for output
            Node max = binaryHeap.extractMax();
            results.push_back(max);
            max.printNode();
        }

        auto endHeapTime = chrono::high_resolution_clock::now();

        //calculate the duration in seconds
        chrono::duration<double> durationHeap = endHeapTime - startHeapTime;
        double elapsedHeapTime = durationHeap.count();

        cout << endl << endl;



        auto startQuickTime = std::chrono::high_resolution_clock::now();

        //testing the quicksort
        sortNodesByScore(results);
        for (int i = 0; i < 10; i++) {
            results[i].printNode();
        }

        auto endQuickTime = chrono::high_resolution_clock::now();

        //calculate the duration in seconds
        chrono::duration<double> durationQuick = endHeapTime - startHeapTime;
        double elapsedQuickTime = durationQuick.count();

        cout << "Elapsed time Heap: " << elapsedHeapTime << " seconds" << endl;
        cout << "Elapsed time Quick: " << elapsedQuickTime << " seconds" << std::endl;

        return results;
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
};