/**
 * Image Capture
 * imageCapture.hpp
 * Purpose: The declaration of imageCapture class.
 * @author: Evangelos Mavropoulos
 * @date: 1/8/2018
 */

#ifndef MOUSECAPTURE_HPP_
#define MOUSECAPTURE_HPP_
#include <string>
#include <opencv2/core.hpp>

namespace bioemtec {

	/**
	 * @brief A class that contains the necessary methods for the extraction of an image from a video.
	 */
	class imageCapture {
        public:
            imageCapture();
			imageCapture(std::string &configFilename);
			~imageCapture();
			cv::Mat fromVideoToImage(std::string &videoFilename, double angle = 0);

        private:
            void addRows(cv::Mat &outputImage, cv::Mat &_inputFrame, cv::Point2i scannerLineLeftestPoint, int scannerLineWidth, int scannerLineHeight, bool upwards);
			void config(std::string &configFileName);
			cv::Point2i scannerSliceUpperLeftestPoint;
            int scannerSliceWidth;
            int scannerSliceHeight;
            int extraSliceHeight;
			int firstFrame;
			int lastFrame;
			bool motion;
            int m_counter;
    };
};
#endif /* MOUSECAPTURE_HPP_ */
