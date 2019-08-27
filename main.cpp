#include "header/type.h"
#include "header/filehandle.h"
#include <iomanip>
#include <iostream>
using namespace std;

#define SETWIDTH1 15
#define SETWIDTH2 25

int main(){
  vector<string> nameLists = {"AC","MC","PA","WR"};
  vector<string> nonOverlapMothedLists = {"GC","InfoMAP","LPA","Walktrap"};
  vector<string> overlapMothedLists = {"GC","COPRA","SLPA","LFM"};

  string name = " ";
  string mothed = " ";

  for(int i=0; i<nameLists.size(); i++){
    cout << setiosflags(ios::fixed) << setiosflags(ios::left) << endl;

    name = nameLists[i];
    cout << setw(SETWIDTH1) << name << setw(SETWIDTH2) << "Edge Converting..." << endl << endl;
    getCommunityEdges( name );

    for(int j=0; j<nonOverlapMothedLists.size(); j++){
      mothed = nonOverlapMothedLists[j];
      cout << setw(SETWIDTH1) << mothed << setw(SETWIDTH2) << "non-overlap label converting..." << endl;
      getNonOverlapCommunity(mothed, name);
    }

    for(int j=0; j<overlapMothedLists.size(); j++){
      mothed = overlapMothedLists[j];
      cout << setw(SETWIDTH1) << mothed << setw(SETWIDTH2) << "overlap label converting..." << endl;
      getOverlapCommunity(mothed, name);
    }

  }

  return 0;
}
