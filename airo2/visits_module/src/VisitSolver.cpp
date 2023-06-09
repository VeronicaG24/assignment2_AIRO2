/*
     <one line to give the program's name and a brief idea of what it does.>
     Copyright (C) 2015  <copyright holder> <email>
     
     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.
     
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
     
     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.
     */

// Importing libraries that are needed
#include "VisitSolver.h"
#include "ExternalSolver.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

#include "armadillo"
#include <initializer_list>

using namespace std;
using namespace arma;


extern "C" ExternalSolver* create_object(){
  return new VisitSolver();
}

extern "C" void destroy_object(ExternalSolver *externalSolver){
  delete externalSolver;
}

VisitSolver::VisitSolver(){

}

VisitSolver::~VisitSolver(){

}

void VisitSolver::loadSolver(string *parameters, int n){
  starting_position = "r0";                 // Initialise our starting position as r0 (0,0)
  string Paramers = parameters[0];

  char const *x[]={"dummy"};
  char const *y[]={"act-cost","triggered"};
  parseParameters(Paramers);
  affected = list<string>(x,x+1);
  dependencies = list<string>(y,y+2);
  std::cout<<"Please insert the number of links between nodes ( the number should be between 5 and 30): "<<std::endl;
  std::cin>>k;                            // The user input the desired K value
  std::cout<<std::endl;
  while(k < 5 || k > 30) {                // If the number is incorrect, the user is asked to insert a new value
    std::cout<<"Error! Please insert a value between 5 and 30"<<std::endl;
    std::cin>>k;
    std::cout<<std::endl;
  }

  string waypoint_file = "./waypoint.txt";
  gen_rnd(waypoint_file);                             // Before parsing the waypoints, we generate the 24 random waypoints ont the file waypoint.txt
  parseWaypoint(waypoint_file);

  build_graph();                                        // Now we build the graph to connect all the waypoints we've generated
}

