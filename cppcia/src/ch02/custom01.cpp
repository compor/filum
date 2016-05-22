//

#include <iostream>
// using std::cout
// using std::endl

#include <thread>
// using std::thread
// using std::this_thread::get_id
// using std::this_thread::sleep_for

#include <chrono>
using namespace std::chrono_literals;

#define WORKING_BY_LUCK


void foo1(unsigned int &n) {
  std::cout << "n: " << n << std::endl;
#ifndef WORKING_BY_LUCK
  std::this_thread::sleep_for(5s);
#endif
}


int main() {
#ifdef WORKING_BY_LUCK
  {
#endif
  unsigned int n = 6;
  std::thread t1(&foo1, std::ref(n));
  t1.detach();
#ifdef WORKING_BY_LUCK
  }
#endif

#ifdef WORKING_BY_LUCK
  std::this_thread::sleep_for(5s);
#endif

  return 0;
}

