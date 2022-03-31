#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;


int main() {
  int a = [](auto x) {
     return x*x; 
  }(9);
  cout << a << endl;

  return 0;
}
