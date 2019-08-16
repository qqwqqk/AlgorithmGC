#include <iostream>
#include <cstdlib>
#include "header/filehandle.h"
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
    map<int,double> cache = iter->second.getTags();
    for(map<int,double>::iterator item = cache.begin(); item != cache.end(); item++){
      cout<< ' ' << item->first;
      communityCache.insert(item->first);
    }
    cout<< endl;
  }

  cout<<"calculation overlap modularity:"<<endl;
  double overlapModularity = calculationOverlapModularity(CommunityResult, UnipartiteNetwork.getEdges());
  cout<<"calculation extend modularity:"<<endl;
  double extendModularity = calculationExtendModularity(CommunityResult, UnipartiteNetwork.getEdges());

  cout << "communityNumber:\t" << communityCache.size() << '\t';
  cout << "extendModularity:\t" << extendModularity << '\t';
  cout << "modularityOverlap:\t" << overlapModularity << endl;


  return 0;
}