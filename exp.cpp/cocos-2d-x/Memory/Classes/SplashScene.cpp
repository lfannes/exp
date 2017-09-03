#include "SplashScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();

    auto layer = SplashScene::create();
    if (layer)
    {
        scene->addChild(layer);
    }
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), 2);

    // add "SplashScene" splash screen"
    auto background = Sprite::create("HelloWorld.png");

    // position the background on the center of the screen
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the background as a child to this layer
    this->addChild(background, 0);
    
    return true;
}



void SplashScene::GoToMainMenuScene(float dt)
{
    std::cout << "GoToMainMenuScene" << std::endl;
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}