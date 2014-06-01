#include "ArtController.h"
#include <math.h>       /* floor */
#include "Types.h"
#include "model/GameManager.h"

using namespace cocos2d;
extern float G_assetScale;

ArtController::ArtController(Layer* parent, std::string artFile, float maxWidth, float maxHeight, float offsetY)
:_parent(parent)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	_image = CCSprite::create(artFile);
	_isNarrow = (_image->getContentSize().height > _image->getContentSize().width);

	auto level = GameManager::getInstance()->getSelectedLevel();
	if (_isNarrow) {
		GameManager::getInstance()->setArtDimensions(level.artSizeSmall, level.artSizeBig);
	}
	else {
		GameManager::getInstance()->setArtDimensions(level.artSizeBig, level.artSizeSmall);
	}
	_artCols = GameManager::getInstance()->getArtCols();
	_artRows = GameManager::getInstance()->getArtRows();

	//figure out which scale to use
	float borderSize = 4 * G_assetScale;
	maxWidth -= borderSize * 2;
	maxHeight -= borderSize * 2;

	float scaleX = maxWidth / _image->getContentSize().width;
	float scaleY = maxHeight / _image->getContentSize().height;
	float scaleItem = std::min(scaleX, scaleY);

	int newWidth = floor(_image->getContentSize().width * scaleItem);
	int newHeight = floor(_image->getContentSize().height * scaleItem);

	//make sure all our math is round
	newWidth = newWidth - newWidth % _artCols;
	newHeight = newHeight - newHeight % _artRows;
	scaleX = newWidth / _image->getContentSize().width;
	scaleY = newHeight / _image->getContentSize().height;
	
	_rootX = visibleSize.width * 0.5f - newWidth * 0.5f - borderSize;
	_rootY = offsetY - newHeight * 0.5f - borderSize;

	auto blackBox = LayerColor::create(Color4B::BLACK, newWidth + borderSize * 2, newHeight + borderSize * 2);
	blackBox->setPosition(Point(_rootX, _rootY));
	_parent->addChild(blackBox);
	_rootX += borderSize;
	_rootY += borderSize;

	_maxX = _rootX + newWidth;
	_maxY = _rootY + newHeight;

	_tilesLeft = _artRows * _artCols;
	//_tilesLeft = 0;


	//image is actually a litte smaller. is used for the peek
	_image->setScale(scaleX * 0.95, scaleY * 0.95);
	_image->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	_parent->getParent()->addChild(_image, 300);
	_image->setVisible(false);
	_pieceWidth = newWidth / _artCols;
	_pieceHeight = newHeight / _artRows;

	//build the boxes based on their correct positions
	for (int row = 0; row < _artRows; row++) {
		for (int col = 0; col < _artCols; col++) {
			ArtGameSquare* box = new ArtGameSquare();
			box->drawSquare(col, row, artFile, Size(_pieceWidth, _pieceHeight), Point(scaleX, scaleY), _artCols, _artRows);
			_boxes.push_back(box);
		}
	}

	std::random_shuffle(_boxes.begin(), _boxes.end());
	int pos = 0;

	for (ArtGameSquare* box : _boxes) {
		int col = pos % _artCols;
		int row = (pos - col) / _artCols;
		box->placeSquare(col, row, Point(_rootX, _rootY));
		_parent->addChild(box, 100);
		pos++;
	}

	for (ArtGameSquare* box : _boxes) {
		checkNeighbors(box);
	}
}

