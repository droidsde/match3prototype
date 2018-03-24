#include "GameOverScene.h"

USING_NS_CC;


cocos2d::Scene * GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	m_lbReplay = Label::createWithTTF(TEXT_REPLAY, FONT_LABEL_PATH, FONT_SIZE);
	m_lbReplay->setColor(Color3B::ORANGE);
	auto itemReplay = MenuItemLabel::create(m_lbReplay, CC_CALLBACK_1(GameOver::replayCallback, this));
	itemReplay->setPosition(Vec2(origin.x + m_lbReplay->getContentSize().width, origin.y + visibleSize.height - m_lbReplay->getContentSize().height));

	auto menuItem = Menu::create(itemReplay, NULL);
	menuItem->setPosition(Vec2::ZERO);
	this->addChild(menuItem, 1);


	return true;
}

void GameOver::replayCallback(cocos2d::Ref * pSender)
{
}

void GameOver::goToMenuCallback(cocos2d::Ref * pSender)
{
}

bool GameOver::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	return false;
}

void GameOver::onTouchEnded(cocos2d::Touch *, cocos2d::Event *)
{
}
