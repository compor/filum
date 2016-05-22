//

#include <iostream>
// using std::cout
// using std::endl

#include <thread>
// using std::thread
// using std::this_thread::sleep_for

#include <chrono>
using namespace std::chrono_literals;


void bar(unsigned int n) {
  std::cout << "n: " << n << std::endl;
}

void foo() {
  unsigned int n = 6;
  std::thread t1(&bar, std::ref(n));
  t1.detach(); // error
}


int main(int argc, const char *argv[])
{
  foo();
  std::this_thread::sleep_for(5s);

  return 0;
}

