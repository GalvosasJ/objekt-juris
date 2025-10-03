#include "../include/generator.h"
#include "../include/timer.h"
#include <random>
#include <fstream>
#include <stdexcept>

double generate_students_file(const GenOptions& opt) {
    std::mt19937 rng(opt.seed ? opt.seed : std::random_device{}());
    std::uniform_int_distribution<int> mark(1, 10);

    std::ofstream out(opt.out_path);
    if (!out) {
        throw std::runtime_error("Nepavyko atidaryti: " + opt.out_path);
    }

    // Antraštė
    out << "Pavarde Vardas";
    for (int i = 1; i <= opt.nd_count; ++i) {
        out << " ND" << i;
    }
    out << " Egz.\n";

    Tick t0;
    for (size_t i = 1; i <= opt.n_records; ++i) {
        out << "Pavarde" << i << ' ' << "Vardas" << i;
        for (int k = 0; k < opt.nd_count; ++k) {
            out << ' ' << mark(rng);
        }
        out << ' ' << mark(rng) << '\n';
    }
    out.flush();

    return seconds_since(t0);
}
