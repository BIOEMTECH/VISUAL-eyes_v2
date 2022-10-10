/**
 * Image Fusion
 * imageFusion.hpp
 *
 * Purpose: The declaration of imageFusion class.
 * @author: Evangelos Mavropoulos
 * @date: 22/11/2018
 */

#ifndef IMAGEFUSION_HPP_
#define IMAGEFUSION_HPP_

#include <string>
#include <opencv2/core.hpp>


/**
 * @brief A class that contains the necessary methods image fusion.
 */
class imageFusion {
    public:
        imageFusion();
        ~imageFusion();
        static cv::Mat
        fusion(cv::Mat &_cameraImage, cv::Mat &_gEyeCameraImage, std::string &lutFilename);
    private:
        static cv::Mat readLUT(std::string &lutFilename);
};



#endif /* IMAGEFUSION_HPP_ */
