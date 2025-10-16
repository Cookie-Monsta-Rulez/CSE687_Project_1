////////////////////////////////////
// David Zapata
// Professor Scott Roueche
// CSE 687 - Object Oriented Design
// Syracuse University
// Phase 1 - MapReduce
// October 14, 2025
// Map.h file - Header file to define the Map class definitions

#pragma once
#include <string>
#include <vector>
#include "FileManagement.h"

class Map
{
public:
	Map(FileManagement& FileMgmt, std::string interFile = "map-0.txt", std::size_t flushBytes = 512 * 1024);
	void map(const std::string& key, const std::string& line);
	void finalize();

private:
	static void tokenize(const std::string& line, std::vector<std::string>& out);
	void exportData(const std::string& key, const std::string& line);
	void flush();

private:
	FileManagement& fileMgmt;
	std::string interName;
	std::size_t flushBytes;
	std::string buffer;

}; // end of Map class