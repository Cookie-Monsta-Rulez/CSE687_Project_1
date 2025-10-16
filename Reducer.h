#ifndef REDUCER_H_
#define REDUCER_H_

#include <map>
#include <string>
#include <vector>

/**
 * @brief The Reducer class performs the reduction step in the MapReduce
 *        pipeline. It sums all intermediate values for each key and writes
 *        the results to disk. It buffers writes to avoid excessive I/O.
 */
class Reducer {
 public:
  /**
   * @brief Sets the directory where reduced results are written.
   *
   * @param dir Output directory path.
   */
  void SetOutputDir(const std::string& dir);

  /**
   * @brief Sums all integer values associated with a key and exports
   *        the result.
   *
   * @param key Word or identifier being reduced.
   * @param values Vector of integer values for this key.
   */
  void Reduce(const std::string& key, const std::vector<int>& values);

  /**
   * @brief Flushes any buffered results to disk and writes a SUCCESS file.
   *
   * @throws std::runtime_error if the output file cannot be opened.
   */
  void Flush();

 private:
  /**
   * @brief Buffers a reduced (key, sum) result and flushes if buffer
   *        exceeds the configured size limit.
   *
   * @param key Word or identifier being reduced.
   * @param reduced_value Final summed value for this key.
   */
  void ExportResult(const std::string& key, int reduced_value);

  std::map<std::string, int> buffer_;
  std::string output_dir_ = "./output";
  const size_t kBufferLimit = 100;
};

#endif  // REDUCER_H_
