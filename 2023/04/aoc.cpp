#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;

void part1(ifstream &input) {
  string line;
  int i, points, res = 0;
  unordered_set<int> winning;
  istringstream iss;
  bool mul;

  while(getline(input, line)) {
    line = line.substr(line.find(':') + 1);
    winning.clear();
    iss.clear();
    iss.str(line);
    mul = false;
    points = 0;

    cout << line << endl;

    while(iss >> i) {
      winning.insert(i);
    }

    iss.clear();
    iss.get();

    while(iss >> i) {
      if(winning.find(i) != winning.end()) {
        if(mul) points *= 2;
        else {
          mul = true;
          points = 1;
        }
      }
    }

    cout << points << " points" << endl;
    res += points;
  }

  cout << "total: " << res << endl;
}

void part2(ifstream &input) {
  string line;
  int i, j, k, num, res = 0;
  unordered_set<int> winning;
  istringstream iss;
  vector<int> copies;
  vector<int> num_cards;

  while(getline(input, line)) {
    line = line.substr(line.find(':') + 1);
    winning.clear();
    iss.clear();
    iss.str(line);
    num = 0;

    cout << line << endl;

    while(iss >> i) {
      winning.insert(i);
    }

    iss.clear();
    iss.get();

    while(iss >> i) {
      if(winning.find(i) != winning.end()) {
        num++;
      }
    }

    copies.push_back(num);
  }

  num_cards.assign(copies.size(), 1);

  for(i = 0; i < num_cards.size(); i++) {
    for(j = 0; j < num_cards[i]; j++) {
      for(k = 0; k < copies[i]; k++) {
        if(i+k+1 >= num_cards.size()) break;
        num_cards[i+k+1]++;
      }
    }
  }

  for(i = 0; i < num_cards.size(); i++) {
    res += num_cards[i];
  }

  cout << "total: " << res << endl;
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