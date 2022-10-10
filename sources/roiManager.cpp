/**
 * ROI Manager
 * roiManager.hpp
 * Purpose: The declaration of ROI Manager class for the extraction of ROIs and the calculation of ROI statistics.
 *
 * @author: Evangelos Mavropoulos
 * @date: 1/2/2018
 */

#include "headers/roiManager.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <opencv2/core/types.hpp>

//using namespace std;
//using namespace cv;

/**
 * @brief Extraction of RECTANGLE and ELLIPSE ROI mask.
 *
 * Returns an image-mask in which the pixels that are included in the ROI have the
 * value of 1 and the pixels that are excluded from the ROI have the value of 0.
 * In order to define the position of the ROI we use a set of points, the upper left and the
 * lower right corner of a rectangle. If the type of ROI is Ellipse then we define as ROI the
 * ellipse that fits in the rectangle of the given set of points.
 *
 * @param mask the output of the roiMap
 * @param upperLeft coordinates of the upper left corner of the ROI
 * @param lowerRight coordinates of the lower right corner of the ROI
 * @param rt type of ROI.
 */
void bioemtec::roiManager::roiMap(cv::Mat mask, cv::Point upperLeft, cv::Point lowerRight,
		roiType rt) {

	if (rt == 0) {
		cv::Rect roiArea(upperLeft, lowerRight);

        cv::rectangle(mask, roiArea, 1, cv::FILLED);

	} else if (rt == 1) {
		float ellipseHorAxis = lowerRight.y - upperLeft.y, ellipseVerAxis =
				lowerRight.x - upperLeft.x;
		float ellipseCenterY = upperLeft.y + ellipseHorAxis / 2,
				ellipseCenterX = upperLeft.x + ellipseVerAxis / 2;

		cv::Point ellipseCenter(ellipseCenterY, ellipseCenterX);
		cv::Size ellipseAxes(ellipseHorAxis / 2, ellipseVerAxis / 2);

        cv::ellipse(mask, ellipseCenter, ellipseAxes, 0, 0, 360, 1, cv::FILLED);

	}
}

/**
 * @brief Extraction of FREEDRAW ROI mask.
 *
 * Returns an image-mask in which the pixels that are included in the ROI have the
 * value of 1 and the pixels that are excluded from the ROI have the value of 0.
 * This member method is used for the free draw mode. In order to define the
 * position of the ROI we use a vector of Points.
 *
 * @param mask the output of the roiMap
 * @param points a vector of points
 */
void bioemtec::roiManager::roiMap(cv::Mat mask, std::vector<cv::Point> &points) {

	int i = 0;
	cv::Point vertices[points.size()];
	for (auto it = points.begin(); it != points.end(); it++, i++) {
		vertices[i] = *it;
	}
	cv::fillConvexPoly(mask, vertices, points.size(), 1);

}

/**
 * @brief Statistics of RECTANGLE and ELLIPSE ROI.
 *
 * Returns the mean,std and sensitivity of a rectangle or ellipse type ROI.
 *
 * @param inputImage  the image that contains the ROI
 * @param upperLeft the coordinates of the upper left corner of the ROI
 * @param lowerRight the coordinates of the lower right corner of the ROI
 * @param mean the mean of ROI
 * @param stdev the standard deviation of ROI
 * @param sensitivity the sensitivity of ROI
 * @param rt type of ROI.
 */
void bioemtec::roiManager::roiStatistics(cv::Mat inputImage, cv::Point upperLeft,
		cv::Point lowerRight, float& mean, float& stdev, float& sensitivity,
        roiType rt, bool isBeta) {

	int rows = inputImage.rows, cols = inputImage.cols;
	std::vector<int32_t> roiVec;
	cv::Mat mask(rows, cols, CV_32S, cv::Scalar(0));
	roiMap(mask, upperLeft, lowerRight, rt);

    float scale = 0.0;
    if(isBeta){
        scale = 4.2*4.2;
    }else{
        scale = 5*5;
    }

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (mask.at<int32_t> (i, j) == 1) {
				roiVec.push_back(inputImage.at<int32_t> (i, j));
			}
		}
	}

	if (roiVec.size() == 0) {
		mean = 0;
		stdev = 0;
		sensitivity = 0;
	} else {
        int32_t sum = std::accumulate(roiVec.begin(), roiVec.end(), 0);
		mean = static_cast<float> (sum) / roiVec.size();
        float localStd = 0;
		for (auto it = roiVec.begin(); it != roiVec.end(); it++) {
			localStd += (*it - mean) * (*it - mean);
		}
        localStd /= roiVec.size() - 1;
		stdev = sqrt(localStd);
        std::cout << mean <<" "<< roiVec.size() << std::endl;
        sensitivity = mean * roiVec.size() / scale;
	}
}

/**
 * @brief Statistics of FREEDRAW ROI.
 *
 * Returns the mean,std and sensitivity of a freedraw type ROI.
 *
 * @param inputImage the image that contains the ROI
 * @param points a vector of points
 * @param mean the mean of ROI
 * @param stdev the standard deviation of ROI
 * @param sensitivity the sensitivity of ROI
 */
void bioemtec::roiManager::roiStatistics(cv::Mat inputImage, std::vector<cv::Point> &points,
        float& mean, float& stdev, float& sensitivity, bool isBeta) {

	std::vector<int32_t> roiVec;
	int rows = inputImage.rows, cols = inputImage.cols;
	cv::Mat mask(rows, cols, CV_32S, cv::Scalar(0));

	roiMap(mask, points);

    float scale = 0.0;
    if(isBeta){
        scale=2.625*2.625;
    }else{
        scale = 5*5;
    }
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (mask.at<int32_t> (i, j) == 1) {
				roiVec.push_back(inputImage.at<int32_t> (i, j));

			}
		}
	}

	if (roiVec.size() == 0) {
		mean = 0;
		stdev = 0;
		sensitivity = 0;
	} else {
        int32_t sum = std::accumulate(roiVec.begin(), roiVec.end(), 0);
		mean = static_cast<float> (sum) / roiVec.size();
        float localStd = 0;
		for (auto it = roiVec.begin(); it != roiVec.end(); it++) {
			localStd += (*it - mean) * (*it - mean);
		}
		localStd /= roiVec.size() - 1;
		stdev = sqrt(localStd);
        std::cout << roiVec.size() << std::endl;
        sensitivity = mean * roiVec.size() / scale;
	}
}
