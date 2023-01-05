
#include "PlayScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    // create menu, it's an autorelease object
    auto menuTitle = MenuItemImage::create("Game_Title.png", "HelloWorld.png");
    auto playItem = MenuItemImage::create("Play_Button.jpg", "play.jpg", CC_CALLBACK_1(HelloWorld::GoToPlayScene, this));

    menuTitle->setScale(2.5);
    playItem->setScale(2.5);

    auto* menu = Menu::create(menuTitle, playItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
    this->addChild(menu);

    

    // add "HelloWorld" splash screen"
    auto background = Sprite::create("backgroundmenu.jpg");
    if (background == nullptr)
    {
        problemLoading("'backgroundmenu.jpg'");
        auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
    else
    {
        // position the sprite on the center of the screen
        background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        background->setScaleY(6.0);
        background->setScaleX(10);
        // add the sprite as a child to this layer
        this->addChild(background, -1);
    }
    return true;
}




void HelloWorld::GoToPlayScene(cocos2d::Ref* pSender)
{
    CCLOG("GoToPlayScene");
    auto scene = PlayScene::createScene();

    Director::getInstance()->pushScene(scene);
}
