#include "GameScene.h"
#include "controller/ColorEvaluator.h"
#include "Util.h"
#include "model/GameManager.h"
#include "components/TopBar.h"

USING_NS_CC;
extern float G_assetScale;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
	

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

GameScene* GameScene::create()
{
	auto scene = new GameScene();
	scene->init();
	scene->autorelease();
	return scene;
}

GameScene::GameScene()
{

}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	scheduleUpdate();

	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(ccc4(255, 255, 255, 255)))
	{
		return false;
	}
	setTouchEnabled(true);

	_level = GameManager::getInstance()->getSelectedLevel();
	_art = GameManager::getInstance()->getSelectedArt();
	_isPaused = false;
	_isGameOver = false;
	_waiting = 0;
	_timeAdd = 0;
	_hintTimer = 0;
	_resetAfterWait = false;
	_isPeeking = false;
	_timeLeft = _level.gameSeconds;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	_redBox = TopBar::create();
	addChild(_redBox);
	float redBoxHeight = _redBox->getContentSize().height;

	int blackBoxHeight = 40 * G_assetScale;
	auto blackBox = LayerColor::create(Color4B::BLACK, visibleSize.width, blackBoxHeight);
	blackBox->setPosition(Point(0, 0));
	addChild(blackBox);

	int midHeight = visibleSize.height - (redBoxHeight + blackBoxHeight);
	auto gradBox1 = LayerGradient::create(Color4B(150, 150, 150, 255), Color4B(243, 243, 243, 255), Point(1, 0));
	gradBox1->setContentSize(Size(visibleSize.width * 0.5f, midHeight));
	gradBox1->setPosition(Point(0, blackBoxHeight));
	addChild(gradBox1);

	auto gradBox2 = LayerGradient::create(Color4B(243, 243, 243, 255), Color4B(150, 150, 150, 150), Point(1, 0));
	gradBox2->setContentSize(Size(visibleSize.width * 0.5f, midHeight));
	gradBox2->setPosition(Point(visibleSize.width * 0.5f, blackBoxHeight));
	addChild(gradBox2);

	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(13 * G_assetScale);

		_timerLabel = LabelTTF::createWithFontDefinition("", fontDef);
		_timerLabel->setPosition(visibleSize.width * 0.5f, _redBox->getPositionY() + redBoxHeight * 0.5f);
		_timerLabel->setColor(Color3B::WHITE);
		addChild(_timerLabel, 220);
	}
	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(24 * G_assetScale);
		_gameOverLabel = LabelTTF::createWithFontDefinition("", fontDef);
		_gameOverLabel->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.75f);
		_gameOverLabel->setColor(Color3B::WHITE);
		addChild(_gameOverLabel, 400);
	}

	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(12 * G_assetScale);

		auto label = LabelTTF::createWithFontDefinition("EXIT", fontDef);
		label->setColor(Color3B::WHITE);

		auto button = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::exitGameClick, this));
		auto menu = Menu::create(button, NULL);
		addChild(menu);

		menu->setPosition(visibleSize.width * 0.15f, _redBox->getPositionY() + redBoxHeight * 0.5f);
	}

	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(12 * G_assetScale);

		auto label = LabelTTF::createWithFontDefinition("SKIP", fontDef);
		label->setColor(Color3B::WHITE);

		auto button = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::skip, this));
		auto menu = Menu::create(button, NULL);
		//addChild(menu);

		menu->setPosition(visibleSize.width * 0.15f, _redBox->getPositionY() + redBoxHeight * 0.5f);
	}

	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(11 * G_assetScale);

		auto label = LabelTTF::createWithFontDefinition("TIME", fontDef);
		label->setColor(Color3B::WHITE);
		label->setPositionX(label->getPositionX() + 15 * G_assetScale);

		auto button = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::timeAddClick, this));
		_timeButton = Menu::create(button, NULL);
		addChild(_timeButton);

		auto image = CCSprite::create("clock.png");
		auto imageScale = (23 * G_assetScale) / image->getContentSize().width;
		image->setScale(imageScale);
		image->setPositionY(8 * G_assetScale);
		button->addChild(image);

		button->setContentSize(Size(button->getContentSize().width, blackBoxHeight));
		_timeButton->setPosition(45 * G_assetScale, blackBox->getPositionY() + blackBoxHeight * 0.75f);
	}

	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(11 * G_assetScale);

		auto label = LabelTTF::createWithFontDefinition("FLIP", fontDef);
		label->setColor(Color3B::WHITE);

		auto button = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::flipClick, this));
		label->setPositionX(label->getPositionX() + 14 * G_assetScale);
		_flipButton = Menu::create(button, NULL);
		addChild(_flipButton);

		auto image = CCSprite::create("flip.png");
		auto imageScale = (23 * G_assetScale) / image->getContentSize().width;
		image->setScale(imageScale);
		image->setPositionY(8 * G_assetScale);
		button->addChild(image);

		button->setContentSize(Size(button->getContentSize().width, blackBoxHeight));
		_flipButton->setPosition(146 * G_assetScale, blackBox->getPositionY() + blackBoxHeight * 0.75f);
	}

	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(11 * G_assetScale);

		auto label = LabelTTF::createWithFontDefinition("RECYCLE", fontDef);
		label->setPositionX(label->getPositionX() + 16 * G_assetScale);
		label->setColor(Color3B::WHITE);

		auto image = CCSprite::create("recycle.png");
		auto imageScale = (23 * G_assetScale) / image->getContentSize().width;
		image->setScale(imageScale);
		image->setPositionY(8 * G_assetScale);

		auto button = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::recycleClick, this));
		button->addChild(image);
		_recycleButton = Menu::create(button, NULL);
		addChild(_recycleButton);
		button->setContentSize(Size(button->getContentSize().width, blackBoxHeight));

		_recycleButton->setPosition(257 * G_assetScale, blackBox->getPositionY() + blackBoxHeight * 0.75f);
	}

	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(11 * G_assetScale);

		auto label = LabelTTF::createWithFontDefinition("PEEK", fontDef);
		label->setColor(Color3B::WHITE);

		auto button = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::peekClick, this));
		label->setPositionX(label->getPositionX() + 14 * G_assetScale);
		_peekButton = Menu::create(button, NULL);
		addChild(_peekButton);

		auto image = CCSprite::create("eye.png");
		auto imageScale = (23 * G_assetScale) / image->getContentSize().width;
		image->setScale(imageScale);
		image->setPositionY(8 * G_assetScale);
		button->addChild(image);

		button->setContentSize(Size(button->getContentSize().width, blackBoxHeight));
		_peekButton->setPosition(156 * G_assetScale, blackBox->getPositionY() + blackBoxHeight * 0.75f);
		_peekButton->setVisible(false);
	}

	{
		FontDefinition fontDef;
		fontDef._fontName = Utils::getExtraBoldFont();
		fontDef._fontSize = round(11 * G_assetScale);

		auto label = LabelTTF::createWithFontDefinition("HINT", fontDef);
		label->setPositionX(label->getPositionX() + 16 * G_assetScale);
		label->setColor(Color3B::WHITE);

		auto image = CCSprite::create("hint.png");
		auto imageScale = (23 * G_assetScale) / image->getContentSize().width;
		image->setScale(imageScale);
		image->setPositionY(8 * G_assetScale);

		auto button = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::hintClick, this));
		button->addChild(image);
		_hintButton = Menu::create(button, NULL);
		addChild(_hintButton);
		button->setContentSize(Size(button->getContentSize().width, blackBoxHeight));

		_hintButton->setPosition(264 * G_assetScale, blackBox->getPositionY() + blackBoxHeight * 0.75f);
		_hintButton->setVisible(false);
	}


	int playPadding = 10 * G_assetScale;
	int playArea = midHeight - playPadding * 2;
	float maxWidth = (visibleSize.width - (BLOB_MARGIN * 2 - BLOB_PADDING));
	float maxHeight = playArea * 0.5f - playPadding * 0.5f;

	float artOffset = blackBoxHeight + maxHeight + playPadding * 2 + maxHeight * 0.5f;
	float maxArtWidth = visibleSize.width - playPadding * 2;

	auto artLayer = Layer::create();
	addChild(artLayer, 50);
	_artController = new ArtController(artLayer, GameManager::getInstance()->getSelectedArt()->image, maxArtWidth, maxHeight, artOffset);

	_lineController = new LineController(this, _blobController);
	_isDragging = false;
    
	//the elements should fill to fit the screen / height
	float itemWidth = maxWidth / GameManager::getInstance()->getSelectedLevel().blobCols - BLOB_PADDING;
	float itemHeight = maxHeight / GameManager::getInstance()->getSelectedLevel().blobRows - BLOB_PADDING;
	float itemSize = std::min(itemWidth, itemHeight);

	_blobController = new BlobController(this, itemSize, GameManager::getInstance()->getSelectedLevel().blobCols, GameManager::getInstance()->getSelectedLevel().blobRows, itemSize + BLOB_PADDING, itemSize + BLOB_PADDING, visibleSize.width * 0.5, blackBoxHeight + playPadding + maxHeight * 0.5f);
	_blobController->fillGrid();

	
	return true;
}

