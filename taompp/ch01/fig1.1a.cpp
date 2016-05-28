// fig 1.1

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <utility>
#include <string>
#include <sstream>

bool
is_prime(unsigned long int num) {
  if (num < 2)
    return false;

  if (num <= 3)
    return true;

  if (num % 2 == 0 || num % 3 == 0)
    return false;

  int i = 5;
  while (i * i < num) {
    if (num % i == 0 || num % (i + 2) == 0)
      return false;

    i += 6;
  }

  return true;
}


void find_prime_range(unsigned long int low, unsigned long int high,
                      std::string &result) {
  if (low > high)
    return;

  auto tid = std::this_thread::get_id();
  unsigned long int nfound = 0;
  std::stringstream out;

  auto start = std::chrono::system_clock::now();

  for (auto n = low; n <= high; n++)
    if (is_prime(n))
      nfound++;

  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_secs = end - start;
  out << "tid: " << tid << " found: " << nfound << " primes ";
  out << "in: " << elapsed_secs.count() << "secs";
  result = out.str();

  return;
}



int main(int argc, const char *argv[]) {
  auto hwcc = std::thread::hardware_concurrency();
  std::cout << "supported concurrent threads: " << hwcc << std::endl;
  if (!hwcc)
    hwcc = 2;

  std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;

  auto start = std::chrono::system_clock::now();

  auto r = static_cast<unsigned long>(std::pow(10, 10));
  auto pr = r / hwcc;
  auto low = 1ul;
  auto high = pr;

  std::map<std::thread::id, std::thread> work_threads;
  std::vector<std::string> work_result(hwcc);

  for (auto i = 0u; i < hwcc; i++) {
    std::cout << "interval: [" << low << ", " << high << "]\n";

    std::thread t(find_prime_range, low, high, std::ref(work_result[i]));
    work_threads[ t.get_id() ] = std::move(t);

    low = high + 1;
    high += pr;
  }

  for (auto &k : work_threads)
    k.second.join();

  for(const auto &r : work_result)
    std::cout << r << std::endl;

  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_secs = end - start;
  std::cout << "total execution: " << elapsed_secs.count() << "secs\n";

  return 0;
}

