#pragma once

//---	#define SINGLE_ROI_TEST

#include <climits>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <mutex>
#include "featureset.h"
#include "histogram.h"
#include "pixel.h"

#define INF 10E200	// Cautious infinity

bool datasetDirsOK (const std::string & dirIntens, const std::string & dirLab, const std::string & dirOut, bool mustCheckDirOut);
bool directoryExists (const std::string & dir);
void readDirectoryFiles (const std::string & dir, std::vector<std::string> & files);
bool scanViaFastloader (const std::string & fpath, int num_threads);
bool scanFilePair (const std::string& intens_fpath, const std::string& label_fpath, int num_fastloader_threads, int num_sensemaker_threads);
bool scanFilePairParallel (const std::string& intens_fpath, const std::string& label_fpath, int num_fastloader_threads, int num_sensemaker_threads);
bool TraverseViaFastloader1 (const std::string& fpath, int num_threads);
std::string getPureFname(std::string fpath);
int ingestDataset (std::vector<std::string> & intensFiles, std::vector<std::string> & labelFiles, int numFastloaderThreads, int numSensemakerThreads, int min_online_roi_size, bool save2csv, std::string csvOutputDir);

// 2 scenarios of saving a result of feature calculation of a label-intensity file pair: saving to a CSV-file and saving to a matrix to be later consumed by a Python endpoint
bool save_features_2_csv (std::string inputFpath, std::string outputDir);
bool save_features_2_buffer (std::vector<double> & resultMatrix);

void showCmdlineHelp();
int checkAndReadDataset(
	// input
	const std::string& dirIntens, const std::string& dirLabels, const std::string& dirOut, bool mustCheckDirOut, 
	// output
	std::vector<std::string>& intensFiles, std::vector<std::string>& labelFiles);

using Histo = OnlineHistogram<PixIntens>;

void init_feature_buffers();
void update_label_stats (int x, int y, int label, PixIntens intensity);
void update_label_stats_parallel (int x, int y, int label, PixIntens intensity);
void print_label_stats();
void print_by_label(const char* featureName, std::unordered_map<int, StatsInt> L, int numColumns = 8); 
void print_by_label(const char* featureName, std::unordered_map<int, StatsReal> L, int numColumns = 4);
void clearLabelStats();
void reduce_all_labels(int min_online_roi_size);

class AABB
{
public:
	AABB() {}
	void init_x (StatsInt x) { xmin = xmax = x; }
	void init_y (StatsInt y) { ymin = ymax = y; }
	void update_x(StatsInt x)
	{
		xmin = std::min(xmin, x);
		xmax = std::max(xmax, x);
	}
	void update_y(StatsInt y)
	{
		ymin = std::min(ymin, y);
		ymax = std::max(ymax, y);
	}
	StatsInt get_height() { return ymax - ymin + 1; }
	StatsInt get_width() { return xmax - xmin + 1; }
	StatsInt get_area() { return get_width() * get_height(); }
	inline StatsInt get_xmin() { return xmin; }
	inline StatsInt get_xmax() { return xmax; }
	inline StatsInt get_ymin() { return ymin; }
	inline StatsInt get_ymax() { return ymax; }

protected:
	StatsInt xmin = INT32_MAX, xmax = INT32_MIN, ymin = INT32_MAX, ymax = INT32_MIN;
};

// Inherited from WNDCHRM, used for Feret and Martin statistics calculation
struct Statistics 
{
	double min, max, mode;
	double mean, median, stdev;
};

Statistics ComputeCommonStatistics2 (std::vector<double>& Data);

class Contour
{
public:
	Contour() {}
	void calculate(std::vector<Pixel2> rawPixels);
	std::vector<Pixel2> theContour;
	StatsInt get_roi_perimeter();
	StatsReal get_diameter_equal_perimeter();
protected:
};

class ConvexHull
{
public:
	ConvexHull() {}
	void calculate (std::vector<Pixel2> & rawPixels);
	double getSolidity();
	double getArea();
	std::vector<Pixel2> CH;
};

