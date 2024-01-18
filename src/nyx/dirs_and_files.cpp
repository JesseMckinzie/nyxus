//
// Helper functions for manipulating directories and files
//

#include <fstream>
#include <string>
#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem> 
  namespace fs = std::experimental::filesystem;
#else
  error "Missing the <filesystem> header."
#endif

#include <vector>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <tiffio.h>
#include "dirs_and_files.h"
#include "strpat.h"
#include "helpers/helpers.h"

namespace Nyxus
{
	bool existsOnFilesystem(const std::string& dir)
	{
		fs::path p(dir);
		return fs::exists(p);
	}

	void readDirectoryFiles_2D (const std::string& dir, const std::string& file_pattern, std::vector<std::string>& files)
	{
		std::regex re(file_pattern);

		for (auto& entry : fs::directory_iterator(dir))
		{
			// Skip hidden objects, e.g. directories '.DS_store' in OSX
			if (entry.path().filename().string()[0] == '.')
			{
				std::cout << "Skipping " << entry.path().filename().string() << "\n";
				continue; 
			}

			std::string fullPath = entry.path().string(),
				pureFname = entry.path().filename().string();
			
			if (std::regex_match(pureFname, re))
				files.push_back(fullPath);
		}
	}

	int read_2D_dataset (
		// input
		const std::string& dirIntens, 
		const std::string& dirLabels, 
		const std::string& filePatt,
		const std::string& dirOut, 
		const std::string& intLabMappingDir, 
		const std::string& intLabMappingFile,
		bool mustCheckDirOut,
		// output
		std::vector <std::string>& intensFiles, 
		std::vector <std::string>& labelFiles)
	{
		// Check directories

		if (!existsOnFilesystem(dirIntens))
		{
			std::cout << "Error: nonexisting directory " << dirIntens << std::endl;
			return 1;
		}
		if (!existsOnFilesystem(dirLabels))
		{
			std::cout << "Error: nonexisting directory " << dirLabels << std::endl;
			return 1;
		}
		if (!existsOnFilesystem(dirOut))
		{
			std::cout << "Error: nonexisting directory " << dirOut << std::endl;
			return 1;
		}

		if (intLabMappingFile.empty())
		{
			// Common case - no ad hoc intensity-label file mapping, 1-to-1 correspondence instead
			readDirectoryFiles_2D (dirIntens, filePatt, intensFiles);
			readDirectoryFiles_2D (dirLabels, filePatt, labelFiles);

			// Check if the dataset is meaningful
			if (intensFiles.size() == 0 || labelFiles.size() == 0)
			{
				std::cout << "No intensity and/or label files to process, probably due to file pattern " << filePatt << std::endl;
				return 2;
			}
			if (intensFiles.size() != labelFiles.size())
			{
				std::cout << "Mismatch: " << intensFiles.size() << " intensity images vs " << labelFiles.size() << " mask images\n";
				return 3;
			}

			// Sort the files to produce an intuitive sequence
			std::sort(intensFiles.begin(), intensFiles.end());
			std::sort(labelFiles.begin(), labelFiles.end());
		}
		else
		{
			// Special case - using intensity and label file pairs defined with the mapping file
			if (!existsOnFilesystem(intLabMappingDir))
			{
				std::cout << "Error: nonexisting directory " << intLabMappingDir << std::endl;
				return 1;
			}

			std::string mapPath = intLabMappingDir + "/" + intLabMappingFile;
			if (!existsOnFilesystem(mapPath))
			{
				std::cout << "Error: nonexisting file " << mapPath << std::endl;
				return 1;
			}		

			// Read 
			std::ifstream file(mapPath);
			std::string ln, intFile, segFile;
			int lineNo = 1;
			while (std::getline(file, ln))
			{
				std::stringstream ss(ln);
				std::string intFname, segFname;
				bool pairOk = ss >> intFname && ss >> segFname;
				if (!pairOk)
				{
					std::cout << "Error: cannot recognize a file name pair in line #" << lineNo << " - " << ln << std::endl;
					return 1;
				}

				// We have a pair of file names. Let's check if they exist
				lineNo++;
				std::string intFpath = dirIntens + "/" + intFname;
				if (!existsOnFilesystem(intFpath))
				{
					std::cout << "Error: nonexisting file " << intFpath << std::endl;
					return 1;
				}

				std::string segFpath = dirLabels + "/" + segFname;
				if (!existsOnFilesystem(intFpath))
				{
					std::cout << "Error: nonexisting file " << intFpath << std::endl;
					return 1;
				}

				// Save the file pair
				intensFiles.push_back (intFpath);
				labelFiles.push_back (segFpath);
			}

			// Check if we have pairs to process
			if (intensFiles.size() == 0)
			{
				std::cout << "Special mapping " << mapPath << " produced no intensity-label file pairs" << std::endl;
				return 1;
			}

			// Inform the user
			std::cout << "Using special mapped intensity-label pairs:" << std::endl;
			for (int i = 0; i < intensFiles.size(); i++)
				std::cout << "\tintensity: " << intensFiles[i] << "\tlabels: " << labelFiles[i] << std::endl;
		}

		return 0; // success
	}

