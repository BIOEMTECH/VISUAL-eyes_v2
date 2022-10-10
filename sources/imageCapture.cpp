/**
 * Image Capture
 * imageCapture.cpp
 * Purpose:The implementation imageCapture class. We use the video, that contains the bed entering the imaging system, in order to
 * create an image of the bed.
 *
 * @author: Evangelos Mavropoulos
 * @date: 1/8/2018
 */

#include <iostream>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/videoio.hpp>
#include "headers/imageCapture.hpp"
using namespace cv;
using namespace std;

/**
 * @brief From video to image.
 * This function takes the filename of a video as input and returns an image, created by the frames of the video.
 *
 * @param videoFilename filename of the video.
 * @param angle angle for correction rotation of the output image.
 * @return the output images
 */
Mat bioemtec::imageCapture::fromVideoToImage(string &videoFilename, double angle) {
     m_counter=0;
	string fileName = videoFilename;
	Mat currFrame, prevFrame, outputImage;
	VideoCapture inputVideo(fileName);
	if (!inputVideo.isOpened()) {
		cout << "Could not open input video " << fileName << endl;
		return outputImage;
	}
	inputVideo >> currFrame;
	int counter = 1;
	while (!currFrame.empty()) {
		if (!currFrame.empty() && counter >= this->firstFrame && counter <= this->lastFrame) {
            cvtColor(currFrame, currFrame, cv::COLOR_BGR2GRAY);
			this->addRows(outputImage, currFrame, this->scannerSliceUpperLeftestPoint,
                    this->scannerSliceWidth, this->scannerSliceHeight, this->motion);
			if (counter == this->lastFrame) {
				this->scannerSliceUpperLeftestPoint.y += this->scannerSliceWidth;
				this->addRows(outputImage, currFrame, this->scannerSliceUpperLeftestPoint,
                        this->scannerSliceWidth, this->extraSliceHeight, this->motion);
				break;
			}
		}
		currFrame.copyTo(prevFrame);
		inputVideo >> currFrame;
		counter++;
        if (currFrame.empty() && counter > this->firstFrame && counter < this->lastFrame && this->extraSliceHeight > 0) {
            cvtColor(currFrame, currFrame, cv::COLOR_BGR2GRAY);
			this->scannerSliceUpperLeftestPoint.y += this->scannerSliceWidth;
			this->addRows(outputImage, prevFrame, this->scannerSliceUpperLeftestPoint,
            this->scannerSliceWidth, this->extraSliceHeight, this->motion);
			break;
		}

	}

	GaussianBlur(outputImage, outputImage, Size(5, 5), 10, 10, BORDER_REPLICATE);
	if (angle > 0) {
		Point2f center((outputImage.cols - 1) / 2.0, (outputImage.rows - 1) / 2.0);
		Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
		warpAffine(outputImage, outputImage, rot, outputImage.size());
	}

	return outputImage;
}

/**
 * @brief Addition of a new slice to the image.
 * Using this function, we add a new slice to the image. The slice size is defined by the input parameters.
 *
 * @param outputImage
 * @param _inputFrame
 * @param scannerSliceLeftestPoint the upper leftest point of the scanner slice
 * @param scannerSliceLength the length of the scanner slice (horizontal)
 * @param scannerSliceWidth the width of the scanner slice (vertical)
 * @param upwards motion of the video (true = upwards, false = downwards)
 */
void bioemtec::imageCapture::addRows(Mat &outputImage, Mat &_inputFrame, Point2i scannerSliceUpperLeftestPoint, int scannerSliceWidth, int scannerSliceHeight, bool upwards) {
	Mat inputFrame;
	_inputFrame.copyTo(inputFrame);
	if (upwards) {       
		Mat newOutput = inputFrame(
				Rect(scannerSliceUpperLeftestPoint.x, scannerSliceUpperLeftestPoint.y,
                        scannerSliceWidth, scannerSliceHeight));
		outputImage.push_back(newOutput);
	}
	else {
//        imwrite("snap"+to_string(m_counter)+".png",inputFrame);
		Mat newOutput = inputFrame(
				Rect(scannerSliceUpperLeftestPoint.x, scannerSliceUpperLeftestPoint.y,
                        scannerSliceWidth, scannerSliceHeight));
        m_counter++;
        rotate(newOutput, newOutput, cv::ROTATE_90_CLOCKWISE);
		outputImage.push_back(newOutput);
	}
}

bioemtec::imageCapture::imageCapture() {
	this->scannerSliceUpperLeftestPoint.x = 0;
	this->scannerSliceUpperLeftestPoint.y = 0;
    this->scannerSliceWidth = 0;
    this->scannerSliceHeight = 0;
    this->extraSliceHeight = 0;
	this->firstFrame = 0;
	this->lastFrame = 0;
	this->motion = false;
}

/**
 *	@brief imageCapture class constructor.
 *	Uses the config method in order to initialize the class member variables.
 *	@param configFileName the filename of the configuration file
 */
bioemtec::imageCapture::imageCapture(std::string &configFileName) {
	this->config(configFileName);
}

bioemtec::imageCapture::~imageCapture() {
}

/**
 * @brief reads the configurations from the configuration file.
 *
 * @param configFileName the filename of the configuration file
 */
void bioemtec::imageCapture::config(string &configFileName) {
	ifstream config;
	config.open(configFileName, ios::in);


	if (config.is_open()) {
        char data[256];
        string numString;

		config >> numString;
		this->scannerSliceUpperLeftestPoint.x = stoi(numString);
		config.getline(data, 256);

		config >> numString;
		this->scannerSliceUpperLeftestPoint.y = stoi(numString);
		config.getline(data, 256);
		cout << "Scanner Slice Upper Leftest Point: (" << this->scannerSliceUpperLeftestPoint.x
				<< ", " << this->scannerSliceUpperLeftestPoint.y << ")" << endl;

		config >> numString;
        this->scannerSliceWidth = stoi(numString);
		config.getline(data, 256);
        cout << "Scanner Slice Length: " << this->scannerSliceWidth << endl;

		config >> numString;
        this->scannerSliceHeight = stoi(numString);
		config.getline(data, 256);
        cout << "Scanner Slice Width: " << this->scannerSliceHeight << endl;

		config >> numString;
        this->extraSliceHeight = stoi(numString);
		config.getline(data, 256);
        cout << "Extra Slice Width: " << this->extraSliceHeight << endl;

		config >> numString;
		this->firstFrame = stoi(numString);
		config.getline(data, 256);
		cout << endl;
		cout << "First Frame: " << this->firstFrame << endl;

		config >> numString;
		this->lastFrame = stoi(numString);
		config.getline(data, 256);
		cout << "Last Frame: " << this->lastFrame << endl;

		config >> numString;
		int motionTemp = stoi(numString);
		config.getline(data, 256);

		if (motionTemp > 0) {
			this->motion = true;
		}
		else {
			this->motion = false;
		}
		cout << "Upward motion: " << this->motion << endl;
	}
	else {
		cout << "Unable to open configuration file" << endl;
		exit(-1);
	}
}




