#ifndef __ARTSCENECELL_H__
#define __ARTSCENECELL_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "model/ArtManager.h"

class ArtSceneCell : public cocos2d::extension::TableViewCell
{
public:
	void init(Art* art);
	virtual void draw(cocos2d::Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;
	
	void setHighlight(bool highlight);

private: 
	cocos2d::LayerColor* _blackBox;
};

#endif /* __ARTSCENECELL_H__ */

