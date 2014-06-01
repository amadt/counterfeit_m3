#include "AppDelegate.h"
#include "scenes/GameScene.h"
#include "scenes/GallaryScene.h"
#include "scenes/ArtScene.h"
#include "scenes/TitleScreen.h"
#include "Util.h"

USING_NS_CC;
extern float G_assetScale;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
		glview->setFrameSize(480, 852);

		director->setOpenGLView(glview);
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	G_assetScale = visibleSize.width / ASSET_SCALE_WIDTH;

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
    //auto scene = GameScene::createScene(_artManager->GetArt(1));
	auto scene = GallaryScene::createScene();

    // run
    director->runWithScene(scene);
	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
