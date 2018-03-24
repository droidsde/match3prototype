#pragma once
#include "cocos2d.h"
#include "MainMenuScene.h"

class MainMenu;

class MenuSettings : public cocos2d::Layer
{
private:
	cocos2d::Label	*m_labelBack;
	cocos2d::Label	*m_labelSave;

	//test animation
	cocos2d::Sprite	*m_sprite;
	Vector<SpriteFrame*>	m_aniFrame;
	void	runAnimation(cocos2d::Sprite* sprite);
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// a selector callback
	void	menuBackCallback(cocos2d::Ref* pSender);
	void	menuSaveCallback(cocos2d::Ref* pSender);

	bool		onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void		onTouchEnded(cocos2d::Touch*, cocos2d::Event*);


	// implement the "static create()" method manually
	CREATE_FUNC(MenuSettings);

};