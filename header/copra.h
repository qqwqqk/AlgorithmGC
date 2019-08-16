#pragma once
#include "type.h"
#include <iostream>
using namespace std;

int generateRandomNumber(int min = 0, int max = 1);

int calculationCommunityNumber(map<int,Node> nodes);

map<int,Node> initializationCommunityNode(map<int,Node> nodes, vector<Edge> edges);

map<int,Node> updateCommunityCaches(map<int,Node> nodes, vector<Edge> edges);

map<int,Node> updateCommunityTags(map<int,Node> nodes, double threshold);