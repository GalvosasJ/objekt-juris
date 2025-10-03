#pragma once
#include <chrono>

struct Tick {
    std::chrono::high_resolution_clock::time_point t;
    Tick() : t(std::chrono::high_resolution_clock::now()) {}
};

inline double seconds_since(const Tick& start) {
    using namespace std::chrono;
    return duration<double>(high_resolution_clock::now() - start.t).count();
}