map<string,double> VisitSolver::callExternalSolver(map<string,double> initialState,bool isHeuristic){
  map<string, double> toReturn;
  map<string, double>::iterator iSIt = initialState.begin();
  map<string, double>::iterator isEnd = initialState.end();
  double dummy;

  map<string, double> is_connected;
  map<string, double> trigger;

  for(;iSIt!=isEnd;++iSIt){

    string parameter = iSIt->first;
    string function = iSIt->first;
    double value = iSIt->second;

    function.erase(0,1);
    function.erase(function.length()-1,function.length());
    int n=function.find(" ");

    if(n!=-1){
      string arg=function;
      string tmp = function.substr(n+1,5);

      function.erase(n,function.length()-1);
      arg.erase(0,n+1);
      if(function=="triggered"){
        trigger[arg] = value>0?1:0;
        if (value>0){
      string from = tmp.substr(0,2);   // from and to are regions, need to extract wps (poses)
      string to = tmp.substr(3,2);
                                              // Here we compute the cost for the movement between two regions;
      act_dist=compute_path(from, to);        // the cost is equal to the total path covered by the robot, passing through the waypoints
      if(act_dist == 10000) {
        act_dist = -1000;                     // If the path does not exist, the cost is assigned to a negative value (with K >= 5, this should not happen!)
      }

    }
  }
}else{
  if(function=="dummy"){
    dummy = act_dist;                         // The cost for the movement between two regions is assigned to dummy

  }
                 }
               }


               double results = calculateExtern();
               if (ExternalSolver::verbose){
                cout << "(dummy) " << results << endl;
              }

              toReturn["(dummy)"] = results;


              return toReturn;
            }

            list<string> VisitSolver::getParameters(){

              return affected;
            }

            list<string> VisitSolver::getDependencies(){

              return dependencies;
            }


            void VisitSolver::parseParameters(string parameters){

              int curr, next;
              string line;
              ifstream parametersFile(parameters.c_str());
              if (parametersFile.is_open()){
                while (getline(parametersFile,line)){
                 curr=line.find(" ");
                 string region_name = line.substr(0,curr).c_str();
                 curr=curr+1;
                 while(true ){
                  next=line.find(" ",curr);
                  region_mapping[region_name].push_back(line.substr(curr,next-curr).c_str());
                  if (next ==-1)
                   break;
                 curr=next+1;

               }                
             }

           }

         }

         double VisitSolver::calculateExtern(){
       double cost = act_dist;
       return cost;
     }

     void VisitSolver::parseWaypoint(string waypoint_file){

       int curr, next;
       string line;
       double pose1, pose2, pose3;
       ifstream parametersFile(waypoint_file);
       if (parametersFile.is_open()){
        while (getline(parametersFile,line)){
         curr=line.find("[");
         string waypoint_name = line.substr(0,curr).c_str();

         curr=curr+1;
         next=line.find(",",curr);

         pose1 = (double)atof(line.substr(curr,next-curr).c_str());
         curr=next+1; next=line.find(",",curr);

         pose2 = (double)atof(line.substr(curr,next-curr).c_str());
         curr=next+1; next=line.find("]",curr);

         pose3 = (double)atof(line.substr(curr,next-curr).c_str());

         waypoint[waypoint_name] = vector<double> {pose1, pose2, pose3};  // Here are the extracted waypoints positions
       }
     }

   }

  // Function to compute the cost (distance) between two regions, given all the waypoints
  double VisitSolver::compute_path(string from, string to){
    int f = extract_num(from);                              // Initialize stuff...
    int t = extract_num(to);
    double distances[30] = {};
    for (int o = 0; o < 30; o++) {                            // Initialize distances to infinity (a high value) 
      distances[o] = 10000;                                 
    }
    bool visited[30] = {};
    distances[f] = 0;
    int n_visited = 1;                                        // Using the Dijkstra algorithm, we compute the total cost of the robot's movement
    while(n_visited < 30) {
      int u = find_unvis(distances, visited);
      n_visited++;
      visited[u] = true;
      for (int v = 0; v < 30; v++) {
        if(adj_matrix[u][v] != 0 && !visited[v] && distances[u] != INT_MAX && distances[u] + dist_matrix[u][v] < distances[v]) {
          distances[v] = distances[u] + dist_matrix[u][v];
        }
      }
    }
    return distances[t];
  }

  // This function is used in the Dijkstra algorithm to find the unvisited node with the minimum distance from the source
  int VisitSolver::find_unvis(double distances[30], bool visited[30]) {
    int min_dist = INT_MAX;
    int min_idx = -1;
    for(int j = 0; j < 30; j++) {
      if (!visited[j] && distances[j] < min_dist) {
        min_dist = distances[j];
        min_idx = j;
      }
    }
    return min_idx;
  }

  // This function i used to compute the euclidean distance between two waypoints
  double VisitSolver::distance_euc(string from, string to){
    map <string, string> regions;
    for(int i = 0; i < 30; i++) {
      regions[reg[i]] = wp[i];
    }

    double x1 = waypoint[regions[from]].at(0);      // We extract the coordinates of the two waypoints
    double y1 = waypoint[regions[from]].at(1);
    
    double x2 = waypoint[regions[to]].at(0);
    double y2 = waypoint[regions[to]].at(1);
    
    distance = sqrt(pow((x2-x1),2) + pow((y2-y1),2));     // The euclidean distance is computed
    return distance;
  }

  // This function build a graph connecting the waypoints 
  void VisitSolver::build_graph() {
    int flag = 0;
    int min_idx;
    int n_links[30] = {};
    for(int i = 0; i < 30; i++) {
      flag = 0;
      for(int j = 0; j < 30; j++) {
        if(i != j) {
          string a = to_string(i);
          string b = to_string(j);
          a = "r" + a;
          b = "r" + b;
          dist_matrix[i][j] = distance_euc(a,b);  // We compute the distance between every couple of waypoints and put the result in dist_matrix
          useful_array[j] = dist_matrix[i][j];             // Useful array is used to find the minimum distances
        }
        else {
          dist_matrix[i][j] = 1000.0;          // Elements on the diagonal are set to a high value, so they do not interfere in the search for the minimum
          useful_array[j] = dist_matrix[i][j];

        }
      }
      while(n_links[i] < k && flag < 30) {    // While the number of connection for the current waypoint are less than K,
        min_idx = find_min();                 // we keep connecting it to the closest waypoints
        if (n_links[min_idx] < k) {           // If the closest waypoint is not already connected to K waypoints, we connect it to the current one
          adj_matrix[i][min_idx] = 1;
          adj_matrix[min_idx][i] = 1;
          n_links[i]++;
          n_links[min_idx]++;
        }
        else {
          flag++;                             // This variable is used to avoid infinite loops
        }
      }
    }
  }

  // This function is used to find the minimum element in useful_array
  int VisitSolver::find_min() {
    int min = useful_array[0];
    int min_index = 0;
    for(int l = 1; l < 30; l++) {
      if(useful_array[l] < min) {
        min_index = l;
        min = useful_array[l];
      }
    }
    useful_array[min_index] = 100.0;
    return min_index;
  }

  void VisitSolver::gen_rnd(string p) {
    float waypoints[24][3];               // Initialise stuff...
    ofstream outfile;                     // Open the file waypoint.txt, to generate on it the random waypoints
    outfile.open(p, ios_base::trunc);
    outfile.close();                      // We first open the file in trunc mode and then close it, so the waypoints.txt file will be emptied
    outfile.open(p, ios_base::app);
    outfile<<"wp0[0,0,0]"<<std::endl;     // Write the six waypoints that are already known
    outfile<<"wp1[-2.5,2.5,0]"<<std::endl;
    outfile<<"wp2[2.5,2.5,1.57]"<<std::endl;
    outfile<<"wp3[-2.5,-2.5,3.14]"<<std::endl;
    outfile << "wp4[2.5,-2.5,-1.57]" << std::endl;
    outfile << "wp5[3,0,0]" << std::endl;
    std::random_device rd;                // Initialize the random number generator 
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-3.0, 3.0);
    for (int i = 6; i <= 29; i++){        // Setting random value for x,y waypoints
        for(int j = 0; j <= 2; j++){
            waypoints[i][j] = dis(gen);
            waypoints[i][j] = std::trunc(waypoints[i][j] * 100.0) / 100.0;    // We truncate the real number to the second decimal digit
            if(j==0) {
              outfile<<"wp"<<i<<"["<<waypoints[i][j]<<",";                      // We write the waypoints on the file 
            }else if(j==1) {
              outfile<<waypoints[i][j]<<",";
            }
            else {
              outfile<<waypoints[i][j]<<"]"<<std::endl;
            }
        }
    }
    outfile.close();
  } 

  int VisitSolver::extract_num(string r){
    string num = r.substr(1);
    int n = 0;
    for (char c : num) {
        if (std::isdigit(c)) {
            n = n * 10 + (c - '0');
        } else {
            std::cout << "Errore: La stringa contiene caratteri non numerici." << std::endl;
            return -1;
        }
    }
    return n;
  }
