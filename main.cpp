#include <iostream>
#include <cstdlib>
#include "header/filehandle.h"
#include "header/lfm.h"

using namespace std;

int main()
{
  string name = "Metadata_WR";
  char intercept = 'E';
  int number = 10000;
  bool connected = true;
  bool sequence = true;
  char nodetype = 'A';

  const double alpha = 1;              //阿尔法系数

  Unipartite UnipartiteNetwork = getUnipartite( name, intercept, number, connected, sequence, nodetype);

  vector<Edge> edgeCache = UnipartiteNetwork.getEdges();            //投影网络边连接信息
  map<int,Node> nodeCache = UnipartiteNetwork.getNodes();           //投影网络节点信息

  nodeCache = initializationCommunityNode(nodeCache, edgeCache);    //初始化节点信息

  int seednode = -1;
  int communityNumber = 1;
  double communityPercentage = 0.0;

  while(1){
    seednode = generateSeedNode(nodeCache);

    if(seednode == -1){ break; }                                    //循环终止条件，不存在未分配的节点

    set<int> communities = generateCommunity(seednode, alpha, nodeCache);

    nodeCache = updateNodeTags(communityNumber, communities, nodeCache);

    communityNumber++;
    communityPercentage = calculationCommunityPercentage(nodeCache);

    cout << "communityNumber:" << communityNumber << "\t communityPercentage:" << communityPercentage << endl;
  }

  printCommunity(nodeCache, name, intercept, number, connected, sequence, nodetype);

  return 0;
}