void ArtController::checkNeighbors(ArtGameSquare* main)
{
	int col = main->getCol();
	int row = main->getRow();
	int oCol = main->getOriginalCol();
	int oRow = main->getOriginalRow();

	//bottom
	if (row > 0) {
		ArtGameSquare* neighbor = boxAtPosition(col, row - 1);
		bool match = (neighbor->getOriginalCol() == oCol && neighbor->getOriginalRow() == oRow - 1);
		main->setNeighbor(ArtBoxSide::BOTTOM, match);
		neighbor->setNeighbor(ArtBoxSide::TOP, match);
	} else {
		main->setNeighbor(ArtBoxSide::BOTTOM, false);
	}

	//top
	if (row < _artRows - 1) {
		ArtGameSquare* neighbor = boxAtPosition(col, row + 1);
		bool match = (neighbor->getOriginalCol() == oCol && neighbor->getOriginalRow() == oRow + 1);
		main->setNeighbor(ArtBoxSide::TOP, match);
		neighbor->setNeighbor(ArtBoxSide::BOTTOM, match);
	} else {
		main->setNeighbor(ArtBoxSide::TOP, false);
	}

	//left
	if (col > 0) {
		ArtGameSquare* neighbor = boxAtPosition(col - 1, row);
		bool match = (neighbor->getOriginalRow() == oRow && neighbor->getOriginalCol() == oCol - 1);
		main->setNeighbor(ArtBoxSide::LEFT, match);
		neighbor->setNeighbor(ArtBoxSide::RIGHT, match);
	} else {
		main->setNeighbor(ArtBoxSide::LEFT, false);
	}

	//right
	if (col < _artCols - 1) {
		ArtGameSquare* neighbor = boxAtPosition(col + 1, row);
		bool match = (neighbor->getOriginalRow() == oRow && neighbor->getOriginalCol() == oCol + 1);
		main->setNeighbor(ArtBoxSide::RIGHT, match);
		neighbor->setNeighbor(ArtBoxSide::LEFT, match);
	} else {
		main->setNeighbor(ArtBoxSide::RIGHT, false);
	}
}

void ArtController::useColor(Color color, int amount) 
{
	int count = floor(amount / COLOR_MATCH_COUNT);

	//simple randimization
	std::vector<int> indexes;
	for (int i = 0; i < _boxes.size(); i++) indexes.push_back(i);

	std::random_shuffle(indexes.begin(), indexes.end());

	for (int i : indexes) {
		ArtGameSquare* box = _boxes.at(i);
		if (box->getColor() == color && box->isCovered()) {
			box->uncover();
			count--;
			_tilesLeft--;
			if(count <= 0) return;
		}
	}
}

void ArtController::flipRandom()
{
	//simple randimization
	std::vector<int> indexes;
	for (int i = 0; i < _boxes.size(); i++) indexes.push_back(i);
	std::random_shuffle(indexes.begin(), indexes.end());

	for (int i : indexes) {
		ArtGameSquare* box = _boxes.at(i);
		if (box->isCovered()) {
			box->uncover();
			_tilesLeft--;
			return;
		}
	}
}

ArtGameSquare* ArtController::boxAtPosition(int col, int row)
{
	for (ArtGameSquare* box : _boxes) {
		if (box->isMatch(col, row)) return box;
	}
	return nullptr;
}

bool ArtController::checkTouch(Touch* touch) {
	Point loc = touch->getLocation();
	_isMoveValid = true;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Rect area;
	

	int width = (_maxX - _rootX) * _parent->getScaleX();
	int height = (_maxY - _rootY) * _parent->getScaleY();

	area.size = Size(width, height);
	area.origin = Point(visibleSize.width * 0.5 - width * 0.5f, visibleSize.height * 0.5f - height * 0.5f);

	if (area.containsPoint(loc))
	{
		float pieceWidth = width / _artCols;
		float pieceHeight = height / _artRows;

		int col = floor((loc.x - area.origin.x) / pieceWidth);
		int row = floor((loc.y - area.origin.y) / pieceHeight);

		ArtGameSquare* box = boxAtPosition(col, row);
		//if (box->isCorrect()) return false;

		drawSelection(box);
		return true;
	}

	return false;
}

void ArtController::drawSelection(ArtGameSquare* box)
{
	_selectionPoly = DrawNode::create();

	addSelectionPoints(ArtBoxSide::LEFT, box);
	_parent->addChild(_selectionPoly, 300);

	finishSelectionBorder(ccc4f(225.0f / 255.0f, 232.0f / 255.0f, 39.0f / 255.0f, 0.7f));
}

