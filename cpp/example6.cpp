#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>
using namespace std;


int main() {
  int caught = 10;
  auto f = [&caught]() {
    cout << caught << endl;
  };
  caught += 5;
  f();

  return 0;
}
