#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

#include "CoinDetector.h"

int main(int argc, char** argv) {
	if (argc < 2) return -1;
	cv::Mat img = cv::imread(argv[1]);
	if (img.empty()) return -1;

	CoinDetector detector;

	auto dets = detector.detect(img);
	detector.drawDetections(img, dets);

	cv::imshow("Result", img);
	cv::imwrite("output.png", img);
	cv::waitKey(0);

	return 0;
}