#pragma once

#include "cocos2d.h"
#include "Candy.h"
#include "defined.h"
#include <iostream>
#include "Chain.h"
#include "GameMgr.h"


class Candy;
class Chain;


class MainGame : public cocos2d::Layer
{

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	GameMgr		*m_gameMgr;
	// a selector callback
	void	menuCloseCallback(cocos2d::Ref* pSender);
	

	// implement the "static create()" method manually
	CREATE_FUNC(MainGame);

	cocos2d::Size	m_visibleSize;
	cocos2d::Vec2	m_origin;
};
