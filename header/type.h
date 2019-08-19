#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class Node{
  protected:
    int _id;
    int _degree;
    vector<int> _tags;
    vector<int> _caches;
  public:
    Node(int id = -1);
    ~Node(){};
    int getID();
    int getDegree();
    int getCurrentTag();
    vector<int> getTags();
    vector<int> getCaches();
    void addDegree();
    void addTag(int tag);
    void clrCaches();
    void addCaches(int tag);
};

class Edge{
  protected:
    int _node_a;
    int _node_b;
    double _weight;
  public:
    Edge(int a = -1, int b = -2);
    ~Edge(){};
    int getNodeA();
    int getNodeB();
    double getWeight();
    void setWeight(double weight);
};

class Unipartite{
  protected:
    string _name;
    map<int,Node> _nodes;
    vector<Edge> _edges;
  public:
    Unipartite(string name = "");
    ~Unipartite(){};
    string getName();
    map<int,Node> getNodes();
    vector<Edge> getEdges();
    void addNode(Node item = Node());
    void addEdge(Edge item = Edge());
};

class Bipartite{
  protected:
    string _name;
    map<int,Node> _nodes_a;
    map<int,Node> _nodes_b;
    vector<Edge> _edges;
  public:
    Bipartite(string name = "");
    ~Bipartite(){};
    string getName();
    map<int,Node> getNodesA();
    map<int,Node> getNodesB();
    vector<Edge> getEdges();
    void addNodeA(Node item = Node());
    void addNodeB(Node item = Node());
    void addEdge(Edge item = Edge());
};
