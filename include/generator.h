#pragma once
#include <string>
#include <cstddef>

struct GenOptions {
    size_t n_records;        // įrašų skaičius
    int nd_count = 5;        // ND kiekis
    unsigned seed = 0;       // 0 = naudoti random_device
    std::string out_path;    // sugeneruoto failo pavadinimas
};

// Sugeneruoja failą su studentų įrašais. Grąžina sugeneravimo laiką (sekundėmis).
double generate_students_file(const GenOptions& opt);
