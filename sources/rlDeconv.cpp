/**
 * Deconvolution
 * deconv.cpp
 * Purpose:The implementation of Richardson-Lucy deconvolution algorithm and the calculation of the psf.
 *
 * @author: Evangelos Mavropoulos
 * @date: 1/2/2018
 */

#include "headers/rlDeconv.hpp"
//#include <opencv2/tracking.hpp>
//#include <opencv2/plot.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
#include <boost/math/special_functions/expint.hpp>
#include <algorithm>
#include <numeric>
#include <iostream>

#ifdef ENABLE_TIME_MEASURE_MACRO
#include <chrono>
using namespace std::chrono;
#endif

using namespace std;
using namespace cv;
using boost::math::constants::pi;
/**
 * @brief Save psf into .txt file.
 *
 * @param outputFileName
 */
void bioemtec::rlDeconv::savePSF(string outputFileName) {
    if (this->psfMat.rows > 0 && this->psfMat.cols > 0) {
        FILE * this_file;
        this_file = fopen(outputFileName.c_str(), "w+");
        rewind(this_file);

        if (this_file != NULL) {
            cout << "Output file " << outputFileName << " successfully saved"
                 << endl;
            for (int i = 0; i < this->psfMat.rows; i++) {
                for (int j = 0; j < this->psfMat.cols; j++) {
                    fprintf(this_file, "%f ", this->psfMat.at<float> (i, j));
                }
                fprintf(this_file, "\n");
            }
        } else {
            std::cout << "Error opening output file" << endl;
            exit(0);
        }
        fclose(this_file);
    } else {
        cout << "PSF is empty" << endl;
    }
}

bioemtec::rlDeconv::rlDeconv() {
}

/**
 * @brief Constructor of rlDeconv class.
 * Constructor of rlDeconv class. It calculate the psf that is necessary for the deconvolution process.
 * res = arg * dist + res0
 *
 * @param sizeX rows of the psf
 * @param sizeY cols of the psf
 * @param dist1 minimum distance of the subject from the base of the camera
 * @param dist2 maximum distance of the subject from the base of the camera
 * @param res0 resolution of the camera at distance of 0mm
 * @param arg the argument of the function that is used for the calculation of the resolution at a specific distance
 * @param pixelSize size of pixel in mm
 */
bioemtec::rlDeconv::rlDeconv(int sizeX, int sizeY, int dist1, int dist2,
                             double res0, double arg, double pixelSize) {
    this->PSF(sizeX, sizeY, dist1, dist2, res0, arg, pixelSize);
}

bioemtec::rlDeconv::~rlDeconv() {
    this->psfMat.release();
}

/**
 * @brief The implementation of the Richardson-Lucy deconvolution.
 *
 *  Lucy–Richardson deconvolution is an iterative procedure for recovering a latent
 *  image that has been blurred by a known point spread function.
 *
 * @param inputImage the input image of the deconvolution.
 * @param outputImage the result of the deconvolution.
 * @param iterations the iterations of the deconvolution.
 * @param dampar noise damping scale.
 * @param histAdj percentage of lower pixel values that are suppressed.
 */
