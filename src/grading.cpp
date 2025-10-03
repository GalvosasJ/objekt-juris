#include "../include/grading.h"
#include <algorithm>
#include <numeric>

double vidurkis(const std::vector<int>& nd) {
    if (nd.empty()) return 0.0;
    double suma = std::accumulate(nd.begin(), nd.end(), 0.0);
    return suma / nd.size();
}

double mediana(std::vector<int> nd) {
    if (nd.empty()) return 0.0;
    std::sort(nd.begin(), nd.end());
    size_t n = nd.size();
    if (n % 2 == 0) {
        return (nd[n/2 - 1] + nd[n/2]) / 2.0;
    } else {
        return nd[n/2];
    }
}
