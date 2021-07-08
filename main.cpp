// sensemaker1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "histogram.h"
#include "sensemaker.h"
#include "version.h"


int main (int argc, char** argv)
{
	std::cout << PROJECT_NAME << " /// " << PROJECT_VER << " /// (c) 2021 Axle Informatics" << std::endl;

	// Check the command line (it's primitive now)
	if (argc != 4)
	{
		showCmdlineHelp();
		return 1;
	}

	std::string dirIntens = argv[1], dirLabels = argv[2], dirOut = argv[3];

    std::cout << 
		"Using" << std::endl << "\t<intensity data directory> = " << dirIntens << std::endl << 
		"\t<labels data directory> = " << dirLabels << std::endl <<
		"\t<output directory> = " << dirOut << std::endl; 

	#ifdef SINGLE_ROI_TEST
	std::cout << std::endl << "Attention! Running the single-ROI test" << std::endl;
	#endif

	// Scan file names
	std::vector <std::string> intensFiles, labelFiles;
	int errorCode = checkAndReadDataset (dirIntens, dirLabels, dirOut, intensFiles, labelFiles);
	if (errorCode)
	{
		std::cout << std::endl << "Dataset structure error" << std::endl;
		return 1; 
	}

	// One-time initialization
	init_feature_buffers();

	// Process the image sdata
	errorCode = ingestDataset (intensFiles, labelFiles, 1 /*# of FastLoader threads*/, dirOut);

	// Check the error code 
	switch (errorCode)
	{
	case 0:		// Success
		break;
	case 1:		// Dataset structure error e.g. intensity-label file name mismatch
		std::cout << std::endl << "Dataset structure error" << std::endl;
		break;
	case 2:		// Internal FastLoader error e.g. TIFF access error
		std::cout << std::endl << "Dataset structure error" << std::endl;
		break;
	case 3:		// Memory error
		std::cout << std::endl << "Dataset structure error" << std::endl;
		break;
	default:	// Any other error
		std::cout << std::endl << "Error #" << errorCode << std::endl;
		break;
	}

	int exitCode = errorCode;
	return exitCode;
}

void showCmdlineHelp()
{
	std::cout 
		<< "Command line format:" << std::endl 
		<< "\t" << PROJECT_NAME << " <intensity directory> <label directory> <output directory>" << std::endl;
}


