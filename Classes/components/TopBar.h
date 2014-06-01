#ifndef __TOPBAR_H__
#define __TOPBAR_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "model/GameManager.h"

class TopBar : public cocos2d::LayerColor
{
public:
	virtual bool init();
	CREATE_FUNC(TopBar);
	void refresh();
private: 
	cocos2d::LabelTTF* _liveText;
	cocos2d::LabelTTF* _tokenText;
};

#endif /* __ARTSCENECELL_H__ */

