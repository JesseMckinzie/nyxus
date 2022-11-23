#pragma once

#include <gtest/gtest.h>

#include "../src/nyx/roi_cache.h"
#include "../src/nyx/parallel.h"
#include "../src/nyx/features/glrlm.h"
#include "../src/nyx/features/pixel.h"
#include "test_data.h"
#include "test_main_nyxus.h"

#include <unordered_map> 

// dig. phantom values for intensity based features
static std::unordered_map<std::string, float> IBSI_glrlm_values {
    {"SRE", 0.641},
    {"LRE", 3.78},
    {"LGLRE", 0.604},
    {"HGLRE", 9.82},
    {"SRLGLE", 0.294},
    {"SRHGLE", 8.57},
    {"LRLGLE", 3.14},
    {"LRHGLE", 17.4},
    {"GLN", 5.2},
    {"GLNN", 0.46},
    {"RLN", 6.12},
    {"RLNN", 0.492},
    {"RP", 0.627},
    {"GLV", 3.35},
    {"RV", 0.761},
    {"RE", 2.17}
};

void test_ibsi_glrlm_sre()
{

    LR roidata;
    // Calculate features
    GLRLMFeature f;
    
    // image 1

    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    // roidata.fvals[GLRLM_SRE][0]


    std::cerr << "-- glcm difference average 1: " << roidata.fvals[GLRLM_SRE][0] << std::endl;

    // image 2
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);
    std::cerr << "glcm difference average: " << roidata.fvals[GLRLM_SRE][0] << std::endl;

    // image 3
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    std::cerr << "glcm difference average: " << roidata.fvals[GLRLM_SRE][0] << std::endl;
    // image 4
    // Calculate features
    load_masked_test_roi_data (roidata, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);


    std::cerr << "glcm difference average: " << roidata.fvals[GLRLM_SRE][0] << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[GLRLM_SRE][0], IBSI_glrlm_values["GLRLM_SRE"], 100.));

}