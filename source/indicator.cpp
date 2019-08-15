#include "../header/indicator.h"
#include <cstdlib>
#include <math.h>
using namespace std;

double calculationModularity(map<int,Node> nodes, vector<Edge> edges){
  const double edges_number = edges.size();
  double community_edge = 0, item_combination = 0, community_combination = 0;

  for(int i=0; i<edges_number; i++){
    int node_a_tag = nodes.find(edges[i].getNodeA())->second.getCommunityTag();
    int node_b_tag = nodes.find(edges[i].getNodeB())->second.getCommunityTag();
    if(node_a_tag == node_b_tag){ community_edge = community_edge + 1; }
  }

  for(map<int,Node>::iterator node_i = nodes.begin(); node_i != nodes.end(); node_i++ ){
    for(map<int,Node>::iterator node_j = nodes.begin(); node_j != nodes.end(); node_j++ ){
      if(node_i->second.getCommunityTag() == node_j->second.getCommunityTag()){ 
        item_combination = 0.5 / edges_number * node_i->second.getDegree() * node_j->second.getDegree();
        community_combination = community_combination + item_combination;
      }
    }
  }

  double modularity = 0.5 / edges_number * (2 * community_edge - community_combination);

  return modularity;
}

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

    vector<int> community_a = nodes.find(edges[i].getNodeA())->second.getCommunityList();
    vector<int> community_b = nodes.find(edges[i].getNodeB())->second.getCommunityList();
    set<int> community_ab;

    for(int i=0; i<community_a.size(); i++){ community_ab.insert(community_a[i]); }
    for(int i=0; i<community_b.size(); i++){ community_ab.insert(community_b[i]); }

    if(community_a.size() + community_b.size() > community_ab.size()){
      item_edges = functionStatisticalProbability(1/community_a.size(), 1/community_b.size());
      community_edges = community_edges + item_edges; 
    }
  }

  //计算节点权
  for(map<int,Node>::iterator node_i = nodes.begin(); node_i != nodes.end(); node_i++ ){
    for(map<int,Node>::iterator node_j = nodes.begin(); node_j != nodes.end(); node_j++ ){
      vector<int> community_a = node_i->second.getCommunityList();
      vector<int> community_b = node_j->second.getCommunityList();
      set<int> community_ab;

      for(int i=0; i<community_a.size(); i++){ community_ab.insert(community_a[i]); }
      for(int i=0; i<community_b.size(); i++){ community_ab.insert(community_b[i]); }

      if(community_a.size() + community_b.size() > community_ab.size()){
        double item_i = 0, item_j = 0;
        for(map<int,Node>::iterator node_k = nodes.begin(); node_k != nodes.end(); node_k++ ){
          item_i = item_i + functionStatisticalProbability(1/community_a.size(), 1/node_k->second.getCommunityList().size());
          item_j = item_j + functionStatisticalProbability(1/community_b.size(), 1/node_k->second.getCommunityList().size());
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

    vector<int> community_a = nodes.find(edges[i].getNodeA())->second.getCommunityList();
    vector<int> community_b = nodes.find(edges[i].getNodeB())->second.getCommunityList();
    set<int> community_ab;

    for(int i=0; i<community_a.size(); i++){ community_ab.insert(community_a[i]); }
    for(int i=0; i<community_b.size(); i++){ community_ab.insert(community_b[i]); }

    if(community_a.size() + community_b.size() > community_ab.size()){
      item_edges = 1.0 / community_a.size() / community_b.size();
      community_edges = community_edges + item_edges; 
    }
  }

  //计算节点权
  for(map<int,Node>::iterator node_i = nodes.begin(); node_i != nodes.end(); node_i++ ){
    for(map<int,Node>::iterator node_j = nodes.begin(); node_j != nodes.end(); node_j++ ){
      vector<int> community_a = node_i->second.getCommunityList();
      vector<int> community_b = node_j->second.getCommunityList();
      set<int> community_ab;

      for(int i=0; i<community_a.size(); i++){ community_ab.insert(community_a[i]); }
      for(int i=0; i<community_b.size(); i++){ community_ab.insert(community_b[i]); }

      if(community_a.size() + community_b.size() > community_ab.size()){
        item_nodes = 0.5 / edges_number * node_i->second.getDegree() / community_a.size() * node_j->second.getDegree() / community_b.size();
        community_nodes = community_nodes + item_nodes; 
      }
    }
  }

  double modularity = 0.5 / edges_number * (2 * community_edges - community_nodes);

  return modularity;
}
