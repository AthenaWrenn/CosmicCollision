# COP3530 - Project 3 - Cosmic Collision
This repository serves to hold project 3 of Data Structures and Algorithms, Cosmic Collision.

## Getting Started

- In order to run this program, all the user must do is run the .exe file provided. However, the Meteorite_Landings.csv file MUST be in the same directory, or an exception will be thrown.
- To set up the program for development, it is recommended to follow the steps provided in [this](https://www.youtube.com/watch?v=ONYW3hBbk-8) video to set up wxWidgets.

## Extended Documentation
### 1.1 Problem
The meteorite landing finder assists non scientists in finding the real meteorite landings they are searching for. This tool easily identifies a known meteorite landing that matches user specifications the closest. Target meteor year, size, and crash locations are first entered and prioritized, and then a ranked list of matching meteorite landings is generated.

### 1.2 Motivation
Details on individual meteorite landings are not readily accessible to the general public. While the meteoritical society maintains strict guidelines on the naming of meteorites, some of these names (like those from duplicate locations) can be confusing to the uninitiated. The many classifications of meteorites provide useful information on the geologic makeup of the meteor, but are not a good organization method for the details of the landings. Additionally, astronomical events can be romanticized in a way that makes it difficult to identify only real confirmed historical meteorite landings from fiction. The meteorite landing finder assists non-scientists in finding the real historical meteorite landings they are searching for.

### 1.3 Features Implemented
The problem is solved by the generation of a list of meteorite landings. The meteorite landings are ordered from the best matches to the worst matches. Users specify the prioritization of the different search criteria, and then each meteorite is scored on how closely it matches what the user is looking for. This is simply displayed through a graphic user interface.

### 1.4 Data
The data used was the publicly available meteorite landings data set provided by [NASA and The Meteoritical Society](https://catalog.data.gov/dataset/meteorite-landings). Each original tuple consisted of a name, id, validity of weathering status, classification, mass, fall record status, year, recovery latitude, recovery longitude, and geolocation. For this project, information on the validity of weathering status and the fall record status was excluded on the basis that it did not serve the purpose of making information on meteorite landings accessible for non-scientists. Geolocation was also excluded in favor of not duplicating the information provided by the recovery latitude and longitude. Additionally, meteorite landings with incomplete information, such as having no recorded mass, were removed from the data.

### 1.5 Tools Used
The backend of the Meteorite Landing Finder was written in C++, and many different libraries were used. The <iostream> and <string> libraries were used in the input and manipulation of user specifications. The <fstream> and <sstream> libraries were used in the input of the data file. The <cmath> and <vector> libraries were used in calculating the similarity of each tuple to the user specified criteria. The <chrono> library was used in the comparison of the two data structures. The front-end was made using wxWidgets, which allowed for the graphic user interface.

### 1.6 Algorithms Implemented
The two main algorithms implemented were used in ordering the different meteorite landings by how similar they are to the user’s specifications. The first method used is a max binary heap. Every node is heap sorted by its similarity score, and the ten closest matching meteorite landings are removed from the top of the heap. The second method used is a quicksorted vector. Every node is inserted into a vector, and that vector is quicksorted by the same meteorite landing similarity scores.

### 1.7 Additional Data Structures/Algorithms Used
A purpose-built function was utilized to score the similarity between each node and the user’s specifications. This compares the year, location, and size of each node to the user defined ideal value. An accuracy is calculated as a decimal value between 0 and 1, and then weighted by multiplying with the user specified priorities to determine a score. While higher scores are more similar, these scores are not grades out of 100%, but instead their own methodology.
