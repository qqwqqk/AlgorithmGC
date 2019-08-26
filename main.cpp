#include "header/type.h"
#include "header/filehandle.h"
#include <iomanip>
#include <iostream>
using namespace std;

#define SETWIDTH 20

int main(){
  vector<string> nameLists = {"AC","MC","PA","WR"};
  vector<string> nonOverlapMothedLists = {"GC","InfoMAP","LPA","Walktrap"};
  vector<string> overlapMothedLists = {"GC","COPRA","SLPA","LFM"};

  string name = " ";
  string mothed = " ";

  for(int i=0; i<nameLists.size(); i++){

    name = nameLists[i];
    cout << name << "Edge Converting..." << endl;
    getCommunityEdges( name );

    for(int j=0; j<nonOverlapMothedLists.size(); j++){
      mothed = nonOverlapMothedLists[j];
      cout << mothed << "Label Converting..." << endl;
      getNonOverlapCommunity(mothed, name);
    }

    for(int j=0; j<overlapMothedLists.size(); j++){
      mothed = overlapMothedLists[j];
      cout << mothed << "Label Converting..." << endl;
      getOverlapCommunity(mothed, name);
    }

  }

  return 0;
}
