#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <map>
#include <limits.h>

using namespace std;

void part1(ifstream &input) {
  string line;
  long i, j, k, map_idx, cur_num, res = LONG_MAX;
  istringstream iss;
  vector<long> seeds;
  vector<map<pair<long, long>, long>> maps(7);

  // get seeds
  getline(input, line);
  line = line.substr(line.find(':') + 1);
  iss.str(line);

  while(iss >> i) seeds.push_back(i);

  // get maps
  map_idx = 0;
  while(getline(input, line)) {
    if(!isdigit(line[0])) continue;

    iss.clear();
    iss.str(line);

    while(iss >> i >> j >> k) {
      maps[map_idx].insert(make_pair(make_pair(j, k), i));
      
      getline(input, line);
      iss.clear();
      iss.str(line);
    }
    
    map_idx++;
  }

  for(auto map : maps) {
    for(auto elem : map) {
      auto src = elem.first;
      auto dst = elem.second;
      cout << src.first << " " << src.second << " -> ";
      cout << dst << endl;
    }
    cout << endl;
  }

  // map seeds to locations
  cout << "mappings:" << endl;
  for(long seed : seeds) {
    cout << seed;
    cur_num = seed;
    for(i = 0; i < maps.size(); i++) {
      for(auto elem : maps[i]) {
        if(cur_num >= elem.first.first && cur_num < elem.first.first + elem.first.second) {
          cur_num = elem.second + (cur_num - elem.first.first);
          break;
        }
      }
      cout << " -> " << cur_num;
      // if not found, cur_num is already identity mapped and ready for the next map
    }
    cout << endl;

    res = min(res, cur_num);
  }
  cout << endl;

  cout << "answer: " << res << endl;
}

void part2(ifstream &input) {
  string line;
  long i, j, k, map_idx, cur_num, res = LONG_MAX;
  istringstream iss;
  vector<pair<long, long>> seeds;
  vector<map<pair<long, long>, long>> maps(7);

  // get seeds
  getline(input, line);
  line = line.substr(line.find(':') + 1);
  iss.str(line);

  while(iss >> i >> j) seeds.push_back(make_pair(i, j));

  // get maps
  map_idx = 0;
  while(getline(input, line)) {
    if(!isdigit(line[0])) continue;

    iss.clear();
    iss.str(line);

    while(iss >> i >> j >> k) {
      maps[map_idx].insert(make_pair(make_pair(j, k), i));
      
      getline(input, line);
      iss.clear();
      iss.str(line);
    }
    
    map_idx++;
  }

  for(auto map : maps) {
    for(auto elem : map) {
      auto src = elem.first;
      auto dst = elem.second;
      cout << src.first << " " << src.second << " -> ";
      cout << dst << endl;
    }
    cout << endl;
  }

  // map seeds to locations
  // cout << "mappings:" << endl;
  for(auto seed_pair : seeds) {
    cout << seed_pair.first << " " << seed_pair.second << endl;
    for(j = seed_pair.first; j < seed_pair.first + seed_pair.second; j++) {
      // cout << j;
      cur_num = j;
      for(i = 0; i < maps.size(); i++) {
        for(auto elem : maps[i]) {
          if(cur_num >= elem.first.first && cur_num < elem.first.first + elem.first.second) {
            cur_num = elem.second + (cur_num - elem.first.first);
            break;
          }
        }
        // cout << " -> " << cur_num;
        // if not found, cur_num is already identity mapped and ready for the next map
      }
      // cout << endl;

      res = min(res, cur_num);
    }
  }
  // cout << endl;

  cout << "answer: " << res << endl;
}

int main() {
  ifstream f;
  f.open("input.txt");

  part1(f);

  cout << endl;

  f.clear();
  f.seekg(0);

  part2(f);

  f.close();
  return 0;
}