#ifndef __ARTSCENE_H__
#define __ARTSCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "model/ArtManager.h"
#include "components/ArtSceneCell.h"
#include "components/DifficultyButton.h"

class ArtScene : public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void drawSelected();

	// implement the "static create()" method manually
	CREATE_FUNC(ArtScene);

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);

private:
	Gallary*		_selectedGallary;
	Art*			_selectedArt;
	ArtSceneCell*	_selectedCell;
	int				_selectedIndex;

	cocos2d::LabelTTF* _artistLabel;
	cocos2d::LabelTTF* _artLabel;
	cocos2d::CCSprite* _artImage;

	DifficultyButton* _starBox1;
	DifficultyButton* _starBox2;
	DifficultyButton* _starBox3;
};

#endif // __ARTSCENE_H__
