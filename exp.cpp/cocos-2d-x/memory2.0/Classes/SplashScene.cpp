#include "SplashScene.h"
#include "StateMachineScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include <iostream>

USING_NS_CC;

Scene* SplashScene::createScene()
{
    return SplashScene::create();
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        std::cout << "ERROR in SplashScene.cpp" << std::endl;
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(schedule_selector(SplashScene::GoToStateMachineScene), DISPLAY_TIME_SPLASH_SCENE);

    auto backgroundSprite = Sprite::create("Splash.png");
    if (!backgroundSprite)
    {
        std::cerr << "Kan Splash.png niet vinden" << std::endl;
        return false;
    }
    backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backgroundSprite);

    return true;
}

void SplashScene::GoToStateMachineScene(float dt)
{
    std::cout << "Everything went OK" << std::endl;
    auto scene = StateMachineScene::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(TRANSITION_TIME, scene));
}
