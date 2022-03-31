#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include <algorithm>
#include <atomic>
#include <iomanip>
using namespace std;

class test {
public:
  test() : exit(false) {}

  ~test() {
    exit = true;
    td.join();
  }

  void increment() {
    td = std::thread([this]() {
      while(!exit) {
        this->count++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
    });
  }

  bool wait() {
    if (count > 10) return true;
    return false;
  }

  std::atomic_int count;
  std::atomic_bool exit;
  std::thread td;
};


int main() {
  cout << fixed << setprecision(0);

  test t;
  auto start = std::chrono::system_clock::now();
  t.increment();
  while(!t.wait()) {
    cout << (std::chrono::system_clock::now() - start).count() << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  cout << "exit" << endl;

  return 0;
}
