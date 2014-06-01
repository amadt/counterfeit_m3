#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include "cocos2d.h"
#include <sstream>

class Utils
{
public:
	static std::string getFont() { return "fonts/MerriweatherSans-Regular.ttf"; }
	static std::string getBoldFont() { return "fonts/MerriweatherSans-Bold.ttf"; }
	static std::string getBoldItalicFont() { return "fonts/MerriweatherSans-BoldItalic.ttf"; }
	static std::string getExtraBoldFont() { return "fonts/MerriweatherSans-ExtraBold.ttf"; }
	static std::string getExtraBoldItalicFont() { return "fonts/MerriweatherSans-ExtraBoldItalic.ttf"; }
	static std::string getLightFont() { return "fonts/MerriweatherSans-Light.ttf"; }
	static std::string getLightItalicFont() { return "fonts/MerriweatherSans-LightItalic.ttf"; }

	template <typename T>
	static std::string NumberToString(T Number)
	{
		std::ostringstream ss;
		ss << Number;
		return ss.str();
	}
};



#endif // __UTIL_H__