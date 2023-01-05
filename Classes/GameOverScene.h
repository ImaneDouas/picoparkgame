#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void update(float dt);

    void GoToPlayScene(Ref* pSender);//will be called when the player clicks on the retry button from the game over s to replace it with game s
    void GoToHelloWorldScene(Ref* pSender);//will be called when the player clicks on the menu button from the game over s to replace it with menu s
};

#endif // __PLAY_SCENE_H__