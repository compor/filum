// ex001

#include <ios>
// using std::ios::unitbuf

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

#include <vector>
// using std::vector

#include <limits>
// using std::numeric_limits

#include <random>
// using std::uniform_int_distribution
// using std::default_random_engine


std::mt19937 g_gen;
std::uniform_int_distribution<unsigned int> g_dis{1, 10};
const std::size_t g_diners_num = 5;


void
ordered_out(const std::string &s) {
  static std::mutex g_ordered_out_mtx;

  std::lock_guard<std::mutex> lock(g_ordered_out_mtx);
  std::cout << s;

  return;
}


template<typename T>
using nl = std::numeric_limits<T>;

struct chopstick {
  std::unique_ptr<std::mutex> mtx;

  chopstick() : mtx(std::make_unique<std::mutex>()) {}
};

using dining_table_t = std::vector<chopstick>;


struct philosopher {
public:
  using utensil_id = std::size_t;

  philosopher(const std::string &name, std::shared_ptr<dining_table_t> table)
  : m_name(name), m_table(table),
  lhs_utensil(nl<utensil_id>::max()), rhs_utensil(nl<utensil_id>::max())
  {
    m_gen.seed(std::random_device()());
  }

  ~philosopher() = default;
  philosopher(const philosopher&) = default;
  philosopher &operator=(const philosopher&) = default;

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

  void dine() {
    auto pos1 = m_dis(m_gen) % m_table->size();
    (*m_table)[pos1].mtx->lock();
    lhs_utensil = pos1;

    std::stringstream ss;
    ss << m_name << " acquired: " << lhs_utensil << std::endl;
    ordered_out(ss.str());
    ss.str("");

    auto pos2 = (lhs_utensil + 1) % m_table->size();
    (*m_table)[pos2].mtx->lock();
    rhs_utensil = pos2;

    ss << m_name << " acquired: " << rhs_utensil << std::endl;
    ordered_out(ss.str());
    ss.str("");

    auto s = m_dis(m_gen) % 10 + 1;
    ss << m_name << " is dining for "<< s << "secs" << std::endl;
    ordered_out(ss.str());
    ss.str("");
    std::this_thread::sleep_for(std::chrono::seconds(s));

    (*m_table)[lhs_utensil].mtx->unlock();
    lhs_utensil = nl<utensil_id>::max();

    ss << m_name << " released: " << pos1 << std::endl;
    ordered_out(ss.str());
    ss.str("");

    (*m_table)[rhs_utensil].mtx->unlock();
    lhs_utensil = nl<utensil_id>::max();

    ss << m_name << " released: " << pos2 << std::endl;
    ordered_out(ss.str());
    ss.str("");

    return;
  }

private:
  std::string m_name;
  std::shared_ptr<dining_table_t> m_table;
  utensil_id lhs_utensil;
  utensil_id rhs_utensil;

  std::mt19937 m_gen;
  std::uniform_int_distribution<utensil_id> m_dis{0, 1000};
};


//

int main(int argc, const char *argv[]) {
  std::cout.setf(std::ios::unitbuf);
  g_gen.seed(std::random_device()());

  auto g_dining_table = std::make_shared<dining_table_t>(g_diners_num);

  for (const auto &d : *g_dining_table)
    g_dining_table->push_back(chopstick{});

  std::vector<philosopher> diners{
    philosopher("Xeno", g_dining_table),
    philosopher("Plato", g_dining_table),
    philosopher("Aristotle", g_dining_table),
    philosopher("Socrates", g_dining_table),
    philosopher("Marcus Aurelius", g_dining_table),
  };

  std::array<std::thread, g_diners_num> work;

  auto lucullan_feast = [](philosopher &p) { while (true) { p.dine(); } };

  for (auto i = 0; i < diners.size(); ++i)
    work[i] = std::thread{ lucullan_feast, std::ref(diners[i]) };

  std::for_each(work.begin(), work.end(), [](auto &t){t.join();});

  return 0;
}

