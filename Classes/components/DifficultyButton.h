#ifndef __DIFFICULTYBUTTON_H__
#define __DIFFICULTYBUTTON_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "model/GameManager.h"

class DifficultyButton : public cocos2d::Layer
{
public:
	void drawLevel(Art* art, Level level);
	virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

	CREATE_FUNC(DifficultyButton);
private: 
	Level _level;
	Art* _art;
};

#endif /* __ARTSCENECELL_H__ */

