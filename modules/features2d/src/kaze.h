
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

public:

    // Constructor
    explicit KAZE(KAZEOptions &options);

    void Allocate_Memory_Evolution(void);
    int Create_Nonlinear_Scale_Space(const cv::Mat &img);
    void Compute_KContrast(const cv::Mat &img, const float &kper);
    void Compute_Multiscale_Derivatives(void);

    // Feature Detection Methods
    void Compute_Detector_Response(void);
    void Feature_Detection(std::vector<cv::KeyPoint> &kpts);
    void Determinant_Hessian_Parallel(std::vector<cv::KeyPoint> &kpts);
    void Find_Extremum_Threading(int level);
    void Do_Subpixel_Refinement(std::vector<cv::KeyPoint> &kpts);
    void Feature_Suppression_Distance(std::vector<cv::KeyPoint> &kpts, float mdist);

    // AOS Methods
    void AOS_Step_Scalar(cv::Mat &Ld, const cv::Mat &Ldprev, const cv::Mat &c, const float stepsize);
    void AOS_Step_Scalar_Parallel(cv::Mat &Ld, const cv::Mat &Ldprev, const cv::Mat &c, const float stepsize);
    void AOS_Rows(const cv::Mat &Ldprev, const cv::Mat &c, const float stepsize);
    void AOS_Columns(const cv::Mat &Ldprev, const cv::Mat &c, const float stepsize);
    void Thomas(cv::Mat a, cv::Mat b, cv::Mat Ld, cv::Mat x);

    // Methods for saving the scale space set of images and detector responses
    void Save_Nonlinear_Scale_Space(void);
    void Save_Detector_Responses(void);
    void Save_Flow_Responses(void);

    // Feature Description methods
    void Feature_Description(std::vector<cv::KeyPoint> &kpts, cv::Mat &desc);
    void Compute_Main_Orientation_SURF(cv::KeyPoint &kpt);

    // Descriptor Mode -> 0 SURF 64
    void Get_SURF_Upright_Descriptor_64(cv::KeyPoint &kpt, float *desc);
    void Get_SURF_Descriptor_64(cv::KeyPoint &kpt, float *desc);

    // Descriptor Mode -> 0 SURF 128
    void Get_SURF_Upright_Descriptor_128(cv::KeyPoint &kpt, float *desc);
    void Get_SURF_Descriptor_128(cv::KeyPoint &kpt, float *desc);

    // Descriptor Mode -> 1 M-SURF 64
    void Get_MSURF_Upright_Descriptor_64(cv::KeyPoint &kpt, float *desc);
    void Get_MSURF_Descriptor_64(cv::KeyPoint &kpt, float *desc);

    // Descriptor Mode -> 1 M-SURF 128
    void Get_MSURF_Upright_Descriptor_128(cv::KeyPoint &kpt, float *desc);
    void Get_MSURF_Descriptor_128(cv::KeyPoint &kpt, float *desc);

    // Descriptor Mode -> 2 G-SURF 64
    void Get_GSURF_Upright_Descriptor_64(cv::KeyPoint &kpt, float *desc);
    void Get_GSURF_Descriptor_64(cv::KeyPoint &kpt, float *desc);

    // Descriptor Mode -> 2 G-SURF 128
    void Get_GSURF_Upright_Descriptor_128(cv::KeyPoint &kpt, float *desc);
    void Get_GSURF_Descriptor_128(cv::KeyPoint &kpt, float *desc);
};

// Inline functions
float Get_Angle(float X, float Y);
float gaussian(float x, float y, float sig);

//*************************************************************************************
//*************************************************************************************

#endif