void GameScene::skip(Ref* sender)
{
	_artController->useColor(Color::RED, 30);
	_artController->useColor(Color::GREEN, 30);
	_artController->useColor(Color::BLUE, 30);
	_artController->useColor(Color::CYAN, 30);
	_artController->useColor(Color::PINK, 30);
	_artController->useColor(Color::YELLOW, 30);
	_artController->useColor(Color::BLACK, 30);
}

void GameScene::update(float delta)
{
	if (_waiting > 0) {
		_waiting -= delta;

		if (_waiting <= 0 && _resetAfterWait)
		{
			_blobController->reset();
			_blobController->fillGaps(true);
			_resetAfterWait = false;
		}
		return;
	}

	if (_hintTimer > 0) {
		_hintTimer -= delta;
		if (_hintTimer <= 0)
		{
			_hintTimer = 0;
			_artController->showHints(false);
		}
	}

	if (_timeAdd) {
		_timeLeft = (_timeAdd - _timeLeft) * 0.15 + _timeLeft;
		if (round(_timeLeft) >= _timeAdd) {
			_timeLeft = _timeAdd;
			_timeAdd = 0;
		}
	} else if (!_isPaused) {
		_timeLeft -= delta;

		if (_timeLeft <= 0)
		{
			showModal();
			_waiting = 2.0f;
			_gameOverLabel->setString("GAME OVER");
			GameManager::getInstance()->useLive();
			_isPaused = true;
			_isGameOver = true;
		}
	}

	updateTimeLabel();
}

