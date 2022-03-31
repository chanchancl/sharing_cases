#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;


int main() {
  float a = []() { return 5; }();
  cout << a << endl;

  return 0;
}
