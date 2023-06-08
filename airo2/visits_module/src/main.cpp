#include <iostream>
#include "VisitSolver.h"
#include <fstream>
#include <list>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// generate random float number between 0 and 6
float generateRandomFloat() {
    return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 6));
}

// Function to generate random waypoints
void randomWaypoint(float waypoints[24][3]){
    // Open file to write waypoints
    ofstream outfile;
    outfile.open("waypoints.txt", ios_base::app);

    // Random number
    float randomNumber = 0.0;
   
   // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Setting random value for x,y waypoints
    for (int i = 0; i < 24; i++) {
        for(int j = 0; j < 2; j++) {
            randomNumber = generateRandomFloat();
            waypoints[i][j] = randomNumber-3.0;
        }
        outfile << "w" << i << "= (" << waypoints[i][0] << ", " << waypoints[i][1] << ", " << waypoints[i][2] << ")" << endl;
    }
    outfile.close();
}


int main(int argc, char **argv) {
    
    VisitSolver visitExample;
    string problem;

    float waypoints[24][3] = {};
    
    randomWaypoint(waypoints);
    
    if (argc > 2){
        problem = argv[1];
    }else{
        cout << "Usage:\n"
        << argv[0] << " problem parameters plan" << endl;
        return 1;
    }
    string parameters[] = {0};
    visitExample.loadSolver(parameters,1);
    map<string,double> initialState;

    initialState["(act-cost)"] = 0;
    initialState["(dummy)"] = 0;
    

    // Declaring Vector of String type 
    vector <string> region; 
  
    // Initialize vector with regions using push_back  
    // command 
    region.push_back("r0"); 
    region.push_back("r1"); 
    region.push_back("r2"); 
    region.push_back("r3"); 
    region.push_back("r4"); 
  
    // store the initial state fluents
    for (int i=0; i<region.size(); i++)   { 
    for(int j=0; j<region.size(); j++){
       if (i != j){       
        initialState["(triggered " + region[i] + " " + region[j]+")"] = 0;
       }
    }
    }   
    return 0;
}
