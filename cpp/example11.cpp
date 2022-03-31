#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include <algorithm>
#include <atomic>
#include <iomanip>
using namespace std;


int main() {
  int local = 0;
  std::vector<std::thread> v;
  std::mutex m;

  for(int i=0; i < 10; i++)
    v.push_back(std::thread([&](){
      for (int i=0; i < 10000; i++) {
        m.lock();
        local += 1;
        m.unlock();
      }
    }));

  for (auto& t : v) t.join();

  std::cout << local << std::endl;

  return 0;
}

