#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <array>
#ifdef WITH_PYTHON_H
#include <pybind11/pybind11.h>
#include "python/pybind_vector.h"	
#endif
#include "environment.h"
#include "globals.h"
#include "helpers/timing.h"

namespace Nyxus
{
	bool gatherRoisMetrics (const std::string& intens_fpath, const std::string& label_fpath, int num_FL_threads)
	{
		int lvl = 0, // Pyramid level
			lyr = 0; //	Layer

		// Read the tiff. The image loader is put in the open state in processDataset()
		size_t nth = theImLoader.get_num_tiles_hor(),
			ntv = theImLoader.get_num_tiles_vert(),
			fw = theImLoader.get_tile_width(),
			th = theImLoader.get_tile_height(),
			tw = theImLoader.get_tile_width(),
			tileSize = theImLoader.get_tile_size(),
			fullwidth = theImLoader.get_full_width(),
			fullheight = theImLoader.get_full_height();

		int cnt = 1;
		for (unsigned int row = 0; row < nth; row++)
			for (unsigned int col = 0; col < ntv; col++)
			{
				// Fetch the tile 
				bool ok = theImLoader.load_tile(row, col);
				if (!ok)
				{
					std::stringstream ss;
					ss << "Error fetching tile row=" << row << " col=" << col;
					#ifdef WITH_PYTHON_H
						throw ss.str();
					#endif	
					std::cerr << ss.str() << "\n";
					return false;
				}

				// Get ahold of tile's pixel buffer
				auto tileIdx = row * nth + col;
				auto dataI = theImLoader.get_int_tile_buffer(),
					dataL = theImLoader.get_seg_tile_buffer();

				// Iterate pixels
				for (size_t i = 0; i < tileSize; i++)
				{
					// Skip non-mask pixels
					auto label = dataL[i];
					if (!label)
						continue;

					int y = row * th + i / tw,
						x = col * tw + i % tw;
					
					// Skip tile buffer pixels beyond the image's bounds
					if (x >= fullwidth || y >= fullheight)
						continue;

					// Collapse all the labels to one if single-ROI mde is requested
					if (theEnvironment.singleROI)
						label = 1;
					
					// Update pixel's ROI metrics
					feed_pixel_2_metrics (x, y, dataI[i], label, tileIdx); // Updates 'uniqueLabels' and 'roiData'
				}

#ifdef WITH_PYTHON_H
				if (PyErr_CheckSignals() != 0)
					throw pybind11::error_already_set();
#endif

				// Show stayalive progress info
				VERBOSLVL2(
					if (cnt++ % 4 == 0)
						std::cout << "\t" << int((row * nth + col) * 100 / float(nth * ntv) * 100) / 100. << "%\t" << uniqueLabels.size() << " ROIs" << "\n";
				);
			}

		return true;
	}

#ifdef WITH_PYTHON_H
	bool gatherRoisMetricsInMemory (const pybind_vector& intens_img, const pybind_vector& label_img)
	{
		std::cout << "---- initialize values ----" << std::endl;
		for (unsigned int row = 0; row < label_img.width; row++) {
			for (unsigned int col = 0; col < label_img.height; col++)
			{

				// Skip non-mask pixels
				auto label = label_img.xy(row, col);
				if (!label)
					continue;

				int y = row,
					x = col;

				// Collapse all the labels to one if single-ROI mde is requested
				if (theEnvironment.singleROI)
					label = 1;
				//std::cout << intens_img.xy(row,col) << " ";
				// Update pixel's ROI metrics
				auto intens = intens_img.xy(row,col);
				std::cout << intens << std::endl;
				feed_pixel_2_metrics (x, y, intens, label, 100); // Updates 'uniqueLabels' and 'roiData'
			}
	

			if (PyErr_CheckSignals() != 0)
				throw pybind11::error_already_set();

		}
		std::cout << std::endl;

		return true;
	}
#endif
}
