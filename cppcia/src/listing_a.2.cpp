#include <memory>

/*struct my_class {
};

class move_only
{
    std::unique_ptr<my_class> data;
public:
    move_only() = default;
    move_only(const move_only&) = delete;
    move_only(move_only&& other):
        data(std::move(other.data))
    {}
    move_only& operator=(const move_only&) = delete;
    move_only& operator=(move_only&& other)
    {
        data=std::move(other.data);
        return *this;
    }
};
move_only m1;
move_only m2(m1);
move_only m3(std::move(m1));*/

int main(int argc, const char *argv[])
{
  return 0;
}
