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

#include <functional>
// using std::ref


// example 1
void bar1(unsigned int &n) {
  ++n;
  std::cout << "m2 tid: " << std::this_thread::get_id();
  std::cout << "n: " << n << std::endl;
}


// example 2
struct qux {
  int num;
};

void bar2(qux &q) {
  std::cout << q.num << std::endl;
}


// example 3
struct foo_t {
  void m1() {
    m_call_cnt++;
    std::cout << "m1 tid: " << std::this_thread::get_id() << std::endl;
    std::cout << "m1 called with count: " << m_call_cnt << std::endl;
  }

  void m2(unsigned int &n) {
    ++n;
    std::cout << "m2 tid: " << std::this_thread::get_id() << std::endl;
    std::cout << "n: " << n << std::endl;
  }

  static unsigned m_call_cnt;
};

unsigned foo_t::m_call_cnt = 0u;



int main() {
  std::cout << "mn tid: " << std::this_thread::get_id() << std::endl;

  // example 1
  foo_t foo1;

  foo1.m1();
  std::thread t1(&foo_t::m1, &foo1);
  t1.detach();

  unsigned int n = 5;
  std::cout << "before t2 - n: " << n << std::endl;

  // example 1
  std::thread t2(&foo_t::m2, &foo1, std::ref(n));
  //std::thread t2(&foo_t::m2, &foo1, n); // error

  // example 2
  //std::thread t2(bar1, std::ref(n));
  //std::thread t2(bar1, n); // error

  // example 3
  //qux q{4};
  //std::thread t2(bar2, std::ref(q));

  t2.join();
  std::cout << "after t2 - n: " << n << std::endl;

  std::this_thread::sleep_for(3s);

  return 0;
}

