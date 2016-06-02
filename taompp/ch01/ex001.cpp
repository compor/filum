// ex001

#include <iostream>
// using std::cout

#include <string>
// using std::string

#include <sstream>
// using std::stringstream

#include <thread>
// using std::thread
// using std::this_thread::sleep_for

#include <mutex>
// using std::mutex

#include <chrono>
using namespace std::chrono_literals;

#include <memory>
// using std::unique_ptr

#include <algorithm>
// using std::for_each

#include <functional>
// using std::ref

#include <array>
// using std::array

#include <limits>
// using std::numeric_limits

#include <random>
// using std::uniform_int_distribution
// using std::default_random_engine


std::mt19937 g_gen;
std::uniform_int_distribution<unsigned int> g_dis{1, 10};
const std::size_t g_diners_num = 5;

template<typename T>
using nl = std::numeric_limits<T>;

struct chopstick {
  std::unique_ptr<std::mutex> mtx;

  chopstick() : mtx(std::make_unique<std::mutex>()) {}
};

template<std::size_t N>
using dining_table_t = std::array<chopstick, N>;

dining_table_t<g_diners_num> g_dining_table{
  { chopstick(), chopstick(), chopstick(), chopstick(), chopstick() } };

struct philosopher {
public:
  using utensil_id = std::size_t;

  philosopher(const std::string &name, dining_table_t<g_diners_num> &table)
  : m_name(name), m_table(table),
  lhs_utensil(nl<utensil_id>::max()), rhs_utensil(nl<utensil_id>::max())
  {
    m_gen.seed(std::random_device()());
  }

  ~philosopher() = default;
  philosopher(const philosopher&) = default;
  philosopher &operator=(const philosopher&) = delete;

  bool is_dining() const {
    bool flag = (lhs_utensil != nl<utensil_id>::max()) &&
      (rhs_utensil != nl<utensil_id>::max());

    return flag;
  }

  bool is_thinking() const {
    return !is_dining();
  }

  utensil_id get_lhs_utensil() const { return lhs_utensil; }
  utensil_id get_rhs_utensil() const { return rhs_utensil; }

  const std::string &get_name() const { return m_name; }

  void acquire_utensils() {
    auto pos1 = m_dis(m_gen) % m_table.size();
    m_table[pos1].mtx->lock();
    lhs_utensil = pos1;

    auto pos2 = (lhs_utensil + 1) % m_table.size();
    m_table[pos2].mtx->lock();
    rhs_utensil = pos2;

    return;
  }

  void release_utensils() {
    //if (is_dining()) {
      m_table[lhs_utensil].mtx->unlock();
      lhs_utensil = nl<utensil_id>::max();

      m_table[rhs_utensil].mtx->unlock();
      lhs_utensil = nl<utensil_id>::max();
    //}

    return;
  }

private:
  std::string m_name;
  dining_table_t<g_diners_num> &m_table;
  utensil_id lhs_utensil;
  utensil_id rhs_utensil;

  std::mt19937 m_gen;
  std::uniform_int_distribution<utensil_id> m_dis{0, 1000};
};


//

int main(int argc, const char *argv[]) {
  g_gen.seed(std::random_device()());

  std::array<philosopher, g_diners_num> diners{ {
    philosopher("Xeno", g_dining_table),
    philosopher("Plato", g_dining_table),
    philosopher("Aristotle", g_dining_table),
    philosopher("Socrates", g_dining_table),
    philosopher("Marcus Aurelius", g_dining_table),
  } };

  std::array<std::thread, g_diners_num> work;

  auto fn = [](philosopher &p) {
    while (true) {
      p.acquire_utensils();

      std::stringstream ss;
      ss << p.get_name() << " acquired: " << p.get_lhs_utensil() << " and " << p.get_rhs_utensil();
      auto s = g_dis(g_gen);
      ss << " for "<< s << "secs";
      std::cout << ss.str() << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(s));

      std::cout << p.get_name() << " releasing" << std::endl;
      p.release_utensils();
    }
  };

  for (auto i = 0; i < diners.size(); ++i)
    work[i] = std::thread{ fn, std::ref(diners[i]) };

  std::for_each(work.begin(), work.end(), [](auto &t){t.join();});

  return 0;
}

