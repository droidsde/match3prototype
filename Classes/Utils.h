#pragma once
#include "cocos2d.h"
#include "defined.h"

USING_NS_CC;


namespace Utils {
	Vec2	GetPositionInWorld(Coord &c);
	// for manual setup
	Vec2	GetPositionInWorldMan(Coord &c);
}
