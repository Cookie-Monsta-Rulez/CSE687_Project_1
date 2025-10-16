#ifndef SORTER_H_
#define SORTER_H_

#include <map>
#include <string>
#include <vector>

/**
 * @brief The Sorter class reads intermediate key-value pairs from disk,
 *        groups them by key, and can export the aggregated data for
 *        later reduction.
 */
class Sorter {
 public:
  /**
   * @brief Reads key-value pairs from an intermediate file and groups
   *        all values by key.
   *
   * @param input_path Path to the intermediate file.
   * @return A map where each key has an associated vector of integer values.
   *
   * @throws std::runtime_error if the file cannot be opened.
   */
  static std::map<std::string, std::vector<int>> Aggregate(
      const std::string& input_path);

  /**
   * @brief Exports grouped (key, [values...]) data to a file for reducer input.
   *
   * @param data Aggregated key-value collection.
   * @param output_path Destination file path.
   *
   * @throws std::runtime_error if the file cannot be opened for writing.
   */
  static void ExportAggregated(
      const std::map<std::string, std::vector<int>>& data,
      const std::string& output_path);
};

#endif  // SORTER_H_
