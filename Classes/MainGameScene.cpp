#include "MainGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Scene* MainGame::createScene()
{
	auto scene = Scene::create();

	auto layer = MainGame::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainGame::menuCloseCallback, this));

	closeItem->setPosition(Vec2(m_origin.x + m_visibleSize.width - closeItem->getContentSize().width / 2,
		m_origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	m_gameMgr = GameMgr::GetInstance();
	m_gameMgr->SetupLabel(this);
#if MANUAL_SETUP
	m_gameMgr->ClearBoardType();
	m_gameMgr->SetUpBoardType("../board4.txt");
	m_gameMgr->SetUpBoardManual(this, "");
#else
	m_gameMgr->SetUpBoard(this);
#endif
	
	
	return true;
}

void		MainGame::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}



