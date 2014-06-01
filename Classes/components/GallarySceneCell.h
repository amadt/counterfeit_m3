#ifndef __GALLARYSCENECELL_H__
#define __GALLARYSCENECELL_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "model/ArtManager.h"

class GallarySceneCell : public cocos2d::extension::TableViewCell
{
public:
	void init(Gallary* art);
	virtual void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;

private: 
	cocos2d::LayerColor* _blackBox;
};

#endif /* __GALLARYSCENECELL_H__ */