	std::string getPureFname(const std::string& fpath)
	{
		fs::path p(fpath);
		return p.filename().string();
	}

	// Helper function to determine Tile Status
	bool check_tile_status(const std::string& filePath)
	{
		TIFF* tiff_ = TIFFOpen(filePath.c_str(), "r");
		if (tiff_ != nullptr)
		{
			if (TIFFIsTiled(tiff_) == 0)
			{
				TIFFClose(tiff_);
				return false;
			}
			else
			{
				TIFFClose(tiff_);
				return true;
			}
		}
		else { throw (std::runtime_error("Tile Loader ERROR: The file can not be opened.")); }
	}


	
	bool readDirectoryFiles_3D (const std::string & dir, const StringPattern & filePatt, std::vector <Imgfile3D_layoutA> & files)
	{
		// grammar is OK to read data
		std::map<std::string, std::vector<std::string>> imgDirs;

		for (auto& fpath : fs::directory_iterator(dir))
		{
			// Skip hidden objects, e.g. directories '.DS_store' in OSX
			if (fpath.path().filename().string()[0] == '.')
				continue;

			std::string fullPath = fpath.path().string(),
				pureFname = fpath.path().filename().string();

			std::string ermsg;
			if (!filePatt.match(pureFname, imgDirs, ermsg))
			{
				std::cerr << "Error parsing file name " << pureFname << ": " << ermsg << '\n';
				break;
			}

		} //- directory scan loop

		// copy the file info to the external container
		files.clear();
		size_t i = 0;
		for (const auto & x : imgDirs)
		{
			Nyxus::Imgfile3D_layoutA img3;
			img3.fname = x.first;	// image name
			img3.z_indices = x.second;	// z-indices as they are in corresponding file names
			files.push_back(img3);
		}

		return true;
	}

	int read_3D_dataset(
		// input:
		const std::string& dirIntens,
		const std::string& dirLabels,
		const StringPattern& filePatt,
		const std::string& dirOut,
		const std::string& intLabMappingDir,
		const std::string& intLabMappingFile,
		bool mustCheckDirOut,
		// output:
		std::vector <Imgfile3D_layoutA>& intensFiles,
		std::vector <Imgfile3D_layoutA>& labelFiles)
	{
		if (!existsOnFilesystem(dirIntens))
		{
			std::cout << "Error: nonexisting directory " << dirIntens << std::endl;
			return 1;
		}
		if (!existsOnFilesystem(dirLabels))
		{
			std::cout << "Error: nonexisting directory " << dirLabels << std::endl;
			return 1;
		}
		if (!existsOnFilesystem(dirOut))
		{
			std::cout << "Error: nonexisting directory " << dirOut << std::endl;
			return 1;
		}

		// Common case - no ad hoc intensity-label file mapping, 1-to-1 correspondence instead
		if (!readDirectoryFiles_3D(dirIntens, filePatt, intensFiles))
		{
			std::cerr << "Error reading directory " << dirIntens << '\n';
			return 1;
		}
		if (!readDirectoryFiles_3D (dirLabels, filePatt, labelFiles))
		{
			std::cerr << "Error reading directory " << dirLabels << '\n';
			return 1;
		}

		// Check if the dataset isn't blank
		if (intensFiles.size() == 0 || labelFiles.size() == 0)
		{
			std::cout << "No intensity and/or label file pairs to process, probably due to file pattern " << filePatt.get_cached_pattern_string() << std::endl;
			return 2;
		}

		// Shallow consistency check 
		if (intensFiles.size() != labelFiles.size())
		{
			std::cout << "Mismatch: " << intensFiles.size() << " intensity images vs " << labelFiles.size() << " mask images\n";
			return 3;
		}

		// Deep consistency check 
		auto nf = intensFiles.size();
		for (auto i = 0; i < nf; i++)
		{
			auto& file_i = intensFiles[i],
				& file_m = labelFiles[i];

			// name mismatch ?
			if (file_i.fname != file_m.fname)
			{
				std::cerr << "Mismatch: intensity " << file_i.fname << " mask " << file_m.fname << '\n';
				return 3;
			}

			// z-stack size mismatch ?
			if (file_i.z_indices.size() != file_m.z_indices.size())
			{
				std::cerr << "Z-stack size mismatch: intensity " << file_i.z_indices.size() << " mask " << file_m.z_indices.size() << '\n';
				return 3;
			}

			// z-stack indices mismatch ?
			std::sort (file_i.z_indices.begin(), file_i.z_indices.end());
			std::sort (file_m.z_indices.begin(), file_m.z_indices.end());
			for (auto j=0; j< file_i.z_indices.size(); j++)
				if (file_i.z_indices[j] != file_m.z_indices[j])
				{
					std::cerr << "Mismatch in z-stack indices: " << file_i.fname << "[" << j << "] != " << file_m.fname << "[" << j << "]\n";
					return 3;
				}
		}

		// let each file know its directory
		for (auto i = 0; i < nf; i++)
		{
			auto& file_i = intensFiles[i],
				& file_m = labelFiles[i];
			file_i.fdir = dirIntens + '/';
			file_m.fdir = dirLabels + '/';
		}

		return 0;
	}

} // namespace Nyxus