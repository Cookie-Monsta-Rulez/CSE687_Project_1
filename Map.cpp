////////////////////////////////////
// David Zapata
// Professor Scott Roueche
// CSE 687 - Object Oriented Design
// Syracuse University
// Phase 1 - MapReduce
// October 14, 2025
// Map.cpp file - Map base class source-code file to initialize and define member functions.

#include "Map.h"
#include <cctype>
#include <algorithm>

using std::string;
using std::vector;

// constructor initializes fileMgmt, interName, flushBytes
Map::Map(FileManagement& FileMgmt, string interFile, std::size_t flushBytes)
	: fileMgmt(FileMgmt), interName(std::move(interFile)), flushBytes(flushBytes)
{
	buffer.reserve(flushBytes + 1024);
} // end Map constructor

// function to tokenize input line into words
void Map::map(const string& key, const string& line)
{
	vector<string> tokens;
	tokens.reserve(32);
	tokenize(line, tokens);

	for (const auto& t : tokens)
	{
		exportData(t, "1");
	} // end for loop
} // end of map function

// function that takes data in memory gets written
void Map::finalize()
{
	flush();
} // end of finalize function

// function that removes punctuation, whitespace, and capitalization
void Map::tokenize(const string& line, vector<string>& out)
{
	out.clear();
	string current;
	current.reserve(32);

	auto push = [&]()
	{
		if (!current.empty())
		{
			std::transform(current.begin(), current.end(), current.begin(),
				[](unsigned char c) {return static_cast<char>(std::tolower(c)); });
			out.emplace_back(std::move(current));
			current.clear();
		} // end if
	}; // end push

	for (unsigned char ch : line)
	{
		if (std::isalnum(ch))
		{
			current.push_back(static_cast<char>(ch));
		} // end if
		else
		{
			push();
		} // end else
	} // end for

	push(); 

} // end of tokenize function

// function that exports key and value
void Map::exportData(const string& key, const string& line)
{
	if (key.empty())
		return;

	buffer.append(key);
	buffer.push_back('\t');
	buffer.append(line);
	buffer.push_back('\n');

	if (buffer.size() >= flushBytes)
	{
		flush();
	} // end if

} // end exportData function

// function to clear data from memory
void Map::flush()
{
	if (buffer.empty())
		return;

	auto out = fileMgmt.openTemp(interName);
	out.write(buffer.data(), static_cast<std::streamsize>(buffer.size()));
	if (!out)
	{
		throw std::runtime_error("Failed to write intermediate data to " + interName);
	} //  end if

	buffer.clear(); 

} // end flush function


