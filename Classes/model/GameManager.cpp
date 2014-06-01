#include "GameManager.h"
#include <math.h>       /* floor */
#include "Types.h"
#include "scenes/GameScene.h"
#include "scenes/GallaryScene.h"
#include "scenes/ArtScene.h"

using namespace cocos2d;

// singleton stuff
static GameManager *s_GameManager = nullptr;

GameManager* GameManager::getInstance()
{
	if (!s_GameManager)
	{
		s_GameManager = new GameManager();
	}

	return s_GameManager;
}


GameManager::GameManager()
:_selectedArt(nullptr)
, _selectedGallary(nullptr)
{
	_tokens = UserDefault::getInstance()->getIntegerForKey("tokens", 5);
	_lives = UserDefault::getInstance()->getIntegerForKey("lives", 5);

	_levels[0].id = 1;
	_levels[0].blobRows = 5;
	_levels[0].blobCols = 7;
	_levels[0].artSizeSmall = 4;
	_levels[0].artSizeBig = 5;
	_levels[0].name = "EASY";
	_levels[0].gameSeconds = 90;

	_levels[1].id = 2;
	_levels[1].blobRows = 5;
	_levels[1].blobCols = 7;
	_levels[1].artSizeSmall = 5;
	_levels[1].artSizeBig = 6;
	_levels[1].name = "MEDIUM";
	_levels[1].gameSeconds = 120;

	_levels[2].id = 3;
	_levels[2].blobRows = 5;
	_levels[2].blobCols = 7;
	_levels[2].artSizeSmall = 7;
	_levels[2].artSizeBig = 8;
	_levels[2].name = "HARD";
	_levels[2].gameSeconds = 150;

	int blobCols;
	int artRows;
	int artCols;

	UserDefault::getInstance()->setBoolForKey("Star0001Level1", true);
	UserDefault::getInstance()->flush();
}

void GameManager::selectGallary(Gallary * gallary) 
{
	_selectedGallary = gallary;

	if (gallary) {
		auto scene = ArtScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	else {
		auto scene = GallaryScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	
}

void GameManager::selectArt(Art * art, Level level)
{
	_selectedArt = art;
	_selectedLevel = level;

	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameManager::resetArt()
{
	auto scene = ArtScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameManager::setTokens(int value) 
{ 
	if (value < 0) value = 10;
	_tokens = value; 
	UserDefault::getInstance()->setIntegerForKey("tokens", _tokens);
	UserDefault::getInstance()->flush();
}
void GameManager::setLives(int value) 
{ 
	if (value < 0) value = 10;
	_lives = value; 
	UserDefault::getInstance()->setIntegerForKey("lives", _lives);
	UserDefault::getInstance()->flush();
}

bool GameManager::checkLevelStatus(Art* art, Level level)
{
	char buffer[50];
	sprintf(buffer, "Star%04dLevel%d", art->id, level.id);
	bool hasVictory = UserDefault::getInstance()->getBoolForKey(buffer, false);
	return hasVictory;
}


void GameManager::setLevelComplete(Art* art, Level level)
{
	char buffer[50];
	sprintf(buffer, "Star%04dLevel%d", art->id, level.id);
	UserDefault::getInstance()->setBoolForKey(buffer, true);
	UserDefault::getInstance()->flush();
}