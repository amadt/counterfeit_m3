#include "GallaryScene.h"
#include "Util.h"
#include <math.h>
#include "components/GallarySceneCell.h"
#include "components/TopBar.h"
#include "model/GameManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
extern float G_assetScale;

Scene* GallaryScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GallaryScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GallaryScene::init()
{
	CCLog("INIT!");
	//draw a giant box behind everything
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto background = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
	background->setPosition(Point(0, 0));
	addChild(background);

	auto redBox = TopBar::create();
	addChild(redBox);

	auto blackBox = LayerColor::create(Color4B::BLACK, visibleSize.width, 40 * G_assetScale);
	blackBox->setPosition(Point(0, 0));
	addChild(blackBox);
	
	auto tableHeight = 400.0f * G_assetScale;
	auto tableY = (visibleSize.height - tableHeight) * 0.5f;

	CCLog("CREATE TABLE VIEW!");
	TableView* tableView = TableView::create(this, Size(Size(visibleSize.width, tableHeight)));
	tableView->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView->setPosition(Point(0, tableY));
	tableView->setDelegate(this);
	this->addChild(tableView);
	CCLog("Reload Data!");
	tableView->reloadData();

    return true;
}


void GallaryScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	CCLOG("cell touched at index: %ld", cell->getIdx());
	GameManager::getInstance()->selectGallary(ArtManager::getInstance()->getGallary(cell->getIdx()));
}

Size GallaryScene::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	auto size = Size(139 * G_assetScale, 400 * G_assetScale);
	return size;
}

TableViewCell* GallaryScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
	auto string = String::createWithFormat("%ld", idx);
	GallarySceneCell *cell = (GallarySceneCell*)table->dequeueCell();
	if (!cell) {
		CCLog("CREATE GallarySceneCell!");
		cell = new GallarySceneCell();
		cell->autorelease();
	}
	CCLog("init GallarySceneCell!");
	cell->init(ArtManager::getInstance()->getGallary(idx));
	CCLog("init GallarySceneCell done");
	return cell;
}

ssize_t GallaryScene::numberOfCellsInTableView(TableView *table)
{
	return ArtManager::getInstance()->getGallaryCount();
}
