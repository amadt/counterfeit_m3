#include "DifficultyButton.h"
#include "Util.h"
#include <CCUserDefault.h>

USING_NS_CC;
extern float G_assetScale;

void DifficultyButton::drawLevel(Art* art, Level level)
{
	removeAllChildrenWithCleanup(true);

	_level = level;
	_art = art;
	setTouchEnabled(true);
	float starBoxSize = 75 * G_assetScale;

	auto starBox = LayerColor::create(Color4B::BLACK, starBoxSize, starBoxSize);
	starBox->setPosition(Point(0, 0));
	addChild(starBox);
	starBox->setTouchEnabled(false);
	
	//figure out if the user has beat this one before
	bool hasVictory = GameManager::getInstance()->checkLevelStatus(art, level);
	std::string starImageFile = (hasVictory) ? "starFull.png" : "starEmpty.png";

	auto starImage = CCSprite::create(starImageFile);
	auto starScale = (starBoxSize - 25 * G_assetScale) / starImage->getContentSize().width;
	starImage->setPosition(Point(starBoxSize * 0.5f, starBoxSize * 0.5f + 10 * G_assetScale));
	starImage->setScale(starScale);
	addChild(starImage);
	
	FontDefinition fontDef;
	fontDef._fontName = Utils::getExtraBoldFont();
	fontDef._fontSize = round(11 * G_assetScale) * 4;
	auto label = LabelTTF::createWithFontDefinition(level.name, fontDef);
	label->setPosition(starBoxSize * 0.5f, 12 * G_assetScale);
	label->setColor(Color3B::WHITE);
	label->setScale(0.25f);
	addChild(label);
}

void DifficultyButton::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
	auto touch = touches.at(0);
	Point point = this->convertToNodeSpace(touch->getLocation());

	float starBoxSize = 75 * G_assetScale;
	if (point.x <= starBoxSize && point.y <= starBoxSize && point.x >= 0 && point.y >= 0)
	{
		GameManager::getInstance()->selectArt(_art, _level);
	}
}

