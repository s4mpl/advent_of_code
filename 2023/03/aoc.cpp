#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

void part1(ifstream &input) {
  string line, num;
  int i, j, n, m, res = 0;
  vector<string> schema;
  char k, around;
  bool is_part;

  while(getline(input, line)) {
    schema.push_back(line);
  }

  for(i = 0; i < schema.size(); i++) {
    for(j = 0; j < schema[0].size(); j++) {
      cout << schema[i][j];
    }
    cout << endl;
  }
  cout << endl;

  for(i = 0; i < schema.size(); i++) {
    for(j = 0; j < schema[0].size(); j++) {
      k = schema[i][j];
      num = "";
      is_part = false;
      
      if(k == '.') continue;
      if(isdigit(k)) {
        while(isdigit(schema[i][j]) && j < schema[0].size()) {
          num += schema[i][j];
          // check the 3 cells vertically to the left of the current number
          // skip check if already a confirmed part
          for(n = -1; n <= 1 && !is_part; n++) {
            if(i+n < 0 || i+n >= schema.size() || j-1 < 0) continue;
            around = schema[i+n][j-1];
            if(!isdigit(around) && around != '.') {
              is_part = true;
            }
          }
          j++;
        }
        // check last right 5 cells
        if(!is_part) {
          j--;
          for(m = 0; m <= 1; m++) {
            for(n = -1; n <= 1 && !is_part; n++) {
              if(i+n < 0 || i+n >= schema.size() || j+m >= schema[0].size()) continue;
              around = schema[i+n][j+m];
              if(!isdigit(around) && around != '.') {
                is_part = true;
              }
            }
          }
        }
      }

      if(is_part) {
        res += stoi(num);
      }
    }
  }

  cout << "total: " << res << endl;
}

void part2(ifstream &input) {
  string line, num;
  int i, j, n, m, res = 0;
  vector<string> schema;
  char k, around;
  bool is_part;
  unordered_map<int, vector<int>> adj;
  vector<int> cur_parts;

  while(getline(input, line)) {
    schema.push_back(line);
  }

  for(i = 0; i < schema.size(); i++) {
    for(j = 0; j < schema[0].size(); j++) {
      cout << schema[i][j];
      if(!isdigit(schema[i][j]) && schema[i][j] != '.') {
        adj.insert(make_pair((i*schema[0].size()+j), 0));
      }
    }
    cout << endl;
  }
  cout << endl;

  for(i = 0; i < schema.size(); i++) {
    for(j = 0; j < schema[0].size(); j++) {
      k = schema[i][j];
      num = "";
      is_part = false;
      cur_parts.clear();

      if(k == '.') continue;
      if(isdigit(k)) {
        while(isdigit(schema[i][j]) && j < schema[0].size()) {
          num += schema[i][j];
          // check the 3 cells vertically to the left of the current number
          for(n = -1; n <= 1; n++) {
            if(i+n < 0 || i+n >= schema.size() || j-1 < 0) continue;
            around = schema[i+n][j-1];
            if(!isdigit(around) && around != '.') {
              is_part = true;
              cur_parts.push_back((i+n)*schema[0].size()+(j-1));
            }
          }
          j++;
        }
        // check last right 5 cells
        if(!is_part) {
          j--;
          for(m = 0; m <= 1; m++) {
            for(n = -1; n <= 1; n++) {
              if(i+n < 0 || i+n >= schema.size() || j+m >= schema[0].size()) continue;
              around = schema[i+n][j+m];
              if(!isdigit(around) && around != '.') {
                is_part = true;
                cur_parts.push_back((i+n)*schema[0].size()+(j+m));
              }
            }
          }
        }
      }

      if(is_part) {
        cout << num << " adj to " << cur_parts.size() << " symbol(s):";
        for(auto part : cur_parts) {
          cout << " " << part;
          adj[part].push_back(stoi(num));
        }
        cout << endl;
      }
    }
  }

  cout << adj.size() << " symbols" << endl;
  for(auto symbol_pair : adj) {
    cout << symbol_pair.first << " with size " << symbol_pair.second.size() << endl;
    if(symbol_pair.second.size() == 2) {
      cout << symbol_pair.first << " with ratio " << symbol_pair.second[0] << " * " << symbol_pair.second[1] << endl;
      res += symbol_pair.second[0] * symbol_pair.second[1];
    }
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