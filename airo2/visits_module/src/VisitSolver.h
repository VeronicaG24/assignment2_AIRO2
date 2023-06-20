#ifndef TESTSOLVER_H
#define TESTSOLVER_H

#include "ExternalSolver.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <queue>
#include <unordered_map>

using namespace std;

class VisitSolver : public ExternalSolver
{
public:
    VisitSolver();
    ~VisitSolver();
    virtual void loadSolver(string* parameters, int n);
    virtual map<string,double> callExternalSolver(map<string,double> initialState, bool isHeuristic);
    virtual  list<string> getParameters();
    virtual  list<string> getDependencies();
    map<string, vector<double>> waypoint;
    map<string, vector<double>> landmark;
    double distance;
    double dist_matrix[30][30];
    double useful_array[30];
    int adj_matrix[30][30];
    int k;
    string wp[30] = {"wp0","wp1","wp2","wp3","wp4","wp5","wp6","wp7","wp8","wp9","wp10","wp11","wp12","wp13","wp14","wp15","wp16","wp17","wp18","wp19","wp20","wp21","wp22","wp23","wp24","wp25","wp26","wp27","wp28", "wp29"};
    string reg[30] = {"r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15","r16","r17","r18","r19","r20","r21","r22","r23","r24","r25","r26","r27","r28", "r29"};
   
    void parseWaypoint(string waypoint_file);
    void parseLandmark(string landmark_file);
     
    map<string, vector<string>> region_mapping;
    vector <string> source, target; 
    string starting_position;
     
    int find_min();
    void build_graph();
    void parseParameters(string parameters);
    double distance_euc(string from, string to);
    void test(double d, const std::string& nomeFile);
    void test2(int i, const std::string& nomeFile);
    void test3(string s, const std::string& nomeFile);
    void gen_rnd(string p);
    int extract_num(string r);

private:
    list<string> affected;
    list<string> dependencies;
      
    double calculateExtern(double external, double total_cost);
    //void localize(string from, string to);
    vector<string> findParameters(string line, int&n);

};

#endif // TESTSOLVER_H