void ArtController::finishSelectionBorder(Color4F color)
{
	int borderWidth = 2;
	Point pointArray[100];
	int i = 0;
	for (Point point : _selectionPoints)
	{
		pointArray[i] = point;
		i++;
	}

	_selectionPoly->clear();
	_selectionPoly->drawPolygon(pointArray, _selectionPoints.size(), ccc4f(0, 0, 0, 0), borderWidth, color);
}

void ArtController::addSelectionPoints(ArtBoxSide firstSide, ArtGameSquare* box)
{
	_selected.push_back(box);
	box->setZOrder(200);

	for (int i = 0; i < 4; i++)
	{
		ArtBoxSide side = (ArtBoxSide)(((int)firstSide + i) % 4);
		addSelectionSide(side, box);
	}
}


void ArtController::addSelectionSide(ArtBoxSide side, ArtGameSquare* box)
{
	Rect borders = box->getBorder(2);
	if (box->hasValidNeighbor(side))
	{
		ArtGameSquare* neighbor;
		if (side == ArtBoxSide::LEFT) neighbor = boxAtPosition(box->getCol() - 1, box->getRow());
		else if (side == ArtBoxSide::TOP) neighbor = boxAtPosition(box->getCol(), box->getRow() + 1);
		else if (side == ArtBoxSide::RIGHT) neighbor = boxAtPosition(box->getCol() + 1, box->getRow());
		else if (side == ArtBoxSide::BOTTOM) neighbor = boxAtPosition(box->getCol(), box->getRow() - 1);

		//check the checked first
		bool isDone = false;
		for (auto done : _selected)
		{
			if (done == neighbor)
			{
				isDone = true;
				break;
			}
		}
		if (!isDone)
		{
			ArtBoxSide startSide;
			if (side == ArtBoxSide::LEFT) startSide = ArtBoxSide::RIGHT;
			else if (side == ArtBoxSide::RIGHT) startSide = ArtBoxSide::LEFT;
			else if (side == ArtBoxSide::TOP) startSide = ArtBoxSide::BOTTOM;
			else if (side == ArtBoxSide::BOTTOM) startSide = ArtBoxSide::TOP;
			addSelectionPoints(startSide, neighbor);
		}
	}
	else
	{
		if (side == ArtBoxSide::LEFT) _selectionPoints.push_back(Point(borders.getMinX(), borders.getMinY()));
		else if (side == ArtBoxSide::TOP) _selectionPoints.push_back(Point(borders.getMinX(), borders.getMaxY()));
		else if (side == ArtBoxSide::RIGHT) _selectionPoints.push_back(Point(borders.getMaxX(), borders.getMaxY()));
		else if (side == ArtBoxSide::BOTTOM) _selectionPoints.push_back(Point(borders.getMaxX(), borders.getMinY()));
	}
}

int ArtController::positionToIndex(int col, int row) 
{
	return row * GameManager::getInstance()->getArtCols() + col;
}

void ArtController::moveSelected(Point movement)
{
	_isMoveValid = true;

	for (auto box : _selected) {
		box->setPosition(box->getPosition() + movement);

		//calculate the new row and col of the item
		Point point = box->getPosition();
		int row = floor((point.y - _rootY) / _pieceHeight);
		int col = floor((point.x - _rootX) / _pieceWidth);
		CCLOG("Col: %d Row: %d", col, row);

		//see if this is valid
		if (row < 0 || row >= _artRows || col < 0 || col >= _artCols) {
			_isMoveValid = false;
		}
	}

	if (_isMoveValid) {
		finishSelectionBorder(ccc4f(225.0f / 255.0f, 232.0f / 255.0f, 39.0f / 255.0f, 0.7f));
	} else {
		finishSelectionBorder(ccc4f(225.0f / 255.0f, 32.0f / 255.0f, 39.0f / 255.0f, 0.7f));
	}

	_selectionPoly->setPosition(_selectionPoly->getPosition() + movement);
}

