#include "Modal.h"
#include "Util.h"

USING_NS_CC;
extern float G_assetScale;

Modal* Modal::show(cocos2d::Node* parent, int zIndex)
{
	Modal* modal = new Modal();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (modal && modal->initWithColor(Color4B(0, 0, 0, 180), visibleSize.width, visibleSize.height))
	{
		parent->addChild(modal, zIndex);
		modal->autorelease();
		return modal;
	}
	CC_SAFE_DELETE(modal);
	return nullptr;
}




