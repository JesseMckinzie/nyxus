//
// This file is a collection of drivers of tiled TIFF file scanning from the FastLoader side
//
#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem> 
  namespace fs = std::experimental::filesystem;
#else
  error "Missing the <filesystem> header."
#endif
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <array>
#ifdef WITH_PYTHON_H
#include <pybind11/pybind11.h>
#endif
#include "environment.h"
#include "globals.h"
#include "helpers/timing.h"
#include "python/pybind_vector.h"

// Sanity
#ifdef _WIN32
#include<windows.h>
#endif

namespace Nyxus
{
	bool processIntSegImagePairInMemory (const pybind_vector& intens, const pybind_vector& label)
	{
		std::vector<int> trivRoiLabels, nontrivRoiLabels;
		
		// Timing block (image scanning)
		{
			//______	STOPWATCH("Image scan/ImgScan/Scan/lightsteelblue", "\t=");

			{ STOPWATCH("Image scan2a/ImgScan2a/Scan2a/lightsteelblue", "\t=");

				// Phase 1: gather ROI metrics
				VERBOSLVL1(std::cout << "Gathering ROI metrics\n");
				std::cout << "before gather metrics" << std::endl;
				bool okGather = gatherRoisMetricsInMemory(intens, label);	// Output - set of ROI labels, label-ROI cache mappings

				LR& data = roiData[1];

				//std::cout << "----------- intensity data ---------:" << std::endl;
				//for (auto& px : data.raw_pixels)
				//{
				//	std::cout << px.inten << " ";
				//} std::cout << std::endl;

				if (!okGather)
					return false;
			}

			{ STOPWATCH("Image scan2b/ImgScan2b/Scan2b/lightsteelblue", "\t=");

					// Allocate each ROI's feature value buffer
				std::cout << "before initializing f vals" << std::endl;
				for (auto lab : uniqueLabels)
				{
					LR& r = roiData[lab];
					r.initialize_fvals();
				}

				// Dump ROI metrics
				//VERBOSLVL4(dump_roi_metrics(label_fpath))	// dumps to file in the output directory

			}

			{ STOPWATCH("Image scan3/ImgScan3/Scan3/lightsteelblue", "\t=");

				// Distribute ROIs among phases - only have trivial for in memory images
				for (auto lab : uniqueLabels)
				{
                    trivRoiLabels.push_back(lab);
				}
			}
		}

		// Phase 2: process trivial-sized ROIs
		if (trivRoiLabels.size())
		{
			VERBOSLVL1(std::cout << "Processing trivial ROIs\n";)
			std::cout << "before processing trivial rois" << std::endl;
			processTrivialRoisInMemory (trivRoiLabels, intens, label, theEnvironment.get_ram_limit());
		}
		std::cout << "here" << std::endl;
		return true;
	}

	int processDatasetInMemory(
		const pybind_vector& intens,
		const pybind_vector& label,
		int numReduceThreads,
		int min_online_roi_size,
		bool save2csv,
		const std::string& csvOutputDir)
	{
		std::cout << "Processing dataset in memory---------------------------" << std::endl;
		std::cout << "Processing dataset in memory---------------------------" << std::endl;
		bool ok = true;
		std::cout << "Processing dataset in memory123123123---------------------------" << std::endl;
		for (int i = 0; i < 1; i++)
		{
           
			#ifdef CHECKTIMING
			Stopwatch::reset();
			#endif
			std::cout << "Processing dataset in memory2---------------------------" << std::endl;
			// Clear ROI label list, ROI data, etc.
			clear_feature_buffers();

			// Cache the file names to be picked up by labels to know their file origin
			theSegFname = "Segmentation"; 
			theIntFname = "Intensity"; 
			std::cout << "Processing dataset in memory3---------------------------" << std::endl;

			
			ok = processIntSegImagePairInMemory (intens, label);		// Phased processing
			std::cout << "Processing dataset in memory4---------------------------" << std::endl;
			if (ok == false)	
			{
				std::cout << "processIntSegImagePair() returned an error code while processing file pair." << std::endl;
				return 1;
			}

			// Save the result for this intensity-label file pair
			std::cout << "save 2 csv: " << save2csv << std::endl;
			if (save2csv)
				ok = save_features_2_csv ("intensity", "label", csvOutputDir);
			else
				ok = save_features_2_buffer(theResultsCache);
			if (ok == false)
			{
				std::cout << "save_features_2_csv() returned an error code" << std::endl;
				return 2;
			}

			//theImLoader.close();

			#ifdef WITH_PYTHON_H
			// Allow heyboard interrupt.
			if (PyErr_CheckSignals() != 0)
						throw pybind11::error_already_set();
			#endif

			#ifdef CHECKTIMING
			// Detailed timing - on the screen
			VERBOSLVL1(Stopwatch::print_stats();)
				
			// Details - also to a file
			VERBOSLVL3(
				fs::path p(theSegFname);
				Stopwatch::save_stats(theEnvironment.output_dir + "/" + p.stem().string() + "_nyxustiming.csv");
			);
			#endif
            
        }

		return 0; // success
	}

	/*
	void dump_roi_metrics(const std::string & label_fpath)
	{
		fs::path pseg (label_fpath);
		std::string fpath = theEnvironment.output_dir + "/roi_metrics_" + pseg.stem().string() + ".csv";
		std::cout << "Dumping ROI metrics to " << fpath << " ...\n";

		std::ofstream f (fpath);

		// header
		f << "label, area, minx, miny, maxx, maxy, width, height, min_intens, max_intens, size_bytes, size_class \n";
		// sort labels
		std::vector<int>  sortedLabs { uniqueLabels.begin(), uniqueLabels.end() };
		std::sort(sortedLabs.begin(), sortedLabs.end());
		// body
		for (auto lab : sortedLabs)
		{
			LR& r = roiData[lab];
			auto szb = r.get_ram_footprint_estimate();
			std::string ovsz = szb < theEnvironment.get_ram_limit() ? "T" : "OVERSIZE";
			f << lab << ", "
				<< r.aux_area << ", "
				<< r.aabb.get_xmin() << ", "
				<< r.aabb.get_ymin() << ", "
				<< r.aabb.get_xmax() << ", "
				<< r.aabb.get_ymax() << ", "
				<< r.aabb.get_width() << ", "
				<< r.aabb.get_height() << ", "
				<< r.aux_min << ", "
				<< r.aux_max << ", "
				<< szb << ", "
				<< ovsz << ", ";
			f << "\n";
		}

		f.flush();
		std::cout << "... done\n";
	}
	*/

} 

