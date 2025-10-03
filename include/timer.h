#pragma once
#include <chrono>

struct Tick {
    std::chrono::high_resolution_clock::time_point t;
    Tick() : t(std::chrono::high_resolution_clock::now()) {}
};

// Grąžina kiek sekundžių praėjo nuo starto
double seconds_since(const Tick& start);
