////////////////////////////////////
// David Zapata
// Professor Scott Roueche
// CSE 687 - Object Oriented Design
// Syracuse University
// Phase 1 - MapReduce
// October 14, 2025
// CSE687_MapReduce.cpp file - "main" cpp file

#include "FileManagement.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char** argv)
{
	std::string in = (argc >= 2) ? argv[1] : "Data/input";
	std::string out = (argc >= 3) ? argv[2] : "Data/output";
	std::string temp = (argc >= 4) ? argv[3] : "Data/temp";

	try
	{
		FileManagement fileMgmt(in, out, temp);
		fileMgmt.initialize();

		Map mapper(fileMgmt, "map-0.txt", 512 * 1024);

		for (const auto& path : fileMgmt.inputFiles())
		{
			auto inFile = fileMgmt.openFile(path);
			std::string line;
			while (std::getline(inFile, line))
			{
				mapper.map(path.filename().string(), line);
			} // end while
		} // end for

		mapper.finalize();

		std::cout << "Mapping complete - Intermediate: " << (std::filesystem::path(temp) / "map-0.txt") << "\n";
		return 0;
	} // end try

	catch (const std::exception& ex)
	{
		std::cerr << "Uh Oh: " << ex.what() << "\n";
		return 1;
	} // end catch

} // end main
