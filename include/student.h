#pragma once
#include <string>
#include <vector>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egzaminas = 0;
};

// Paprastesnis variantas dideliems failams (naudojamas streaming režime)
struct RowView {
    std::string vardas;
    std::string pavarde;
    double galutinis = 0.0;
};
