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

enum Type { HIGH, ONE, TWO, THREE, FULL, FOUR, FIVE };

auto camel_sort = [](const pair<string, int> &a, const pair<string, int> &b) {
  if(a.second == b.second) return a.first < b.first;
  return a.second < b.second;
};

void part1(ifstream &input) {
  string line, cards;
  int i, j, k, type, res = 0;
  istringstream iss;
  char buf[6];
  map<pair<string, int>, int, decltype(camel_sort)> hands(camel_sort);
  unordered_map<char, int> hand;

  while(getline(input, line)) {
    sscanf(line.c_str(), "%s %u\n", buf, &i);
    cards = buf;

    // substitute to match card strength with ASCII value
    replace(cards.begin(), cards.end(), 'A', 'E');
    replace(cards.begin(), cards.end(), 'K', 'D');
    replace(cards.begin(), cards.end(), 'Q', 'C');
    replace(cards.begin(), cards.end(), 'J', 'B');
    replace(cards.begin(), cards.end(), 'T', 'A');

    cout << cards << endl;

    hand.clear();
    type = HIGH;

    // determine hand strength
    for(char c : cards) hand[c]++;
    if(hand.size() == 1) {
      // five of a kind
      type = FIVE;
    } else if(hand.size() == 2) {
      auto num = hand.begin()->second;
      // four of a kind
      if(num == 4 || num == 1) type = FOUR;
      // full house
      else type = FULL;
    } else if(hand.size() == 3) {
      // pigeonhole principle!
      auto num1 = hand.begin()->second;
      auto num2 = (++hand.begin())->second;
      // two pair
      if(num1 == 2 || num2 == 2) type = TWO;
      // three of a kind
      else type = THREE;
    } else if(hand.size() == 4) {
      // one pair
      type = ONE;
    } else {} // high card

    hands.insert(make_pair(make_pair(cards, type), i));
  }
  cout << endl;

  i = 1;
  for(auto elem : hands) {
    cout << elem.first.first << " " << elem.first.second << " " << elem.second << endl;
    res += i++ * elem.second;
  }
  cout << endl;

  cout << "answer: " << res << endl;
}

void part2(ifstream &input) {
  string line, cards;
  int i, j, k, type, res = 0;
  istringstream iss;
  char buf[6];
  map<pair<string, int>, int, decltype(camel_sort)> hands(camel_sort);
  unordered_map<char, int> hand;

  while(getline(input, line)) {
    sscanf(line.c_str(), "%s %u\n", buf, &i);
    cards = buf;

    // substitute to match card strength with ASCII value
    replace(cards.begin(), cards.end(), 'A', 'E');
    replace(cards.begin(), cards.end(), 'K', 'D');
    replace(cards.begin(), cards.end(), 'Q', 'C');
    replace(cards.begin(), cards.end(), 'J', '1');
    replace(cards.begin(), cards.end(), 'T', 'A');

    cout << cards << endl;

    hand.clear();
    type = HIGH;

    // determine hand strength
    for(char c : cards) hand[c]++;
    auto f = hand.find('1');
    if(hand.size() == 1) {
      // five of a kind
      type = FIVE;
    } else if(hand.size() == 2) {
      if(f != hand.end()) {
        type = FIVE;
      } else {
        auto num = hand.begin()->second;
        // four of a kind
        if(num == 4 || num == 1) type = FOUR;
        // full house
        else type = FULL;
      }
    } else if(hand.size() == 3) {
      // pigeonhole principle!
      auto num1 = hand.begin()->second;
      auto num2 = (++hand.begin())->second;
      // two pair
      if(num1 == 2 || num2 == 2) {
        if(f != hand.end() && f->second == 1) type = FULL;
        else if(f != hand.end()) type = FOUR;
        else type = TWO;
      }
      // three of a kind
      else {
        if(f != hand.end()) type = FOUR;
        else type = THREE;
      }
    } else if(hand.size() == 4) {
      // one pair
      if(f != hand.end()) type = THREE;
      else type = ONE;
    } else {
      // high card
      if(f != hand.end()) type = ONE;
    }

    hands.insert(make_pair(make_pair(cards, type), i));
  }
  cout << endl;

  i = 1;
  for(auto elem : hands) {
    cout << elem.first.first << " " << elem.first.second << " " << elem.second << endl;
    res += i++ * elem.second;
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