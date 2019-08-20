#pragma once
#include "type.h"
#include <iostream>
using namespace std;

map<int,Node> initializationCommunityNode(map<int,Node> nodes, vector<Edge> edges);

int generateSeedNode(map<int,Node> nodes);

set<int> generateCommunity(int seednode, double alpha, map<int,Node> nodes);

map<int,Node> updateNodeTags(int communitytag, set<int> communities, map<int,Node> nodes);

double calculationCommunityPercentage(map<int,Node> nodes);
