    
#include "../header/filehandle.h"
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

vector<Edge> getCommunityEdges( string name ){
  const string edgepath = "dataset/unipartite/ProjectionTypeA_" + name +".txt";

  ifstream infile;
  string line;
  const char dilem = ',';
  vector<Edge> edgeCache;

  infile.open(edgepath, ios::in);
  if(!infile){ cout<< "file open error!" << edgepath <<endl; exit(1); }

  while(!infile.eof()){
    getline(infile, line);
    int linePos = 0;
    int lineSize = 0;
    string cache;
    vector<int> array;

    for(int i = 0 ; i < line.size(); i++){
      if(line[i] == dilem){
        lineSize = i - linePos;
        cache = line.substr(linePos, lineSize);
        array.push_back(stoi(cache));
        linePos = i+1;
      }
    }
    cache = line.substr(linePos, line.size() - linePos);
    if(cache.size()>0){ array.push_back(stoi(cache)); }

    //记录两人种类型节点数量并将解析的内容写入边对象缓存
    if(array.size() > 2){
      Edge item(array[1],array[2]);
      edgeCache.push_back(item);
    }
  }
  infile.close();

  return edgeCache;
}

map<int,Node> getNonOverlapCommunity( string mothed, string name ){
  const string split = "_";
  const string resultpath = "result/non_overlap/NonOverlapResult_" + mothed +split + name +".txt";

  ifstream infile;
  string line;
  const char dilem = '\t';
  map<int, Node> communityCache;
  map<int, Node>::iterator iter;

  //按行读取TXT文件，并解析
  infile.open(resultpath, ios::in);
  if(!infile){ cout<< "file open error!" << resultpath <<endl; exit(1); }

  while(!infile.eof()){
    getline(infile, line);
    int linePos = 0;
    int lineSize = 0;
    string cache;
    vector<int> array;

    for(int i = 0 ; i < line.size(); i++){
      if(line[i] == dilem){
        lineSize = i - linePos;
        cache = line.substr(linePos, lineSize);
        array.push_back(stoi(cache));
        linePos = i+1;
      }
    }
    cache = line.substr(linePos, line.size() - linePos);
    if(cache.size()>0){ array.push_back(stoi(cache)); }

    //记录两人种类型节点数量并将解析的内容写入边对象缓存
    if(array.size() > 1){
      iter = communityCache.find(array[0]);
      if(iter == communityCache.end()){
        Node item(array[0]);
        item.addListTag(array[1]);
        communityCache.insert(pair<int,Node>(array[0],item));
      }
    }
  }
  infile.close();

  return communityCache;
}

map<int,Node> getOverlapCommunity(string mothed, string name){
  const string split = "_";
  const string resultpath = "result/overlap/OverlapResult_" + mothed +split + name +".txt";

  ifstream infile;
  string line;
  const char dilem1 = ':';
  const char dilem2 = ' ';
  map<int, Node> communityCache;
  map<int, Node>::iterator iter;

  //按行读取TXT文件，并解析
  infile.open(resultpath, ios::in);
  if(!infile){ cout<< "file open error!" << resultpath <<endl; exit(1); }

  while(!infile.eof()){
    getline(infile, line);
    int linePos = 0;
    int lineSize = 0;
    string cache;
    vector<int> array;

    for(int i = 0 ; i < line.size(); i++){
      if(line[i] == dilem1 || line[i] == dilem2){
        lineSize = i - linePos;
        cache = line.substr(linePos, lineSize);
        array.push_back(stoi(cache));
        linePos = i+1;
      }
    }
    cache = line.substr(linePos, line.size() - linePos);
    if(cache.size()>0){ array.push_back(stoi(cache)); }

    //记录两人种类型节点数量并将解析的内容写入边对象缓存
    if(array.size() > 1){
      iter = communityCache.find(array[0]);
      if(iter == communityCache.end()){
        Node item(array[0]);
        for(int i=1; i<array.size(); i++){
          item.addListTag(array[i]);
        }
        communityCache.insert(pair<int,Node>(array[0],item));
      }
    }
  }
  infile.close();

  return communityCache;
}