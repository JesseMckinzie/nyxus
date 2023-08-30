#include <vector>

// Ground truth at 
//      'gabor_f0': 0.1
//      'gabor_freqs' : [4.0, 16.0, 32.0, 64.0]
//      'gabor_thetas' : [0.0, 45.0, 90.0, 135.0]
//      'gabor_gamma' : 0.1
//      'gabor_kersize' : 16
//      'gabor_sig2lam' : 0.8
//      'gabor_thold' : 0.025
//
const static std::vector<std::vector<double>> gabor_truth = {
    {   1.0112359550561798,
        0.83146067415730340,
        0.79775280898876400,
        0.49438202247191010 },

    {   1.0044843049327354,
        0.72645739910313900,
        0.0,
        0.0 },

    {   1.0053763440860215,
        0.89247311827956988,
        0.12903225806451613,
        0.0 },

    {   1.0103626943005182,
        0.89637305699481862,
        0.34715025906735753,
        0.0 },
};