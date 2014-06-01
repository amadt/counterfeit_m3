#ifndef __COLOR_EVALUATOR_H__
#define __COLOR_EVALUATOR_H__

#include "Types.h"
#include "cocos2d.h"

class ColorEvaluator
{

public:
	ColorEvaluator();

	void AddColor(Color color);
	std::pair<Color, int>  Evaluate();

private:
	
	int _r;
	int _g;
	int _b;
	int _c;
	int _m;
	int _y;
};


#endif