#include "header/type.h"
#include "header/indicator.h"
#include "header/filehandle.h"
#include <iomanip>
#include <iostream>
using namespace std;

#define SETWIDTH 20

#define GC "GC"
#define COPRA "COPRA"
#define SLPA "SLPA"
#define LFM "LFM"

int main(){
  const string mothed = GC;
  const string name = "AC";

  cout << "Network File Loading..." << endl;
  vector<Edge> edgeCaches = getCommunityEdges( name );
  map<int,Node> nodeCaches =  getOverlapCommunity( mothed, name );

  int nodeNumber = nodeCaches.size();
  int edgeNumber = edgeCaches.size();

  cout << "Degree Initializing..." << endl;
  for(int i=0; i<edgeCaches.size(); i++){
    nodeCaches.find(edgeCaches[i].getNodeA())->second.addDegree();
    nodeCaches.find(edgeCaches[i].getNodeB())->second.addDegree();
  }

  cout << "CommunityNumber Calculating..." << endl;
  int communityNumber = calculationCommunityNumber(nodeCaches);

  cout << "Extend Modularity Calculating..." << endl;
  double extendModularity = calculationExtendModularity(nodeCaches, edgeCaches);

  cout << setiosflags(ios::fixed) << setiosflags(ios::left) << endl;
  cout << setw(SETWIDTH) << "Name:" << setw(SETWIDTH) << name << endl;
  cout << setw(SETWIDTH) << "Mothed:" << setw(SETWIDTH) << mothed << endl << endl;
  cout << setw(SETWIDTH) << "NodeNumber:" << setw(SETWIDTH) << nodeNumber << endl;
  cout << setw(SETWIDTH) << "EdgeNumber:" << setw(SETWIDTH) << edgeNumber << endl;
  cout << setw(SETWIDTH) << "CommunityNumber:" << setw(SETWIDTH) << communityNumber << endl;
  cout << setw(SETWIDTH) << "ExtendModularity:" << setw(SETWIDTH) << setprecision(6) << extendModularity << endl;
  
  return 0;
}
