#pragma once

#define		Z_INDEX_CANDY		50
#define		Z_INDEX_LABEL		40
#define		Z_INDEX_BG			20

#define		SCALE_OF_TILE		(0.6f)

#define		RAND_MIN_RANGE			1
#define		RAND_MAX_RANGE			20

#define		NUM_OF_COL		7
#define		NUM_OF_ROW		5

#define		DEBUGGABLE	0

// setup board manual
#define		MANUAL_SETUP	1

#define		ENABLE_ANIMATION  1

// thực hiện xong animation swap.
#define		STATE_IS_SWAPPED	1

// thực hiện xong animation undo swap.
#define		STATE_IS_UNDO_SWAPPED	2

// có match-3 sau khi swap.
#define		STATE_IS_M3_AFTER_SWAPPED	3

// có match-3 sau khi check toàn bộ board.
#define		STATE_IS_M3_AFTER_CHECK_ALL_BOARD	4

#define		FONT_LABEL_PATH		"fonts/Marker Felt.ttf"

#define		TITLE_GAME			"Match 3 Prototype"
#define		TEXT_START			"Start Game"
#define		TEXT_HIGHSCORE			"High Scores"
#define		TEXT_EXIT			"Exit Game"
#define		TEXT_SETTINGS			"Settings"
#define		TEXT_BACK			"Back"
#define		TEXT_SAVE			"Save"
#define		TEXT_REPLAY			"Replay"
#define		TEXT_GO2MENU			"Main Menu"

#define		FONT_SIZE		30

// 35%
#define		TYPE_ONE	1
#define		SCORE_ONE	10

// 20%
#define		TYPE_TWO	2
#define		SCORE_TWO	20

// 15%
#define		TYPE_THREE	3
#define		SCORE_THREE 40

// 10%
#define		TYPE_FOUR	4
#define		SCORE_FOUR	50

// 20%
#define		TYPE_FIVE	5
#define		SCORE_FIVE	20
/*
/ goc toa do la goc trai duoi
/ witdh = 800, height = 480
*/
#define		BOT_LEFT_X	100
#define		BOT_LEFT_Y	100

#define		TOP_LEFT_X	100
#define		TOP_LEFT_Y	360

#define		OFFSET_X	(100*SCALE_OF_TILE)
#define		OFFSET_Y	(100*SCALE_OF_TILE)
#define		OFFSET_LABEL	30

// thoi gian khoi tao = 120s
#define		INIT_TIMER	120

typedef struct Coord	// coordinate
{
	int		m_x; // chỉ số theo trục x
	int		m_y; // chỉ số theo trục y

	// khởi tạo giá trị mặc định (-1, -1) để tránh nhầm với gốc tọa độ (0, 0).
	Coord(int x = -1, int y = -1)
	{
		m_x = x;
		m_y = y;
	}

	void operator=(const Coord& p)
	{
		m_x = p.m_x;
		m_y = p.m_y;
	}

	bool operator==(const Coord& p)
	{
		if ((m_x == p.m_x) && (m_y == p.m_y))
		{
			return true;
		}
		return false;
	}

	bool operator!=(const Coord& p)
	{
		if ((m_x != p.m_x) || (m_y != p.m_y))
		{
			return true;
		}
		return false;
	}

}Coord;
