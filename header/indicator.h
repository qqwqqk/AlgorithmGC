#pragma once
#include "type.h"
using namespace std;

double calculationModularity(map<int,Node> nodes, vector<Edge> edges);

double calculationOverlapModularity(map<int, Node> nodes, vector<Edge> edges);

double calculationExtendModularity(map<int, Node> nodes, vector<Edge> edges);