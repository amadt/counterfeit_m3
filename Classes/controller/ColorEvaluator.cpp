#include "ColorEvaluator.h"
#include <math.h>      
#include "Types.h"

using namespace cocos2d;

ColorEvaluator::ColorEvaluator()
:_r(0)
, _g(0)
, _b(0)
, _c(0)
, _m(0)
, _y(0) {

}

void ColorEvaluator::AddColor(Color color) {

	switch (color)
	{
	case Color::RED:
		_r++;
		break;
	case Color::GREEN:
		_g++;
		break;
	case Color::BLUE:
		_b++;
		break;
	case Color::CYAN:
		_c++;
		break;
	case Color::PINK:
		_m++;
		break;
	case Color::YELLOW:
		_y++;
		break;
	}
}

std::pair<Color, int> ColorEvaluator::Evaluate() {

	std::pair<Color, int> ret;
	int rgbs = _r + _g + _b;
	int cmys = _c + _m + _y;
	int total = rgbs + cmys;

	if (_r == _g && _r == _b && _c == _m && _c == _y && total > 0) {
		ret.first = Color::BLACK;
		ret.second = _r * 3;
		return ret;
	}
	
	if (_g == 0 && _b == 0 && _c == 0 && _m == _y && (_r > 0 || _m > 0)) {
		ret.first = Color::RED;
		ret.second = _r + _g + _y ;
		return ret;
	}

	if (_r == 0 && _b == 0 && _m == 0 && _c == _y && (_g > 0 || _c > 0)) {
		ret.first = Color::GREEN;
		ret.second = _g + _y + _c;
		return ret;
	}

	if (_g == 0 && _r == 0 && _y == 0 && _c == _m && (_b > 0 || _c > 0)) {
		ret.first = Color::BLUE;
		ret.second = _b + _c + _m;
		return ret;
	}

	if (_m == 0 && _y == 0 && _r == 0 && _g == _b && (_c > 0 || _b > 0)) {
		ret.first = Color::CYAN;
		ret.second = _c + _g + _b;
		return ret;
	}

	if (_c == 0 && _y == 0 && _g == 0 && _r == _b && (_m > 0 || _b > 0)) {
		ret.first = Color::PINK;
		ret.second = _m + _r + _b;
		return ret;
	}

	if (_c == 0 && _m == 0 && _b == 0 && _r == _g && (_y > 0 || _r > 0)) {
		ret.first = Color::YELLOW;
		ret.second = _y + _r + _g;
		return ret;
	}
	ret.first = Color::INVALID;
	ret.second = -1;
	return ret;
}