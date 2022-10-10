 /**
 * Image Fusion
 * imageFusion.cpp
 *
 * Purpose: The implementation imageFusion class. We fuse two images by changing the colormap of the gEye image and adding the to the camera image.
 * @author: Evangelos Mavropoulos
 * @date: 22/11/2018
 */

#include <iostream>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "headers/imageFusion.hpp"

using namespace std;
using namespace cv;

/**
 * @brief Adding two images.
 * This function fuses two images by adding them. The colormap of one gEyeCameraImage changes in order for the result to be successful.
 *
 * @param _cameraImage image output of the camera
 * @param _gEyeCameraImage image output of the gEye
 * @param lutFilename filename of the LUT containing the colormap
 * @return the fussed image
 */
Mat imageFusion::fusion(Mat &_cameraImage, Mat &_gEyeCameraImage, string &lutFilename) {
    if (_cameraImage.empty()) {
        cerr << "camera image is empty" << endl;
        return Mat::eye(10, 10, CV_8UC1);
    }
    else if (_gEyeCameraImage.empty()) {
        cerr << "gEye image is empty" << endl;
        return Mat::eye(10, 10, CV_8UC1);
    }

    Mat fussedImage, cameraImage, gEyeCameraImage;
    _cameraImage.copyTo(cameraImage);
    _gEyeCameraImage.copyTo(gEyeCameraImage);

    normalize(gEyeCameraImage, gEyeCameraImage, 0, 255, NORM_MINMAX);
    gEyeCameraImage.convertTo(gEyeCameraImage, CV_8UC1);
    cameraImage.convertTo(cameraImage, CV_8UC1);

    resize(cameraImage, cameraImage, Size(gEyeCameraImage.cols, gEyeCameraImage.rows), 0, 0,
            INTER_CUBIC);
    cvtColor(gEyeCameraImage, gEyeCameraImage, COLOR_GRAY2BGR);
    cvtColor(cameraImage, cameraImage, COLOR_GRAY2BGR);

    Mat lut = readLUT(lutFilename);
    LUT(gEyeCameraImage, lut, gEyeCameraImage);
    add(gEyeCameraImage, cameraImage, fussedImage);


    return fussedImage;
}

/**
 * @brief Reads the colormap file.
 *
 * @param lutFilename filename of the LUT containing the colormap
 * @return the LUT
 */
Mat imageFusion::readLUT(string &lutFilename) {
	ifstream config;
	config.open(lutFilename, ios::in);
	string numString;

	Mat lut(1, 256, CV_8UC(3));
	if (config.is_open()) {
		for (int i = 0; i < 256; i++) {
			config >> numString;
			config >> numString;
			lut.at<Vec3b> (i)[0] = stoi(numString);
			config >> numString;
			lut.at<Vec3b> (i)[1] = stoi(numString);
			config >> numString;
			lut.at<Vec3b> (i)[2] = stoi(numString);
		}
	}
	else {
		cerr << "Error opening colormap file";
	}
	return lut;
}

