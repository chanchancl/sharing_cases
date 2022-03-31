#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;


int main() {
  int caught = 10;
  [&caught](auto x) {
    caught += x;
  }(9);
  cout << caught << endl;

  return 0;
}
