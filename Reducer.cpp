#include "Reducer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

void Reducer::ReduceAggregatedFile(const std::string& aggregated_file, const std::vector<int>& /*dummyVec*/) {
    std::ifstream input(aggregated_file);
    if (!input.is_open()) {
        std::cerr << "[Reducer] Failed to open aggregated file: " << aggregated_file << "\n";
        return;
    }

    std::string output_dir = "./output";
    if (!fs::exists(output_dir)) {
        fs::create_directories(output_dir);
    }

    fs::path output_file = fs::path(output_dir) / "final_results.txt";
    std::ofstream output(output_file);
    if (!output.is_open()) {
        std::cerr << "[Reducer] Failed to create output file: " << output_file << "\n";
        return;
    }

    std::unordered_map<std::string, int> counts;
    std::string key;
    int value;

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        if (!(iss >> key >> value)) continue;
        counts[key] += value;
    }

    for (const auto& [k, v] : counts) {
        output << k << "\t" << v << "\n";
    }

    // Create SUCCESS flag file
    fs::path success_file = fs::path(output_dir) / "SUCCESS";
    std::ofstream success(success_file);
    success.close();

    std::cout << "[Reducer] Reduced output written to: " << output_file << std::endl;
}
