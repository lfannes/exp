#include "SplashScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

using namespace std;
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	cout << "MainMenuScene" << endl;
	auto scene = Scene::create();

	auto layer = MainMenuScene::create();
	if (layer)
		scene->addChild(layer);

	return scene;
}

bool MainMenuScene::init()
{
	if (!Layer::init())
	{
		cout << "FOUT in MainMenuScene" << endl;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto playItem = MenuItemImage::create("res/play.png", "res/playClicked.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/1.5 + origin.y));
    playItem->setScale(0.5f);

    auto exitItem = MenuItemImage::create("res/exit.png", "CloseSelected.png", CC_CALLBACK_1(MainMenuScene::Exit, this));
    exitItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/3.25 + origin.y));
    exitItem->setScale(0.5f);

    auto menu = Menu::create(playItem, exitItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

	return true;
}

void MainMenuScene::GoToGameScene(Ref* sender)
{
	cout << "Button pressed" << endl;
	auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
	
}

void MainMenuScene::Exit(Ref* sender)
{
	cout << "exit" << endl;
	exit(1);
}