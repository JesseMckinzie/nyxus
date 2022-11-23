#pragma once

#include <gtest/gtest.h>

#include "../src/nyx/roi_cache.h"
#include "../src/nyx/parallel.h"
#include "../src/nyx/features/intensity.h"
#include "../src/nyx/features/pixel.h"
#include "test_data.h"
#include "test_main_nyxus.h"

#include <unordered_map> 

// dig. phantom values for intensity based features
static std::unordered_map<std::string, float> IBSI_intensity_values {
    {"MEAN", 2.15},
    {"VARIANCE", 3.05},
    {"SKEWNESS", 1.08},
    {"KURTOSIS", -0.355},
    {"MEDIAN", 1},
    {"MINIMUM", 1},
    {"P10", 1},
    {"P90", 4},
    {"MAXIMUM", 6},
    {"INTERQUARTILE", 3},
    {"RANGE", 5},
    {"MEAN_ABSOLUTE_DEVIATION", 1.55},
    {"ROBUST_MEAN_ABSOLUTE_DEVIATION", 1.11},
    {"ENERGY", 567},
    {"ROOT_MEAN_SQUARED", 2.77}
};

void test_ibsi_mean_intensity()
{

    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "mean: " << roidata.fvals[MEAN][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[MEAN][0], IBSI_intensity_values["MEAN"], 100.));

}

void test_ibsi_skewness_intensity()
{

    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "skewness: " << roidata.fvals[SKEWNESS][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[SKEWNESS][0], IBSI_intensity_values["SKEWNESS"], 100.));

}


void test_ibsi_kurtosis_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "kurtosis: " << roidata.fvals[KURTOSIS][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[KURTOSIS][0], IBSI_intensity_values["KURTOSIS"], 100.));

}

void test_ibsi_median_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "median: " << roidata.fvals[MEDIAN][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[MEDIAN][0], IBSI_intensity_values["MEDIAN"], 100.));

}

void test_ibsi_minimum_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "minimum: " << roidata.fvals[MIN][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[MIN][0], IBSI_intensity_values["MINIMUM"], 100.));

}

void test_ibsi_p10_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "p10: " << roidata.fvals[P10][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[P10][0], IBSI_intensity_values["P10"], 100.));

}

void test_ibsi_p90_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "p90: " << roidata.fvals[P90][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[P90][0], IBSI_intensity_values["P90"], 100.));

}

void test_ibsi_interquartile_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "interquartile: " << roidata.fvals[INTERQUARTILE_RANGE][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[INTERQUARTILE_RANGE][0], IBSI_intensity_values["INTERQUARTILE"], 100.));

}

void test_ibsi_range_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "range: " << roidata.fvals[RANGE][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[RANGE][0], IBSI_intensity_values["RANGE"], 100.));

}

void test_ibsi_mean_absolute_deviation_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "mean absolute deviation: " << roidata.fvals[MEAN_ABSOLUTE_DEVIATION][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[MEAN_ABSOLUTE_DEVIATION][0], IBSI_intensity_values["MEAN_ABSOLUTE_DEVIATION"], 100.));

}

void test_ibsi_robust_mean_absolute_deviation_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "robust mean absolute deviation: " << roidata.fvals[ROBUST_MEAN_ABSOLUTE_DEVIATION][0] << std::endl;
    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "robust mean absolute deviation: " << roidata.fvals[ROBUST_MEAN_ABSOLUTE_DEVIATION][0] << std::endl;
    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "robust mean absolute deviation: " << roidata.fvals[ROBUST_MEAN_ABSOLUTE_DEVIATION][0] << std::endl;
    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "robust mean absolute deviation: " << roidata.fvals[ROBUST_MEAN_ABSOLUTE_DEVIATION][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[ROBUST_MEAN_ABSOLUTE_DEVIATION][0], IBSI_intensity_values["ROBUST_MEAN_ABSOLUTE_DEVIATION"], 100.));

}

void test_ibsi_energy_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "energy: " << roidata.fvals[ENERGY][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[ENERGY][0], IBSI_intensity_values["ENERGY"], 100.));

}

void test_ibsi_root_mean_squared_intensity()
{
    
    LR roidata;
    // Calculate features
    PixelIntensityFeatures f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "energy: " << roidata.fvals[ROOT_MEAN_SQUARED][0] << std::endl;
    // Check the feature values vs ground truth
    ASSERT_TRUE(agrees_gt(roidata.fvals[ROOT_MEAN_SQUARED][0], IBSI_intensity_values["ROOT_MEAN_SQUARED"], 100.));

}