#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

void part1(ifstream &input) {
  string line, game, handful, color;
  int i, res = 0, game_id = 1, num;
  unordered_map<string, int> freq;
  istringstream iss, iss2;

  while(getline(input, line)) {
    freq = {
      {"red",   0},
      {"green", 0},
      {"blue",  0},
    };

    line = line.substr(line.find(':') + 1);
    cout << line << endl;
    iss.clear();
    iss.str(line);

    while(getline(iss, game, ';')) {
      cout << "\t" << game << endl;
      iss2.clear();
      iss2.str(game);
      
      while(getline(iss2, handful, ',')) {
        cout << "\t\t" << handful << endl;
        char buf[6];
        sscanf(handful.c_str(), " %u %s", &num, buf);
        color = buf;
        cout << "\t\t" << "num: " << num << ", color: " << color << endl;
        freq[color] = max(freq[color], num);
      }
    }

    if(freq["red"] <= 12 && freq["green"] <= 13 && freq["blue"] <= 14) res += game_id;
    game_id++;
  }

  cout << res << endl;
}

void part2(ifstream &input) {
  string line, game, handful, color;
  int i, res = 0, game_id = 1, num;
  unordered_map<string, int> freq;
  istringstream iss, iss2;

  while(getline(input, line)) {
    freq = {
      {"red",   0},
      {"green", 0},
      {"blue",  0},
    };

    line = line.substr(line.find(':') + 1);
    cout << line << endl;
    iss.clear();
    iss.str(line);

    while(getline(iss, game, ';')) {
      cout << "\t" << game << endl;
      iss2.clear();
      iss2.str(game);

      while(getline(iss2, handful, ',')) {
        cout << "\t\t" << handful << endl;
        char buf[6];
        sscanf(handful.c_str(), " %u %s", &num, buf);
        color = buf;
        cout << "\t\t" << "num: " << num << ", color: " << color << endl;
        freq[color] = max(freq[color], num);
      }
    }

    res += freq["red"] * freq["green"] * freq["blue"];
    game_id++;
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