#include "GallarySceneCell.h"
#include "Util.h"

USING_NS_CC;
extern float G_assetScale;

void GallarySceneCell::init(Gallary* gallary)
{
	auto boxWidth = 115 * G_assetScale;
	auto boxHeight = 400 * G_assetScale;
	auto boxLeft = 12 * G_assetScale;
	auto boxBottom = 0 * G_assetScale;

	auto corner = Point(boxLeft, boxBottom);

	auto blackBorder = LayerColor::create(Color4B::BLACK, boxWidth, boxHeight);
	blackBorder->setPosition(corner);
	addChild(blackBorder);

	_blackBox = LayerColor::create(Color4B::BLACK, boxWidth - 2, boxHeight - 2);
	_blackBox->setPosition(corner + Point(1,1));
	addChild(_blackBox);
	
	auto starSize = 18 * G_assetScale;
	auto starY = corner.y + 9 * G_assetScale + starSize * 0.5f;
	auto starLeft = boxLeft + 37 * G_assetScale;
	
	auto starImage = CCSprite::create("starFull.png");
	auto starScale = (starSize) / starImage->getContentSize().width;
	starImage->setPosition(Point(starLeft, starY));
	starImage->setScale(starScale);
	addChild(starImage);

	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(16 * G_assetScale);

		auto label = LabelTTF::createWithFontDefinition(gallary->romanNumber, fontDef);
		label->setPosition(boxLeft + boxWidth * 0.5f, boxHeight - 15 * G_assetScale);
		label->setColor(Color3B::WHITE);
		addChild(label);
	}
	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getBoldItalicFont();
		fontDef._fontSize = round(12 * G_assetScale);

		auto label = LabelTTF::createWithFontDefinition(gallary->name, fontDef);
		label->setPosition(boxLeft + boxWidth * 0.5f, 36 * G_assetScale);
		label->setColor(Color3B::WHITE);
		addChild(label);
	}
	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(13 * G_assetScale);

		auto label = LabelTTF::createWithFontDefinition("11/45", fontDef);
		label->setPosition(boxLeft + 67 * G_assetScale, 20 * G_assetScale);
		label->setColor(Color3B::WHITE);
		addChild(label);
	}

	auto artWidth = boxWidth - 10 * G_assetScale;
	auto artHeight = 325.0f * G_assetScale;
	auto artPadLeft = boxLeft + 5.0f * G_assetScale;
	auto artPadBot = 50.0f * G_assetScale;
	auto image = CCSprite::create(gallary->image);
	auto scale = artHeight / image->getContentSize().height;
	auto xPos = (image->getContentSize().width - artWidth / scale) * 0.5;// -art->croppedOffset * G_assetScale;
	auto rect = Rect(xPos, 0.0f, artWidth / scale, (float)image->getContentSize().height);
	image->setTextureRect(rect);
	image->setPosition(Point(artPadLeft + artWidth * 0.5f, artPadBot + artHeight * 0.5f));
	image->setScale(scale);
	addChild(image);
}

void GallarySceneCell::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
	TableViewCell::draw(renderer, transform, transformUpdated);
}
