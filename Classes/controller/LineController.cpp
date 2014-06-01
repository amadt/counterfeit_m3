#include "LineController.h"
#include <math.h>      
#include "Types.h"

using namespace cocos2d;
extern float G_blobScale;

LineController::LineController(Layer* blobTarget, BlobController* positionController)
:_blobTarget(blobTarget)
,_currentLineData(nullptr)
,_previousLineData(nullptr)
,_positionController(positionController) {

}

void LineController::checkPoint(int col, int row) {

	//ignore the current point
	if (_currentLineData && _currentLineData->col == col && _currentLineData->row == row) {
		return;
	}
	
	if (col < 0 || row < 0) {
		return;
	}

	//if this is the previous point, we will remove the current point
	if (_previousLineData && _previousLineData->col == col && _previousLineData->row == row) {
		_currentLineData->circle->removeFromParentAndCleanup(true);
		_currentLineData->line->removeFromParentAndCleanup(true);
		_lineData.pop_back();
		_currentLineData = _previousLineData;
		if (_lineData.size() > 1) _previousLineData = _lineData.at(_lineData.size() - 2);
		else _previousLineData = nullptr;
	}

	//if it is already selected, we ignore it
	for (auto data : _lineData) {
		if (data->col == col && data->row == row) return;
	}

	//make sure it's next to the current point
	if (_currentLineData) {

		int xDiff = _currentLineData->col - col;
		int yDiff = _currentLineData->row - row;
		if (abs(xDiff) > 1 || abs(yDiff) > 1) return;
	}

	LineData* data = new LineData();

	//otherwise we add it
	data->truePoint = _positionController->getElementPosition(col, row);

	//draw a dot and add it to the layer
/*	 auto circle = CCSprite::create("lineEndPoint.png", CCRectMake(0, 0, 40, 40));
	 circle->setPosition(data->truePoint);
	 circle->setScale(G_blobScale);*/
	auto circle = DrawNode::create();
	circle->drawDot(data->truePoint, LINE_POINT_RADIUS, ccc4f(0.86f, 0.86f, 0.86f, 1));

	_blobTarget->addChild(circle, 200);
	
	data->circle = circle;
	data->row = row; 
	data->col = col;

	if (_currentLineData) {
		auto line = DrawNode::create();
		_blobTarget->addChild(line);
		line->drawSegment(_currentLineData->truePoint, data->truePoint, 2, ccc4f(0.86f, 0.86f, 0.86f, 1));
		data->line = line;
	}
	else {
		data->line = nullptr;
	}
	_previousLineData = _currentLineData;
	_currentLineData = data;

	_lineData.push_back(data);
}

void LineController::reset() {

	_previousLineData = nullptr;
	_currentLineData = nullptr;
	for (auto data : _lineData) {
		if (data->line) data->line->removeFromParentAndCleanup(true);
		data->circle->removeFromParentAndCleanup(true);
	}
	_lineData.clear();
}

