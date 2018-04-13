#include "StateMachineScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "GameScene.h"
#include <iostream>

USING_NS_CC;

Scene* StateMachineScene::createScene()
{
    return StateMachineScene::create();
}

// on "init" you need to initialize your instance
bool StateMachineScene::init()
{
	class StateMachine
	{
	public:

	private:
		enum class State
		{
			GameScene, Shop, AboutScene
		};

		void change_state_(State newState)
		{
			if (state_ == newState)
				return;
			state_ = newState;


			//enter
			switch(state_)
			{
				case State::GameScene:

				break;

				case State::Shop:

				break;

				case State::AboutScene:

				break;
			}
		}

		State state_ = State::GameScene;
	};

    return true;
}
