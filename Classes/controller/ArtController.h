#ifndef __ART_CONTROLLER_H__
#define __ART_CONTROLLER_H__

#include "Types.h"
#include "cocos2d.h"
#include "components/ArtGameSquare.h"

class ArtController
{

public:
	ArtController(cocos2d::Layer* parent, std::string artFile, float maxWidth, float maxHeight, float offsetY);
	bool checkTouch(cocos2d::Touch* touch);
	void useColor(Color color, int amount);
	bool isReady() { return _tilesLeft <= 0; }

	void checkNeighbors(ArtGameSquare* main);
	void moveSelected(cocos2d::Point movement);
	void dropSelected(cocos2d::Point movement);
	bool isComplete();
	bool getIsNarrow() { return _isNarrow; }
	void centerOnScreen();
	void flipRandom();
	void showPreview(bool show = true);
	void showHints(bool show = true);
private:
	int positionToIndex(int col, int row);
	ArtGameSquare* boxAtPosition(int col, int row);
	void drawSelection(ArtGameSquare* main);
	void addSelectionPoints(ArtBoxSide firstSide, ArtGameSquare* box);
	void addSelectionSide(ArtBoxSide side, ArtGameSquare* box);
	void finishSelectionBorder(cocos2d::Color4F color);

private:
	float _rootX;
	float _rootY;
	float _maxX;
	float _maxY;
	int _pieceWidth;
	int _pieceHeight;
	int _tilesLeft;
	int _artRows;
	int _artCols;

	cocos2d::DrawNode* _selectionPoly;
	cocos2d::Sprite* _image;
	cocos2d::Layer* _parent;
	std::vector<cocos2d::Point> _selectionPoints;

	std::vector<ArtGameSquare*> _boxes;
	std::vector<ArtGameSquare*> _selected;
	bool _isMoveValid;
	bool _isNarrow;
};


#endif