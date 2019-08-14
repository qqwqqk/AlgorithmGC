#include "gravitycoefficient.h"
#include <cstdlib>
#include <math.h>
using namespace std;

double calculationGravityCoefficient(vector<Edge> edges, char nodetype, int item_i, int item_j){
  if(nodetype != 'A' && nodetype !='B'){ cout<<"Invalid node type input"<<endl; exit(1);}
  set<int> set_i, set_j, set_ij;
  for(int i=0; i<edges.size(); i++){
    const int node_id = nodetype != 'A' ? edges[i].getNodeA() : edges[i].getNodeB();
    const int node_tag = nodetype != 'A' ? edges[i].getNodeB() : edges[i].getNodeA();

    if(node_id == item_i){ set_i.insert(node_tag); set_ij.insert(node_tag); }
    if(node_id == item_j){ set_j.insert(node_tag); set_ij.insert(node_tag); }
  }
  double gravitycoefficient = 2.0 * ( set_i.size() + set_j.size() - set_ij.size()) / ( set_i.size() + set_j.size() );
  return gravitycoefficient;
}

double calculationGravityCoefficient(map<int,Node> nodes, vector<Edge> edges, char nodetype, int item_i, int item_j){
  if(nodetype != 'A' && nodetype !='B'){ cout<<"Invalid node type input"<<endl; exit(1);}
  set<int> community_i, community_j;
  set<int> sub_i, sub_j, sub_ij;
  
  //缓存community_i,community_j所属节点
  for(map<int, Node>::iterator iter=nodes.begin(); iter != nodes.end(); iter++){
    if(iter->second.getCommunityTag() == item_i){ community_i.insert(iter->first);}
    if(iter->second.getCommunityTag() == item_j){ community_j.insert(iter->first);}
  }
  const int communitynumber_i = community_i.size();
  const int communitynumber_j = community_j.size();

  //缓存sub_i,sub_j
  for(int i=0; i<edges.size(); i++){
    const int node_id = nodetype != 'A' ? edges[i].getNodeA() : edges[i].getNodeB();
    const int node_tag = nodetype != 'A' ? edges[i].getNodeB() : edges[i].getNodeA();
    if(community_i.find(node_id) != community_i.end()){ 
      sub_i.insert(node_tag); sub_ij.insert(node_tag);
    }
    if(community_j.find(node_id) != community_j.end()){ 
      sub_j.insert(node_tag); sub_ij.insert(node_tag);
    }
  }
  
  //calculation item of community
  vector<double> moleculeList, denominatorList;
  for(set<int>::iterator iter_i = sub_i.begin(); iter_i != sub_i.end(); iter_i++){
    const int item_id = *iter_i;
    if(sub_j.find(item_id) != sub_j.end()){
      moleculeList.push_back(1.0 * sub_i.count(item_id) / communitynumber_i);
      moleculeList.push_back(1.0 * sub_j.count(item_id) / communitynumber_j);

      // double sub_item = 1.0 * sqrt(1.0 * sub_i.count(item_id) / communitynumber_i * sub_j.count(item_id) / communitynumber_j);
      // moleculeList.push_back(sub_item);
    }
    denominatorList.push_back(1.0 * sub_i.count(item_id) / communitynumber_i);
  }
  for(set<int>::iterator iter_j = sub_j.begin(); iter_j != sub_j.end(); iter_j++){
    const int item_id = *iter_j;
    denominatorList.push_back(1.0 * sub_j.count(item_id) / communitynumber_j);
  }

  //calculation community
  double molecule = accumulate(moleculeList.begin(), moleculeList.end(), 0.0);
  double denominator = accumulate(denominatorList.begin(), denominatorList.end(), 0.0);
  //double factor = 1.0 * ( sub_i.size() + sub_j.size() - sub_ij.size()) / ( sub_ij.size() );
  double gravitycoefficient = molecule / denominator;

  return gravitycoefficient;
}

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

map<int, int> calculationMergeList(vector<Link> links){
  map<int,int> mergeList;
  double gravityMax = 0;

  for(int i=0; i<links.size(); i++){
    gravityMax = gravityMax > links[i].gravitycoefficient ? gravityMax : links[i].gravitycoefficient;
  }

  for(int i=0; i<links.size(); i++){
    if(links[i].gravitycoefficient == gravityMax){
      int node_a = links[i].community_a;
      int node_b = links[i].community_b;

      map<int, int>::iterator iter_a = mergeList.find(node_a);
      map<int, int>::iterator iter_b = mergeList.find(node_b);

      if(iter_a != mergeList.end() || iter_b != mergeList.end()){
        if(iter_a == mergeList.end()){
          mergeList.insert(pair<int, int> (node_a, iter_b->second));
        } else {
          mergeList.insert(pair<int, int> (node_b, iter_a->second));
        }
      } else {
        mergeList.insert(pair<int, int> (node_a, node_a));
        mergeList.insert(pair<int, int> (node_b, node_a));
      }
    }
  }
  return mergeList;
}

int calculationCommunityNumber(map<int,Node> nodes){
  set<int> communityCache;

  for(map<int, Node>::iterator iter = nodes.begin(); iter != nodes.end(); iter++){
    communityCache.insert(iter->second.getCommunityTag());
  }

  return communityCache.size();
}

map<int, Node> calculationResult(vector<double> modularityCache, map<int,Node> nodes, vector<Edge> edges, char nodetype){
  if(nodetype != 'A' && nodetype !='B'){ cout<<"Invalid node type input"<<endl; exit(1);}
  map<int, set<int>> communityCache;
  map<int, Node> resultCache;

  vector<double>::iterator modularityMax = std::max_element(begin(modularityCache), end(modularityCache));
  int modularityIndex = distance(begin(modularityCache), modularityMax);

  for(map<int, Node>::iterator iter_node = nodes.begin(); iter_node != nodes.end(); iter_node++){
    int communityTag = iter_node->second.getCommunityTag(modularityIndex);
    map<int, set<int>>::iterator iter_result = communityCache.find(communityTag);
    if(iter_result == communityCache.end()){
      set<int> cache = {iter_node->first};
      communityCache.insert(pair<int, set<int>> (communityTag, cache));
    } else {
      iter_result->second.insert(iter_node->first);
    }
  }

  for(map<int, set<int>>::iterator iter_tag = communityCache.begin(); iter_tag != communityCache.end(); iter_tag++){
    for(int i=0; i<edges.size();i++){
      int sourceID = nodetype != 'A' ? edges[i].getNodeA() : edges[i].getNodeB();
      int targetID = nodetype == 'A' ? edges[i].getNodeA() : edges[i].getNodeB();
      if(iter_tag->second.find(sourceID) != iter_tag->second.end()){
        map<int, Node>::iterator iter_temp = resultCache.find(targetID);
        if(iter_temp == resultCache.end()){
          Node cache(iter_tag->first);
          resultCache.insert(pair<int, Node> (targetID, cache));
        } else {
          vector<int> cache = iter_temp->second.getCommunityList();
          bool repeat = false;
          for(int i=0; i<cache.size(); i++){
            if(cache[i] == iter_tag->first){ repeat = true; break; }
          }
          if(!repeat){ iter_temp->second.addListTag(iter_tag->first); }
        } 
      }
    }
  }

  return resultCache;
}
