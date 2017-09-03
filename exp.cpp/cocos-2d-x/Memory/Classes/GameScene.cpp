#include "SplashScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
USING_NS_CC;

string GetString(int x)
{
	ostringstream oss;
	oss << x << endl;
	return oss.str();
}

Scene* GameScene::createScene()
{
	cout << "GameScene" << endl;
	auto scene = Scene::create();

	auto layer = GameScene::create();
	if (layer)
		scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		cout << "FOUT in GameScene" << endl;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("HelloWorld.png");
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(background);

    int score = 0;
    auto scoreString = std::string("Score: ") + std::to_string(score);

    auto scoreLabel = Label::createWithSystemFont(scoreString, "Arial", 16);
    scoreLabel->setPosition(Vec2(visibleSize.width/1.15 + origin.x, visibleSize.height/10 + origin.y));
    scoreLabel->setColor(Color3B(245, 10, 10));
    this->addChild(scoreLabel);

    return true;
}