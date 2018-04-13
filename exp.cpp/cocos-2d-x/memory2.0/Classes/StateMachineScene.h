#ifndef __STATEMACHINE_SCENE_H__
#define __STATEMACHINE_SCENE_H__

#include "cocos2d.h"

class StateMachineScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(StateMachineScene);
};

#endif // __HELLOWORLD_SCENE_H__
