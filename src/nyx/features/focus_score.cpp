#include "focus_score.h"
#include "../parallel.h"

using namespace Nyxus;

FocusScoreFeature::FocusScoreFeature() : FeatureMethod("FocusScoreFeature") {
    provide_features(FocusScoreFeature::featureset);
}

void FocusScoreFeature::calculate(LR& r) {

    // Get ahold of the ROI image matrix
    const ImageMatrix& Im0 = r.aux_image_matrix;

    focus_score_ = this->variance(this->laplacian(Im0.ReadablePixels(), Im0.height, Im0.width));

    local_focus_score_ = this->get_local_focus_score(Im0.ReadablePixels(), Im0.height, Im0.width);

}

void FocusScoreFeature::parallel_process(std::vector<int>& roi_labels, std::unordered_map <int, LR>& roiData, int n_threads)
{
	size_t jobSize = roi_labels.size(),
		workPerThread = jobSize / n_threads;

	runParallel(FocusScoreFeature::parallel_process_1_batch, n_threads, workPerThread, jobSize, &roi_labels, &roiData);
}

void FocusScoreFeature::parallel_process_1_batch(size_t firstitem, size_t lastitem, std::vector<int>* ptrLabels, std::unordered_map <int, LR>* ptrLabelData)
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
		FocusScoreFeature f;
		f.calculate(r);
		f.save_value(r.fvals);
	}
}

bool FocusScoreFeature::required(const FeatureSet& fs) 
{ 
    return fs.anyEnabled (FocusScoreFeature::featureset); 
}

void FocusScoreFeature::reduce (size_t start, size_t end, std::vector<int>* ptrLabels, std::unordered_map <int, LR>* ptrLabelData)
{
    for (auto i = start; i < end; i++)
    {
        int lab = (*ptrLabels)[i];
        LR& r = (*ptrLabelData)[lab];

        FocusScoreFeature fsf;

        fsf.calculate (r);

        fsf.save_value (r.fvals);
    }
}

void FocusScoreFeature::save_value(std::vector<std::vector<double>>& feature_vals) {
    
    feature_vals[(int)Feature2D::FOCUS_SCORE].resize(1);
    feature_vals[(int)Feature2D::FOCUS_SCORE][0] = focus_score_;

    feature_vals[(int)Feature2D::LOCAL_FOCUS_SCORE].resize(1);
    feature_vals[(int)Feature2D::LOCAL_FOCUS_SCORE][0] = local_focus_score_;

}

double FocusScoreFeature::get_local_focus_score(const std::vector<PixIntens>& image, int height, int width, int ksize, int scale) {

    local_focus_score_ = 0;

    int M = height / scale;
    int N = width / scale;

    double focus_score;
    for (int y = 0; y < height; y += M) {
        for (int x = 0; x < width; x += N) {

            // Extract image tile
            std::vector<PixIntens> image_tile;
            for (int i = y; i < y + M; i++) {
                for (int j = x; j < x + N; j++) {
                    image_tile.push_back(image[i * width + j]);
                }
            }
            
            // calculate focus score for tile
            focus_score = this->variance(this->laplacian(image_tile, M, N, ksize));
        }

        local_focus_score_ += focus_score;
    }

    return local_focus_score_ / (scale * scale); // average scores
}

std::vector<double> FocusScoreFeature::laplacian(const std::vector<PixIntens>& image, int n_image, int m_image, int ksize) {

    int m_kernel = 3;
    int n_kernel = 3;

    std::vector<int> kernel;

    if (ksize == 1) {
        kernel = { 0, 1, 0, 
                   1, -4, 1, 
                   0, 1, 0 };
    } else {
        kernel = { 2, 0, 2, 
                   0, -8, 0, 
                   2, 0, 2 };
    }

    std::vector<double> out(m_image * n_image, 0);

    int xKSize = n_kernel; // number of columns
    int yKSize = m_kernel; // number of rows

    int kernelCenterX = xKSize / 2.;
    int kernelCenterY = yKSize / 2.;

    int ikFlip, jkFlip;
    int ii, jj;

    for(int i = 0; i < m_image; ++i){
        for(int j = 0; j < n_image; ++j){
            for(int ik = 0; ik < yKSize; ++ik){
                ikFlip = yKSize - 1 - ik;
                for(int jk = 0; jk < xKSize; ++jk){
                    jkFlip = xKSize - 1 - jk;

                    ii = i + (kernelCenterY - ikFlip);
                    jj = j + (kernelCenterX - jkFlip);

                    if(ii >= 0 && ii < m_image && jj >= 0 && jj < n_image &&
                       ikFlip >= 0 && jkFlip >=0 && ikFlip < m_kernel && jkFlip < n_kernel){
                        out[i* n_image + j] += image[ii * n_image + jj] * kernel[ikFlip * n_kernel + jkFlip];
                    }
                }
            }
        }
    }
    
    return out;
}

double FocusScoreFeature::mean(std::vector<double> image) {

    double sum = 0.;

    for (const auto& pix: image) {
        sum += std::abs(pix);
    }

    return sum / image.size();
}


double FocusScoreFeature::variance(std::vector<double> image) {
    double image_mean = this->mean(image);
    double sum_squared_diff = 0.0;

    for (const auto& pix: image) {
        sum_squared_diff += std::pow(std::abs(pix) - image_mean, 2);
    }

    return sum_squared_diff / (image.size());
}