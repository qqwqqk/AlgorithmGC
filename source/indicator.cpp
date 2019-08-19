#include "../header/indicator.h"
#include <cstdlib>
#include <math.h>
using namespace std;

double functionStatisticalProbability(double ai, double aj){
  const double z = 30; 
  const double func_i = 2.0 * z * ai - z; 
  const double func_j = 2.0 * z * aj - z; 
  const double result = 1.0 / ( 1 + exp(-func_i)) / ( 1 + exp(-func_j));
  return result;
}

double calculationOverlapModularity(map<int,Node> nodes, vector<Edge> edges){
  const double edges_number = edges.size();
  double item_edges = 0, community_edges = 0;
  double item_nodes = 0, community_nodes = 0;

  //初始节点度 计算边权
  for(int i=0; i<edges_number; i++){
    nodes.find(edges[i].getNodeA())->second.addDegree();
    nodes.find(edges[i].getNodeB())->second.addDegree();

    vector<int> community_a = nodes.find(edges[i].getNodeA())->second.getTags();
    vector<int> community_b = nodes.find(edges[i].getNodeB())->second.getTags();
    set<int> community_ab;

    for(vector<int>::iterator item_a = community_a.begin(); item_a != community_a.end(); item_a++){ 
      community_ab.insert(*item_a); 
    }
    for(vector<int>::iterator item_b = community_b.begin(); item_b != community_b.end(); item_b++){ 
      community_ab.insert(*item_b);
    }

    if(community_a.size() + community_b.size() > community_ab.size()){
      item_edges = functionStatisticalProbability(1/community_a.size(), 1/community_b.size());
      community_edges = community_edges + item_edges; 
    }
  }

  //计算节点权
  for(map<int,Node>::iterator node_i = nodes.begin(); node_i != nodes.end(); node_i++ ){
    for(map<int,Node>::iterator node_j = nodes.begin(); node_j != nodes.end(); node_j++ ){
      vector<int> community_a = node_i->second.getTags();
      vector<int> community_b = node_j->second.getTags();
      set<int> community_ab;

      for(vector<int>::iterator item_a = community_a.begin(); item_a != community_a.end(); item_a++){ 
        community_ab.insert(*item_a); 
      }
      for(vector<int>::iterator item_b = community_b.begin(); item_b != community_b.end(); item_b++){ 
        community_ab.insert(*item_b); 
      }

      if(community_a.size() + community_b.size() > community_ab.size()){
        double item_i = 0, item_j = 0;
        for(map<int,Node>::iterator node_k = nodes.begin(); node_k != nodes.end(); node_k++ ){
          item_i = item_i + functionStatisticalProbability(1/community_a.size(), 1/node_k->second.getTags().size());
          item_j = item_j + functionStatisticalProbability(1/community_b.size(), 1/node_k->second.getTags().size());
        }
    
        item_nodes = 0.5 / edges_number * item_i * node_i->second.getDegree() / nodes.size() * item_j * node_j->second.getDegree() / nodes.size();
        community_nodes = community_nodes + item_nodes; 
      }
    }
  }

  double modularity = 0.5 / edges_number * (2 * community_edges - community_nodes);

  return modularity;
}

double calculationExtendModularity(map<int, Node> nodes, vector<Edge> edges){
  const double edges_number = edges.size();
  double item_edges = 0, community_edges = 0;
  double item_nodes = 0, community_nodes = 0;

  //初始节点度 计算边权
  for(int i=0; i<edges_number; i++){
    nodes.find(edges[i].getNodeA())->second.addDegree();
    nodes.find(edges[i].getNodeB())->second.addDegree();

    vector<int> community_a = nodes.find(edges[i].getNodeA())->second.getTags();
    vector<int> community_b = nodes.find(edges[i].getNodeB())->second.getTags();
    set<int> community_ab;

    for(vector<int>::iterator item_a = community_a.begin(); item_a != community_a.end(); item_a++){ 
      community_ab.insert(*item_a); 
    }
    for(vector<int>::iterator item_b = community_b.begin(); item_b != community_b.end(); item_b++){ 
      community_ab.insert(*item_b); 
    }

    if(community_a.size() + community_b.size() > community_ab.size()){
      item_edges = 1.0 / community_a.size() / community_b.size();
      community_edges = community_edges + item_edges; 
    }
  }

  //计算节点权
  for(map<int,Node>::iterator node_i = nodes.begin(); node_i != nodes.end(); node_i++ ){
    for(map<int,Node>::iterator node_j = nodes.begin(); node_j != nodes.end(); node_j++ ){
      vector<int> community_a = node_i->second.getTags();
      vector<int> community_b = node_j->second.getTags();
      set<int> community_ab;

      for(vector<int>::iterator item_a = community_a.begin(); item_a != community_a.end(); item_a++){ 
        community_ab.insert(*item_a); 
      }
      for(vector<int>::iterator item_b = community_b.begin(); item_b != community_b.end(); item_b++){ 
        community_ab.insert(*item_b); 
      }

      if(community_a.size() + community_b.size() > community_ab.size()){
        item_nodes = 0.5 / edges_number * node_i->second.getDegree() / community_a.size() * node_j->second.getDegree() / community_b.size();
        community_nodes = community_nodes + item_nodes; 
      }
    }
  }

  double modularity = 0.5 / edges_number * (2 * community_edges - community_nodes);

  return modularity;
}
