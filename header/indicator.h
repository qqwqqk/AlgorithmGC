#pragma once
#include "type.h"
#include <iostream>
using namespace std;

int calculationCommunityNumber(map<int,Node> nodes);

double calculationModularity(map<int,Node> nodes, vector<Edge> edges);

double calculationOverlapModularity(map<int, Node> nodes, vector<Edge> edges);

double calculationExtendModularity(map<int, Node> nodes, vector<Edge> edges);
