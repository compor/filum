#include <thread>
// using std::thread

#include <utility>
// using std::move


void foo() {
}

void bar() {
}

int main(int argc, const char *argv[])
{
  std::thread t1(foo);
  std::thread t2(bar);
  t1 = std::move(t2); // error - calls std::terminate
  t1.join();
  t2.join();

  return 0;
}
