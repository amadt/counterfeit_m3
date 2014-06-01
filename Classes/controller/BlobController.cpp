#include "BlobController.h"
#include <math.h>       /* floor */
#include "Types.h"
#include "model/GameManager.h"

using namespace cocos2d;
extern float G_blobScale;



BlobController::BlobController(Layer* blobTarget, int itemWidth, int cols, int rows, float spacingX, float spacingY, float offsetX, float offsetY) :
_blobTarget(blobTarget),
_itemWidth(itemWidth),
_cols(cols),
_rows(rows),
_spacingX(spacingX),
_spacingY(spacingY),
_offsetX(offsetX),
_offsetY(offsetY) {

	int totalWidth = _cols * _spacingY;
	int totalHeight = _rows * _spacingX;

	float left = offsetX - totalWidth * 0.5;
	float bottom = offsetY - totalHeight * 0.5;
	_blobArea = cocos2d::Rect(left, bottom, totalWidth, totalHeight);
}

int BlobController::positionToIndex(int col, int row) 
{ 
	return row * GameManager::getInstance()->getSelectedLevel().blobCols + col;
}

void BlobController::fillGrid() {

	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < GameManager::getInstance()->getSelectedLevel().blobCols; ++col)
		{
			//draw the blob
			blobList.push_back(drawBlob(col, row));
		}
	}
}

BlobInstance* BlobController::drawBlob(int col, int row)
{
	Point position = getElementPosition(col, row);

	BlobInstance* blob = new BlobInstance();
	blob->row = row;
	blob->col = col;
	blob->color = Color(rand() % (int)Color::COUNT);
	std::string blobImageName = "blots2/" + colorToString(blob->color) + ".png";

	blob->node = CCSprite::create(blobImageName, CCRectMake(0, 0, 64, 64));
	blob->node->setPosition(position);
	G_blobScale = _itemWidth / 64;

	blob->node->setScale(G_blobScale);

	_blobTarget->addChild(blob->node);
	return blob;
}

BlobInstance* BlobController::getBlob(int col, int row)
{
	return blobList.at(positionToIndex(col, row));
}


bool BlobController::isValidTouch(Touch* touch) {

	Point loc = touch->getLocation();
	return (loc.x >= _blobArea.getMinX() && loc.x <= _blobArea.getMaxX() && loc.y >= _blobArea.getMinY() && loc.y <= _blobArea.getMaxY());
}

cocos2d::Point BlobController::getElementPosition(int col, int row)
{
	float colsSplit = floor(_cols / 2.0f);
	float rowsSplit = floor(_rows / 2.0f);

	float positionX = (col - colsSplit) * _spacingX;
	float positionY = (row - rowsSplit) * _spacingY;

	//evens need to be offset
	if (_cols % 2 == 0) positionX += 0.5f * (_spacingX);
	if (_rows % 2 == 0) positionY += 0.5f * (_spacingY);

	Point point = Point(positionX + _offsetX, positionY + _offsetY);
	return point;
}

cocos2d::Point BlobController::getClosestCoordinates(cocos2d::Touch* touch, Point lastPos) {

	float x = touch->getLocation().x;
	float y = touch->getLocation().y;

	//remove the offsets
	x -= _offsetX;
	y -= _offsetY;

	if (_cols % 2 == 0) x -= 0.5f * (_spacingX);
	if (_rows % 2 == 0) y -= 0.5f * (_spacingY);

	float colsSplit = floor(_cols / 2.0f);
	float rowsSplit = floor(_rows / 2.0f);

	float yPos = y / _spacingY + rowsSplit;
	float xPos = x / _spacingX + colsSplit;

	if (lastPos.x >= 0) {

		//we need to move at least a third into the new pos
		float xDiff = xPos - lastPos.x;
		float yDiff = yPos - lastPos.y;
		if (abs(xDiff) < LINE_PRECISION && abs(yDiff) < LINE_PRECISION)
		{
			return lastPos;
		}
	}

	return Point(round(xPos), round(yPos));
}

void BlobController::moveAllOff()
{
	for (int col = 0; col < _cols; col++) {
		for (int row = 0; row < _rows; row++) {
			BlobInstance* blob = getBlob(col, row);
			if (blob && blob->node) {
				// Create the movement
				float targetX = (col < _cols * 0.5f) ? -100 : 100 + Director::getInstance()->getVisibleSize().width;

				auto actionMove = CCMoveTo::create(0.6f, Point(targetX, blob->node->getPositionY()));
				auto easeMove = CCEaseIn::create(actionMove, 0.4f);
				auto delayMove = CCDelayTime::create(0.07 * (_rows - row));

				blob->node->runAction(CCSequence::create(delayMove, easeMove, NULL, NULL));
			}
		}
	}
}

void BlobController::fillGaps(bool fastDrop)
{
	//now fill in all the gaps
	for (int col = 0; col < _cols; col++) {
		int gaps = 0;
		for (int row = 0; row < _rows; row++) {
			BlobInstance* blob = getBlob(col, row);
			if (!blob->node) {
				gaps++;
			}
			else if (gaps > 0) {
				//move the node
				BlobInstance* gapBlob = getBlob(col, row - gaps);
				replaceInstance(blob, gapBlob, fastDrop);
			}
		}

		for (int row = _rows; row < _rows + gaps; row++) {
			//create a new blob
			BlobInstance* newBlob = drawBlob(col, row);
			BlobInstance* gapBlob = getBlob(col, row - gaps);
			replaceInstance(newBlob, gapBlob, fastDrop);
		}
	}
}

void BlobController::replaceInstance(BlobInstance* source, BlobInstance* target, bool fastDrop)
{
	target->color = source->color;
	target->node = source->node;
	source->node = nullptr;
	float dropSpeed = (fastDrop) ? DROP_SPEED_FAST : DROP_SPEED;

	// Create the movement
	CCFiniteTimeAction* actionMove =
		CCMoveTo::create(dropSpeed * (source->row - target->row), getElementPosition(target->col, target->row));
	target->node->runAction(CCSequence::create(actionMove, NULL, NULL));
}

void BlobController::reset()
{
	for (int col = 0; col < _cols; col++) {
		for (int row = 0; row < _rows; row++) {
			BlobInstance* blob = getBlob(col, row);
			if (blob && blob->node) {
				blob->node->removeFromParentAndCleanup(true);
				blob->node = nullptr;
			}
		}
	}
}

