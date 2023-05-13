/* Result example (tested at https://www.onlinegdb.com/online_c++_compiler)

  if padding exists:
    Elapsed Time: 1.90473 seconds

  if no padding exists:
    Elapsed Time: 5.58251 seconds

*/

#include <iostream>
#include <thread>
#include <chrono>
#include <functional>

struct Pair {
    int x;
    char padding[64];  // Padding to avoid false sharing
    int y; // semantically independent to the x (processed independently by different cores)
};

Pair p {};

constexpr long long num_try = 500000000;

void incrementX() {
    for (int i = 0; i < num_try; ++i) {
        ++p.x;
    }
}

void incrementY() {
    for (int i = 0; i < num_try; ++i) {
        ++p.y;
    }
}


template <typename F>
void calcTime(F func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double elapsed_time = duration.count();
    std::cout << "Elapsed Time: " << elapsed_time << " seconds" << std::endl;
}

int main() {

    std::thread t1([]() { calcTime(incrementX); });
    std::thread t2([]() { calcTime(incrementY); });
    t1.join();
    t2.join();

    return 0;
}
