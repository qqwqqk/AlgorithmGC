#include <iostream>
#include <cstdlib>
#include "header/filehandle.h"
#include "header/copra.h"

using namespace std;

int main()
{
  string name = "Metadata_MC";
  char intercept = 'B';
  int number = 800;
  bool connected = true;
  bool sequence = true;
  char nodetype = 'A';

  const int termination = 2;                      //终止条件迭代次数
  const int communitymax = 2;                     //单个节点最多隶属社区数目
  const double threshold = 1.0 /  communitymax;   //阈值

  Bipartite BipartiteNetwork = getBipartite( name, intercept, number, connected, sequence);
  Unipartite UnipartiteNetwork = getUnipartite( name, intercept, number, connected, sequence, nodetype);

  vector<Edge> edgeCache = UnipartiteNetwork.getEdges();            //投影网络边连接信息
  map<int,Node> nodeCache = UnipartiteNetwork.getNodes();           //投影网络节点信息

  nodeCache = initializationCommunityNode(nodeCache, edgeCache);    //初始化节点信息

  int beforeNumber, updatedNumber, iteration = 0;

  while(iteration < termination){
    beforeNumber = calculationCommunityNumber(nodeCache);

    nodeCache = updateCommunityCaches(nodeCache, edgeCache);
    nodeCache = updateCommunityTags(nodeCache, threshold);

    updatedNumber = calculationCommunityNumber(nodeCache);

    cout<<"communityNumber:"<<updatedNumber<<endl;
    
    if(beforeNumber == updatedNumber){iteration++;} else {iteration = 0;}
  }

  printCommunity(nodeCache, name, intercept, number, connected, sequence, nodetype);

  return 0;
}