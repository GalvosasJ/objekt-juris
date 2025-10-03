#include "../include/io.h"
#include "../include/timer.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

int detect_nd_columns(const std::string& header) {
    std::istringstream iss(header);
    std::string token;
    int nd_cols = 0;
    while (iss >> token) {
        if (token.rfind("ND", 0) == 0) {
            ++nd_cols;
        }
    }
    return nd_cols;
}

size_t process_students_streaming(
    const std::string& input_path,
    const std::function<double(const std::string&, int)>& line_to_final,
    const std::function<void(const std::string&, const std::string&, double)>& sink_low,
    const std::function<void(const std::string&, const std::string&, double)>& sink_high,
    double threshold,
    double& read_seconds,
    double& split_seconds,
    double& write_seconds
) {
    using std::string;
    std::ifstream in(input_path);
    if (!in) {
        throw std::runtime_error("Nepavyko atidaryti: " + input_path);
    }

    string header;
    if (!std::getline(in, header)) {
        throw std::runtime_error("Tuščias failas: " + input_path);
    }
    int nd_cols = detect_nd_columns(header);

    size_t count = 0;
    string line;

    read_seconds = split_seconds = write_seconds = 0.0;

    while (true) {
        Tick t_read;
        if (!std::getline(in, line)) break;
        read_seconds += seconds_since(t_read);
        if (line.empty()) continue;

        // Paimam pavardę ir vardą
        std::istringstream iss(line);
        string pav, var;
        iss >> pav >> var;

        Tick t_split;
        double galutinis = line_to_final(line, nd_cols);
        bool high = galutinis >= threshold;
        split_seconds += seconds_since(t_split);

        Tick t_write;
        if (high) sink_high(var, pav, galutinis);
        else      sink_low(var, pav, galutinis);
        write_seconds += seconds_since(t_write);

        ++count;
    }

    return count;
}