void bioemtec::rlDeconv::deconv(const Mat& inputImage, Mat& outputImage,
                                int iterations, double dampar, double histAdj) {

    if (this->psfMat.rows != this->psfMat.cols) {
        cout << "The psf must be a square image (rows = cols)." << endl;
        exit(0);
    }

    if (inputImage.channels() > 1) {
        cout << "The input image must contain only one channel." << endl;
        exit(0);
    }

    if (this->psfMat.cols < inputImage.cols && this->psfMat.rows
            < inputImage.rows) {
        cout << "The input image must have the same dimensions as the psf."
             << endl;
        exit(0);
    }

    copyMakeBorder(inputImage, outputImage, 0,
                   this->psfMat.rows - inputImage.rows, 0,
                   this->psfMat.cols - inputImage.cols, BORDER_REPLICATE);

    Mat OST(this->psfMat.rows, this->psfMat.cols, CV_32F);
    dft(this->psfMat, OST);

#ifdef ENABLE_TIME_MEASURE_MACRO
    high_resolution_clock::time_point t1, t2;
    t1 = high_resolution_clock::now();
    t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds> (t2 - t1).count();
    vector<int> dur;
#endif
    double lambda = 0;
    int gm = 10;
    Mat Gk1(1, outputImage.cols * outputImage.rows, CV_32F, Scalar::all(0)),
            Gk2,
            Xk,
            Xk1(outputImage.rows, outputImage.cols, CV_32F, Scalar::all(0)),
            h(outputImage.rows, outputImage.cols, CV_32F, Scalar::all(0)),
            y(outputImage.rows, outputImage.cols, CV_32F, Scalar::all(0)),
            Y, ReBlurred, ImRatio, AnEstimate, CC, temp, temp2, wI, weight, conjOTF, SCALE,
            scale, tempG, powG, TEMP, tempOutput;

    outputImage.copyTo(wI);
    dft(Mat::ones(outputImage.rows, outputImage.cols, CV_32F), weight);
    mulSpectrums(weight, OST, SCALE, 0, true);
    dft(SCALE, scale, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
    scale = scale + sqrt(FLT_EPSILON);
    outputImage.copyTo(Xk);
    double tempDampar = dampar * dampar / 2;

    for (int k = 0; k < iterations; k++) {
#ifdef ENABLE_TIME_MEASURE_MACRO
        t1 = high_resolution_clock::now();
#endif
        if (k > 1) {
            lambda = Gk1.dot(Gk2) / (Gk2.dot(Gk2) + FLT_EPSILON);
            lambda = max(min(lambda, 1.0), 0.0);
        }
        h = (Xk - Xk1);
        y = max(Xk + (lambda * h), 0);
        dft(y, Y);
        mulSpectrums(OST, Y, Y, 0, false);
        dft(Y, ReBlurred, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
        ReBlurred = max(ReBlurred, FLT_EPSILON);
        fftShift(ReBlurred, ReBlurred);
        //circShift1(ReBlurred, ReBlurred);

        divide(outputImage, ReBlurred, ImRatio);
        AnEstimate = ImRatio + FLT_EPSILON;
        if (tempDampar == 0) {
            ImRatio = AnEstimate;
        } else {
            cv::log(AnEstimate, tempG);
            tempG = (wI.mul(tempG) + ReBlurred - wI) / tempDampar;
            tempG = min(tempG, 1.0);
            pow(tempG, gm - 1, powG);
            tempG = (gm - (gm - 1) * tempG).mul(powG);
            ImRatio = 1 + tempG.mul(AnEstimate - 1);
        }
        dft(ImRatio, CC);
        Xk.copyTo(Xk1);
        mulSpectrums(CC, OST, TEMP, 0, true);
        dft(TEMP, tempOutput, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
        fftShift(tempOutput, tempOutput);
        //circShift2(tempOutput, tempOutput);
        multiply(tempOutput, y, Xk);
        Xk = Xk / scale;
        Xk = max(Xk, 0);
        Gk1.copyTo(Gk2);
        subtract(Xk, y, temp2);
        transpose(temp2, temp2);
        Gk1 = temp2.reshape(0, 1);
#ifdef ENABLE_TIME_MEASURE_MACRO
        t2 = high_resolution_clock::now();
        duration = duration_cast<microseconds> (t2 - t1).count();
        dur.push_back(duration);
#endif
    }
#ifdef ENABLE_TIME_MEASURE_MACRO
    sort(dur.begin(), dur.end());
    float meanTime = accumulate(dur.begin() + 2, dur.end() - 2, 0.0) / (iterations - 4);
    cout << meanTime << "μs" << endl;
#endif

    Xk.copyTo(outputImage);

    double min, max;
    outputImage = outputImage(Rect(0, 0, inputImage.cols, inputImage.rows));
    minMaxLoc(inputImage, &min, &max);

    normalize(outputImage, outputImage, min, max, CV_MINMAX);

    if (histAdj > 0.0) {
        imAdjust(outputImage, outputImage, histAdj);
    }
}

/**
 * @brief The calculation of the psf.
 *
 * The calculation of psf using the definite integral of a Gauss function. The start value is equal to the distance
 * of the object from the camera and the end value is equal to the distance plus the height of the object.
 *
 * @param _sizeX rows of the psf
 * @param _sizeY cols of the psf
 * @param dist1 minimum distance of the subject from the base of the camera
 * @param dist2 maximum distance of the subject from the base of the camera
 * @param res0 resolution of the camera at distance of 0 mm
 * @param arg the argument of the function that is used for the calculation of the resolution at a specific distance
 * @param pixelSize size of pixel in mm
 */
void bioemtec::rlDeconv::PSF(int _sizeX, int _sizeY, int dist1, int dist2,
                             double res0, double arg, double pixelSize) {

    int sizeX = _sizeX & -2; //dft works only for even size matrices
    int sizeY = _sizeY & -2;

    this->psfMat = Mat(sizeX, sizeY, CV_32F, Scalar::all(0));
    double x0 = (double) sizeX / 2;
    double y0 = (double) sizeY / 2;
    double integral1, integral2;

    double res1 = arg * dist1 + res0;
    res1 = res1 / pixelSize; //from mm to pixels
    double sigma1 = res1 / (2 * sqrt(2 * log(2)));
    double sigmaSquare1 = sigma1 * sigma1;

    double res2 = arg * dist2 + res0;
    res2 = res2 / pixelSize; //from mm to pixels
    double sigma2 = res2 / (2 * sqrt(2 * log(2)));
    double sigmaSquare2 = sigma2 * sigma2;
    double a = sqrt(2.0f * pi<double> ());

    for (int i = 1; i <= sizeX; i++) {
        for (int j = 1; j <= sizeY; j++) {
            double b = (i - x0) * (i - x0) + (j - y0) * (j - y0);
            b /= 2;
            if (sigma1 == 0) {
                integral1 = 0;
            } else if (b == 0) {
                integral1 = log(sigma1);
            } else {
                integral1 = -0.5f * boost::math::expint(-b / (sigmaSquare1));
            }
            if (sigma2 == 0) {
                integral2 = 0;
            } else if (b == 0) {
                integral2 = log(sigma2);
            } else {
                integral2 = -0.5f * boost::math::expint(-b / (sigmaSquare2));
            }
            this->psfMat.at<float> (i - 1, j - 1) = static_cast<float> ((1 / a)
                                                                        * (integral2 - integral1));
        }
    }
}

/**
 * @brief FFT Shift
 *
 * Fourier transform image shift. 	Rearranges the quadrants of Fourier image so that the origin is at the image center.
 *
 * @param inputImage the image that we want to apply the FFT shift
 * @param outputImage the result of the FFT shift
 */
void bioemtec::rlDeconv::fftShift(const Mat& inputImage, Mat& outputImage) {
    Mat mag;
    inputImage.copyTo(mag);
    int cx = (float) mag.cols / 2;
    int cy = (float) mag.rows / 2;

    Mat tmp;
    Mat q0(mag, Rect(0, 0, cx, cy));
    Mat q1(mag, Rect(cx, 0, cx, cy));
    Mat q2(mag, Rect(0, cy, cx, cy));
    Mat q3(mag, Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    tmp.release();

    mag.copyTo(outputImage);

    mag.release();
}

/**
 * @brief Histogram Adjustment of the Image
 *
 * The adjustment of the histogram by suppressing a percentage of the minimum values to zero.
 *
 * @param _inputImage the image that we want to apply the FFT shift
 * @param _outputImage the result of the FFT shift
 * @param clipPerc the percentage of lowest pixel values that are suppressed to zero.
 */
void bioemtec::rlDeconv::imAdjust(const Mat& _inputImage, Mat& _outputImage,
                                  float clipPerc) {

    Mat inputImage, outputImage;
    _inputImage.copyTo(inputImage);

    double min, max;
    minMaxLoc(inputImage, &min, &max);
    double clipValue = max * clipPerc;

    normalize(inputImage, outputImage, -clipValue, max, CV_MINMAX);
    minMaxLoc(outputImage, &min, &max);

    threshold(outputImage, outputImage, 0, max, THRESH_TOZERO);
    outputImage.copyTo(_outputImage);

}

