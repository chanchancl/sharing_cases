#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;


int main() {
  int caught = 10;
  int a = [caught](auto x) {
    return caught * x;
  }(9);
  cout << a << endl;

  return 0;
}