class Hexagonality_and_Polygonality
{
public:
	Hexagonality_and_Polygonality() {}
	std::tuple<double, double, double> calculate(int num_neighbors, int roi_area, int roi_perimeter, double convhull_area, double min_feret_diam, double max_feret_diam);

};

// Longest chord, Feret, Martin, Nassenstein diameters
class ParticleMetrics
{
public:
	ParticleMetrics(std::vector<Pixel2>& _convex_hull);

	void calc_ferret(
		// output:
		double& minFeretDiameter,
		double& minFeretAngle,
		double& maxFeretDiameter,
		double& maxFeretAngle,
		std::vector<double>& all_D);
	void calc_martin (std::vector<double>& D);
	void calc_nassenstein (std::vector<double>& D);
	const int NY = 10;
	const int rot_angle_increment = 10;	// degrees
protected:
	std::tuple<StatsInt, StatsInt, StatsInt, StatsInt> get_pixelcloud_bounds (std::vector<Pixel2> & pixels);	// Returns minX, minY, maxX, maxY
	void rotate_pixels(
		// in 
		float angle_deg,
		std::vector<Pixel2> & P, 
		// out
		std::vector<Pixel2>& P_rot);

	std::vector<Pixel2>& convex_hull;
};

class EulerNumber
{
public:
	long euler_number;
	EulerNumber (std::vector<Pixel2>& P, StatsInt min_x, StatsInt  min_y, StatsInt max_x, StatsInt max_y, int mode);
protected:
	long calculate (std::vector<unsigned char>& I, int height, int width, int mode);
};

class MinEnclosingCircle
{
public:
	MinEnclosingCircle() {}
	double calculate_diam (std::vector<Pixel2>& Contour);
	const float EPS = 1.0e-4f;

protected:
	void minEnclosingCircle (
		// in:
		std::vector<Pixel2> & Contour, 
		// out:
		Point2f &center, 
		float &radius);
	void findMinEnclosingCircle (const std::vector<Pixel2>& pts, int count, Point2f& center, float& radius);
	void findSecondPoint (const std::vector<Pixel2>& pts, int i, Point2f& center, float& radius);
	void findThirdPoint (const std::vector<Pixel2>& pts, int i, int j, Point2f& center, float& radius);
	void findCircle3pts (const std::vector<Pixel2>& pts, Point2f& center, float& radius);
};

class InscribingCircumscribingCircle
{
public:
	std::tuple <double, double> calculateInsCir (std::vector<Pixel2>& contours, double xCentroid, double yCentroid);
};

class GeodeticLength_and_Thickness
{
public:
	GeodeticLength_and_Thickness() {}
	std::tuple<double, double> calculate(StatsInt roiArea, StatsInt roiPerimeter);

protected:
};

void haralick2D(
	// in
	std::vector <Pixel2>& nonzero_intensity_pixels,
	AABB & aabb,
	double distance,
	// out
	std::vector<double>& Texture_Feature_Angles,
	std::vector<double>& Texture_AngularSecondMoments,
	std::vector<double>& Texture_Contrast,
	std::vector<double>& Texture_Correlation,
	std::vector<double>& Texture_Variance,
	std::vector<double>& Texture_InverseDifferenceMoment,
	std::vector<double>& Texture_SumAverage,
	std::vector<double>& Texture_SumVariance,
	std::vector<double>& Texture_SumEntropy,
	std::vector<double>& Texture_Entropy,
	std::vector<double>& Texture_DifferenceVariance,
	std::vector<double>& Texture_DifferenceEntropy,
	std::vector<double>& Texture_InfoMeas1,
	std::vector<double>& Texture_InfoMeas2);

extern FeatureSet featureSet;

// Label record - structure aggregating label's cached data and calculated features
struct LR
{
	// Helper objects
	std::vector <Pixel2> raw_pixels;	
	AABB aabb;	
	ConvexHull convHull;
	Contour cntr;

	//==== Pixel intensity statistics