void ArtController::dropSelected(cocos2d::Point movement)
{
	_selectionPoly->removeFromParentAndCleanup(true);
	_selectionPoly = nullptr;
	auto origin = Point(_rootX, _rootY);

	//start with point 1
	auto box1 = _selected.at(0);
	Point box1Point = box1->getPosition();
	int box1Row = floor((box1Point.y - _rootY) / _pieceHeight);
	int box1Col = floor((box1Point.x - _rootX) / _pieceWidth);
	std::vector<ArtGameSquare*> moved;

	//if the move isn't valid or nothing moved, quickly exit
	if (box1Row == box1->getRow() && box1Col == box1->getCol() || !_isMoveValid) {
		for (auto box : _selected) {
			box->placeSquare(box->getCol(), box->getRow(), origin);
		}
	} 
	else {
		Point moveTos[100];
		int i = 0;

		//first, get the tiles we are swapping to in place
		for (auto box : _selected) {
			Point point = box->getPosition();
			int row = floor((point.y - _rootY) / _pieceHeight);
			int col = floor((point.x - _rootX) / _pieceWidth);
			moveTos[i] = Point(col, row);
			i++;
		}

		i = 0;
		for (auto box : _selected) {
			auto newPos = moveTos[i];
			i++;

			auto swapWith = boxAtPosition(newPos.x, newPos.y);

			//skip if the target is selected
			bool found = false;
			for (auto boxAgain : _selected) {
				if (swapWith == boxAgain) {
					found = true;
					break;
				}
			}
			
			bool isValid = false;
			auto swapPos = newPos;

			while (!isValid) {
				//find a box that's going in this spot
				int j = 0;
				for (auto box2 : _selected) {
					auto newPos = moveTos[j];
					if (newPos == swapPos) {
						swapPos = Point(box2->getCol(), box2->getRow());

						//validate this swapPos
						isValid = true;
						for (int k = 0; k < _selected.size(); k++) {
							if (moveTos[k] == swapPos) {
								isValid = false;
								break;
							}
						}
						break;
					}
					j++;
				}
			}
			swapWith->placeSquare(swapPos.x, swapPos.y, origin);
			moved.push_back(swapWith);
		}
	
		//now place the tiles
		i = 0;
		for (auto box : _selected) {
			auto newPos = moveTos[i];
			box->placeSquare(newPos.x, newPos.y, origin);
			box->setZOrder(100);
			i++;
		}
		
		//check neighbors
		for (auto box : _selected) {
			checkNeighbors(box);
		}
		for (auto box : moved) {
			checkNeighbors(box);
		}
	}
	_selected.clear();
	_selectionPoints.clear();
}

bool ArtController::isComplete()
{
	for (int row = 0; row < _artRows; row++) {
		for (int col = 0; col < _artCols; col++) {
			auto box = boxAtPosition(col, row);
			if (!box->isCorrect()) {
				return false;
			}
		}
	}
	return true;
}

void ArtController::centerOnScreen()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float scaleBy = (visibleSize.width - 30 * G_assetScale) / (_maxX - _rootX);

	auto oldHeight = _maxY - _rootY;
	auto newHeight = oldHeight * scaleBy;

	auto newRootY = visibleSize.height * 0.5f - newHeight * 0.5f;
	float offset = newRootY - _rootY;

	auto actionMove = CCMoveTo::create(0.6f, Point(_parent->getPositionX(), _parent->getPositionY() + offset));
	auto scaleMove = CCScaleTo::create(0.6f, scaleBy);
	//auto easeMove = CCEaseIn::create(actionMove, 0.4f);
	auto delayMove = CCDelayTime::create(0.3f);
	auto delayMove2 = CCDelayTime::create(0.3f);
	_parent->runAction(CCSequence::create(delayMove, actionMove, NULL, NULL));
	_parent->runAction(CCSequence::create(delayMove2, scaleMove, NULL, NULL));
	//_parent->setPositionY(_parent->getPositionY() + offset);
}

void ArtController::showPreview(bool show)
{
	_image->setVisible(show);
}

void ArtController::showHints(bool show)
{
	for (int row = 0; row < _artRows; row++) {
		for (int col = 0; col < _artCols; col++) {
			auto box = boxAtPosition(col, row);
			if (!box->isCorrect()) {
				box->showArrow(show);
			}
		}
	}
}
