/**
 * ROI Manager
 * roiManager.hpp
 * Purpose: The declaration of ROI Manager class for the extraction of ROIs and ROI statistics.
 *
 * @author: Evangelos Mavropoulos
 * @date: 1/2/2018
 */

#ifndef ROIMANAGER_HPP_
#define ROIMANAGER_HPP_

#include <stdint.h>
#include <utility>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <numeric>

namespace bioemtec {
/**
 * @brief An enum that contains the type of ROIs (RECTANGLE, ELLIPSE, FREEDRAW).
 */
enum roiType {
	RECTANGLE, ELLIPSE, FREEDRAW
};
/**
 * @brief A class that contains the necessary methods for the extraction of ROIs and the measurement of statistics(mean, std, sensitivity).
 */
class roiManager {
public:
	/**
	 * @brief Extraction of RECTANGLE and ELLIPSE ROI mask
	 */
	static void roiMap(cv::Mat mask, cv::Point upperLeft, cv::Point lowerRight,
			roiType rt);
	/**
	 * @brief Extraction of FREEDRAW ROI mask.
	 */
	static void roiMap(cv::Mat mask, std::vector<cv::Point> &points);
	/**
	 * @brief Statistics of RECTANGLE and ELLIPSE ROI.
	 */
	static void roiStatistics(cv::Mat inputImage, cv::Point upperLeft,
			cv::Point lowerRight, float& mean, float& stdev,
            float& sensitivity, roiType rt, bool isBeta);
	/**
	 * @brief Statistics of FREEDRAW ROI.
	 */
	static void roiStatistics(cv::Mat inputImage,
			std::vector<cv::Point> &points, float& mean, float& stdev,
            float& sensitivity, bool isBeta);
};
}

#endif /* ROIMANAGER_HPP_ */
