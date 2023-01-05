#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

class PauseScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();




    void Resume(Ref* pSender);//will be called when player clicks on resume button from the Pause scene to pop the Pause scene off the stack.
    void GoToHelloWodldScene(Ref* pSender); //will be called when player  clicks on menu button from the Pause scene to replace the current scene with the Main Menu scene while popping all the scenes off the stack.
    void Retry(Ref* pSender); //will be called when the player clicks on the retry button from the Pause scene to replace the current scene with the Game scene while popping all the scenes off the stack
};

#endif // __PLAY_SCENE_H__