#include "MenuSettingsScene.h"

USING_NS_CC;

void MenuSettings::runAnimation(cocos2d::Sprite* sprite)
{
	auto animation = Animation::createWithSpriteFrames(m_aniFrame, 0.1f);
	auto animate = Animate::create(animation);
	auto removeSelf = CallFunc::create([&](){
		//CCLOG("--- action DONE ! --");
	});
	sprite->runAction(Sequence::create(animate, removeSelf, NULL));
}

cocos2d::Scene * MenuSettings::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuSettings::create();

	scene->addChild(layer);

	return scene;
}

bool MenuSettings::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	m_labelBack = Label::createWithTTF(TEXT_BACK, FONT_LABEL_PATH, FONT_SIZE);
	m_labelBack->setColor(Color3B::ORANGE);
	auto itemBack = MenuItemLabel::create(m_labelBack, CC_CALLBACK_1(MenuSettings::menuBackCallback, this));
	itemBack->setPosition(Vec2(origin.x + m_labelBack->getContentSize().width, origin.y + visibleSize.height - m_labelBack->getContentSize().height));

	m_labelSave = Label::createWithTTF(TEXT_SAVE, FONT_LABEL_PATH, FONT_SIZE);
	m_labelSave->setColor(Color3B::GREEN);
	auto itemSave = MenuItemLabel::create(m_labelSave, CC_CALLBACK_1(MenuSettings::menuSaveCallback, this));
	itemSave->setPosition(Vec2(origin.x + visibleSize.width - m_labelSave->getContentSize().width, origin.y + m_labelSave->getContentSize().height));

	auto menuItem = Menu::create(itemBack, itemSave, NULL);
	menuItem->setPosition(Vec2::ZERO);
	this->addChild(menuItem, 1);

	// step 1:
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/explosion_green.plist");
	m_sprite = Sprite::create("candy/type_one.png");
	m_sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(m_sprite, 10);

	// step 2:
	std::string		fileName = "explosion_green_0";
	std::string		fileExt = ".png";
	std::string		file;
	for (int i = 1; i <= 5; i++)
	{
		file = fileName + std::to_string(i) + fileExt;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
		m_aniFrame.pushBack(frame);
	}

	auto _listener = EventListenerTouchOneByOne::create();
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = CC_CALLBACK_2(MenuSettings::onTouchBegan, this);
	_listener->onTouchEnded = CC_CALLBACK_2(MenuSettings::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
	// step 3:
	//auto animation = Animation::createWithSpriteFrames(aniFrame, 0.1f);
	//auto animate = Animate::create(animation);
	////auto callWhenDone = CallFunc::create([](cocos2d::Sprite* spr) {
	////	spr->setVisible(false);
	////});
	//auto removeSelf = RemoveSelf::create();
	//m_sprite->runAction(Sequence::create(animate, removeSelf, NULL));
	

	return true;
}

void MenuSettings::menuBackCallback(cocos2d::Ref * pSender)
{
	// back without save settings
	Director::getInstance()->popScene();
	CCLOG("--- Back !");
}

void MenuSettings::menuSaveCallback(cocos2d::Ref * pSender)
{
	CCLOG("--- Save !");
	// save any setting & back
	Director::getInstance()->popScene();
}

bool MenuSettings::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	if (m_sprite && m_sprite->getBoundingBox().containsPoint(touch->getLocation()))
	{
		CCLOG("--- selected !");
		runAnimation(m_sprite);
	}
	else
	{
		CCLOG("--- sprite is NULL ");
	}
	return true;
}

void MenuSettings::onTouchEnded(cocos2d::Touch *, cocos2d::Event *)
{
}
