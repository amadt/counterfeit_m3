#ifndef __TYPES_H__
#define __TYPES_H__

#include <string>
#include "cocos2d.h"

enum class Color {
	INVALID = -1, RED, GREEN, BLUE, CYAN, PINK, YELLOW, COUNT, BLACK
};

const int BLOB_PADDING = 10;
const int BLOB_MARGIN = 25;
const int LINE_POINT_RADIUS = 7;
const float LINE_PRECISION = 0.8f;
const int COLOR_MATCH_COUNT = 3;
const float DROP_SPEED = 0.15f;
const float DROP_SPEED_FAST = 0.08f;
const float ASSET_SCALE_WIDTH = 320;
const float TIME_AMOUNT = 20.0f;

std::string colorToString(Color color);
cocos2d::Color4F colorToCCColor(Color color, float alpha = 1.0f);


#endif // __TYPES_H__