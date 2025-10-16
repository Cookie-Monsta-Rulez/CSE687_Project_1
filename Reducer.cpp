#include "reducer.h"

#include <fstream>
#include <stdexcept>

void Reducer::SetOutputDir(const std::string& dir) {
  output_dir_ = dir;
}

void Reducer::Reduce(const std::string& key,
                     const std::vector<int>& values) {
  int sum = 0;
  for (int v : values) {
    sum += v;
  }
  ExportResult(key, sum);
}

void Reducer::ExportResult(const std::string& key, int reduced_value) {
  buffer_[key] = reduced_value;

  if (buffer_.size() >= kBufferLimit) {
    Flush();
  }
}

void Reducer::Flush() {
  std::ofstream outfile(output_dir_ + "/reduced_output.txt",
                        std::ios::app);
  if (!outfile.is_open()) {
    throw std::runtime_error("Could not write reduce output.");
  }

  for (const auto& [key, value] : buffer_) {
    outfile << key << "," << value << "\n";
  }

  outfile.close();
  buffer_.clear();

  // Write a SUCCESS marker file.
  std::ofstream success(output_dir_ + "/SUCCESS");
  success.close();
}
