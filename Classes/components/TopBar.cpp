#include "TopBar.h"
#include "Util.h"
#include <CCUserDefault.h>

USING_NS_CC;
extern float G_assetScale;

bool TopBar::init()
{
	CCLog("INIT RED BOX!");
	int height = 40 * G_assetScale;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	LayerColor::initWithColor(Color4B(208, 5, 1, 255), visibleSize.width, height);
	setPosition(Point(0, visibleSize.height - height));

	CCLog("ADD HEIRT!");
	auto heartImage = CCSprite::create("heart.png");
	auto heartScale = (23 * G_assetScale) / heartImage->getContentSize().width;
	heartImage->setPosition(Point(visibleSize.width - 100 * G_assetScale, height * 0.5f));
	heartImage->setScale(heartScale);
	addChild(heartImage);

	CCLog("ADD Brush!");
	auto brushImage = CCSprite::create("brush.png");
	auto brushScale = (23 * G_assetScale) / brushImage->getContentSize().width;
	brushImage->setPosition(Point(visibleSize.width - 40 * G_assetScale, height * 0.5f));
	brushImage->setScale(brushScale);
	addChild(brushImage);

	CCLog("ADD _liveText!");
	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(14 * G_assetScale);
		_liveText = LabelTTF::createWithFontDefinition("Z", fontDef);
		_liveText->setPosition(visibleSize.width - 80 * G_assetScale, height * 0.5f);
		_liveText->setColor(Color3B::WHITE);
		addChild(_liveText);
	}

	CCLog("ADD _tokenText!");
	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(14 * G_assetScale);
		_tokenText = LabelTTF::createWithFontDefinition("Z", fontDef);
		_tokenText->setPosition(visibleSize.width - 20 * G_assetScale, height * 0.5f);
		_tokenText->setColor(Color3B::WHITE);
		addChild(_tokenText);
	}
	CCLog("REFRESH!");
	refresh();
	return true;
}

void TopBar::refresh()
{
	_liveText->setString(Utils::NumberToString(GameManager::getInstance()->getLives()));
	_tokenText->setString(Utils::NumberToString(GameManager::getInstance()->getTokens()));
}


