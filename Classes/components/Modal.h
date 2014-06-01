#ifndef __MODAL_H__
#define __MODAL_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "model/GameManager.h"

class Modal : public cocos2d::LayerColor
{
public:
	static Modal* show(cocos2d::Node* parent, int zIndex = 200);
	CREATE_FUNC(Modal);
private: 

};

#endif /* __MODAL_H__ */

