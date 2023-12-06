#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <map>
#include <limits.h>
#include <math.h>

using namespace std;

void part1(ifstream &input) {
  string line;
  int i, j, k, ways, discriminant, res = 1;
  istringstream iss;
  vector<int> times, distances;

  // get times
  getline(input, line);
  line = line.substr(line.find(':') + 1);
  iss.str(line);

  while(iss >> i) times.push_back(i);

  // get distances
  getline(input, line);
  line = line.substr(line.find(':') + 1);
  iss.clear();
  iss.str(line);

  while(iss >> i) distances.push_back(i);

  for(i = 0; i < times.size(); i++) {
    ways = 0;

    /* no brute forcing today!
    for(j = 0; j < times[i]; j++) {
      if((j * (times[i] - j)) > distances[i]) ways++;
    }
    */

    /* quadratic solve `y = x(t_i - x) - d_i`
      -> `y = -x^2 + (t_i)x - d_i = 0`
      -> a = -1, b = t_i, c = -d_i ; (-b +- sqrt(b^2 - 4ac)) / (2a)
    */
    discriminant = times[i]*times[i] - 4*(-1)*(-distances[i]);
    if(discriminant >= 0) {
      // avoid equality by always rounding integers down/up respectively
      ways += (ceil(((-times[i] - sqrt(discriminant)) / (2*(-1))) - 1))
           - (floor(((-times[i] + sqrt(discriminant)) / (2*(-1))) + 1))
           + 1;
    }

    cout << ways << " ways" << endl;

    res *= ways;
  }

  cout << "answer: " << res << endl;
}

void part2(ifstream &input) {
  string line;
  int i, j, k, res = 0;
  istringstream iss;
  char c;
  string time = "", dist = "";
  long t, d, discriminant;

  // get times
  getline(input, line);
  line = line.substr(line.find(':') + 1);
  iss.str(line);

  while(iss >> c) {
    if(isdigit(c)) time += c;
    if(c == '\n') break;
  }

  // get distances
  getline(input, line);
  line = line.substr(line.find(':') + 1);
  iss.clear();
  iss.str(line);

  while(iss >> c) {
    if(isdigit(c)) dist += c;
    if(c == '\n') break;
  }

  cout << "time: " << time << ", distance: " << dist << endl;

  t = stol(time), d = stol(dist);

  /* no brute forcing today!
  for(i = 0; i < t; i++) {
    if((i * (t - i)) > d) res++;
  }
  */
  
  /* quadratic solve `y = x(t_i - x) - d_i`
    -> `y = -x^2 + (t_i)x - d_i = 0`
    -> a = -1, b = t_i, c = -d_i ; (-b +- sqrt(b^2 - 4ac)) / (2a)
  */
  discriminant = t*t - 4*(-1)*(-d);
  if(discriminant >= 0) {
    // avoid equality by always rounding integers down/up respectively
    res += (ceil(((-t - sqrt(discriminant)) / (2*(-1))) - 1))
        - (floor(((-t + sqrt(discriminant)) / (2*(-1))) + 1))
        + 1;
  }

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