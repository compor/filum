#include <condition_variable>
#include <mutex>

std::condition_variable cond;
bool data_ready;
std::mutex m;
void wait_for_data()
{
    std::unique_lock<std::mutex> lk(m);
    cond.wait(lk,[]{return data_ready;});
}

int main(int argc, const char *argv[])
{
  return 0;
}
