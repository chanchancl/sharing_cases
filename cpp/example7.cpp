#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include <algorithm>
using namespace std;

typedef struct {
  int time;
  int cost;
} road;


int main() {
  vector<road> v = {
    road{30,10},
    road{10,20},
    road{30,15},
    road{1,5},
    road{1,10},
    road{20,5},
  };

  sort(v.begin(), v.end(), [](const auto& a, const auto& b){
    if (a.time == b.time) return a.cost < b.cost;
    return a.time < b.time;
  });

  for (auto& r : v) {
    cout << "road : " << r.time << ", " << r.cost << endl;
  }

  return 0;
}
