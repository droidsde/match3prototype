#pragma once
#include "Chain.h"
#include "Candy.h"
#include <vector>
#include <string>
#include "Utils.h"


class Chain;
class Candy;


class GameMgr {
public:
	static GameMgr* GetInstance();

	/// for board
	void	SetUpBoard(cocos2d::Layer *layer);
	void	SetUpBoardManual(cocos2d::Layer *layer, std::string fileName);
	void	SetUpBoardType(std::string fileName);
	void	PrintBoardType();
	void	ClearBoardType();
	void	RemoveTile(int x, int y);
	void	Update(float dt);

	void	CheckMatchThreeInRow();

	void	PrintBoard();
	void	CheckMatchVertical(Candy* currCandy, bool isAfterSwap = false);
	void	CheckMatchHorizontal(Candy* currCandy, bool isAfterSwap = false);
	void	CheckAllMatch3();
	bool	CheckMatch3AfterSwap();

	// kiểm tra p có thuộc 1 trong các tile (cái kẹo).
	void	CheckAllSprite(Vec2 &p);
	bool	IsValidSwap();
	// for manual setup
	bool	IsValidSwapMan();
	void	PrintAllMatch3();

	void	SwapTiles();
	// for manual setup
	void	SwapTilesMan();
	void	UndoSwapTiles();

	// for manual setup
	void	FalldownAllMan();
	void	ReFillBoard();
	void	RemoveAllMatch3();

	void	SetupLabel(cocos2d::Layer *layer);
	int		CalculateScore();
	void	UpdateScore();
	void	UpdateTimer(float dt);
	/// get & set
	int		GetNumOfAllChains();
	int		GetNumOfChainAfterSwap();
	/// member

	// xác định trạng thái hiện tại của game.
	int				m_currState = 0;

	Coord			m_firstPos;
	Coord			m_firstPosAfterSwap;
	Coord			m_secondPos;
	Coord			m_secondPosAfterSwap;

	Vec2			m_pointClicked;
	// flags
	bool			m_isTouchable = true;

	// this flag for checkAllMatch() function, all sprites must be display on board.(animation have been done)
	bool			m_isBoardFilled;

	bool			m_isRemoveDone;

	bool			m_isAllFalling;

	bool			m_isActionDone;

	bool			m_isSwaping;

	const Coord		INIT_COORD = Coord();
	const std::string  SCORE_LB = "Score: ";
	const std::string  TIMER_LB = "Time: ";
private:
	Candy*		m_board[NUM_OF_COL][NUM_OF_ROW];
	int			m_boardType[NUM_OF_COL][NUM_OF_ROW];

	std::vector<Chain>		m_allChainsVertical; // chứa các chain theo chiều dọc.
	std::vector<Chain>		m_allChainsHorizontal; // chứa các chain theo chiều ngang.

	std::vector<Chain>		m_chainVerticalAfterSwap; // chứa các chain dọc(nếu có) sau khi swap.
	std::vector<Chain>		m_chainHorizontalAfterSwap; // chứa các chain ngang(nếu có) sau khi swap.

	static GameMgr* m_pInstance;
	cocos2d::Layer*	m_layer;
	
	// hiển thị điểm
	cocos2d::Label		*m_scoreLb;
	// hiển thị "Score: "
	cocos2d::Label		*m_labelScore;
	// hiển thị thời gian
	cocos2d::Label		*m_timerLb;
	// hiển thị "Time: "
	cocos2d::Label		*m_labelTimer;
	// tổng số score.
	int				m_totalScore;
	cocos2d::Label		*m_labelStart;
	cocos2d::Label		*m_labelGameOver;


	// lưu score của chain vừa bị remove.
	int				m_currScore;
	float				m_timer;
	GameMgr() 
	{
		m_firstPos = INIT_COORD;
		m_secondPos = INIT_COORD;
		m_isSwaping = false;
		m_isBoardFilled = true;
		m_isAllFalling = false;
		m_totalScore = 0;
		m_currScore = 0;
		m_timer = INIT_TIMER;
	};
	GameMgr(const GameMgr&) {};
	GameMgr& operator=(const GameMgr&) {};

	// true nếu tất cả các viên kẹo còn lại đã rơi xong, ngược lại false.
	bool	CheckAllFalldownDone();
	// true nếu board đc filled, ko thì false.
	bool	CheckAllBoardFilled();
	int		GetLowestYNull(int column);
	int		GetLowestYCandy(int column);
};
