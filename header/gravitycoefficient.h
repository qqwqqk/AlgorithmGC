#pragma once
#include "type.h"
#include <iostream>
using namespace std;

double calculationGravityCoefficient(vector<Edge> edges, char nodetype, int item_i = 0, int item_j = 0);

double calculationGravityCoefficient(map<int,Node> nodes, vector<Edge> edges, char nodetype, int item_i = 0, int item_j = 0);

map<int, int> calculationMergeList(vector<Link> links);

int calculationCommunityNumber(map<int,Node> nodes);

map<int, Node> calculationResult(vector<double> modularityCache, map<int,Node> nodes, vector<Edge> edges, char nodetype); 

void printProgress(int iterationNumber, int communityNumber, double modularity);
