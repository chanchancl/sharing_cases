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
    v.push_back(std::thread([&](int id){
      try {
        for (int i=0; i < 10; i++) {
          cout << "thread" << id << " want to lock the mutex" << endl;
          {
            lock_guard<mutex> lock(m);
            if (i == 5 && id == 2)
              throw "Simulate an exception";
            local += 1;
          }
          cout << "thread" << id << " unlock the mutex" << endl;
        }
      } catch (...) {
        cout << "thread" << id << " meet a exception" << endl;
        return;
      }
    }, i));

  std::this_thread::sleep_for(std::chrono::seconds(2));

  for (auto& t : v) t.join();

  return 0;
}

