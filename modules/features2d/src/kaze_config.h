
/**
 * @file kaze_config.h
 * @brief Configuration file
 * @date Dec 27, 2011
 * @author Pablo F. Alcantarilla
 */

#ifndef _KAZE_CONFIG_H_
#define _KAZE_CONFIG_H_

// OPENCV Includes
#include "opencv2/core/core.hpp"

// Some default options
const float DEFAULT_SCALE_OFFSET = 1.60; // Base scale offset (sigma units)
const float DEFAULT_OCTAVE_MAX = 4.0; // Maximum octave evolution of the image 2^sigma (coarsest scale sigma units)
const int DEFAULT_NSUBLEVELS = 4; // Default number of sublevels per scale level
const float DEFAULT_DETECTOR_THRESHOLD = 0.001f; // Detector response threshold to accept point
const float DEFAULT_MIN_DETECTOR_THRESHOLD = 0.00001;     // Minimum Detector response threshold to accept point
const int DEFAULT_DESCRIPTOR_MODE = 1; // Descriptor Mode 0->SURF, 1->M-SURF
const bool DEFAULT_UPRIGHT = false;  // Upright descriptors, not invariant to rotation
const bool DEFAULT_EXTENDED = false; // Extended descriptor, dimension 128

const int DEFAULT_DIFFUSIVITY_TYPE = 1;  // 0 -> PM G1, 1 -> PM G2, 2 -> Weickert

const bool DEFAULT_VERBOSITY = false; // Verbosity level (0->no verbosity)

// Some important configuration variables
const float DEFAULT_SIGMA_SMOOTHING_DERIVATIVES = 1.0;
const float DEFAULT_KCONTRAST = .01;
const float KCONTRAST_PERCENTILE = 0.7;
const int KCONTRAST_NBINS = 300;
const bool COMPUTE_KCONTRAST = true;
const bool SUBPIXEL_REFINEMENT = true;
const bool USE_CLIPPING_NORMALIZATION = false;
const float CLIPPING_NORMALIZATION_RATIO = 1.6;
const int CLIPPING_NORMALIZATION_NITER = 5;

// Options structure
struct KAZEOptions
{
	float soffset;      // Base scale offset
	int omax;           // Maximum octave level
	int nsublevels;     // Number of sublevels per octave level
	int img_width;      // Width of the original image
	int img_height;     // Height of the original image
    int diffusivity;    // Diffusivity type, 0->PM G1, 1->PM G2, 2-> Weickert
	float sderivatives; // Standard deviation of the Gaussian for the nonlinear diff. derivatives
	float dthreshold;   // Feature detector threshold response
	float dthreshold2;

	bool upright; // Set to true in case we want to use the upright version of the descriptors
    bool extended; // Set to true in case we want to use the extended version of the descriptors
	int descriptor;

    bool verbose;     // Verbosity level

    KAZEOptions()
        : soffset(DEFAULT_SCALE_OFFSET)
        , omax(DEFAULT_OCTAVE_MAX)
        , nsublevels(DEFAULT_NSUBLEVELS)
        , img_width(0)
        , img_height(0)
        , dthreshold(DEFAULT_DETECTOR_THRESHOLD)
        , dthreshold2(DEFAULT_DETECTOR_THRESHOLD)
        , diffusivity(DEFAULT_DIFFUSIVITY_TYPE)
        , sderivatives(DEFAULT_SIGMA_SMOOTHING_DERIVATIVES)
        , upright(DEFAULT_UPRIGHT)
        , extended(DEFAULT_EXTENDED)
        , descriptor(DEFAULT_DESCRIPTOR_MODE)
        , verbose(DEFAULT_VERBOSITY)
    {
        
    }
};

typedef struct
{
	cv::Mat Lx, Ly;	// First order spatial derivatives
	cv::Mat Lxx, Lxy, Lyy;	// Second order spatial derivatives
	cv::Mat Lflow;	// Diffusivity image
	cv::Mat Lt;	// Evolution image
	cv::Mat Lsmooth; // Smoothed image
	cv::Mat Lstep; // Evolution step update
	cv::Mat Ldet; // Detector response
	float etime;	// Evolution time
	float esigma;	// Evolution sigma. For linear diffusion t = sigma^2 / 2
	float octave;	// Image octave
	float sublevel;	// Image sublevel in each octave
	int sigma_size;	// Integer esigma. For computing the feature detector responses
} tevolution;


#endif




