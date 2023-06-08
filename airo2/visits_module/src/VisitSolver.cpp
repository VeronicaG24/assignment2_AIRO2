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



    //map <string, vector<double> > region_mapping;

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
  starting_position = "r0";
  string Paramers = parameters[0];

  char const *x[]={"dummy"};
  char const *y[]={"act-cost","triggered"};
  parseParameters(Paramers);
  affected = list<string>(x,x+1);
  dependencies = list<string>(y,y+2);

  string waypoint_file = "visits_domain/waypoint.txt";   // change this to the correct path
  parseWaypoint(waypoint_file);

  string landmark_file = "visits_domain/landmark.txt";  // change this to the correct path
  parseLandmark(landmark_file);

  gen_rnd(waypoint_file);

        //startEKF();
}

map<string,double> VisitSolver::callExternalSolver(map<string,double> initialState,bool isHeuristic){

  map<string, double> toReturn;
  map<string, double>::iterator iSIt = initialState.begin();
  map<string, double>::iterator isEnd = initialState.end();
  double dummy;
  double act_cost;


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
      string to = tmp.substr(3,2);     // HERE ARE EXTRACTED THE NAME OF THE REGIONS (SUCH AS r0, r1 AND SO ON...)


      distance_euc(from, to);

    }
  }
}else{
  if(function=="dummy"){
    dummy = value;

  }else if(function=="act-cost"){
    act_cost = value;
                 } //else if(function=="dummy1"){
                    //duy = value;              
                    ////cout << parameter << " " << value << endl;
                 //}
                 }
               }


               double results = calculateExtern(dummy, act_cost);
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

         double VisitSolver::calculateExtern(double external, double total_cost){
       //float random1 = static_cast <float> (rand())/static_cast <float>(RAND_MAX);
       double cost = 2;//random1; TODO: change it into distance + unc(trace)
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

         waypoint[waypoint_name] = vector<double> {pose1, pose2, pose3};  //HERE ARE EXTRACTED THE WAYPOINTS POSITION
       }
     }

   }

   void VisitSolver::parseLandmark(string landmark_file){

     int curr, next;
     string line;
     double pose1, pose2, pose3;
     ifstream parametersFile(landmark_file);
     if (parametersFile.is_open()){
      while (getline(parametersFile,line)){
       curr=line.find("[");
       string landmark_name = line.substr(0,curr).c_str();
       
       curr=curr+1;
       next=line.find(",",curr);

       pose1 = (double)atof(line.substr(curr,next-curr).c_str());
       curr=next+1; next=line.find(",",curr);

       pose2 = (double)atof(line.substr(curr,next-curr).c_str());
       curr=next+1; next=line.find("]",curr);

       pose3 = (double)atof(line.substr(curr,next-curr).c_str());

       landmark[landmark_name] = vector<double> {pose1, pose2, pose3};  //SAME AS PARSEWAYPOINT
     }
   }
   
 }


  void VisitSolver::distance_euc(string from, string to){
    string wp[5] = {"wp0","wp1","wp2","wp3","wp4"};
    map <string, string> regions;
    regions["r0"] = wp[0];
    regions["r1"] = wp[1];
    regions["r2"] = wp[2];
    regions["r3"] = wp[3];
    regions["r4"] = wp[4];

    double x1 = waypoint[regions[from]].at(0);
    double y1 = waypoint[regions[from]].at(1);
    
    double x2 = waypoint[regions[to]].at(0);
    double y2 = waypoint[regions[to]].at(1);
    
    distance = sqrt(pow((x2-x1),2) + pow((y2-y1),2));
    test(distance,"test.txt");
  }

  void VisitSolver::test(double d, const std::string& nomeFile) {
    std::ofstream file(nomeFile);
    if (file.is_open()) {
        file << d;
        file.close();
        std::cout << "Numero reale scritto sul file con successo." << std::endl;
    } else {
        std::cout << "Impossibile aprire il file." << std::endl;
    }
  }

  void VisitSolver::gen_rnd(string p) {
    // Initialise stuff...
    float waypoints[24][3];
    // Open the file waypoint.txt, to generate on it the random waypoints
    ofstream outfile;
    // We first open the file in trunc mode and then close it, so the waypoints.txt file will be emptied
    outfile.open(p, ios_base::trunc);
    outfile.close();
    outfile.open(p, ios_base::app);
    // Write the five waypoints that are already known
    outfile<<"wp0[0,0,0]"<<std::endl;
    outfile<<"wp1[-2.5,2.5,0]"<<std::endl;
    outfile<<"wp2[2.5,2.5,1.57]"<<std::endl;
    outfile<<"wp3[-2.5,-2.5,3.14]"<<std::endl;
    outfile<<"wp4[2.5,-2.5,-1.57]"<<std::endl;
    // Initialize the random number generator 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-3.0, 3.0);
    // Setting random value for x,y waypoints
    for (int i = 5; i <= 28; i++){
        for(int j = 0; j <= 2; j++){
            waypoints[i][j] = dis(gen);
            waypoints[i][j] = std::trunc(waypoints[i][j] * 100.0) / 100.0;
            if(j==0) {
              outfile<<"wp"<<i<<"["<<waypoints[i][j]<<",";
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



