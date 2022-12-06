#pragma once

#include <gtest/gtest.h>

#include "../src/nyx/roi_cache.h"
#include "../src/nyx/parallel.h"
#include "../src/nyx/features/ngtdm.h"
#include "../src/nyx/features/pixel.h"
#include "test_data.h"
#include "test_main_nyxus.h"

#include <unordered_map> 

// dig. phantom values for intensity based features
static std::unordered_map<std::string, float> IBSI_ngtdm_values {
    {"NGTDM_COARSENESS", 0.121},
    {"NGTDM_CONTRAST", 0.925},
    {"NGTDM_BUSYNESS", 2.99},
    {"NGTDM_COMPLEXITY", 10.4},
    {"NGTDM_STRENGTH", 2.88}
};

void test_ibsi_ngtdm_coarseness()
{

    LR roidata;
    // Calculate features
    NGTDMFeature f;
    
    // image 1
    double total = 0;
    load_masked_test_roi_data (roidata, ibsi_phantom_z1_intensity, ibsi_phantom_z1_mask,  sizeof(ibsi_phantom_z1_intensity) / sizeof(NyxusPixel));
    ASSERT_NO_THROW(f.calculate(roidata));

    // Initialize per-ROI feature value buffer with zeros
    roidata.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f.save_value(roidata.fvals);

    total += roidata.fvals[NGTDM_COARSENESS][0];
    std::cerr << "total: " << total << std::endl;
    // image 2
    // Calculate features
    LR roidata1;
    // Calculate features
    NGTDMFeature f1;
    load_masked_test_roi_data (roidata1, ibsi_phantom_z2_intensity, ibsi_phantom_z2_mask,  sizeof(ibsi_phantom_z2_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f1.calculate(roidata1));

    // Initialize per-ROI feature value buffer with zeros
    roidata1.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f1.save_value(roidata1.fvals);

    total += roidata1.fvals[NGTDM_COARSENESS][0];
    std::cerr << "total: " << total << std::endl;
    // image 3
    // Calculate features
    LR roidata2;
    // Calculate features
    NGTDMFeature f2;
    load_masked_test_roi_data (roidata2, ibsi_phantom_z3_intensity, ibsi_phantom_z3_mask,  sizeof(ibsi_phantom_z3_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f2.calculate(roidata2));

    // Initialize per-ROI feature value buffer with zeros
    roidata2.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f2.save_value(roidata2.fvals);

    total += roidata2.fvals[NGTDM_COARSENESS][0];
    std::cerr << "total: " << total << std::endl;
    // image 4
    // Calculate features
    LR roidata3;
    // Calculate features
    NGTDMFeature f3;
    load_masked_test_roi_data (roidata3, ibsi_phantom_z4_intensity, ibsi_phantom_z4_mask,  sizeof(ibsi_phantom_z4_intensity) / sizeof(NyxusPixel));

    ASSERT_NO_THROW(f3.calculate(roidata3));

    // Initialize per-ROI feature value buffer with zeros
    roidata3.initialize_fvals();

    // Retrieve values of the features implemented by class 'PixelIntensityFeatures' into ROI's feature buffer
    f3.save_value(roidata3.fvals);

    total += roidata3.fvals[NGTDM_COARSENESS][0];
    std::cerr << "total: " << total << std::endl;
    // Check the feature values vs ground truth

    ASSERT_TRUE(agrees_gt(roidata.fvals[NGTDM_COARSENESS][0], IBSI_ngtdm_values["NGTDM_COARSENESS"], 100.));

}