#include "ArtScene.h"
#include "Util.h"
#include <math.h>
#include "components/TopBar.h"
#include "model/GameManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
extern float G_assetScale;

Scene* ArtScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = ArtScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ArtScene::init()
{
	setTouchEnabled(false);
	CCLog("INIT!");
	//draw a giant box behind everything
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	_selectedIndex = 0;
	_selectedGallary = GameManager::getInstance()->getSelectedGallary();
	_selectedArt = ArtManager::getInstance()->getArt(_selectedGallary->artIds.at(_selectedIndex));

	auto background = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
	background->setPosition(Point(0, 0));
	addChild(background);

	auto redBox = TopBar::create();
	addChild(redBox);

	auto blackBox = LayerColor::create(Color4B::BLACK, visibleSize.width, 40 * G_assetScale);
	blackBox->setPosition(Point(0, 0));
	addChild(blackBox);

	auto gradBox1 = LayerGradient::create(Color4B(120, 120, 120, 255), Color4B(243, 243, 243, 255), Point(1, 0));
	gradBox1->setContentSize(Size(visibleSize.width * 0.5f, 60 * G_assetScale));
	gradBox1->setPosition(Point(0, 40 * G_assetScale));
	addChild(gradBox1);

	auto gradBox2 = LayerGradient::create(Color4B(243, 243, 243, 255), Color4B(120, 120, 120, 255), Point(1, 0));
	gradBox2->setContentSize(Size(visibleSize.width * 0.5f, 60 * G_assetScale));
	gradBox2->setPosition(Point(visibleSize.width * 0.5f, 40 * G_assetScale));
	addChild(gradBox2);

	auto slimBar = LayerColor::create(Color4B(151, 151, 151, 255), visibleSize.width, 1);
	slimBar->setPosition(Point(0, 100 * G_assetScale));
	addChild(slimBar);

	auto slimBar2 = LayerColor::create(Color4B(51, 51, 51, 255), visibleSize.width, 1);
	slimBar2->setPosition(Point(0, visibleSize.height - redBox->getContentSize().height - 1));
	addChild(slimBar2);

	auto picBox = LayerColor::create(Color4B::BLACK, visibleSize.width - 50, 120 * G_assetScale);
	picBox->setPosition(Point(25, visibleSize.height - 240 * G_assetScale));
	addChild(picBox);

	auto artY = 180.0f * G_assetScale;
	_artImage = CCSprite::create();
	_artImage->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height - artY));
	addChild(_artImage);

	float starBoxSize = 75 * G_assetScale;
	float starBoxPadding = 18 * G_assetScale;
	float starY = 128 * G_assetScale;
	float starX1 =(visibleSize.width - starBoxSize) * 0.5f;
	float starX2 = starX1 - (starBoxPadding + starBoxSize);
	float starX3 = starX1 + starBoxPadding + starBoxSize;
	
	_starBox1 = (DifficultyButton*)DifficultyButton::create();
	_starBox1->setPosition(starX2, starY);
	addChild(_starBox1);
	
	_starBox2 = (DifficultyButton*)DifficultyButton::create();
	_starBox2->setPosition(starX1, starY);
	addChild(_starBox2);

	_starBox3 = (DifficultyButton*)DifficultyButton::create();
	_starBox3->setPosition(starX3, starY);
	addChild(_starBox3);
	
	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(12 * G_assetScale) * 4;

		auto label = LabelTTF::createWithFontDefinition("GALLARY " + _selectedGallary->romanNumber, fontDef);
		label->setPosition(visibleSize.width * 0.5f, visibleSize.height - 60 * G_assetScale);
		label->setColor(Color3B::BLACK);
		label->setScale(0.25f);
		addChild(label);
	}
	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getBoldItalicFont();
		fontDef._fontSize = round(24 * G_assetScale) * 4;
		
		auto label = LabelTTF::createWithFontDefinition(_selectedGallary->name, fontDef);
		label->setPosition(visibleSize.width * 0.5f, visibleSize.height - 79 * G_assetScale);
		label->setColor(Color3B::BLACK);
		label->setScale(0.25f);
		addChild(label);
	}
	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getBoldItalicFont();
		fontDef._fontSize = round(16 * G_assetScale) * 4;

		_artLabel = LabelTTF::createWithFontDefinition("", fontDef);
		_artLabel->setPosition(visibleSize.width * 0.5f, visibleSize.height - 265 * G_assetScale);
		_artLabel->setColor(Color3B::BLACK);
		_artLabel->setScale(0.25f);
		addChild(_artLabel);
	}
	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getBoldItalicFont();
		fontDef._fontSize = round(12 * G_assetScale) * 4;
		_artistLabel = LabelTTF::createWithFontDefinition("", fontDef);
		_artistLabel->setPosition(visibleSize.width * 0.5f, visibleSize.height - 285 * G_assetScale);
		_artistLabel->setColor(Color3B::BLACK);
		_artistLabel->setScale(0.25f);
		addChild(_artistLabel);
	}
	
	TableView* tableView = TableView::create(this, Size(Size(visibleSize.width, 60 * G_assetScale)));
	tableView->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView->setPosition(Point(0, 40 * G_assetScale));
	tableView->setDelegate(this);
	this->addChild(tableView);
	tableView->reloadData();

	drawSelected();

    return true;
}

void ArtScene::drawSelected()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	_artistLabel->setString(_selectedArt->artist + " (" + Utils::NumberToString(_selectedArt->year) + ")");
	_artLabel->setString(_selectedArt->name);

	auto artPad = 30.0f;
	auto artHeight = 112.0f * G_assetScale;

	_artImage->setTexture(_selectedArt->image);
	_artImage->getTexture()->setAntiAliasTexParameters();
	auto scale = (visibleSize.width - artPad * 2) / _artImage->getContentSize().width;
	auto yPos = (_artImage->getContentSize().height - artHeight / scale) * 0.5 - _selectedArt->croppedOffset * G_assetScale;
	auto rect = Rect(0.0f, yPos, (float)_artImage->getContentSize().width, artHeight / scale);
	_artImage->setTextureRect(rect);
	_artImage->setScale(scale);

	_starBox1->drawLevel(_selectedArt, GameManager::getInstance()->getLevel(0));
	_starBox2->drawLevel(_selectedArt, GameManager::getInstance()->getLevel(1));
	_starBox3->drawLevel(_selectedArt, GameManager::getInstance()->getLevel(2));
}

void ArtScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());

	if (_selectedCell) _selectedCell->setHighlight(false);
	((ArtSceneCell*)cell)->setHighlight(true);

	_selectedCell = (ArtSceneCell*)cell;
	_selectedIndex = cell->getIdx();
	_selectedArt = ArtManager::getInstance()->getArt(_selectedGallary->artIds.at(_selectedIndex));
	drawSelected();
}

Size ArtScene::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	auto size = Size(58 * G_assetScale, 42 * G_assetScale);
	if (idx == _selectedGallary->artIds.size() - 1) size.width += 10 * G_assetScale;
	return size;
}

TableViewCell* ArtScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
	auto string = String::createWithFormat("%ld", idx);
	ArtSceneCell *cell = (ArtSceneCell*)table->dequeueCell();
	if (!cell) {
		cell = new ArtSceneCell();
		cell->autorelease();
	}
	cell->init(ArtManager::getInstance()->getArt(_selectedGallary->artIds.at(idx)));
	if (idx == _selectedIndex) {
		_selectedCell = cell;
	}
	cell->setHighlight(idx == _selectedIndex);
	return cell;
}

ssize_t ArtScene::numberOfCellsInTableView(TableView *table)
{
	return _selectedGallary->artIds.size();
}

