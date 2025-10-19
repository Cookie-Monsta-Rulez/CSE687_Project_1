// Reducer.h (clean version)
#ifndef REDUCER_H_
#define REDUCER_H_

#include <string>
#include <vector>

class Reducer {
public:
    static void ReduceAggregatedFile(const std::string& aggregated_file,
        const std::vector<int>& dummyVec);
};

#endif  // REDUCER_H_
