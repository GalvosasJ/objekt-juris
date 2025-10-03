#pragma once
#include <string>
#include <functional>

// Apskaičiuoja ND stulpelių skaičių iš failo antraštės
int detect_nd_columns(const std::string& header);

// Streaming būdu apdoroja studentų įrašus.
// Callback’ai leidžia atskirti į dvi grupes be visų duomenų laikymo atmintyje.
size_t process_students_streaming(
    const std::string& input_path,
    const std::function<double(const std::string&, int /*nd_cols*/ )>& line_to_final,
    const std::function<void(const std::string&, const std::string&, double)>& sink_low,
    const std::function<void(const std::string&, const std::string&, double)>& sink_high,
    double threshold,
    double& read_seconds,
    double& split_seconds,
    double& write_seconds
);
