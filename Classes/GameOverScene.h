#pragma once

#include "cocos2d.h"
#include "defined.h"
#include "MainGameScene.h"

class MainGame;


class GameOver : public cocos2d::Layer
{
private:
	cocos2d::Label	*m_lbReplay;
	cocos2d::Label	*m_lbGoToMenu;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// a selector callback
	void	replayCallback(cocos2d::Ref* pSender);
	void	goToMenuCallback(cocos2d::Ref* pSender);

	bool		onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void		onTouchEnded(cocos2d::Touch*, cocos2d::Event*);


	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);
};
