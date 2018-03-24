#include "Utils.h"

Vec2 Utils::GetPositionInWorld(Coord & c)
{
	return Vec2(BOT_LEFT_X + c.m_x * OFFSET_X, BOT_LEFT_Y + c.m_y * OFFSET_Y);
}

/*
*  Viên kẹo ở vị trí (x; y) = (0;0) ở góc bên trái.
*  Xếp từ trái qua phải, từ trên xuống dưới.
*/
Vec2 Utils::GetPositionInWorldMan(Coord & c)
{
	return Vec2(BOT_LEFT_X + c.m_x * OFFSET_X, BOT_LEFT_Y + c.m_y * OFFSET_Y);
}
