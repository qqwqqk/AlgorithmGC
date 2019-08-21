#include "../header/lfm.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

double calculationFitness(double alpha, set<int> tags, map<int,Node> nodes){
  int k_in = 0, k_out = 0;
  for(set<int>::iterator iter = tags.begin(); iter!=tags.end(); iter++){
    vector<int> lists = nodes[*iter].getContiguity();
    for(int i=0; i<lists.size(); i++){
      if(tags.count(lists[i]) > 0){ k_in++; } else { k_out++; }
    }
  }
  double fitness = 1.0 * k_in / pow((k_in + k_out), alpha);
  return fitness;
}

map<int,Node> initializationCommunityNode(map<int,Node> nodes, vector<Edge> edges){
  for(int i=0; i<edges.size(); i++){
    const int node_a = edges[i].getNodeA();
    const int node_b = edges[i].getNodeB();

    nodes[node_a].addDegree();
    nodes[node_b].addDegree();

    nodes[node_a].addContiguity(node_b);
    nodes[node_b].addContiguity(node_a);
  }
  return nodes;
}

int generateSeedNode(map<int,Node> nodes){
  for(map<int,Node>::iterator iter = nodes.begin(); iter!=nodes.end(); iter++){
    if(iter->second.getTags().size() < 1){ return iter->first;}
  }
  return -1;
}

set<int> generateCommunity(int seednode, double alpha, map<int,Node> nodes){
  set<int> tags = {seednode};
  set<int> neighborhood = {};
  double initFitness, currFitness, deltaFitness = 0.0;
  double fitnessMax = 0.0;
  vector<int> fitnessCaches;
  while(1){
    //计算邻域节点
    neighborhood.clear();
    for(set<int>::iterator iter = tags.begin(); iter!=tags.end(); iter++){
      vector<int> lists = nodes[*iter].getContiguity();
      for(int i=0; i<lists.size(); i++){
        int tag_item = lists[i];
        if(tags.count(tag_item) < 1){ neighborhood.insert(lists[i]); }
      }
    }

    //计算能使fitness增加的节点列表
    fitnessMax = 0.0; fitnessCaches.clear();
    initFitness = calculationFitness(alpha, tags, nodes);
    for(set<int>::iterator iter_near = neighborhood.begin(); iter_near != neighborhood.end(); iter_near++){
      set<int> tags_curr = tags;
      tags_curr.insert(*iter_near);
      currFitness = calculationFitness(alpha, tags_curr, nodes);
      deltaFitness = currFitness - initFitness;
      if(deltaFitness == fitnessMax){ fitnessCaches.push_back(*iter_near); }
      if(deltaFitness > fitnessMax){
        fitnessMax = deltaFitness;
        fitnessCaches.clear();
        fitnessCaches.push_back(*iter_near);
      }
    }

    //若不存在可以使fitness增加的节点退出循环，否则将对应的节点插入社区列表
    if(fitnessCaches.size() < 1){ break; }
    else{
      for(int i=0; i<fitnessCaches.size(); i++){
        tags.insert(fitnessCaches[i]);
      }
    }
  }
  return tags;
}

map<int,Node> updateNodeTags(int communitytag, set<int> communities, map<int,Node> nodes){
  for(set<int>::iterator iter = communities.begin(); iter != communities.end(); iter++){
    nodes[*iter].addTag(communitytag);
  }
  return nodes;
}

double calculationCommunityPercentage(map<int,Node> nodes){
  const int length = nodes.size();
  int count = 0;

  for(map<int,Node>::iterator iter = nodes.begin(); iter!=nodes.end(); iter++){
    if(iter->second.getTags().size() > 0){ count++; }
  }

  double percentage = 1.0 * count / length;
  return percentage;
}
