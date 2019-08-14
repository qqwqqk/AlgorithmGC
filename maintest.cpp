#include <iostream>
#include <cstdlib>
#include "src/pretreatment/filehandle.h"
#include "src/algorithm/gravitycoefficient.h"

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

  double overlapModularity = calculationOverlapModularity(CommunityResult, UnipartiteNetwork.getEdges());

  set<int> communityCache;
  for(map<int,Node>::iterator iter = CommunityResult.begin(); iter != CommunityResult.end(); iter++){
    cout<< iter->first<<":";
    vector<int> cache = iter->second.getCommunityList();
    for(int i=0; i<cache.size(); i++){
      cout<< ' ' << cache[i];
      communityCache.insert(cache[i]);
    }
    cout<< endl;
  }

  cout << "\nmodularityOverlap:\t" << overlapModularity << "\tcommunityNumber:\t" << communityCache.size() << endl;


  return 0;
}