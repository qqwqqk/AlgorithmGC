#include "../header/type.h"
#include <string>
using std::string;

//节点类型基本的定义
Node::Node(int id){
  _id = id;
  _degree = 0;
  _taglists = vector<int>{};
}
int Node::getID(){
  return _id;
}
int Node::getDegree(){
  return _degree;
}
int Node::getCommunityTag(){
  return _taglists.back();
}
vector<int> Node::getCommunityList(){
  return _taglists;
}
void Node::addDegree(){
  _degree = _degree + 1;
}
void Node::addListTag(int tag){
  _taglists.push_back(tag);
}

//边类型基本的定义
Edge::Edge(int a, int b){
  _node_a = a; _node_b = b;
}
int Edge::getNodeA(){
  return _node_a;
}
int Edge::getNodeB(){
  return _node_b;
}
