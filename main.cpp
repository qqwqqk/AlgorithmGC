#include <iostream>
#include <cstdlib>
#include "header/filehandle.h"
#include "header/gravitycoefficient.h"
#include "header/indicator.h"

using namespace std;

int main()
{
  string name = "Metadata_MC";
  char intercept = 'E'; 
  int number = 99999;
  bool connected = true;
  bool sequence = true;
  char nodetype = 'A';

  const int termination = 20;            //最大迭代次数

  Bipartite BipartiteNetwork = getBipartite( name, intercept, number, connected, sequence);
  Unipartite UnipartiteNetworkA = getUnipartite( name, intercept, number, connected, sequence, 'A');
  Unipartite UnipartiteNetworkB = getUnipartite( name, intercept, number, connected, sequence, 'B');

  vector<Edge> bipartiteEdgeCache = BipartiteNetwork.getEdges();        //计算GC用二分网络原始边连接信息
  
  vector<Edge> unipartiteEdgeCache;               //计算模块度用投影网络边连接信息
  vector<Edge> resultEdgeCache;                   //计算重叠模块度用投影网络边连接信息
  map<int,Node> nodeCache;                        //社区合并过程记录节点信息
  map<int,Node> resultCache;                      //社区划分结果信息
  
  vector<Link> linkCache;                         //社区合并过程记录连接信息
  map<string, double> linkUpdate;                 //单次合并过程更新的连接

  //初始化一些定义
  switch (nodetype){
  case 'A':
    resultEdgeCache = UnipartiteNetworkA.getEdges();
    unipartiteEdgeCache = UnipartiteNetworkB.getEdges();
    nodeCache = UnipartiteNetworkB.getNodes();
    break;
  case 'B':
    resultEdgeCache = UnipartiteNetworkB.getEdges();
    unipartiteEdgeCache = UnipartiteNetworkA.getEdges();
    nodeCache = UnipartiteNetworkA.getNodes();
    break;
  default:
    exit(1);
  }


  //初始化 degree of nodeCache 与 bpi of linkCache
  for(int i=0; i<unipartiteEdgeCache.size(); i++){
    int node_a = unipartiteEdgeCache[i].getNodeA();
    int node_b = unipartiteEdgeCache[i].getNodeB();

    nodeCache[node_a].addDegree();
    nodeCache[node_b].addDegree();

    double gc = calculationGravityCoefficient(bipartiteEdgeCache, nodetype, node_a, node_b);
    Link item = {community_a: node_a, community_b: node_b, gravitycoefficient:gc };
    linkCache.push_back(item);
  }

  int communityNumber = nodeCache.size();                                     //当前社区数目
  double modularity = calculationModularity(nodeCache, unipartiteEdgeCache);  //当前的模块度
  vector<double> modularityCache;                                             //模块度缓存
  modularityCache.push_back(modularity);

  printProgress(modularityCache.size() - 1, communityNumber, modularity);     //输出初始信息

  int iteration = 0;
  while(communityNumber > 1 && iteration < termination){
    linkUpdate.clear();
    map<int, int> mergeList = calculationMergeList(linkCache);
  
    //更新nodeCache
    for(map<int, Node>::iterator iter_node = nodeCache.begin(); iter_node != nodeCache.end(); iter_node++){
      int original_tag = iter_node->second.getCommunityTag();
      map<int,int>::iterator iter_cache = mergeList.find(original_tag);
      int current_tag = iter_cache != mergeList.end() ? iter_cache->second : original_tag;
      iter_node->second.addListTag(current_tag);
    }

    //更新linkCache
    for(int i=0; i<linkCache.size(); i++){
      map<int,int>::iterator iter_a = mergeList.find(linkCache[i].community_a);
      map<int,int>::iterator iter_b = mergeList.find(linkCache[i].community_b);

      if(iter_a == mergeList.end() && iter_b == mergeList.end()){ continue; } 
      
      const int key_a = iter_a == mergeList.end() ? linkCache[i].community_a : iter_a->second;
      const int key_b = iter_b == mergeList.end() ? linkCache[i].community_b : iter_b->second;
      const string key_link = key_a < key_b ? to_string(key_a)+"_"+to_string(key_b) : to_string(key_b)+"_"+to_string(key_a);
      map<string, double>::iterator iter_link = linkUpdate.find(key_link);

      if(iter_link != linkUpdate.end() || key_a == key_b){
        linkCache.erase(linkCache.begin() + i);
        i--;
      } else {
        double gc = calculationGravityCoefficient(nodeCache, bipartiteEdgeCache, nodetype, key_a, key_b);
        linkCache[i].community_a = key_a; linkCache[i].community_b = key_b; linkCache[i].gravitycoefficient = gc;
        linkUpdate.insert(pair<string,double>(key_link, gc));
      }
    }

    //更新当前社区数量以及模块度相关
    communityNumber = calculationCommunityNumber(nodeCache);
    modularity = calculationModularity(nodeCache, unipartiteEdgeCache);
    if(modularity <= modularityCache.back()){ iteration++; } else { iteration = 0; }
    modularityCache.push_back(modularity);

    printProgress(modularityCache.size() - 1, communityNumber, modularity);     //输出合并进度
  }

  resultCache = calculationResult(modularityCache, nodeCache, bipartiteEdgeCache, nodetype);

  printCommunity(resultCache, name, intercept, number, connected, sequence, nodetype);                                   //输出社区划分结果

  //double overlapModularity = calculationOverlapModularity(resultCache, resultEdgeCache);

  return 0;
}
