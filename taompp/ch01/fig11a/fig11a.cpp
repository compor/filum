// fig 1.1

#include <iostream>
#include <map>
#include <thread>
#include <chrono>
#include <utility>

bool
is_prime(unsigned long int num) {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return false;
}


void print_prime(unsigned long int low, unsigned long int high) {
    if (low > high)
        return;

    std::cout << "worker thread id: " << std::this_thread::get_id() << std::endl;

    for (auto n = low; n < high; n++)
        if (is_prime(n))
            std::cout << n << std::endl;

    return;
}



int main(int argc, const char *argv[])
{
    auto hwcc = std::thread::hardware_concurrency();

    std::cout << "supported concurrent threads: " << hwcc << std::endl;

    std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;

    auto range = 80ul;
    auto part_range = range / hwcc;
    auto current_low = 0ul;
    auto current_high = 0ul;

    std::map<std::thread::id, std::thread> work_threads;

    for (auto i = 0u; i < hwcc; i++) {
        std::thread single_thread(print_prime, current_low, current_high);
        work_threads[ single_thread.get_id() ] = std::move(single_thread);

        current_low = current_high;
        current_high += part_range;
    }

    for (auto &k : work_threads)
        k.second.join();

    return 0;
}

