#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "controller/BlobController.h"
#include "controller/LineController.h"
#include "controller/ArtController.h"
#include "model/ArtManager.h"
#include "model/GameManager.h"
#include "components/Modal.h"

class TopBar;
class GameScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	static GameScene* create();
	GameScene();

	virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

	virtual void update(float delta);
	void exitGameClick(Ref* sender);
	void timeAddClick(Ref* sender);
	void recycleClick(Ref* sender);
	void flipClick(Ref* sender);
	void peekClick(Ref *sender);
	void hintClick(Ref *sender);

	void skip(Ref* sender);

private:
	void updateTimeLabel();
	bool checkBlobPhaseEnd();
	void showModal(bool show = true);

	BlobController* _blobController;
	LineController* _lineController;
	ArtController* _artController;
	bool _isDragging;
	cocos2d::Point _lastCoords;
	Level _level;
	Art* _art;
	bool _isPaused;
	bool _isGameOver;
	float _timeLeft;
	float _waiting;
	float _timeAdd;
	float _hintTimer;
	Modal* _modal;
	bool _resetAfterWait;
	bool _isPeeking;
	cocos2d::LabelTTF* _timerLabel;
	cocos2d::LabelTTF* _gameOverLabel;

	cocos2d::Menu* _timeButton;
	cocos2d::Menu* _recycleButton;
	cocos2d::Menu* _flipButton;
	cocos2d::Menu* _hintButton;
	cocos2d::Menu* _peekButton;
	TopBar* _redBox;
};

#endif // __GAME_SCENE_H__
