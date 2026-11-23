#pragma once

#include <opencv2/opencv.hpp>
#include "Types.h"

class CoinDetector {
public:
	CoinDetector(double dp = 1.0, double minDist = 50.0,
				 double param1 = 100.0, double param2 = 70.0,
				 int minRadius = 70, int maxRadius = 400);

	std::vector<Coin> detect(const cv::Mat& image);
	void drawDetections(cv::Mat& image, const std::vector<Coin>& detections);

private:
	double dp_, minDist_, param1_, param2_;
	int minRadius_, maxRadius_;
};