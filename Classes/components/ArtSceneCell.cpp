#include "ArtSceneCell.h"
#include "Util.h"
#include "model/GameManager.h"

USING_NS_CC;
extern float G_assetScale;

void ArtSceneCell::init(Art* art) 
{
	auto boxWidth = 49 * G_assetScale;
	auto boxHeight = 40 * G_assetScale;
	auto boxLeft = 10 * G_assetScale;
	auto boxBottom = 10 * G_assetScale;

	auto corner = Point(boxLeft, boxBottom);

	auto blackBorder = LayerColor::create(Color4B::BLACK, boxWidth, boxHeight);
	blackBorder->setPosition(corner);
	addChild(blackBorder);

	_blackBox = LayerColor::create(Color4B::BLACK, boxWidth - 2, boxHeight - 2);
	_blackBox->setPosition(corner + Point(1,1));
	addChild(_blackBox);
	
	auto starSize = 13 * G_assetScale;
	auto starY = corner.y + 1 * G_assetScale + starSize * 0.5f;
	auto starInnerPad = 2 * G_assetScale;
	auto starLeft = 9 * G_assetScale;
	
	auto gm = GameManager::getInstance();
	std::string starFile1 = (gm->checkLevelStatus(art, gm->getLevel(0)) ? "starFull.png" : "starEmpty.png");
	auto starImage1 = CCSprite::create(starFile1);
	auto starScale = (starSize) / starImage1->getContentSize().width;
	starImage1->setPosition(Point(corner.x + starLeft, starY));
	starImage1->setScale(starScale);
	addChild(starImage1);

	std::string starFile2 = (gm->checkLevelStatus(art, gm->getLevel(1)) ? "starFull.png" : "starEmpty.png");
	auto starImage2 = CCSprite::create(starFile2);
	starImage2->setPosition(Point(corner.x + (starLeft + starInnerPad + starSize), starY));
	starImage2->setScale(starScale);
	addChild(starImage2);

	std::string starFile3 = (gm->checkLevelStatus(art, gm->getLevel(2)) ? "starFull.png" : "starEmpty.png");
	auto starImage3 = CCSprite::create(starFile3);
	starImage3->setPosition(Point(corner.x + (starLeft + starInnerPad * 2 + starSize * 2), starY));
	starImage3->setScale(starScale);
	addChild(starImage3);

	auto artWidth = 43.0f * G_assetScale;
	auto artHeight = 22.0f * G_assetScale;
	auto artPadLeft = boxLeft + 3.0f * G_assetScale;
	auto artPadBot = boxBottom + starSize + 2.0f * G_assetScale;
	auto image = CCSprite::create(art->image);
	auto scale = artWidth / image->getContentSize().width;
	auto yPos = (image->getContentSize().height - (artHeight) / scale) * 0.5 - art->croppedOffset * G_assetScale;
	auto rect = Rect(0.0f, yPos, (float)image->getContentSize().width, artHeight / scale);
	image->setTextureRect(rect);
	image->setPosition(Point(artPadLeft + artWidth * 0.5f, artPadBot + artHeight * 0.5f));
	image->setScale(scale);
	addChild(image);
}

void ArtSceneCell::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
	TableViewCell::draw(renderer, transform, transformUpdated);
}

void ArtSceneCell::setHighlight(bool highlight)
{
	if (highlight) _blackBox->setColor(Color3B::WHITE);
	else _blackBox->setColor(Color3B::BLACK);

}