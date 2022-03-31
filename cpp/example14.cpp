#include <iostream>
#include <assert.h>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include <algorithm>
#include <atomic>
#include <iomanip>
#include <queue>
#include <sstream>
#include <condition_variable>
using namespace std;

constexpr auto MaxItem = 10;

constexpr auto NumberOfProductor = 1;
constexpr auto NumberOfConsumer = 2;
constexpr auto ProduceSeconds = 1;
constexpr auto ConsumeSeconds = 2;

static std::mutex m_CoutMutex;
namespace my {
  struct cout
  {
    std::unique_lock<std::mutex> m_Lock;
    cout():
      m_Lock(std::unique_lock<std::mutex>(m_CoutMutex))
    {

    }

    template<typename T>
    cout& operator<<(const T& message)
    {
      std::cout << message;
      return *this;
    }

    cout& operator<<(std::ostream& (*fp)(std::ostream&))
    {
      std::cout << fp;
      return *this;
    }
  };
}

int main() {
  std::atomic_bool exit(false);

  std::queue<int> queue;
  std::mutex m;
  std::condition_variable condc, condp;

  std::vector<std::thread> v;

  // consumer
  for (int i = 0; i < NumberOfConsumer; i++) {
    v.push_back(std::thread([&](int id){
      while(!exit) {
        my::cout() << "consumer " << id << " get the lock" << endl;
        std::unique_lock<mutex> lock(m);
        while(queue.empty()) {
          my::cout() << "consumer " << id << " wait the condition" << endl;
          condc.wait(lock);
        }
        assert(!queue.empty());
        auto item = queue.front();
        queue.pop();
        my::cout() << "consumer " << id << " is awake, and consume item " << item << endl;
        lock.unlock();

        my::cout() << "consumer " << id << " notify producer to produce" << endl;
        condp.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(ConsumeSeconds));
      }
    }, i));
  }

  // producer
  for (int i = 0; i < NumberOfProductor; i++) {
    v.push_back(std::thread([&](int id){
      while(!exit) {
        my::cout() << "\tproducer " << id << " get the lock" << endl;
        std::unique_lock<mutex> lock(m);
        while(queue.size() >= MaxItem) {
          my::cout() << "\tproducer " << id << " wait the condition" << endl;
          condp.wait(lock);
        }
        assert(queue.size() < MaxItem);
        auto item = random();
        queue.push(item);
        lock.unlock();
        my::cout() << "\tproducer " << id << " is awake, and produce item " << item << endl;

        my::cout() << "\tproducer " << id << " notify consumer to consume" << endl;
        condc.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(ProduceSeconds));
      }
    }, i));
  }

  for (auto& t : v) t.join();

  return 0;;

}

