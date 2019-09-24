#include "../header/gravitycoefficient.h"
#include <cstdlib>
#include <math.h>
#include <iomanip>
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
  map<int,int> sub_i, sub_j, sub_ij;
  
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
      if(sub_i.find(node_tag) == sub_i.end()){ sub_i.insert(pair<int,int> (node_tag,1)); } 
      else { sub_i[node_tag] = sub_i[node_tag] + 1; }

      if(sub_ij.find(node_tag) == sub_ij.end()){ sub_ij.insert(pair<int,int> (node_tag,1)); } 
      else { sub_ij[node_tag] = sub_ij[node_tag] + 1; }
    }
    if(community_j.find(node_id) != community_j.end()){ 
      if(sub_j.find(node_tag) == sub_j.end()){ sub_j.insert(pair<int,int> (node_tag,1)); } 
      else { sub_j[node_tag] = sub_j[node_tag] + 1; }

      if(sub_ij.find(node_tag) == sub_ij.end()){ sub_ij.insert(pair<int,int> (node_tag,1)); } 
      else { sub_ij[node_tag] = sub_ij[node_tag] + 1; }
    }
  }
  
   //calculation item of community
  vector<double> moleculeList, denominatorList;
  for(map<int, int>::iterator iter_i = sub_i.begin(); iter_i != sub_i.end(); iter_i++){
    const int item_id = iter_i->first;
    if(sub_j.find(item_id) == sub_j.end()){
      denominatorList.push_back(1.0 * sub_i[item_id] / communitynumber_i);
    } else {
      double sub_item = 1.0 * sqrt(1.0 * sub_i[item_id] / communitynumber_i * sub_j[item_id] / communitynumber_j);
      moleculeList.push_back(sub_item);
    }
  }
  for(map<int,int>::iterator iter_j = sub_j.begin(); iter_j != sub_j.end(); iter_j++){
    const int item_id = iter_j->first;
    if(sub_i.find(item_id) == sub_i.end()){
      denominatorList.push_back(1.0 * sub_j[item_id] / communitynumber_j);
    }
  }

  //calculation community
  double M11 = accumulate(moleculeList.begin(), moleculeList.end(), 0.0);
  double M10_M01 = accumulate(denominatorList.begin(), denominatorList.end(), 0.0);
  double gravitycoefficient = 1.0 *  M11 / (M10_M01 + M11);

  return gravitycoefficient;
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

void printProgress(int iterationNumber, int communityNumber, double modularity){
  cout << "IterationNumber:" << setw(4) << iterationNumber << '\t';
  cout << "CommunityNumber:" << setw(4) << communityNumber << '\t';
  cout << "Modularity:" << setw(9) << setiosflags(ios::fixed) << setprecision(5) << modularity << '\t' << endl;
}
