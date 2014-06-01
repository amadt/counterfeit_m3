#ifndef __BLOB_CONTROLLER_H__
#define __BLOB_CONTROLLER_H__

#include "Types.h"
#include "cocos2d.h"

class BlobInstance
{
public:
	Color color;
	int row;
	int col;
	cocos2d::Node* node;

};

class BlobController
{

public:
	BlobController(cocos2d::Layer* blobTarget, int itemWidth, int cols, int rows, float spacingX, float spacingY, float offsetX, float offsetY);
	void fillGrid();
	BlobInstance* drawBlob(int col, int row); 
	BlobInstance* getBlob(int col, int row);

	cocos2d::Point getElementPosition(int col, int row);
	bool isValidTouch(cocos2d::Touch* touch);

	cocos2d::Point getClosestCoordinates(cocos2d::Touch* touch, cocos2d::Point lastPos = cocos2d::ccp(-1, -1));
	
	void moveAllOff();
	void fillGaps(bool fastDrop);
	void reset();
	
private:
	int positionToIndex(int col, int row);
	void replaceInstance(BlobInstance* target, BlobInstance* source, bool fastDrop);

private:
	std::vector<BlobInstance*> blobList;

	cocos2d::Layer* _blobTarget;
	float _itemWidth;

	float _spacingX;
	float _spacingY;
	float _offsetX;
	float _offsetY;
	int _rows;
	int _cols;

	cocos2d::Rect _blobArea;


};

#endif