#include "CoinDetector.h"

CoinDetector::CoinDetector(double dp, double minDist,
						   double param1, double param2,
						   int minRadius, int maxRadius)
	: dp_(dp), minDist_(minDist), param1_(param1), param2_(param2),
	minRadius_(minRadius), maxRadius_(maxRadius) 
{

}

std::vector<Coin> CoinDetector::detect(const cv::Mat& image) {
	cv::Mat gray, blurred;
	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 1.5);

	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(blurred, circles, cv::HOUGH_GRADIENT, dp_,
					  minDist_, param1_, param2_, minRadius_, maxRadius_);

	std::vector<Coin> result;
	result.reserve(circles.size());

	for (const auto& c: circles) {
		result.emplace_back(c[0], c[1], c[2]);
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
