#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main(){
  const string code = "ML";
  string readpath = "dataset/sourcedata/" + code + ".txt";
  string writepath = "dataset/metadata/Metadata_" + code + ".txt";

  ifstream infile;
  string line;
  const char dilem = ' ';

  //按行读取TXT文件，并解析
  infile.open(readpath, ios::in);
  if(!infile){ cout<< "open file error:\t" << readpath <<endl; exit(1); }

  ofstream outfile( writepath , ios::out);

  int count = 0;
  while(!infile.eof()){
    getline(infile, line);
    if(line.size() == 0){ break; }
    if(line[0] == '%'){ continue; }

    int linePos = 0;
    int lineSize = 0;
    string cache;
    vector<int> array;

    for(int i = 0 ; i < line.size(); i++){
      if(line[i] == dilem){
        lineSize = i - linePos;
        cache = line.substr(linePos, lineSize);
        array.push_back(stoi(cache));
        linePos = i+1;
      }
    }
    cache = line.substr(linePos, line.size() - linePos);
    if(cache.size()>0){ array.push_back(stoi(cache)); }

    // if(array.size() > 1)
    if(array.size() > 2 && array[2] > 4)
    {
      count++;
      cout << count << ',' << array[0] << ',' << array[1] << '\n';
      outfile << count << ',' << array[0] << ',' << array[1] << '\n';
    }
  }
  infile.close();
  outfile.close();

  return 0;
}