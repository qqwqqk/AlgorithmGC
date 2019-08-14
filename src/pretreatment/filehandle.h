#pragma once
#include "../datastructure/type.h"
#include <iostream>
using namespace std;

Bipartite getBipartite(
  string name, 
  char intercept = 'A', 
  int number = -1, 
  bool connected = false, 
  bool sequence = false
);

Bipartite pretreatmentBipartite(
  string name, 
  char intercept = 'A', 
  int number = -1, 
  bool connected = false, 
  bool sequence = false
);

Unipartite getUnipartite(
  string name, 
  char intercept = 'A', 
  int number = -1, 
  bool connected = false, 
  bool sequence = false,
  char nodetype = 'A'
);

Unipartite pretreatmentUnipartite(
  string name, 
  char intercept = 'A', 
  int number = -1, 
  bool connected = false, 
  bool sequence = false,
  char nodetype = 'A'
);

map<int,Node> getOverlapCommunity(
  string name,
  char intercept = 'A', 
  int number = -1, 
  bool connected = false, 
  bool sequence = false,
  char nodetype = 'A'
);

void printProgress(
  int iterationNumber = 0, 
  int communityNumber = 0, 
  double modularity = 0.0
);

void printCommunity(
  map<int,Node> nodeCache,
  string name, 
  char intercept = 'A', 
  int number = -1, 
  bool connected = false, 
  bool sequence = false,
  char nodetype = 'A'
);

void printResult(
  map<int, Node> resultCache,
  double resultModularity
);
