/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2009, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/** Authors: Ievgen Khvedchenia */

#include "precomp.hpp"
#include "KAZE.h"
#include <iterator>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace cv
{
    KAZE::KAZE()
    {

    }

    int KAZE::descriptorSize() const
    {
        return 64; // TODO Return 128 if descriptor type is extended
    }

    int KAZE::descriptorType() const
    {
        return CV_32F;
    }

    void KAZE::operator()(InputArray image, InputArray mask, vector<KeyPoint>& keypoints) const
    {
        (*this)(image, mask, keypoints, noArray(), false);
    }

    void KAZE::operator()(InputArray _image, InputArray _mask, vector<KeyPoint>& _keypoints,
        OutputArray _descriptors, bool useProvidedKeypoints) const
    {

        bool do_keypoints = !useProvidedKeypoints;
        bool do_descriptors = _descriptors.needed();

        if( (!do_keypoints && !do_descriptors) || _image.empty() )
            return;

        cv::Mat img1_32;
        _image.getMat().convertTo(img1_32, CV_32F, 1.0/255.0,0);

        KAZEOptions opt;
        opt.img_width = img1_32.cols;
        opt.img_height = img1_32.rows;

        ::KAZE evolution(opt);

        evolution.Create_Nonlinear_Scale_Space(img1_32);

        if (do_keypoints)
        {
            evolution.Feature_Detection(_keypoints);

            if (!_mask.empty())
            {
                KeyPointsFilter::runByPixelsMask(_keypoints, _mask.getMat());
            }
        }

        if (do_descriptors)
        {
            //cv::KeyPointsFilter::runByImageBorder(_keypoints, cv::Size(opt.img_width, opt.img_height), 40);
            cv::Mat& descriptors = _descriptors.getMatRef();
            evolution.Feature_Description(_keypoints, descriptors);
        }
    }

    void KAZE::detectImpl( const Mat& image, vector<KeyPoint>& keypoints, const Mat& mask) const
    {
        (*this)(image, mask, keypoints, noArray(), false);
    }

    void KAZE::computeImpl( const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors) const
    {
        (*this)(image, Mat(), keypoints, descriptors, true);
    }

}
