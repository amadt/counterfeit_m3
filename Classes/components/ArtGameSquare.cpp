#include "ArtGameSquare.h"
#include "Util.h"

USING_NS_CC;
extern float G_assetScale;

void ArtGameSquare::drawSquare(int col, int row, std::string artFile, Size size, Point scale, int artCols, int artRows)
{
	_artRows = artRows;
	_neighbors[ArtBoxSide::TOP] = false;
	_neighbors[ArtBoxSide::BOTTOM] = false;
	_neighbors[ArtBoxSide::LEFT] = false;
	_neighbors[ArtBoxSide::RIGHT] = false;

	removeAllChildrenWithCleanup(true);

	_originalCol = col;
	_originalRow = row;
	_pieceSize = size;
	_color = Color(rand() % (int)Color::COUNT);
	_scale = scale;

	float innerWidth = _pieceSize.width * 0.4f;
	float innerHeight = _pieceSize.height * 0.4f;

	_image = CCSprite::create(artFile, CCRectMake(col * _pieceSize.width / _scale.x, (_artRows - (row + 1)) * _pieceSize.height / _scale.y, _pieceSize.width / _scale.x, _pieceSize.height / _scale.y));
	_image->setScale(scale.x, scale.y);

	_arrow = CCSprite::create("hintLeft.png");
	float arrowHeight = 24 * G_assetScale;
	_arrow->setScale(arrowHeight / _arrow->getContentSize().height);
	_arrow->setVisible(false);

	Point blPoint = Point(-_pieceSize.width * 0.5f, -_pieceSize.height * 0.5f);
	Point brPoint = Point(_pieceSize.width * 0.5f, -_pieceSize.height * 0.5f);
	Point tlPoint = Point(-_pieceSize.width * 0.5f, _pieceSize.height * 0.5f);
	Point trPoint = Point(_pieceSize.width * 0.5f, _pieceSize.height * 0.5f);

	//draw the 4 border lines
	_sides[ArtBoxSide::TOP] = DrawNode::create();
	_sides[ArtBoxSide::TOP]->drawSegment(tlPoint, trPoint, 1, Color4F::BLACK);
	_sides[ArtBoxSide::BOTTOM] = DrawNode::create();
	_sides[ArtBoxSide::BOTTOM]->drawSegment(blPoint, brPoint, 1, Color4F::BLACK);
	_sides[ArtBoxSide::LEFT] = DrawNode::create();
	_sides[ArtBoxSide::LEFT]->drawSegment(tlPoint, blPoint, 1, Color4F::BLACK);
	_sides[ArtBoxSide::RIGHT] = DrawNode::create();
	_sides[ArtBoxSide::RIGHT]->drawSegment(trPoint, brPoint, 1, Color4F::BLACK);

	_cover = DrawNode::create();
	//draw the outer box
	Point points[] = { blPoint, tlPoint, trPoint, brPoint };
	_cover->drawPolygon(points, 4, ccc4f(0.96f, 0.96f, 0.96f, 0.8f), 0, ccc4f(0.86f, 0.86f, 0.86f, 0.8f));
	//draw the inner box
	Point innerPoints[] = { Point(-innerWidth * 0.5f, -innerHeight * 0.5f), Point(innerWidth * 0.5f, -innerHeight * 0.5f), Point(innerWidth * 0.5f, innerHeight * 0.5f), Point(-innerWidth * 0.5f, innerHeight * 0.5f) };
	_cover->drawPolygon(innerPoints, 4, colorToCCColor(_color), 0, ccc4f(0.86f, 0.86f, 0.86f, 0.9f));

	addChild(_image);
	addChild(_arrow);
	addChild(_sides[ArtBoxSide::LEFT]);
	addChild(_sides[ArtBoxSide::RIGHT]);
	addChild(_sides[ArtBoxSide::TOP]);
	addChild(_sides[ArtBoxSide::BOTTOM]);
	addChild(_cover);
}

void ArtGameSquare::placeSquare(int col, int row, Point root)
{
	int posX = root.x + col * _pieceSize.width + 0.5 * _pieceSize.width;
	int posY = root.y + row * _pieceSize.height + 0.5 * _pieceSize.height;

	setPosition(posX, posY);
	_col = col;
	_row = row;
	updateArrow();
}

void ArtGameSquare::cover()
{
	int borderWidth = 6;
	float bW = (_pieceSize.width - borderWidth) * 0.5f;
	float bH = (_pieceSize.height - borderWidth) * 0.5f;

	_cover = DrawNode::create();
	Point points[] = { Point(-bW, -bH), Point(bW, -bH), Point(bW, bH), Point(-bW, bH) };
	_cover->drawPolygon(points, 4, ccc4f(0.96f, 0.96f, 0.96f, 0.0f), borderWidth, ccc4f(0.86f, 0.86f, 0.86f, 0.7f));
	addChild(_cover);
	_cover->setPosition(_image->getPosition());
}

void ArtGameSquare::uncover()
{
	_cover->removeFromParentAndCleanup(true);
	_cover = NULL;
}

void ArtGameSquare::setNeighbor(ArtBoxSide side, bool match)
{
	if (_neighbors[side] != match){
		_neighbors[side] = match;
		if (match && _sides[side]) {
			_sides[side]->removeFromParent();
			_sides[side] = nullptr;
		}
	}
}

Rect ArtGameSquare::getBorder(int borderWidth)
{
	Rect rect;
	rect.size = Size(_pieceSize.width, _pieceSize.height);
	rect.origin = Point(getPositionX() - _pieceSize.width * 0.5f, getPositionY() - _pieceSize.height * 0.5f);
	return rect;
}

void ArtGameSquare::showArrow(bool show)
{
	_arrow->setVisible(show);
}

void ArtGameSquare::updateArrow()
{
	float arrowSize = _arrow->getContentSize().height * _arrow->getScaleY();
	float padding = 3 * G_assetScale;

	std::string imageName;
	Point imagePos;

	float left = -_pieceSize.width * 0.5f + arrowSize * 0.5f + padding;
	float center = 0;
	float right = _pieceSize.width * 0.5f - arrowSize * 0.5f - padding;
	
	float bottom = -_pieceSize.height * 0.5f + arrowSize * 0.5f + padding;
	float middle = 0;
	float top = _pieceSize.height * 0.5f - arrowSize * 0.5f - padding;

	if (_originalRow == _row) {
		if (_originalCol < _col) {
			imageName = "hintLeft.png";
			imagePos = Point(left, middle);
		}
	    else if (_originalCol == _col) {
			_arrow->setVisible(false);
			return;
	    } else {
			imageName = "hintRight.png";
			imagePos = Point(right, middle);
		}
	} else if (_originalRow > _row) {
		if (_originalCol < _col) {
			imageName = "hintTopLeft.png";
			imagePos = Point(left, top);
		}else if (_originalCol == _col) {
			imageName = "hintUp.png";
			imagePos = Point(center, top);
		}
		else {
			imageName = "hintTopRight.png";
			imagePos = Point(right, top);
		}
	}
	else {
		if (_originalCol < _col) {
			imageName = "hintBottomLeft.png";
			imagePos = Point(left, bottom);
		}
		else if (_originalCol == _col) {
			imageName = "hintDown.png";
			imagePos = Point(center, bottom);
		}
		else {
			imageName = "hintBottomRight.png";
			imagePos = Point(right, bottom);
		}
	}


	_arrow->setPosition(imagePos);
	_arrow->setTexture(imageName);
}