	StatsInt pixelCount;	// Area
	StatsInt labelPrevCount;
	StatsInt labelPrevIntens;
	StatsReal mean;
	//std::shared_ptr<std::unordered_set<PixIntens>> labelUniqueIntensityValues;
	StatsInt labelMedians;
	StatsInt labelMins;
	StatsInt labelMaxs;
	StatsInt labelMassEnergy;
	StatsReal labelVariance;
	StatsReal labelStddev;	
	StatsReal centroid_x;
	StatsReal centroid_y;
	StatsReal labelM2;
	StatsReal labelM3;
	StatsReal labelM4;
	StatsReal labelSkewness;
	StatsReal labelKurtosis;
	StatsReal labelMAD;
	StatsReal labelRMS;		// Root Mean Squared (RMS) is the square-root of the mean of all the squared intensity values. It is another measure of the magnitude of the image values.
	std::shared_ptr<Histo> labelHistogram;
	StatsReal labelP10;
	StatsReal labelP25;
	StatsReal labelP75;
	StatsReal labelP90;
	StatsReal labelIQR;
	StatsReal labelEntropy;
	StatsReal labelMode;
	StatsReal labelUniformity;
	StatsReal labelRMAD;

	//==== Morphology

	int num_neighbors;
	void init_aabb (StatsInt x, StatsInt y);
	void update_aabb (StatsInt x, StatsInt y);
	StatsReal extent;	// Calculated in reduce(), not accumulated online

	// --ellipse related
	StatsReal major_axis_length;
	StatsReal minor_axis_length;
	StatsReal eccentricity;
	StatsReal orientation;

	StatsReal	aspectRatio;
	StatsReal	equivDiam;
	StatsInt	roiPerimeter;
	StatsReal	circularity;
	StatsReal	convHullArea;
	StatsReal	solidity;

	// --extrema
	StatsReal	
		extremaP1y, extremaP1x,
		extremaP2y, extremaP2x,
		extremaP3y, extremaP3x,
		extremaP4y, extremaP4x,
		extremaP5y, extremaP5x,
		extremaP6y, extremaP6x,
		extremaP7y, extremaP7x,
		extremaP8y, extremaP8x;

	// --Feret
	StatsReal	maxFeretDiameter,
		maxFeretAngle,
		minFeretDiameter,
		minFeretAngle,
		feretStats_minDiameter,	// ratios[59]
		feretStats_maxDiameter,	// ratios[60]
		feretStats_meanDiameter,	// ratios[61]
		feretStats_medianDiameter,	// ratios[62]
		feretStats_stddevDiameter,	// ratios[63]
		feretStats_modeDiameter;	// ratios[64]

	// --Martin
	StatsReal	
		martinStats_minDiameter,	// ratios[59]
		martinStats_maxDiameter,	// ratios[60]
		martinStats_meanDiameter,	// ratios[61]
		martinStats_medianDiameter,	// ratios[62]
		martinStats_stddevDiameter,	// ratios[63]
		martinStats_modeDiameter;	// ratios[64]

	// --Nassenstein
	StatsReal
		nassStats_minDiameter,	// ratios[59]
		nassStats_maxDiameter,	// ratios[60]
		nassStats_meanDiameter,	// ratios[61]
		nassStats_medianDiameter,	// ratios[62]
		nassStats_stddevDiameter,	// ratios[63]
		nassStats_modeDiameter;	// ratios[64]

	// --Euler
	long euler_number;

	// --hexagonality & polygonality
	double polygonality_ave, hexagonality_ave, hexagonality_stddev;

	// --Circle fitting
	double diameter_min_enclosing_circle,	// ratios[45]
		diameter_circumscribing_circle,		//ratios[46] 
		diameter_inscribing_circle;			// ratios[47] 

	double geodeticLength,	// ratios[53] 
		thickness;			// ratios[54]

	// --Haralick 2D aka CellProfiler_*
	double Texture_AngularSecondMoment_0,
		Texture_AngularSecondMoment_135,
		Texture_AngularSecondMoment_45,
		Texture_AngularSecondMoment_90,

		Texture_Contrast_0,
		Texture_Contrast_135,
		Texture_Contrast_45,
		Texture_Contrast_90,

		Texture_Correlation_0,
		Texture_Correlation_135,
		Texture_Correlation_45,
		Texture_Correlation_90,

		Texture_DifferenceEntropy_0,
		Texture_DifferenceEntropy_135,
		Texture_DifferenceEntropy_45,
		Texture_DifferenceEntropy_90,

