#ifndef __TITLESCREEN_H__
#define __TITLESCREEN_H__

#include "cocos2d.h"

class TitleScreen : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

	// implement the "static create()" method manually
	CREATE_FUNC(TitleScreen);
};

#endif // __TITLESCREEN_H__
