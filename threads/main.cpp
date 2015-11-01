//============================================================================
// Name        : C++11 - threads
// Author      : Luigi Briamonte
// Version     :
//============================================================================

#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::yield
#include <atomic>         // std::atomic
#include <mutex>          // std::mutex

std::atomic<bool> ready (false);
std::atomic<int> sum (0);
std::mutex mtx;           // mutex for critical section

void count1m(int id) {
  while (!ready) {             // wait until main() sets ready...
    std::this_thread::yield();
  }
  volatile int i=0;
  for (; i<10; ++i) {
      std::unique_lock<std::mutex> lck (mtx);
      std::cout << "thread " << id << "- counter = " << i << std::endl;
  }
  std::unique_lock<std::mutex> lck (mtx);
  std::cout << "thread " << id << " - counter = " << i << " - sum.is_lock_free() = " << std::boolalpha << sum.is_lock_free() << '\n';
  sum += i;
}

int main ()
{
  std::thread threads[10];
  std::cout << "race of 10 threads that count to 1 million:\n";
  for (int i=0; i<10; ++i) threads[i]=std::thread(count1m,i);
  ready = true;               // go!
  for (auto& th : threads) th.join();
  std::cout << sum << '\n';

  return 0;
}
