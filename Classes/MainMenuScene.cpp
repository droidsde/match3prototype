#include "MainMenuScene.h"

USING_NS_CC;

cocos2d::Scene * MainMenu::createScene()
{
	auto scene = Scene::create();

	auto layer = MainMenu::create();

	scene->addChild(layer);

	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// set for label Title
	m_lbTitle = Label::createWithTTF(TITLE_GAME, FONT_LABEL_PATH, FONT_SIZE);
	m_lbTitle->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + 400));
	this->addChild(m_lbTitle, Z_INDEX_LABEL);


	// set for label Play
	m_lbPlay = Label::createWithTTF(TEXT_START, FONT_LABEL_PATH, FONT_SIZE);
	m_lbPlay->setColor(Color3B::BLUE);
	auto itemPlay = MenuItemLabel::create(m_lbPlay, CC_CALLBACK_1(MainMenu::menuPlayCallback, this));
	itemPlay->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 320));
	//this->addChild(m_labelPlay, Z_INDEX_LABEL);

	// set for label Settings
	m_lbSettings = Label::createWithTTF(TEXT_SETTINGS, FONT_LABEL_PATH, FONT_SIZE);
	m_lbSettings->setColor(Color3B::YELLOW);
	auto itemSettings = MenuItemLabel::create(m_lbSettings, CC_CALLBACK_1(MainMenu::menuSettingsCallback, this));
	itemSettings->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 240));
	
	// set for label HighScore
	m_lbHighScore = Label::createWithTTF(TEXT_HIGHSCORE, FONT_LABEL_PATH, FONT_SIZE);
	m_lbHighScore->setColor(Color3B::GREEN);
	auto itemHighScore = MenuItemLabel::create(m_lbHighScore, CC_CALLBACK_1(MainMenu::menuHighScoreCallback, this));
	itemHighScore->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 160));

	// set for label Exit
	m_lbExit = Label::createWithTTF(TEXT_EXIT, FONT_LABEL_PATH, FONT_SIZE);
	m_lbExit->setColor(Color3B::RED);
	auto itemExit = MenuItemLabel::create(m_lbExit, CC_CALLBACK_1(MainMenu::menuExitCallback, this));
	itemExit->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 80));
	

	auto menuItem = Menu::create(itemPlay, itemSettings, itemHighScore, itemExit, NULL);
	menuItem->setPosition(Vec2::ZERO);
	this->addChild(menuItem, 1);

	return true;
}

void MainMenu::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainMenu::menuPlayCallback(cocos2d::Ref * pSender)
{
	auto playGameScene = MainGame::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, playGameScene));
	CCLOG("-- Play ");
}

void MainMenu::menuHighScoreCallback(cocos2d::Ref * pSender)
{
	CCLOG("--- High Score ");
}

void MainMenu::menuSettingsCallback(cocos2d::Ref * pSender)
{
	auto settingScene = MenuSettings::createScene();
	Director::getInstance()->pushScene(settingScene);
	CCLOG("-- Settings ");
}

void MainMenu::menuExitCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
	CCLOG("-- Exit ");
}

bool MainMenu::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	CCLOG("--- Go to GamePlayScene ---");
	return true;
}

void MainMenu::onTouchEnded(cocos2d::Touch *, cocos2d::Event *)
{
}
