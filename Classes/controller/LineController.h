#ifndef __LINE_CONTROLLER_H__
#define __LINE_CONTROLLER_H__

#include "Types.h"
#include "cocos2d.h"
#include "BlobController.h"

struct LineData {
	int col;
	int row;
	cocos2d::Point truePoint;
	cocos2d::Node* circle;
	cocos2d::Node* line;
};

class LineController
{

public:
	LineController(cocos2d::Layer* blobTarget, BlobController* positionController);

	void checkPoint(int col, int row);
	void reset();

	int						getCount() { return _lineData.size(); }
	std::vector<LineData*>	getList() { return _lineData; }

private:
	BlobController* _positionController;
	cocos2d::Layer* _blobTarget;

	std::vector<LineData*> _lineData;
	LineData* _currentLineData;
	LineData* _previousLineData;
};


#endif