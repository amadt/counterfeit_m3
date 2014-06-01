#include "TitleScreen.h"

USING_NS_CC;

Scene* TitleScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer =  TitleScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScreen::init()
{
	CCLog("INIT!");


	//draw a giant box behind everything
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto clickBox = LayerColor::create(Color4B(192, 0, 0, 255), visibleSize.width, visibleSize.height);
	clickBox->setCascadeColorEnabled(false);
	clickBox->setPosition(Point(0, 0));
	clickBox->setTouchEnabled(false);

	addChild(clickBox);
	
	auto label = LabelTTF::create("Counterfeit", "Arial", 34);

	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height - 100));

	// add the label as a child to this layer
	addChild(label);
	setTouchEnabled(true);

 




    return true;
}

void TitleScreen::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
	CCLog("Touch Pressed ");


}


