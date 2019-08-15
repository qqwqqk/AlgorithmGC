#include <iostream>
#include <cstdlib>
#include "header/filehandle.h"
#include "header/gravitycoefficient.h"
#include "header/indicator.h"

using namespace std;

int main()
{
  string name = "Metadata_MC";
  char intercept = 'B'; 
  int number = 800;
  bool connected = true;
  bool sequence = true;
  char nodetype = 'A';

  Unipartite UnipartiteNetwork = getUnipartite( name, intercept, number, connected, sequence, nodetype);
  map<int,Node> CommunityResult = getOverlapCommunity( name, intercept, number, connected, sequence, nodetype);

  set<int> communityCache;
  cout<<"community:"<<endl;
  for(map<int,Node>::iterator iter = CommunityResult.begin(); iter != CommunityResult.end(); iter++){
    cout<< iter->first<<":";
    vector<int> cache = iter->second.getCommunityList();
    for(int i=0; i<cache.size(); i++){
      cout<< ' ' << cache[i];
      communityCache.insert(cache[i]);
    }
    cout<< endl;
  }

  cout<<"calculation overlap modularity:"<<endl;
  double overlapModularity = calculationOverlapModularity(CommunityResult, UnipartiteNetwork.getEdges());
  cout<<"calculation extend modularity:"<<endl;
  double extendModularity = calculationExtendModularity(CommunityResult, UnipartiteNetwork.getEdges());

  cout << "\t communityNumber:\t" << communityCache.size();
  cout << "\t extendModularity:\t" << extendModularity;
  cout << "\t modularityOverlap:\t" << overlapModularity;
  cout << endl;


  return 0;
}