#pragma once

#include <gtest/gtest.h>

#include "../src/nyx/roi_cache.h"
#include "../src/nyx/parallel.h"
#include "../src/nyx/features/glcm.h"
#include "../src/nyx/features/pixel.h"
#include "test_data.h"
#include "test_main_nyxus.h"

#include <unordered_map> 

// dig. phantom values for intensity based features
static std::unordered_map<std::string, float> IBSI_glcm_values {
    {"GLCM_DIFFERENCEAVERAGE", 1.42},
    {"GLCM_DIFFERENCEVARIANCE", 2.9},
    {"GLCM_DIFFERENCEENTROPY", 1.4},
    {"GLCM_SUMAVERAGE", 4.28},
    {"GLCM_SUMVARIANCE", 5.47},
    {"GLCM_SUMENTROPY", 1.6}, 
    {"GLCM_ANGULAR2NDMOMENT", 0.368},
    {"GLCM_CONTRAST", 5.28},
    {"GLCM_INVERSEDIFFERENCEMOMENT", 0.678},
    {"GLCM_CORRELATION", -0.0121},
    {"GLCM_INFOMEAS1", -0.155},
    {"GLCM_INFOMEAS2", 0.487}

};

/*
    {"GLCM_DIFFERENCEVARIANCE", },
    {"GLCM_DIFFERENCEENTROPY", },
    {"GLCM_SUMAVERAGE", },
    {"GLCM_SUMVARIANCE", },
    {"GLCM_SUMENTROPY", },
    {"GLCM_ANGULAR2NDMOMENT", },
    {"GLCM_CONTRAST", },
    {"GLCM_INVERSEDIFFERENCEMOMENT", },
    {"GLCM_CORRELATION", },
    {"GLCM_INFOMEAS1", },
    {"GLCM_INFOMEAS2", }
*/

void test_ibsi_glcm_difference_average()
{
    double total = 0;
    LR roidata;
    // Calculate features
    GLCMFeature f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_mask) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
 

    std::cerr << "0: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    std::cerr << "1: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][1] << std::endl;
    std::cerr << "2: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][2] << std::endl;
    std::cerr << "3: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][3] << std::endl;

    total += roidata.fvals[GLCM_DIFFERENCEAVERAGE][0];

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    total += roidata.fvals[GLCM_DIFFERENCEAVERAGE][0];

    std::cerr << "0: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    std::cerr << "1: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][1] << std::endl;
    std::cerr << "2: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][2] << std::endl;
    std::cerr << "3: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][3] << std::endl;

    // image 3
    // Calculate features


    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    total += roidata.fvals[GLCM_DIFFERENCEAVERAGE][0];

    std::cerr << "0: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    std::cerr << "1: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][1] << std::endl;
    std::cerr << "2: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][2] << std::endl;
    std::cerr << "3: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][3] << std::endl;

    // image 4
    // Calculate features

    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    // Check the feature values vs ground truth
    total += roidata.fvals[GLCM_DIFFERENCEAVERAGE][0];
    std::cerr << "0: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    std::cerr << "1: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][1] << std::endl;
    std::cerr << "2: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][2] << std::endl;
    std::cerr << "3: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][3] << std::endl;

    std::cerr << "averaged glcm at [0]: " << total / 4 << std::endl;

    ASSERT_TRUE(agrees_gt(total / 4, IBSI_glcm_values["GLCM_DIFFERENCEAVERAGE"], 100.));

}

/*
void test_ibsi_glcm_difference_average()
{
    double total = 0;
    LR roidata;
    // Calculate features
    GLCMFeature f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // roidata.fvals[GLCM_DIFFERENCEAVERAGE][0]

    std::cerr << "0: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    std::cerr << "1: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][1] << std::endl;
    std::cerr << "2: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][2] << std::endl;
    std::cerr << "3: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][3] << std::endl;


    std::cerr << "glcm difference average 1: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    total += roidata.fvals[GLCM_DIFFERENCEAVERAGE][0];
    LR roidata;
    // Calculate features
    GLCMFeature f;
    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm difference average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    total += roidata.fvals[GLCM_DIFFERENCEAVERAGE][0];
    // image 3
    // Calculate features

    LR roidata;
    // Calculate features
    GLCMFeature f;
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "glcm difference average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    total += roidata.fvals[GLCM_DIFFERENCEAVERAGE][0];
    // image 4
    // Calculate features
    LR roidata;
    // Calculate features
    GLCMFeature f;
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "glcm difference average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    std::cerr << "averaged glcm: " << total / 4 << std::endl;
    // Check the feature values vs ground truth
    total += roidata.fvals[GLCM_DIFFERENCEAVERAGE][0];
    ASSERT_TRUE(agrees_gt(total / 4, IBSI_glcm_values["GLCM_DIFFERENCEAVERAGE"], 100.));

}
*/


void test_ibsi_glcm_difference_variance()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
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


    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEVARIANCE][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_DIFFERENCEVARIANCE][0], IBSI_glcm_values["GLCM_DIFFERENCEVARIANCE"], 100.));

}

void test_ibsi_glcm_difference_entropy()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
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


    std::cerr << "glcm sum entropy: " << roidata.fvals[GLCM_DIFFERENCEENTROPY][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_DIFFERENCEENTROPY][0], IBSI_glcm_values["GLCM_DIFFERENCEENTROPY"], 100.));

}

// -------------------------------------------------

void test_ibsi_glcm_sum_average()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm difference average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm difference average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "glcm difference average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "glcm difference average: " << roidata.fvals[GLCM_SUMAVERAGE][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_SUMAVERAGE][0], IBSI_glcm_values["GLCM_SUMAVERAGE"], 100.));

}

void test_ibsi_glcm_sum_variance()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
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


    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEVARIANCE][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_DIFFERENCEVARIANCE][0], IBSI_glcm_values["GLCM_DIFFERENCEVARIANCE"], 100.));

}

void test_ibsi_glcm_sum_entropy()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
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


    std::cerr << "glcm sum entropy: " << roidata.fvals[GLCM_SUMENTROPY][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_SUMENTROPY][0], IBSI_glcm_values["GLCM_SUMENTROPY"], 100.));

}



void test_ibsi_glcm_angular_2d_moment()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_ANGULAR2NDMOMENT][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_ANGULAR2NDMOMENT][0], IBSI_glcm_values["GLCM_ANGULAR2NDMOMENT"], 100.));

}

void test_ibsi_glcm_contrast()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_CONTRAST][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_CONTRAST][0], IBSI_glcm_values["GLCM_CONTRAST"], 100.));

}

void test_ibsi_glcm_inversed_difference_moment()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_INVERSEDIFFERENCEMOMENT][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_INVERSEDIFFERENCEMOMENT][0], IBSI_glcm_values["GLCM_INVERSEDIFFERENCEMOMENT"], 100.));

}

void test_ibsi_glcm_correlation()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_CORRELATION][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_CORRELATION][0], IBSI_glcm_values["GLCM_CORRELATION"], 100.));

}

void test_ibsi_glcm_infomeas1()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_INFOMEAS1][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_INFOMEAS1][0], IBSI_glcm_values["GLCM_INFOMEAS1"], 100.));

}

void test_ibsi_glcm_infomeas2()
{

    LR roidata;
    // Calculate features
    GLCMFeature f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;

    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_DIFFERENCEAVERAGE][0] << std::endl;
    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "glcm sum average: " << roidata.fvals[GLCM_INFOMEAS2][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLCM_INFOMEAS2][0], IBSI_glcm_values["GLCM_INFOMEAS2"], 100.));

}
