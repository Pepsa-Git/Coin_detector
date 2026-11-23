#include "CoinDetector.h"

CoinDetector::CoinDetector(double dp, double minDist,
						   double param1, double param2,
						   int minRadius, int maxRadius)
	: dp_(dp), minDist_(minDist), param1_(param1), param2_(param2),
	minRadius_(minRadius), maxRadius_(maxRadius) 
{

}

std::vector<Coin> CoinDetector::detect(const cv::Mat& image) {
	cv::Mat img;

	int targetWidth = 1000;

	double scale = static_cast<double>(targetWidth) / image.cols;
	cv::resize(image, img, cv::Size(), scale, scale);
	

	cv::Mat gray, blurred;
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	cv::medianBlur(gray, blurred, 7);

	int minRadius = img.cols * 0.02;
	int maxRadius = img.cols * 0.15;

	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(blurred, circles, cv::HOUGH_GRADIENT, 1,
					  minRadius * 2.0, 100, 70, minRadius, maxRadius);

	std::vector<Coin> result;
	result.reserve(circles.size());

	double invScale = 1.0 / scale;
	for (const auto& c: circles) {
		result.emplace_back(c[0] * invScale, c[1] * invScale, c[2] * invScale);
	}
	
	return result;
}

void CoinDetector::drawDetections(cv::Mat& image, const std::vector<Coin>& detections) {
	for (const auto& d : detections) {
		cv::circle(image, cv::Point(cvRound(d.x), cvRound(d.y)),
				   cvRound(d.radius), cv::Scalar(0, 0, 255), 2);
		cv::circle(image, cv::Point(cvRound(d.x), cvRound(d.y)),
				   5, cv::Scalar(255, 0, 0), -1);
	}
}
