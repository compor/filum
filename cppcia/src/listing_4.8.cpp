#include <string>
#include <vector>
#include <future>

namespace std {

template<>
class packaged_task<std::string(std::vector<char>*,int)>
{
public:
    template<typename Callable>
    explicit packaged_task(Callable&& f);
    std::future<std::string> get_future();
    void operator()(std::vector<char>*,int);
};

} // namespace std

int main(int argc, char *argv[])
{
  return 0;
}

