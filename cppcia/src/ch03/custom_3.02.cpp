//

#include <iostream>
// using std::cout
// using std::endl

#include <thread>
// using std::thread
// using std::this_thread::sleep_for

#include <chrono>

using namespace std::chrono_literals;


std::thread *pth1 = nullptr;
std::thread *pth2 = nullptr;


void foo1() {
  std::cout << "foo1\n";
  std::this_thread::sleep_for(3s);
  if (pth2) {
    std::cout << "join t2\n";
    pth2->join();
  }
  std::cout << "foo1 finishing\n";
  std::cout.flush();
}

void foo2() {
  std::cout << "foo2\n";
  std::this_thread::sleep_for(5s);
  if (pth1) {
    std::cout << "join t1\n";
    pth1->join();
  }
  std::cout << "foo2 finishing\n";
  std::cout.flush();
}

void ugly() {
  std::thread t1(&foo1);
  std::thread t2(&foo2);
  pth1 = &t1;
  pth2 = &t2;

  std::this_thread::sleep_for(10s);
}

int main() {
  std::thread t3(&ugly);
  t3.join();

  std::cout << "ugly things happening!\n";

  return 0;
}

