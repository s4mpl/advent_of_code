#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

void part1(ifstream &input) {
  string line, calibration;
  int i, res = 0;

  while(getline(input, line)) {
    calibration = "";
    for(i = 0; i < line.size(); i++) {
      if(isdigit(line[i])) {
        calibration += line[i];
        break;
      }
    }
    for(i = line.size() - 1; i >= 0; i--) {
      if(isdigit(line[i])) {
        calibration += line[i];
        break;
      }
    }
    res += stoi(calibration);
  }

  cout << res << endl;
}

void part2(ifstream &input) {
  string line, calibration;
  int i, res = 0;

  unordered_map<string, string> digits = {
    {"one",   "1"},
    {"two",   "2"},
    {"three", "3"},
    {"four",  "4"},
    {"five",  "5"},
    {"six",   "6"},
    {"seven", "7"},
    {"eight", "8"},
    {"nine",  "9"},
  };

  while(getline(input, line)) {
    calibration = "";
    for(i = 0; i < line.size(); i++) {
      if(isdigit(line[i])) {
        calibration += line[i];
      } else {
        for(auto digit_pair : digits) {
          auto f = line.find(digit_pair.first);
          if(f != string::npos && f <= i) {
            calibration += digit_pair.second;
            break;
          }
        }
      }
      if(calibration.size() == 1) break;
    }
    for(i = line.size() - 1; i >= 0; i--) {
      if(isdigit(line[i])) {
        calibration += line[i];
      } else {
        for(auto digit_pair : digits) {
          auto f = line.rfind(digit_pair.first);
          if(f != string::npos && f >= i) {
            calibration += digit_pair.second;
            break;
          }
        }
      }
      if(calibration.size() == 2) break;
    }
    res += stoi(calibration);
  }

  cout << res << endl;
}

int main() {
  ifstream f;
  f.open("input.txt");

  part1(f);

  f.clear();
  f.seekg(0);
  
  part2(f);

  f.close();
  return 0;
}
