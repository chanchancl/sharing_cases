#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include <algorithm>
using namespace std;


int main() {
  vector<int> v_even = { 2, 4, 6, 8, 10};
  vector<int> v = {1,5 ,8 , 200, 105, 999};

  auto is_even = [](auto in) {
    return in % 2 == 0;
  };

  bool flag1 = std::all_of(v.begin(), v.end(), is_even);
  bool flag2 = std::all_of(v.begin(), v.end(), is_even);

  int num = std::count_if(v.begin(), v.end(), [](auto in){
    return in < 100;
  });

  cout << flag1 << endl
       << flag2 << endl
       << num   << endl;

  return 0;
}
