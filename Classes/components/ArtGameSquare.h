#ifndef __ARTGAMESCENE_H__
#define __ARTGAMESCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "model/GameManager.h"

enum ArtBoxSide { LEFT = 0, TOP, RIGHT, BOTTOM };

class ArtGameSquare : public cocos2d::Layer
{
public:
	void drawSquare(int col, int row, std::string artFile, cocos2d::Size size, cocos2d::Point scale, int artCols, int artRows);
	void placeSquare(int col, int row, cocos2d::Point root);
	void cover();
	void uncover();
	bool isCovered() { return _cover != nullptr; }
	Color getColor(){ return _color; }
	bool isMatch(int col, int row) { return _col == col && _row == row; }
	int getCol() { return _col; }
	int getRow() { return _row; }
	int getOriginalCol() { return _originalCol; }
	int getOriginalRow() { return _originalRow; }
	void setNeighbor(ArtBoxSide side, bool match);
	bool hasValidNeighbor(ArtBoxSide side) { return _neighbors[side]; }
	cocos2d::Rect getBorder(int width);
	bool isCorrect() { return _originalCol == _col && _originalRow == _row; }
	void showArrow(bool show = true);
	void updateArrow();
private:
	Color _color;
	int _col;
	int _row;
	int _originalCol;
	int _originalRow;
	int _artRows;
	cocos2d::Sprite* _image;
	cocos2d::DrawNode* _cover;
	cocos2d::DrawNode* _sides[4];
	cocos2d::Sprite* _arrow;
	cocos2d::Size _pieceSize;
	cocos2d::Point _scale;

	bool _neighbors[4];

};

#endif /* __ARTGAMESCENE_H__ */

