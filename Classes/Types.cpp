#include "Types.h"

using namespace cocos2d;

float G_blobScale = 0.0f;

std::string colorToString(Color color) {

	if (color == Color::RED)	 return "red";
	if (color == Color::GREEN)	 return "green";
	if (color == Color::BLUE)	 return "blue";
	if (color == Color::CYAN)	 return "cyan";
	if (color == Color::PINK)    return "pink";
	if (color == Color::YELLOW)  return "yellow";
	return "";
}

cocos2d::Color4F colorToCCColor(Color color, float alpha)
{
	if (color == Color::RED)	 return ccc4f(225 / 255.f, 49 / 255.f, 49 / 255.f, alpha);
	if (color == Color::GREEN)	 return ccc4f(16 / 255.f, 189 / 255.f, 16 / 255.f, alpha);
	if (color == Color::BLUE)	 return ccc4f(38 / 255.f, 38 / 255.f, 216 / 255.f, alpha);
	if (color == Color::CYAN)	 return ccc4f(38 / 255.f, 216 / 255.f, 210 / 255.f, alpha);
	if (color == Color::PINK)    return ccc4f(216 / 255.f, 38 / 255.f, 214 / 255.f, alpha);
	if (color == Color::YELLOW)  return ccc4f(218 / 255.f, 221 / 255.f, 1 / 255.f, alpha);
	return ccc4f(25 / 255.f, 25 / 255.f, 25 / 255.f, alpha);
}