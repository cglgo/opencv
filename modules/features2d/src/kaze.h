
/**
* @file KAZE.h
* @brief Main program for detecting and computing descriptors in a nonlinear
* scale space
* @date Jan 21, 2012
* @author Pablo F. Alcantarilla
*/

#ifndef _KAZE_H_
#define _KAZE_H_

//*************************************************************************************
//*************************************************************************************

// Includes
#include "kaze_config.h"
#include "kaze_nldiffusion_functions.h"

// KAZE Class Declaration
class KAZE
{
private:
    // Parameters of the Nonlinear diffusion class
    KAZEOptions options;

    float kcontrast; // The contrast parameter for the scalar nonlinear diffusion

    // Vector of nonlinear diffusion evolution
    std::vector<tevolution> evolution;	

    // Vector of keypoint vectors for finding extrema in multiple threads
    std::vector<std::vector<cv::KeyPoint> > kpts_par;

    // Computation times variables in ms
    double tkcontrast;	// Kcontrast factor computation
    double tnlscale;	// Nonlinear Scale space generation
    double tdetector;	// Feature detector
    double tmderivatives; // Multiscale derivatives computation
    double tdresponse;	// Detector response computation
    double tdescriptor;	// Feature descriptor
    double tsubpixel;	// Subpixel refinement

    // Some auxiliary variables used in the AOS step
    cv::Mat Ltx, Lty, px, py, ax, ay, bx, by, qr, qc;

    // Methods used in the nonlinear scale space construction
    void Allocate_Memory_Evolution(void);
    void Compute_KContrast(const cv::Mat &img, const float &kper);
    void Compute_Multiscale_Derivatives(void);

public:

    // Constructor
    explicit KAZE(KAZEOptions &options);

    // Feature Detection Methods
    int Create_Nonlinear_Scale_Space(const cv::Mat &img);
    void Compute_Detector_Response(void);
    void Feature_Detection(std::vector<cv::KeyPoint> &kpts);
    void Find_Extrema_Parallel(std::vector<cv::KeyPoint> &kpts);
    void Do_Subpixel_Refinement(std::vector<cv::KeyPoint> &kpts);

    // AOS Methods
    void AOS_Step_Scalar(cv::Mat &Ld, const cv::Mat &Ldprev, const cv::Mat &c, const float stepsize);
    void AOS_Rows(const cv::Mat &Ldprev, const cv::Mat &c, const float stepsize);
    void AOS_Columns(const cv::Mat &Ldprev, const cv::Mat &c, const float stepsize);
    void Thomas(cv::Mat a, cv::Mat b, cv::Mat Ld, cv::Mat x);

    // Feature Description methods
    void Feature_Description(std::vector<cv::KeyPoint> &kpts, cv::Mat &desc);
};

//*************************************************************************************
//*************************************************************************************

#endif
