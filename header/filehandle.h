#pragma once
#include "type.h"
using namespace std;

vector<Edge> getCommunityEdges( string name );

map<int,Node> getNonOverlapCommunity( string mothed, string name );

map<int,Node> getOverlapCommunity( string mothed, string name );
