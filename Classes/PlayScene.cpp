#include "PlayScene.h"
#include "PauseScene.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* PlayScene::createScene()
{
    return PlayScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();


    //white back ground
    auto background = Sprite::create("bggame.jpg");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScaleY(9.0);
    background->setScaleX(9.0);
    this->addChild(background, -4);

    // orange nodes
    auto ground1 = Sprite::create("ground1.png");
    ground1->setScaleY(4.0);
    ground1->setScaleX(4.0);
    ground1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    ground1->setPosition(Vec2::ZERO);

    auto ground2 = Sprite::create("ground1.png");
    ground2->setScaleY(4.0);
    ground2->setScaleX(4.0);
    ground2->setPosition(Vec2(2000, 80));

    auto groundup = Sprite::create("ground1.png");
    groundup->setScaleY(2.0);
    groundup->setScaleX(2.0);
    groundup->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    groundup->setPosition(Vec2(800, 300));

    auto groundup2 = Sprite::create("ground1.png");
    groundup2->setScaleY(2.0);
    groundup2->setScaleX(2.0);
    groundup2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    groundup2->setPosition(Vec2(1200, 500));




    this->scheduleUpdate();
    /*The update function is used to handle the game's logic and takes a float parameter
    called delta time, which is the time between frames. As all devices are not capable of
    running at 60 fps, this is factored in during gameplay to provide a smooth experience
    across a wide variety of devices*/


    //pause icon

    //creates an image item with the parameters
    auto pauseItem = MenuItemImage::create("HelloWorld.png",
        "HelloWorld.png",
        CC_CALLBACK_1(PlayScene::GoToPauseScene, this));

    //sets the position of the menu item to the top-left corner of the screen.
    pauseItem->setPosition(Point(pauseItem->getContentSize().width - (pauseItem->getContentSize().width / 4) + origin.x,
        visibleSize.height - pauseItem->getContentSize().height + (pauseItem->getContentSize().width / 4) + origin.y));
    //creates a menu with the Menu item.
    auto menu = Menu::create(pauseItem, NULL);
    //sets the menu's position to 0, as the menu item was positioned separately.
    menu->setPosition(Point::ZERO);
    //adds the menu as a child to the scene. To add children to the scene, the addChild() method requires a node
    this->addChild(menu);




    initWithPhysics();
    sceneWorld = getPhysicsWorld();
    sceneWorld->setGravity(Vec2(0, -98));
    sceneWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);



    auto ground1Body = PhysicsBody::createBox(ground1->getContentSize(), PhysicsMaterial(0, 1, 0));
    ground1Body->setDynamic(false);
    ground1->setPhysicsBody(ground1Body);

    auto ground2Body = PhysicsBody::createBox(ground2->getContentSize(), PhysicsMaterial(0, 1, 0));

    ground2Body->setDynamic(false);//par defaut kayjiw static in order to make em dynamic we set this functio to false
    ground2->setPhysicsBody(ground2Body);

    auto groundupbd = PhysicsBody::createBox(ground2->getContentSize(), PhysicsMaterial(0, 1, 0));

    groundupbd->setDynamic(false);//par defaut kayjiw static in order to make em dynamic we set this functio to false
    groundup->setPhysicsBody(groundupbd);

    auto groundup2bd = PhysicsBody::createBox(ground2->getContentSize(), PhysicsMaterial(0, 1, 0));

    groundup2bd->setDynamic(false);//par defaut kayjiw static in order to make em dynamic we set this functio to false
    groundup2->setPhysicsBody(groundup2bd);

    auto obs1 = Sprite::create("obs1.png");
    obs1->setScaleX(2.75);
    obs1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    obs1->setPosition(Vec2(900, 10));
    auto obsbd = PhysicsBody::createBox(ground2->getContentSize(), PhysicsMaterial(0, 1, 0));

    obsbd->setCollisionBitmask(2);
    obsbd->setContactTestBitmask(true);
    obsbd->setDynamic(false);
    obs1->setPhysicsBody(obsbd);





    auto mySprite = Sprite::create("picoplayer.png");
    mySprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // Create a physics body for the hero
    auto heroBody = PhysicsBody::createBox(mySprite->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.0f));
    heroBody->setCollisionBitmask(1);
    heroBody->setContactTestBitmask(true);
    // Set the physics body of the hero
    mySprite->setPhysicsBody(heroBody);



    this->addChild(mySprite);
    this->addChild(ground1, -1);
    this->addChild(ground2, -1);
    this->addChild(groundup, -1);
    this->addChild(groundup2, -1);
    this->addChild(obs1, -1);





    auto eventListener = EventListenerKeyboard::create();


    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {

        bool leftkeypressed = false;
        bool rightkeypressed = false;

        Vec2 loc = event->getCurrentTarget()->getPosition();
        auto newPosition = loc + Vec2(0, 30);
        auto jumpHeight = 100;
        auto jumpDuration = 0.5f;
        auto jumpActionright = MoveTo::create(jumpDuration, loc + Vec2(30, jumpHeight));
        auto jumpActionleft = MoveTo::create(jumpDuration, loc + Vec2(-30, jumpHeight));

        auto downDuration = 0.5f;
        auto downActionright = MoveTo::create(downDuration, loc + Vec2(30, 0));
        auto downActionleft = MoveTo::create(downDuration, loc + Vec2(-30, 0));
        auto sequenceright = Sequence::create(jumpActionright, downActionright, NULL);
        auto sequenceleft = Sequence::create(jumpActionleft, downActionleft, NULL);
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            event->getCurrentTarget()->setScaleX(-1);
            event->getCurrentTarget()->setPosition(loc.x - 30, loc.y);

            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:

            event->getCurrentTarget()->setScaleX(1);
            event->getCurrentTarget()->setPosition(loc.x + 30, loc.y);
            break;


        case EventKeyboard::KeyCode::KEY_SPACE:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_W:
            if (event->getCurrentTarget()->getScaleX() == 1)
                event->getCurrentTarget()->runAction(sequenceright);


            //event->getCurrentTarget()->runAction(sequence);;
            else
                event->getCurrentTarget()->runAction(sequenceleft);

            break;
        }

    };



    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, mySprite);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


    return true;
}





void PlayScene::update(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

}





//include pause scene & gameover s so that they can be accessed
void PlayScene::GoToPauseScene(cocos2d::Ref* pSender)
{
    CCLOG("GoToPauseScene");
    auto scene = PauseScene::createScene();

    Director::getInstance()->pushScene(scene);
}
void PlayScene::GoToGameOverScene(cocos2d::Ref* pSender)
{
    auto scene = GameOver::createScene();

    Director::getInstance()->pushScene(scene);
}

bool PlayScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    // check if the bodies have collided
    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        CCLOG("COLLISION HAS OCCURED");
        auto scene = GameOver::createScene();

        Director::getInstance()->replaceScene(scene);
        CCLOG("GOTOGAMEOVR");
    }

    return true;
}