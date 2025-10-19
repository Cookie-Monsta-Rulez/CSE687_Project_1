////////////////////////////////////
// David Zapata, Lorenzo Mujica, Sean Cooke
// Professor Scott Roueche
// CSE 687 - Object Oriented Design
// Syracuse University
// Phase 1 - MapReduce
// October 18, 2025
// Main.cpp file - Main source-code file to execute MapReduce workflow.

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <fstream>

// ==================== TEAM MODULES ====================
#include "FileManagement.h"  // Task 1 - File Management Class
#include "Map.h"             // Task 2 - Map Class
#include "Sorter.h"          // Task 3 - Sorting
#include "Reducer.h"         // Task 4 - Reducer

// ======================================================
// ================   WORKFLOW CLASS   ==================
// ======================================================

/**
 * @brief Orchestrates the entire MapReduce workflow.
 */
class Workflow {
public:
    Workflow(FileManagement* file_manager, Map* mapper)
        : file_manager_(file_manager), mapper_(mapper) {
    }

    /**
     * @brief Executes the full MapReduce process.
     *
     * @param input_dir Directory containing input text files.
     * @param temp_dir Directory for intermediate map outputs.
     * @param output_dir Directory for final reduced outputs.
     */
    void Execute(const std::string& input_dir,
        const std::string& temp_dir,
        const std::string& output_dir) {
        std::cout << "[*] Starting MapReduce workflow...\n";

        // Step 1: Gather input files
        file_manager_->initialize();
        std::vector<std::filesystem::path> files = file_manager_->inputFiles();
        if (files.empty()) {
            std::cerr << "[!] No input files found in: " << input_dir << "\n";
            return;
        }

        // Step 2: Map each file’s contents
        for (const auto& filePath : files) {
            std::cout << "  [MAP] Processing: " << filePath.string() << "\n";
            std::ifstream in = file_manager_->openFile(filePath);
            if (!in) {
                std::cerr << "[!] Failed to open input file: " << filePath.string() << "\n";
                continue;
            }

            std::string line;
            while (std::getline(in, line)) {
                mapper_->map(filePath.string(), line);
            }
        }

        // Step 3: Flush mapper’s buffer to intermediate files
        mapper_->finalize();

        // Step 4: Sort and aggregate intermediate data
        std::cout << "  [SORT] Aggregating intermediate results...\n";
        std::string aggregated_file = temp_dir + "/aggregated.txt";
        if (!Sorter::SortAndAggregate(temp_dir, aggregated_file)) {
            std::cerr << "[!] Sort phase failed.\n";
            return;
        }

        // Step 5: Reduce aggregated data
        std::cout << "  [REDUCE] Reducing aggregated results...\n";
        try {
            Reducer::ReduceAggregatedFile(aggregated_file, std::vector<int>{});
        }
        catch (const std::exception& ex) {
            std::cerr << "[!] Reduce phase failed: " << ex.what() << "\n";
            return;
        }
    }

private:
    FileManagement* file_manager_;
    Map* mapper_;
};

// ======================================================
// ================   EXECUTIVE CLASS   =================
// ======================================================

/**
 * @brief Parses command-line arguments and kicks off the workflow.
 */
class Executive {
public:
    int Run(int argc, char* argv[]) {
        if (argc < 4) {
            std::cerr << "Usage: " << argv[0]
                << " <input_dir> <temp_dir> <output_dir>\n";
            return 1;
        }

        std::string input_dir = argv[1];
        std::string temp_dir = argv[2];
        std::string output_dir = argv[3];

        // Create instances using the headers’ constructors
        FileManagement file_manager(input_dir, output_dir, temp_dir);
        Map mapper(file_manager);

        Workflow workflow(&file_manager, &mapper);
        workflow.Execute(input_dir, temp_dir, output_dir);

        return 0;
    }
};

// ======================================================
// ================       MAIN()       ==================
// ======================================================

/**
 * @brief Program entry point.
 */
int main(int argc, char* argv[]) {
    Executive exec;
    return exec.Run(argc, argv);
}
