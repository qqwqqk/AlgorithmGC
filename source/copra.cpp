#include "../header/copra.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

int generateRandomNumber(int min, int max){
  srand(time(NULL));
  return rand() % (max - min) + min;
}

int calculationCommunityNumber(map<int,Node> nodes){
  set<int> communityCache;
  for(map<int,Node>::iterator iter_node = nodes.begin(); iter_node!=nodes.end(); iter_node++){
    map<int,double> communitys = iter_node->second.getTags();
    for(map<int,double>::iterator iter_tag = communitys.begin(); iter_tag != communitys.end(); iter_tag++){
      communityCache.insert(iter_tag->first);
    }
  }
  return communityCache.size();
}

map<int,Node> initializationCommunityNode(map<int,Node> nodes, vector<Edge> edges){
  for(int i=0; i<edges.size(); i++){
    nodes[edges[i].getNodeA()].addDegree();
    nodes[edges[i].getNodeB()].addDegree();
  }

  for(map<int,Node>::iterator iter = nodes.begin(); iter!=nodes.end(); iter++){
    map<int,double> temp;
    temp.insert(pair<int,double>(iter->first, 1.0));
    iter->second.setTags(temp);
  }

  return nodes;
}

map<int,Node> updateCommunityCaches(map<int,Node> nodes, vector<Edge> edges){
  for(int i=0; i<edges.size(); i++){
    const int node_a = edges[i].getNodeA();
    const int node_b = edges[i].getNodeB();

    map<int,double> community_a = nodes[node_a].getTags();
    map<int,double> community_b = nodes[node_b].getTags();

    for(map<int,double>::iterator iter_b = community_b.begin(); iter_b != community_b.end(); iter_b++){
      double factor = 1.0 / nodes[node_a].getDegree();
      nodes[node_a].addCaches(iter_b->first, iter_b->second * factor);
    }
    for(map<int,double>::iterator iter_a = community_a.begin(); iter_a != community_a.end(); iter_a++){
      double factor = 1.0 / nodes[node_b].getDegree();
      nodes[node_b].addCaches(iter_a->first, iter_a->second * factor);
    }
  }

  return nodes;
}

map<int,Node> updateCommunityTags(map<int,Node> nodes, double threshold){
  for(map<int,Node>::iterator iter = nodes.begin(); iter != nodes.end(); iter++){
    map<int,double> list = iter->second.getCaches();
    map<int,double> tags;
    double count = 0.0;

    for(map<int,double>::iterator item = list.begin(); item != list.end(); item++){
      if(item->second >= threshold){
        tags.insert(pair<int,double> (item->first, item->second));
        count += item->second;
      }
    }
    for(map<int,double>::iterator item = tags.begin(); item != tags.end(); item++){
      item->second = item->second / count;
    }

    if(tags.size() < 1){
      int length = list.size();
      int index = generateRandomNumber(0,length);
      map<int,double>::iterator item = list.begin();
      while(index > 0){ item++; index--;}
      tags.insert(pair<int,double> (item->first, 1));
    }

    iter->second.setTags(tags);
    iter->second.clrCaches();
  }
  return nodes;
}