void GameScene::updateTimeLabel()
{
	int roundedTimeLeft = ceil(_timeLeft);
	int seconds = roundedTimeLeft % 60;
	int minutes = (roundedTimeLeft - seconds) / 60;

	std::string secondStr = Utils::NumberToString(seconds);
	if (secondStr.length() == 1) secondStr = "0" + secondStr;
	_timerLabel->setString(Utils::NumberToString(minutes) + ":" + secondStr);
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	CCLog("Touch Pressed ");
	if (_isPeeking) return;
	if (_waiting > 0) return;
	if (_isPaused) return;
	if (touches.size() == 1) {
		Touch* touch = touches.at(0);
		if (!_artController->isReady()) {
			if (_blobController->isValidTouch(touch)) {
				Point coords = _blobController->getClosestCoordinates(touch);
				_lineController->checkPoint(coords.x, coords.y);
				_isDragging = true;
				_lastCoords = coords;
			}
		}
		else 
		{
			if (_artController->checkTouch(touch)) {
				_isDragging = true;
				_lastCoords = touch->getLocation();
			}
		}
	}
}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	if (_waiting > 0) return;
	if (_isPaused) return;
	Touch* touch = touches.at(0);
	if (!_artController->isReady()) {
		if (_isDragging && _blobController->isValidTouch(touch)) {
			Point coords = _blobController->getClosestCoordinates(touch, _lastCoords);
			_lineController->checkPoint(coords.x, coords.y);
			_lastCoords = coords;
		}
	}
	else {
		if (_isDragging) {
			Point newPos = touch->getLocation();
			Point movement = newPos - _lastCoords;
			_artController->moveSelected(movement);
			_lastCoords = newPos;

		}
	}

}

void GameScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	if (_waiting > 0) return;
	if (_isGameOver) {
		GameManager::getInstance()->resetArt();
		return;
	}
	if (_isPeeking)
	{
		showModal(false);
		_artController->showPreview(false);
		_isPeeking = false;
		return;
	}

	Touch* touch = touches.at(0);
	if (_isDragging && !_artController->isReady()) {

		if (_lineController->getCount() >= COLOR_MATCH_COUNT) {

			ColorEvaluator* evaluator = new ColorEvaluator();

			//see if we matched a specific color
			for (LineData* data : _lineController->getList()) {

				BlobInstance* blob = _blobController->getBlob(data->col, data->row);
				evaluator->AddColor(blob->color);
			}

			auto evaluation = evaluator->Evaluate();
			if (evaluation.first != Color::INVALID) {

				_artController->useColor(evaluation.first, evaluation.second);

				//clear the blobs
				for (LineData* data : _lineController->getList()) {
					BlobInstance* blob = _blobController->getBlob(data->col, data->row);
					blob->node->removeFromParentAndCleanup(true);
					blob->node = nullptr;
				}

				if (!checkBlobPhaseEnd())
				{
					_blobController->fillGaps(false);
				}
			}
		}
		_lineController->reset();
	}
	else if (_isDragging && _artController->isReady()) {
		_artController->dropSelected(touch->getLocation());

		if (_artController->isComplete())
		{
			showModal();
			_gameOverLabel->setString("VICTORY");
			_isPaused = true;
			_isGameOver = true;
			_waiting = 2.0f;
			GameManager::getInstance()->setLevelComplete(_art, _level);
		}
	}
	_isDragging = false;
	CCLog("Touch End ");

}

void GameScene::exitGameClick(Ref* sender)
{
	GameManager::getInstance()->resetArt();
}

void GameScene::timeAddClick(Ref* sender)
{
	GameManager::getInstance()->useToken();
	_redBox->refresh();
	_timeAdd = _timeLeft + TIME_AMOUNT;
}

void GameScene::recycleClick(Ref *sender)
{
	GameManager::getInstance()->useToken();
	_redBox->refresh();
	_resetAfterWait = true;
	_waiting = .5f;
	_blobController->moveAllOff();
}

void GameScene::flipClick(Ref *sender)
{
	GameManager::getInstance()->useToken();
	_redBox->refresh();
	_artController->flipRandom();
	checkBlobPhaseEnd();
}

void GameScene::peekClick(Ref *sender)
{
	GameManager::getInstance()->useToken();
	_redBox->refresh();
	showModal();
	_isPeeking = true;
	_artController->showPreview();
}

void GameScene::hintClick(Ref *sender)
{
	GameManager::getInstance()->useToken();
	_redBox->refresh();
	_hintTimer = 2.0f;
	_artController->showHints();
}
bool GameScene::checkBlobPhaseEnd() {
	if (_artController->isReady())
	{
		_waiting = 1.5;
		//send all the blobs to the sides
		_blobController->moveAllOff();
		_hintButton->setVisible(true);
		_peekButton->setVisible(true);
		_recycleButton->setVisible(false);
		_flipButton->setVisible(false);
		_artController->centerOnScreen();
		return true;
	}
	return false;
}

void GameScene::showModal(bool show) {
	if (show)
	{
		_modal = Modal::show(this);
	}
	else
	{
		_modal->removeFromParentAndCleanup(true);
	}
	_hintButton->setEnabled(!show);
	_peekButton->setEnabled(!show);
	_recycleButton->setEnabled(!show);
	_flipButton->setEnabled(!show);
	_timeButton->setEnabled(!show);
}