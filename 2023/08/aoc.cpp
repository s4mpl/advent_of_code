#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <map>
#include <limits.h>
#include <math.h>
#include <cstdio>
#include <algorithm>

using namespace std;

void part1(ifstream &input) {
  string line, directions, cur = "AAA";
  int i, j, k, res = 0;
  istringstream iss;
  unordered_map<string, pair<string, string>> network;
  char buf1[4], buf2[4], buf3[4];

  getline(input, directions);
  cout << directions << endl;
  getline(input, line); // consume blank line

  while(getline(input, line)) {
    sscanf(line.c_str(), "%3s = (%3s, %3s)\n", buf1, buf2, buf3);

    cout << buf1 << " -> " << "(" << buf2 << ", " << buf3 << ")" << endl;

    network.insert(make_pair(buf1, make_pair(buf2, buf3)));
  }
  cout << endl;

  for(i = 0;; i = (i + 1) % directions.size()) {
    auto f = network.find(cur)->second;
    cur = ((directions[i] == 'L') ? f.first : f.second);
    res++;
    if(cur == "ZZZ") break;
  }

  cout << "answer: " << res << endl;
}

void part2(ifstream &input) {
  string line, directions;
  long i, j, k, res = 0;
  istringstream iss;
  unordered_map<string, pair<string, string>> network;
  char buf1[4], buf2[4], buf3[4];
  vector<string> curs;
  unordered_set<string *> ends;

  getline(input, directions);
  cout << directions << endl;
  getline(input, line); // consume blank line

  while(getline(input, line)) {
    sscanf(line.c_str(), "%3s = (%3s, %3s)\n", buf1, buf2, buf3);

    cout << buf1 << " -> " << "(" << buf2 << ", " << buf3 << ")" << endl;

    network.insert(make_pair(buf1, make_pair(buf2, buf3)));
    if(buf1[2] == 'A') curs.push_back(buf1);
  }
  cout << endl;

  cout << "starting:";
  for(auto cur : curs) {
    cout << " " << cur;
  }
  cout << endl;

  for(i = 0;; i = (i + 1) % directions.size()) {
    for(string &cur : curs) {
      auto f = network.find(cur)->second;
      cur = ((directions[i] == 'L') ? f.first : f.second);
      if(cur.back() == 'Z') ends.insert(&cur);
      else ends.erase(&cur);
    }
    res++;

    // for(auto cur : curs) {
    //   cout << " " << cur;
    // }
    // cout << endl;

    if(curs.size() == ends.size()) break;
  }

  cout << "ending:";
  for(auto cur : curs) {
    cout << " " << cur;
  }
  cout << endl;

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