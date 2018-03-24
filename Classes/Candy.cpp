#include "Candy.h"

Candy::Candy()
{
	m_isAppear = false;
	m_isMoving = false;
	m_isFalling = false;
}

Candy* Candy::createCandyWithFileName(char *fileName)
{
	auto sprite = new Candy;
	if (sprite && sprite->initWithFile(fileName))
	{
		//sprite->setVisible(false);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Candy*		Candy::InitWithType(int  randomType)
{
	auto sprite = new Candy;
	switch (randomType)
	{
	case TYPE_ONE:

		break;
	case TYPE_TWO:
		break;
	case TYPE_THREE:
		break;
	case TYPE_FOUR:
		break;
	case TYPE_FIVE:
		break;
	default:
		break;
	}
	return nullptr;
}

void Candy::Init(Coord coord, int type)
{
	m_coord = coord;
	m_type = type;
	m_isMoving = false;
}

bool		Candy::IsSelected(const Point& p)
{
	// hàm trả về true nếu "viên kẹo" được chọn
	if (this->getBoundingBox().containsPoint(p))
	{
		//CCLOG("Candy have touched !!");
		return true;
	}
	return false;
}

void Candy::SelectAnimation()
{
	CCLOG("Candy::SelectAnimation--");
}

void Candy::ExploseAnimation()
{
	
}

void		Candy::DisAppear()
{
	auto fadeOut = FadeOut::create(1.0f);
	auto setDisAppearDone = CallFunc::create([&]()
	{
		/// this callback function will call when animation have been done.
		m_isAppear = false;
	});
	this->runAction(Sequence::create(fadeOut, setDisAppearDone, nullptr));
}

void		Candy::Appear()
{
	auto fadeIn = FadeIn::create(1.0f);
	auto setAppearDone = CallFunc::create([&]()
	{
		/// this callback function will call when animation have been done.
		m_isAppear = true;
	});
	this->runAction(Sequence::create(fadeIn, setAppearDone, nullptr));
}

void		Candy::FallDownTo(int x, int y)
{
	CCLOG(" Candy::FallDownTo, x = %d, y = %d ", x, y);
	// thời gian rơi
	float dt;
	// vị trí đích.
	Vec2	destination;
	// vị trí hiện tại
	Vec2	source;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	destination = Utils::GetPositionInWorldMan(Coord(x, y));
	source = Utils::GetPositionInWorldMan(m_coord);
	// công thức này mình tự định nghĩa thôi.
	dt = (destination.y - source.y) / (2 * visibleSize.height);
	m_isFalling = true;
	auto fallDown = MoveTo::create(dt, destination);
	auto actionDone = CallFunc::create([&]() {
		m_isFalling = false;
	});
	this->runAction(Sequence::create(fallDown, actionDone, NULL));
}

