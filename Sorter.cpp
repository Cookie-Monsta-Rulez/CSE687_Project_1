#include "sorter.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::map<std::string, std::vector<int>> Sorter::Aggregate(
    const std::string& input_path) {
  std::ifstream infile(input_path);
  if (!infile.is_open()) {
    throw std::runtime_error("Could not open intermediate file: " + input_path);
  }

  std::map<std::string, std::vector<int>> grouped;
  std::string line;
  while (std::getline(infile, line)) {
    std::stringstream ss(line);
    std::string key;
    std::string value_str;

    // Expecting format: key,value
    if (std::getline(ss, key, ',') && std::getline(ss, value_str)) {
      try {
        int value = std::stoi(value_str);
        grouped[key].push_back(value);
      } catch (...) {
        // Skip malformed lines.
      }
    }
  }

  infile.close();
  return grouped;
}

void Sorter::ExportAggregated(
    const std::map<std::string, std::vector<int>>& data,
    const std::string& output_path) {
  std::ofstream outfile(output_path);
  if (!outfile.is_open()) {
    throw std::runtime_error("Could not write to output: " + output_path);
  }

  for (const auto& [key, values] : data) {
    outfile << key << ",";
    for (size_t i = 0; i < values.size(); ++i) {
      outfile << values[i];
      if (i < values.size() - 1) {
        outfile << " ";
      }
    }
    outfile << "\n";
  }

  outfile.close();
}