		Texture_DifferenceVariance_0,
		Texture_DifferenceVariance_135,
		Texture_DifferenceVariance_45,
		Texture_DifferenceVariance_90,

		Texture_Entropy_0,
		Texture_Entropy_135,
		Texture_Entropy_45,
		Texture_Entropy_90,

		Texture_InfoMeas1_0,
		Texture_InfoMeas1_135,
		Texture_InfoMeas1_45,
		Texture_InfoMeas1_90,

		Texture_InfoMeas2_0,
		Texture_InfoMeas2_135,
		Texture_InfoMeas2_45,
		Texture_InfoMeas2_90,

		Texture_InverseDifferenceMoment_0,
		Texture_InverseDifferenceMoment_135,
		Texture_InverseDifferenceMoment_45,
		Texture_InverseDifferenceMoment_90,

		Texture_SumAverage_0,
		Texture_SumAverage_135,
		Texture_SumAverage_45,
		Texture_SumAverage_90,

		Texture_SumEntropy_0,
		Texture_SumEntropy_135,
		Texture_SumEntropy_45,
		Texture_SumEntropy_90,

		Texture_SumVariance_0,
		Texture_SumVariance_135,
		Texture_SumVariance_45,
		Texture_SumVariance_90,

		Texture_Variance_0,
		Texture_Variance_135,
		Texture_Variance_45,
		Texture_Variance_90;

	std::vector<double> Texture_Feature_Angles,	// (auxiliary field) angles e.g. 0, 45, 90, 135, etc.
		Texture_AngularSecondMoments, // Angular Second Moment
		Texture_Contrast, // Contrast
		Texture_Correlation, // Correlation
		Texture_Variance, // Variance
		Texture_InverseDifferenceMoment, // Inverse Diffenence Moment
		Texture_SumAverage, // Sum Average
		Texture_SumVariance, // Sum Variance
		Texture_SumEntropy, // Sum Entropy
		Texture_Entropy, // Entropy
		Texture_DifferenceVariance, // Difference Variance
		Texture_DifferenceEntropy, // Diffenence Entropy
		Texture_InfoMeas1, // Measure of Correlation 1
		Texture_InfoMeas2; // Measure of Correlation 2

	double getValue(AvailableFeatures f);
};

void init_label_record(LR& lr, int x, int y, int label, PixIntens intensity);
void update_label_record(LR& lr, int x, int y, int label, PixIntens intensity);
void reduce_neighbors (int labels_collision_radius);

// Timing
extern double totalTileLoadTime, totalPixStatsCalcTime;
double test_containers1();
double test_containers2();
bool test_histogram();

// Spatial hashing
inline bool aabbNoOverlap (
	StatsInt xmin1, StatsInt xmax1, StatsInt ymin1, StatsInt ymax1, 
	StatsInt xmin2, StatsInt xmax2, StatsInt ymin2, StatsInt ymax2,
	int R)
{
	bool retval = xmin2 - R > xmax1 + R || xmax2 + R < xmin1 - R
		|| ymin2 - R > ymax1 + R || ymax2 + R < ymin1 - R;
	return retval;
}

inline bool aabbNoOverlap (LR & r1, LR & r2, int radius)
{
	bool retval = aabbNoOverlap(r1.aabb.get_xmin(), r1.aabb.get_xmax(), r1.aabb.get_ymin(), r1.aabb.get_ymax(),
		r2.aabb.get_xmin(), r2.aabb.get_xmax(), r2.aabb.get_ymin(), r2.aabb.get_ymax(), radius);
	return retval;
}

inline unsigned long spat_hash_2d (StatsInt x, StatsInt y, int m)
{
	unsigned long h = x * 73856093;
	h = h ^ y * 19349663;
	// hash   hash  z � 83492791	// For the future
	// hash   hash  l � 67867979
	unsigned long retval = h % m;
	return retval;
}

// Label data
extern std::unordered_set<int> uniqueLabels;
extern std::unordered_map <int, LR> labelData;
extern std::vector<double> calcResultBuf;	// [# of labels X # of features]
extern std::unordered_map <int, std::shared_ptr<std::mutex>> labelMutexes;