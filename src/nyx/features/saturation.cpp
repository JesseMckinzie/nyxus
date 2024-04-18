#include "saturation.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>

#include "../helpers/helpers.h"
#include "../helpers/fft.h"
#include "../parallel.h"

using namespace Nyxus;

SaturationFeature::SaturationFeature() : FeatureMethod("SaturationFeature") {
    provide_features({Feature2D::SATURATION});
}

void SaturationFeature::calculate(LR& r) {

    // Get ahold of the ROI image matrix
    const ImageMatrix& Im0 = r.aux_image_matrix;

    std::tie(min_saturation_, max_saturation_) = get_percent_max_pixels(Im0);

    std::cerr << "min saturation: " << min_saturation_ << std::endl;
    std::cerr << "max saturation: " << max_saturation_ << std::endl;
}

void SaturationFeature::parallel_process(std::vector<int>& roi_labels, std::unordered_map <int, LR>& roiData, int n_threads)
{
	size_t jobSize = roi_labels.size(),
		workPerThread = jobSize / n_threads;

	runParallel(SaturationFeature::parallel_process_1_batch, n_threads, workPerThread, jobSize, &roi_labels, &roiData);
}

void SaturationFeature::parallel_process_1_batch(size_t firstitem, size_t lastitem, std::vector<int>* ptrLabels, std::unordered_map <int, LR>* ptrLabelData)
{
	// Calculate the feature for each batch ROI item 
	for (auto i = firstitem; i < lastitem; i++)
	{
		// Get ahold of ROI's label and cache
		int roiLabel = (*ptrLabels)[i];
		LR& r = (*ptrLabelData)[roiLabel];

		// Skip the ROI if its data is invalid to prevent nans and infs in the output
		if (r.has_bad_data())
			continue;

		// Calculate the feature and save it in ROI's csv-friendly buffer 'fvals'
		SaturationFeature f;
		f.calculate(r);
		f.save_value(r.fvals);
	}
}

bool SaturationFeature::required(const FeatureSet& fs) 
{ 
    return fs.isEnabled (Feature2D::SATURATION); 
}

void SaturationFeature::reduce (size_t start, size_t end, std::vector<int>* ptrLabels, std::unordered_map <int, LR>* ptrLabelData)
{
    for (auto i = start; i < end; i++)
    {
        int lab = (*ptrLabels)[i];
        LR& r = (*ptrLabelData)[lab];

        SaturationFeature fsf;

        fsf.calculate (r);

        for (auto& vec: r.fvals) {
            for (auto& value: vec) {
                std::cout << "val: " << value << std::endl;
            }
        }
        fsf.save_value (r.fvals);
    }
}

void SaturationFeature::save_value(std::vector<std::vector<double>>& feature_vals) {
    
    if (feature_vals[(int)Feature2D::SATURATION].size() != 2) {
        feature_vals[(int)Feature2D::SATURATION].resize(2);
    }
 
    feature_vals[(int)Feature2D::SATURATION][0] = min_saturation_;
    feature_vals[(int)Feature2D::SATURATION][1] = max_saturation_;
}

std::tuple<double, double> SaturationFeature::get_percent_max_pixels(const ImageMatrix& Im) {

    readOnlyPixels image = Im.ReadablePixels();

    auto max_pixel = *std::max_element(image.begin(), image.end());
    auto min_pixel = *std::min_element(image.begin(), image.end());

    double max_pixel_count = 0;
    double min_pixel_count = 0;

    for (const auto& pix: image) {
        if (pix == max_pixel) {
            ++max_pixel_count;
        } else if (pix == min_pixel) {
            ++min_pixel_count;
        }
    }

    return std::make_tuple(min_pixel_count / image.size(), max_pixel_count / image.size());
}
