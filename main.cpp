#include "header/type.h"
#include "header/indicator.h"
#include "header/filehandle.h"
#include <iomanip>
#include <iostream>
using namespace std;

#define SETWIDTH 20

#define GC "GC"
#define INFOMAP "InfoMAP"
#define LPA "LPA"
#define WALKTRAP "Walktrap"

int main(){
  const string mothed = GC;
  const string name = "AC";

  cout << "Network File Loading..." << endl;
  vector<Edge> edgeCaches = getCommunityEdges( name );
  map<int,Node> nodeCaches =  getNonOverlapCommunity( mothed, name );

  int nodeNumber = nodeCaches.size();
  int edgeNumber = edgeCaches.size();

  cout << "Degree Initializing..." << endl;
  for(int i=0; i<edgeCaches.size(); i++){
    nodeCaches.find(edgeCaches[i].getNodeA())->second.addDegree();
    nodeCaches.find(edgeCaches[i].getNodeB())->second.addDegree();
  }

  cout << "CommunityNumber Calculating..." << endl;
  int communityNumber = calculationCommunityNumber(nodeCaches);

  cout << "Modularity Calculating..." << endl;
  double Modularity = calculationModularity(nodeCaches, edgeCaches);

  cout << setiosflags(ios::fixed) << setiosflags(ios::left) << endl;
  cout << setw(SETWIDTH) << "Name:" << setw(SETWIDTH) << name << endl;
  cout << setw(SETWIDTH) << "Mothed:" << setw(SETWIDTH) << mothed << endl << endl;
  cout << setw(SETWIDTH) << "NodeNumber:" << setw(SETWIDTH) << nodeNumber << endl;
  cout << setw(SETWIDTH) << "EdgeNumber:" << setw(SETWIDTH) << edgeNumber << endl;
  cout << setw(SETWIDTH) << "CommunityNumber:" << setw(SETWIDTH) << communityNumber << endl;
  cout << setw(SETWIDTH) << "Modularity:" << setw(SETWIDTH) << setprecision(6) << Modularity << endl;
  
  return 0;
}
