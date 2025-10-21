# CSE 687 - Object Oriented Design Project: MapReduce Phase 1

## Overview
This project implements a **single-machine, command-line MapReduce workflow** in C++ for counting word frequencies across multiple text files. The program is designed to run as a single process (no threads or multiple processes) and demonstrates the MapReduce paradigm by reading input files, mapping words, sorting intermediate results, reducing counts, and producing an output file.

---

---

## Project Components

| Component | Description |
|-----------|-------------|
| **File Management Class** | Handles all file system interactions. Abstracts reading, writing, and buffering of data. |
| **Map Class** | Contains `map()` function to tokenize lines into words, normalize text, and call `export()` to store intermediate results in temporary directory. |
| **Sort / Aggregation** | Sorts intermediate key-value pairs and groups identical keys to prepare for reduce. |
| **Reduce Class** | Contains `reduce()` function to sum counts for each key and write final results to output directory. Calls `export()` to handle output. |
| **Workflow** | Connects the Map, Sort, and Reduce components to execute the entire word count workflow. |
| **Executive** | Handles command-line arguments, input/output/temporary directories, and triggers workflow execution. |

---

## Install

**Requires MinGW or similar compiler**

```
git clone https://github.com/Cookie-Monsta-Rulez/CSE687_Project_1.git
cd CSE687_Project_1
g++  -std=c++17 *.cpp -o MapReduce.exe
```
---

## Usage

### Command-line Arguments
.\CSE687_Project_1.exe <input_directory> <output_directory> <temporary_directory>

- `<input_directory>` – Directory containing text files to process.
- `<output_directory>` – Directory where the final results will be written.
- `<temporary_directory>` – Directory for storing intermediate results.
