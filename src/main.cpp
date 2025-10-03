#include "../include/generator.h"
#include "../include/io.h"
#include "../include/grading.h"
#include "../include/timer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Pagreitintas I/O
static struct FastIO { FastIO(){ std::ios::sync_with_stdio(false); std::cin.tie(nullptr);} } fastio;

// Apskaičiuoja galutinį balą iš vienos eilutės
static double compute_final_from_line(const std::string& line, int nd_cols, bool use_median) {
    std::istringstream iss(line);
    std::string pav, var;
    iss >> pav >> var;
    std::vector<int> nd;
    nd.reserve(nd_cols);
    for (int i = 0; i < nd_cols; i++) {
        int x; iss >> x;
        nd.push_back(x);
    }
    int egz; iss >> egz;
    double base = use_median ? mediana(nd) : vidurkis(nd);
    return 0.4 * base + 0.6 * egz;
}

static void print_usage(const char* prog) {
    std::cout <<
    "Naudojimas:\n"
    "  Generuoti failą:\n"
    "    " << prog << " gen <n> <out_path> [nd_count=5] [seed=0]\n\n"
    "  Padalinti studentus:\n"
    "    " << prog << " split <input> <out_base> [mode=vid|med] [threshold=5.0]\n\n"
    "  Bench režimas (1k, 10k, 100k, 1M, 10M):\n"
    "    " << prog << " bench [nd_count=5]\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 0;
    }

    std::string cmd = argv[1];
    try {
        if (cmd == "gen") {
            if (argc < 4) { print_usage(argv[0]); return 1; }
            size_t n = std::stoull(argv[2]);
            GenOptions opt;
            opt.n_records = n;
            opt.out_path = argv[3];
            opt.nd_count = (argc >= 5) ? std::stoi(argv[4]) : 5;
            opt.seed     = (argc >= 6) ? static_cast<unsigned>(std::stoul(argv[5])) : 0;

            double sec = generate_students_file(opt);
            std::cout << "[GEN] N=" << n << " -> " << opt.out_path
                      << " per " << sec << " s\n";
        }
        else if (cmd == "split") {
            if (argc < 4) { print_usage(argv[0]); return 1; }
            std::string in   = argv[2];
            std::string base = argv[3];
            std::string mode = (argc >= 5) ? argv[4] : "vid";
            double threshold = (argc >= 6) ? std::stod(argv[5]) : 5.0;
            bool use_median  = (mode == "med");

            std::ofstream out_low(base + "_vargsiukai.txt");
            std::ofstream out_high(base + "_kietiakiai.txt");
            if (!out_low || !out_high)
                throw std::runtime_error("Nepavyko sukurti išvesties failų");

            out_low  << "Vardas Pavarde Galutinis\n";
            out_high << "Vardas Pavarde Galutinis\n";

            double t_read, t_split, t_write;
            size_t n = process_students_streaming(
                in,
                [use_median](const std::string& line, int ndc){
                    return compute_final_from_line(line, ndc, use_median);
                },
                [&](const std::string& v, const std::string& p, double g){
                    out_low << v << ' ' << p << ' ' << g << '\n';
                },
                [&](const std::string& v, const std::string& p, double g){
                    out_high << v << ' ' << p << ' ' << g << '\n';
                },
                threshold, t_read, t_split, t_write
            );

            std::cout << "[SPLIT] " << in << " -> "
                      << base << "_vargsiukai.txt / " << base << "_kietiakiai.txt\n";
            std::cout << "         įrašų: " << n << "\n";
            std::cout << "         skaitymas: " << t_read  << " s\n";
            std::cout << "         dalinimas: " << t_split << " s\n";
            std::cout << "         rašymas:   " << t_write << " s\n";
        }
        else if (cmd == "bench") {
            int ndc = (argc >= 3) ? std::stoi(argv[2]) : 5;
            std::vector<size_t> sizes = {1000, 10000, 100000, 1000000, 10000000};

            for (auto n : sizes) {
                std::string src = "students_" + std::to_string(n) + ".txt";

                // 1) Generavimas
                double gen_s = generate_students_file(GenOptions{n, ndc, 0u, src});
                std::cout << "[GEN] N=" << n << " per " << gen_s << " s\n";

                // 2) Padalinimas
                std::ofstream out_low("students_" + std::to_string(n) + "_vargsiukai.txt");
                std::ofstream out_high("students_" + std::to_string(n) + "_kietiakiai.txt");

                out_low  << "Vardas Pavarde Galutinis\n";
                out_high << "Vardas Pavarde Galutinis\n";

                double t_read=0, t_split=0, t_write=0;
                auto count = process_students_streaming(
                    src,
                    [](const std::string& line, int ndc){
                        return compute_final_from_line(line, ndc, /*use median*/ false);
                    },
                    [&](const std::string& v, const std::string& p, double g){
                        out_low << v << ' ' << p << ' ' << g << '\n';
                    },
                    [&](const std::string& v, const std::string& p, double g){
                        out_high << v << ' ' << p << ' ' << g << '\n';
                    },
                    5.0, t_read, t_split, t_write
                );

                std::cout << "[SPLIT] N=" << count
                          << " read=" << t_read  << " s"
                          << " split=" << t_split << " s"
                          << " write=" << t_write << " s\n";
            }
        }
        else {
            print_usage(argv[0]);
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "KLAIDA: " << e.what() << "\n";
        return 2;
    }

    return 0;
}
