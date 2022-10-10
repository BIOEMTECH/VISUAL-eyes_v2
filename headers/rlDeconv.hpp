/**
 * Deconvolution
 * deconv.hpp
 * Purpose: The declaration of Richardson Lucy deconvolution class(rlDeconv).
 * @author: Evangelos Mavropoulos
 * @date: 1/2/2018
 */

#ifndef DECONVOLUTION_HPP_
#define DECONVOLUTION_HPP_

#include <opencv2/opencv.hpp>
#include <string>

namespace bioemtec {
/**
 * @brief A class that contains the implementation of the Richardson-Lucy deconvolution algorithm.
 */
class rlDeconv {

public:
    rlDeconv();
    rlDeconv(int _sizeX, int _sizeY, int dist1, int dist2, double res0,
            double arg, double pixelSize);
    ~rlDeconv();

    void deconv(const cv::Mat& inputImage, cv::Mat& outputImage, int iterations,
			double dampar = 0, double histAdj = 0);
    void fftShift(const cv::Mat& inputImage, cv::Mat& outputImage);
    void savePSF(std::string outputFileName = "PSF.txt");
    void imAdjust(const cv::Mat& _inputImage, cv::Mat& _outputImage, float clipPerc);

protected:
	cv::Mat psfMat; /**<Container of the PSF*/
    void PSF(int, int, int, int, double, double, double);
};
}
#endif /* DECONVOLUTION_HPP_ */
