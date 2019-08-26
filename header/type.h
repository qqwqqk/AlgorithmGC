#pragma once
#include <set>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

class Node{
  protected:
    int _id;
    int _degree;
    vector<int> _taglists;
  public:
    Node(int id = -1);
    ~Node(){};
    int getID();
    int getDegree();
    int getCommunityTag();
    vector<int> getCommunityList();
    void addDegree();
    void addListTag(int tag = -1);
};

class Edge{
  protected:
    int _node_a;
    int _node_b;
  public:
    Edge(int a = -1, int b = -2);
    ~Edge(){};
    int getNodeA();
    int getNodeB();
};
