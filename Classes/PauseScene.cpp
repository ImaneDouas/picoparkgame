#include "PauseScene.h"
#include "HelloWorldScene.h"
#include "PlayScene.h"

USING_NS_CC;

Scene* PauseScene::createScene()
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
bool PauseScene::init()
{

    if (!Layer::init())
    {
        return false;
    }
  /* auto pauseItem = MenuItemImage::create("GameScreen/Pause_Button.png", "GameScreen/Pause_Button(Click).png", CC_CALLBACK_1(GameScreen::GoToPauseScene, this));
    pauseItem->setPosition(Point(pauseItem->getContentSize().width -(pauseItem->getContentSize().width / 4) + origin.x, visibleSize.height - pauseItem->getContentSize().height +(pauseItem->getContentSize().width / 4) + origin.y));
    
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);*/ 
}
Size visibleSize = Director::getInstance()->getVisibleSize();
Point origin = Director::getInstance()->getVisibleOrigin();

void PauseScene::Resume(cocos2d::Ref* pSender)
{
    Director::getInstance()->popScene();
}

void PauseScene::GoToHelloWodldScene(cocos2d::Ref* pSender)
{
    auto scene = HelloWorld::createScene();

    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}
/*The GoToMainMenuScene
function first creates a local scene instance of the Main Menu scene, then it pops
the current scene off the stack and the Game scene is replaced with the Main Menu
scene*/
void PauseScene::Retry(cocos2d::Ref* pSender)
{
    auto scene = PlayScene::createScene();

    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}
/*The Retry function first creates a local scene instance of the Game scene, then
it pops the current scene off the stack and the current Game scene is replaced with
the new Game scene (restarts the game). */

