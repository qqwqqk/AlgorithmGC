#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

struct Link{ 
  int community_a, community_b; 
  double gravitycoefficient; 
};

class Node{
  protected:
    int _id;
    int _degree;
    map<int,double> _tags;
    map<int,double> _caches;
  public:
    Node(int id = -1);
    ~Node(){};
    int getID();
    int getDegree();
    map<int,double> getTags();
    map<int,double> getCaches();
    void addDegree();
    void setTags(map<int,double> tags);
    void clrCaches();
    void addCaches(int tag, double proportion);
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
