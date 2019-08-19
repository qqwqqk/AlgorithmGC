#include "../header/slpa.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

int generateRandomNumber(int min, int max){
  srand(time(NULL));
  return rand() % (max - min) + min;
}

vector<int> findMode(vector<int> nums){
  vector<int> res;
  map<int,int> caches;
  int count = 0;
  for(int i=0;i<nums.size();i++){
    map<int,int>::iterator iter = caches.find(nums[i]);
    if(iter == caches.end()){
      caches.insert(pair<int,int> (nums[i],1));
    } else {
      int tag = iter->second + 1;
      iter->second = tag;
      if(tag == count){ res.push_back(iter->first); }
      if(tag > count){
        count = tag;
        res.clear();
        res.push_back(iter->first);
      }
    }
  }
  return res;
}

int calculationCommunityNumber(map<int,Node> nodes){
  set<int> communityCache;
  for(map<int,Node>::iterator iter_node = nodes.begin(); iter_node!=nodes.end(); iter_node++){
    int tag = iter_node->second.getCurrentTag();
    communityCache.insert(tag);
  }
  return communityCache.size();
}

map<int,Node> initializationCommunityNode(map<int,Node> nodes, vector<Edge> edges){
  for(int i=0; i<edges.size(); i++){
    nodes[edges[i].getNodeA()].addDegree();
    nodes[edges[i].getNodeB()].addDegree();
  }
  for(map<int,Node>::iterator iter = nodes.begin(); iter!=nodes.end(); iter++){
    iter->second.addTag(iter->first);  // iter->second.clrCaches();
  }
  return nodes;
}

map<int,Node> updateCommunityCaches(map<int,Node> nodes, vector<Edge> edges){
  for(int i=0; i<edges.size(); i++){
    const int node_a = edges[i].getNodeA();
    const int node_b = edges[i].getNodeB();

    const int tag_a = nodes[node_a].getCurrentTag();
    const int tag_b = nodes[node_b].getCurrentTag();

    nodes[node_a].addCaches(tag_b);
    nodes[node_b].addCaches(tag_a);
  }
  return nodes;
}

map<int,Node> updateCommunityTags(map<int,Node> nodes){
  for(map<int,Node>::iterator iter = nodes.begin(); iter != nodes.end(); iter++){
    vector<int> caches = iter->second.getCaches();
    vector<int> tags = findMode(caches);
    
    int length = tags.size();
    int index = generateRandomNumber(0, length);
    int tag = tags[index];

    iter->second.addTag(tag);
    iter->second.clrCaches();
  }
  return nodes;
}

map<int,Node> updateResult(map<int,Node> nodes, double threshold){
  for(map<int,Node>::iterator iter = nodes.begin(); iter != nodes.end(); iter++){
    iter->second.clrCaches();

    vector<int> lists = iter->second.getTags();
    const int count = lists.size();
    map<int,int> tags;

    for(int i=0; i<lists.size(); i++){
      map<int,int>::iterator iter_item = tags.find(lists[i]);
      if(iter_item == tags.end()){
        tags.insert(pair<int,int> (lists[i],1));
      } else {
        iter_item->second = iter_item->second + 1;
      }
    }

    for(map<int,int>::iterator iter_tag = tags.begin(); iter_tag != tags.end(); iter_tag++){
      if(count * threshold < iter_tag->second){
        iter->second.addCaches(iter_tag->first);
      }
    }
  }
  return nodes;
}
