#pragma once

#include <opencv2/core.hpp>

struct Coin {
	float x;
	float y;
	float radius;

	Coin() : x(0.0f), y(0.0f), radius(0.0f) {}

	Coin(float _x, float _y, float _r) : x(_x), y(_y), radius(_r) {}

	cv::Point2f getCenter() const {
		return cv::Point2f(x, y);
	}

};