#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "PlayScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{

    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();





}
void GameOver::GoToPlayScene(cocos2d::Ref* pSender)
{
    auto scene = PlayScene::createScene();

    Director::getInstance()->replaceScene(scene);
}
void GameOver::GoToHelloWorldScene(cocos2d::Ref* pSender)
{
    auto scene = HelloWorld::createScene();

    Director::getInstance()->replaceScene(scene);
}


