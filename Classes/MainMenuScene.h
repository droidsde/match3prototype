#pragma once
#include "defined.h"
#include "cocos2d.h"
#include "MainGameScene.h"
#include "MenuSettingsScene.h"


class HelloWorld;
class MenuSettings;

class MainMenu : public cocos2d::Layer 
{
private:
	cocos2d::Label	*m_lbTitle;
	cocos2d::Label	*m_lbPlay;
	cocos2d::Label	*m_lbHighScore;
	cocos2d::Label	*m_lbSettings;
	cocos2d::Label	*m_lbExit;


public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// a selector callback
	void	menuCloseCallback(cocos2d::Ref* pSender);
	void	menuPlayCallback(cocos2d::Ref* pSender);
	void	menuHighScoreCallback(cocos2d::Ref* pSender);
	void	menuSettingsCallback(cocos2d::Ref* pSender);
	void	menuExitCallback(cocos2d::Ref* pSender);

	bool		onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void		onTouchEnded(cocos2d::Touch*, cocos2d::Event*);

	void	UpdateGame(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);
};
