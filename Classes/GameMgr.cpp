#include "GameMgr.h"

#include "GameMgr.h"
#include <ctime>
#include <chrono>
#include "defined.h"
#include "Chain.h"
#include <iostream>
#include <fstream>
#include <sstream>


GameMgr* GameMgr::m_pInstance = nullptr;

GameMgr * GameMgr::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GameMgr();
	}
	return m_pInstance;
}

void GameMgr::SetUpBoard(cocos2d::Layer *layer)
{
	m_layer = layer;
	int x = 0, y = 0;

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::srand(seed);
	int random = 0;
	/// x là chỉ số của cột, y là chỉ số của hàng.
	/// gốc của board là góc dưới bên trái.
	/// một tile có vị trí (x; y) = (hàng, cột)
	for (x = 0; x < NUM_OF_COL; x++)
	{
		for (y = 0; y < NUM_OF_ROW; y++)
		{
			random = RAND_MIN_RANGE + std::rand() % (RAND_MAX_RANGE - RAND_MIN_RANGE + 1);
			if (random <= 6) // 1 - 6
			{
				m_board[x][y] = Candy::createCandyWithFileName("candy/type_one.png");
				m_board[x][y]->m_type = TYPE_ONE;
			}
			else if (random <= 10) // 7 - 10
			{
				m_board[x][y] = Candy::createCandyWithFileName("candy/type_two.png");
				m_board[x][y]->m_type = TYPE_TWO;
			}
			else if (random <= 13) // 11 - 13
			{
				m_board[x][y] = Candy::createCandyWithFileName("candy/type_three.png");
				m_board[x][y]->m_type = TYPE_THREE;
			}
			else if (random <= 15) // 14 - 15
			{
				m_board[x][y] = Candy::createCandyWithFileName("candy/type_four.png");
				m_board[x][y]->m_type = TYPE_FOUR;
			}
			else // 17 - Max_range
			{
				m_board[x][y] = Candy::createCandyWithFileName("candy/type_five.png");
				m_board[x][y]->m_type = TYPE_FIVE;
			}
			m_board[x][y]->setScale(SCALE_OF_TILE);
			m_board[x][y]->m_coord = Coord(x, y);
			m_board[x][y]->setPosition(Utils::GetPositionInWorld(Coord(x, y)));
			layer->addChild(m_board[x][y], Z_INDEX_CANDY);
		}
	}

}

void GameMgr::SetUpBoardManual(cocos2d::Layer * layer, std::string fileName)
{
	int type = 0;
	m_layer = layer;
	for (int x = 0; x < NUM_OF_COL; x++)
	{
		for (int y = 0; y < NUM_OF_ROW; y++)
		{
			type = m_boardType[x][4-y];
			switch (type)
			{
			case 1:
				m_board[x][y] = Candy::createCandyWithFileName("candy/type_one.png");
				m_board[x][y]->m_type = TYPE_ONE;
				m_board[x][y]->m_score = SCORE_ONE;
				break;
			case 2:
				m_board[x][y] = Candy::createCandyWithFileName("candy/type_two.png");
				m_board[x][y]->m_type = TYPE_TWO;
				m_board[x][y]->m_score = SCORE_TWO;
				break;
			case 3:
				m_board[x][y] = Candy::createCandyWithFileName("candy/type_three.png");
				m_board[x][y]->m_type = TYPE_THREE;
				m_board[x][y]->m_score = SCORE_THREE;
				break;
			case 4:
				m_board[x][y] = Candy::createCandyWithFileName("candy/type_four.png");
				m_board[x][y]->m_type = TYPE_FOUR;
				m_board[x][y]->m_score = SCORE_FOUR;
				break;
			case 5:
				m_board[x][y] = Candy::createCandyWithFileName("candy/type_five.png");
				m_board[x][y]->m_type = TYPE_FIVE;
				m_board[x][y]->m_score = SCORE_FIVE;
				break;

			default:
				break;
			}
			m_board[x][y]->setScale(SCALE_OF_TILE);
			m_board[x][y]->m_coord = Coord(x, y);
			m_board[x][y]->setPosition(Utils::GetPositionInWorldMan(Coord(x, y)));
			layer->addChild(m_board[x][y], Z_INDEX_CANDY);
		}
	}
}

void GameMgr::SetUpBoardType(std::string fileName)
{
	std::ifstream	file(fileName);
	if (!file.is_open())
	{
		CCLOG("Could not open file '%s' !", fileName.c_str());
		return;
	}
	std::string line;
	int		y = 0;
	while (std::getline(file, line))
	{
		std::istringstream	iss(line);
		for (int x = 0; x < NUM_OF_COL; x++)
		{
			iss >> m_boardType[x][y];
		}
		y++;
	}
	file.close();
}

void GameMgr::PrintBoardType()
{
	for (int x = 0; x < NUM_OF_COL; x++)
	{
		for (int y = 0; y < NUM_OF_ROW; y++)
		{
			CCLOG(" %d ", m_boardType[x][y]);
		}
		
	}
}

void GameMgr::ClearBoardType()
{
	for (int x = 0; x < NUM_OF_COL; x++)
	{
		for (int y = 0; y < NUM_OF_ROW; y++)
		{
			m_boardType[x][y] = 0;
		}
	}
}


void	GameMgr::RemoveTile(int x, int y)
{
	m_layer->removeChild(m_board[x][y]);
	m_board[x][y] = nullptr;
}

void GameMgr::Update(float dt)
{
	// process user's input
	if ((m_firstPos != INIT_COORD) && (m_secondPos != INIT_COORD))
	{
#if DEBUGGABLE
		CCLOG("--- giap: before swap ---");
		CCLOG("--- giap: 1st(%d, %d) %d ", m_firstPos.m_x, m_firstPos.m_y, m_board[m_firstPos.m_x][m_firstPos.m_y]->m_type);
		CCLOG("--- giap: 2nd(%d, %d) %d ", m_secondPos.m_x, m_secondPos.m_y, m_board[m_secondPos.m_x][m_secondPos.m_y]->m_type);
#endif
#if MANUAL_SETUP
		if (IsValidSwapMan())
		{
			SwapTilesMan();
		}
		else
		{
			m_firstPos = INIT_COORD;
			m_secondPos = INIT_COORD;
		}
#else
		if (IsValidSwap())
		{
			SwapTiles();
		}
		else
		{
			m_firstPos = INIT_COORD;
			m_secondPos = INIT_COORD;
		}
#endif
#if DEBUGGABLE
		CCLOG("--- giap: after swap ---");
		CCLOG("--- giap: 1st(%d, %d) %d ", m_firstPos.m_x, m_firstPos.m_y, m_board[m_firstPos.m_x][m_firstPos.m_y]->m_type);
		CCLOG("--- giap: 2nd(%d, %d) %d ", m_secondPos.m_x, m_secondPos.m_y, m_board[m_secondPos.m_x][m_secondPos.m_y]->m_type);
#endif
		// kiem tra xem co match-3 ở vị trí vừa swap ko
		// nếu k có thì swap trở lại.
		if (!CheckMatch3AfterSwap())
		{
			CCLOG("--- giap: Undo Swap Tile ----");
#if MANUAL_SETUP
			SwapTilesMan();
#else
			SwapTiles();
#endif
		}
		// swap xong thì remove 2 tọa độ đã lưu
		m_firstPos = INIT_COORD;
		m_secondPos = INIT_COORD;
		m_isSwaping = false; // enable touch from player
	}

	// finding match-3 & remove if find out.
	CheckAllMatch3();
	if (GetNumOfAllChains() > 0)
	{
		PrintAllMatch3();
		// tinh diem
		m_currScore = CalculateScore();
		// remove all chain
		RemoveAllMatch3();
		
		m_allChainsVertical.clear();
		m_allChainsHorizontal.clear();
	}
	else
	{
		//CCLOG("--- KO TIM THAY CHAIN NAO !");
	}

	//UpdateScore();
	//UpdateTimer(dt);

	// dồn các viên kẹo xuống phía dưới.
	FalldownAllMan();
	if (CheckAllFalldownDone())
	{
		// khi các viên kẹo đã rơi xong.
		m_isAllFalling = false;
	}

	// re-fill board if board isn't full.
	ReFillBoard();

	// ktra nếu tất cả các viên kẹo đã rơi xuống thì set m_isBoardFilled = true;
	if (CheckAllBoardFilled())
	{
		m_isBoardFilled = true;
	}
}

void	GameMgr::CheckMatchThreeInRow()
{
	/// for each row:
	/// n: number of tile is same type
	/// n = 1
	/// if currentTile == previousTile: n += 1
	/// else if (n < 3): n = 1
	/// else if (n >= 3): call func to remove these tiles.
	for (int y = 0; y < NUM_OF_ROW; y++)
	{
		int  numOfSameTile = 1;
		for (int x = 1; x < NUM_OF_COL; x++)
		{
			Candy*		currentTile = m_board[x][y];
			Candy*		previousTile = m_board[x - 1][y];
			if (currentTile->m_type == previousTile->m_type)
			{
				numOfSameTile += 1;
			}
			else if (numOfSameTile < 3)
			{
				numOfSameTile = 1;
			}
			else if (numOfSameTile >= 3)
			{
				/// call func to remove these tiles.
				CCLOG("----- Remove match-%d ----", numOfSameTile);
			}
		}
	}
}

void GameMgr::PrintBoard()
{
	CCLOG("=========================");
	CCLOG("COLUMN = %d, ROW = %d", NUM_OF_COL, NUM_OF_ROW);
	int x = 0, y = 0;
	for (x = 0; x < NUM_OF_COL; x++)
	{
		CCLOG("x = %d", x);
		for (y = 0; y < NUM_OF_ROW; y++)
		{
			CCLOG(" %2d ", m_board[x][y]->m_type);
		}
		CCLOG("-------------------");
	}
	CCLOG("=========================");
}


void GameMgr::CheckMatchVertical(Candy* currCandy, bool isAfterSwap /* false*/)
{
	if (currCandy == nullptr)
	{
		return;
	}
	/// ktra nếu ptu đang xét đã thuộc 1 chain nào đó (trong tất cả các chain dọc) rồi thì bỏ qua.
	Coord		posOfCandy = currCandy->m_coord;
	const int currType = currCandy->m_type;
	const int currScore = currCandy->m_score;
	for (auto it = m_allChainsVertical.begin(); it != m_allChainsVertical.end(); it++)
	{
		auto chain = (*it);
		if (chain.CheckIfInChain(currType, posOfCandy.m_x, posOfCandy.m_y))
		{
			return;
		}
	}

	/// khởi tạo chuỗi ban đầu bằng ptu đang xét.
	Chain	chain(currType, posOfCandy.m_x, posOfCandy.m_y, posOfCandy.m_x, posOfCandy.m_y, true, currScore);

	const int posX = posOfCandy.m_x;
	const int posY = posOfCandy.m_y;

	int y = 0;
	/// duyệt từ ptu == candy lên phía trên.
	for (y = posY + 1; y < NUM_OF_ROW; y++)
	{
		if (m_board[posX][y] != nullptr)
		{
			if (m_board[posX][y]->m_type == currType)
			{
				chain.AddOneNodeToChain(posX, y);
			}
			else
			{
				break;
			}
		}
	}

	/// duyệt từ ptu == candy xuống phía dưới.
	for (y = posY - 1; y >= 0; y--)
	{
		if (m_board[posX][y] != nullptr)
		{
			if (m_board[posX][y]->m_type == currType)
			{
				chain.AddOneNodeToChain(posX, y);
			}
			else
			{
				break;
			}
		}
	}

	/// ktra nếu length của chain >=3 thì add vào m_allChains.
	if (chain.GetLength() >= 3)
	{
		m_allChainsVertical.push_back(chain);
		if (isAfterSwap)
		{
			m_chainVerticalAfterSwap.push_back(chain);
		}
	}
}

void GameMgr::CheckMatchHorizontal(Candy* currCandy, bool isAfterSwap /* false */)
{
	if (currCandy == nullptr)
	{
		return;
	}
	/// ktra nếu ptu đang xét đã thuộc 1 chain nào đó (trong tất cả các chain ngang) rồi thì bỏ qua.
	Coord		posOfCandy = currCandy->m_coord;
	const int		currType = currCandy->m_type;
	const int		currScore = currCandy->m_score;
	for (auto it = m_allChainsHorizontal.begin(); it != m_allChainsHorizontal.end(); it++)
	{
		auto chain = (*it);
		if (chain.CheckIfInChain(currType, posOfCandy.m_x, posOfCandy.m_y))
		{
			return;
		}
	}

	/// khởi tạo chuỗi ban đầu bằng ptu đang xét.	
	Chain	chain(currType, posOfCandy.m_x, posOfCandy.m_y, posOfCandy.m_x, posOfCandy.m_y, false, currScore);

	const int posX = posOfCandy.m_x;
	const int posY = posOfCandy.m_y;

	int x = 0;
	/// duyệt từ ptu == candy sang bên phải
	for (x = posX + 1; x < NUM_OF_COL; x++)
	{
		if (m_board[x][posY] != nullptr)
		{
			if (m_board[x][posY]->m_type == currType)
			{
				chain.AddOneNodeToChain(x, posY);
			}
			else
			{
				break;
			}
		}
	}

	/// duyệt từ ptu == candy sang bên trái
	for (x = posX - 1; x >= 0; x--)
	{
		if (m_board[x][posY] != nullptr)
		{
			if (m_board[x][posY]->m_type == currType)
			{
				chain.AddOneNodeToChain(x, posY);
			}
			else
			{
				break;
			}
		}
	}

	/// ktra nếu length của chain >=3 thì add vào m_allChains.
	if (chain.GetLength() >= 3)
	{
		m_allChainsHorizontal.push_back(chain);
		if (isAfterSwap)
		{
			m_chainHorizontalAfterSwap.push_back(chain);
		}
	}
}

void GameMgr::CheckAllMatch3()
{
	if (m_isBoardFilled)
	{
		CCLOG("--- Checking all match 3 ...");
		for (int x = 0; x < NUM_OF_COL; x++)
		{
			for (int y = 0; y < NUM_OF_ROW; y++)
			{
				CheckMatchHorizontal(m_board[x][y]);
				CheckMatchVertical(m_board[x][y]);
			}
		}
	}
}

bool	GameMgr::CheckMatch3AfterSwap()
{
	/*
	/	return true nếu tại 2 tile vừa swap có match-3, ngược lại false.
	*/
	CheckMatchHorizontal(m_board[m_firstPos.m_x][m_firstPos.m_y], true);
	CheckMatchVertical(m_board[m_firstPos.m_x][m_firstPos.m_y], true);

	CheckMatchHorizontal(m_board[m_secondPos.m_x][m_secondPos.m_y], true);
	CheckMatchVertical(m_board[m_secondPos.m_x][m_secondPos.m_y], true);
	if (GetNumOfChainAfterSwap() > 0)
	{
		return true;
	}
	return false;
}

bool GameMgr::IsValidSwapMan()
{
	// check if these tiles are same row.
	if (m_firstPos.m_y == m_secondPos.m_y)
	{
		if (m_firstPos.m_x == (m_secondPos.m_x + 1) || (m_firstPos.m_x + 1) == m_secondPos.m_x)
		{
			return true;
		}
	}
	// check if these tiles are same column.
	else if (m_firstPos.m_x == m_secondPos.m_x)
	{
		if (m_firstPos.m_y == (m_secondPos.m_y + 1) || (m_firstPos.m_y + 1) == m_secondPos.m_y)
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

void GameMgr::PrintAllMatch3()
{
	if (m_allChainsVertical.size() > 0)
	{
		CCLOG("--- giap: Tong so chain vertical: %d ", m_allChainsVertical.size());
		auto it = m_allChainsVertical.begin();
		for (; it != m_allChainsVertical.end(); it++)
		{
			(*it).PrintChain();
		}
	}
	else
	{
		CCLOG("--- giap: Ko co chain Vertical nao ! ");
	}

	if (m_allChainsHorizontal.size() > 0)
	{
		CCLOG("--- giap: Tong so chain horizontal: %d ", m_allChainsHorizontal.size());
		auto it = m_allChainsHorizontal.begin();
		for (; it != m_allChainsHorizontal.end(); it++)
		{
			(*it).PrintChain();
		}
	}
	else
	{
		CCLOG("--- giap: Ko co chain Horizontal nao ! ");
	}
}

void GameMgr::FalldownAllMan()
{
	if (!m_isBoardFilled && !m_isAllFalling)
	{

		m_isAllFalling = true;
		for (int x = 0; x < NUM_OF_COL; x++)
		{
			/*
			* lowestNullCell: ô trống thấp nhất trong cột x,
			* lowestCandy: viên kẹo thấp nhất trong cột x mà trên 1 ô trống.
			* for (lowestCandy: các viên kẹo còn lại)
			* {

			* }
			*/
			// tìm ô null thấp nhất (có y nhỏ nhất)
			int  nullCellY = GetLowestYNull(x);
			// tìm y của cái kẹo thấp nhất.
			int candyY = GetLowestYCandy(x);
			for (; candyY < NUM_OF_ROW; candyY++)
			{
				if (m_board[x][candyY])
				{
					// animation fall down
					m_board[x][candyY]->FallDownTo(x, nullCellY);
					// di chuyển cả con trỏ
					m_board[x][nullCellY] = m_board[x][candyY];
					m_board[x][nullCellY]->m_coord = Coord(x, nullCellY);
					m_board[x][candyY] = nullptr;
					nullCellY++;
				}
			}

		}
	}
}

void	GameMgr::ReFillBoard()
{
	if (!m_isBoardFilled)
	{
		m_isBoardFilled = false;
		CCLOG("--- Refilling board...");
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::srand(seed);
		int random = 0;

		for (int x = 0; x < NUM_OF_COL; x++)
		{
			for (int y = 0; y < NUM_OF_ROW; y++)
			{
				if (!m_board[x][y])
				{
					random = RAND_MIN_RANGE + std::rand() % (RAND_MAX_RANGE - RAND_MIN_RANGE + 1);
					if (random <= 6) // 1 - 6 ~ 35%
					{
						m_board[x][y] = Candy::createCandyWithFileName("candy/type_one.png");
						m_board[x][y]->m_type = TYPE_ONE;
						m_board[x][y]->m_score = SCORE_ONE;
					}
					else if (random <= 10) // 7 - 10 ~ 20%
					{
						m_board[x][y] = Candy::createCandyWithFileName("candy/type_two.png");
						m_board[x][y]->m_type = TYPE_TWO;
						m_board[x][y]->m_score = SCORE_TWO;
					}
					else if (random <= 13) // 11 - 13 ~ 15%
					{
						m_board[x][y] = Candy::createCandyWithFileName("candy/type_three.png");
						m_board[x][y]->m_type = TYPE_THREE;
						m_board[x][y]->m_score = SCORE_THREE;
					}
					else if (random <= 15) // 14 - 15 ~ 10%
					{
						m_board[x][y] = Candy::createCandyWithFileName("candy/type_four.png");
						m_board[x][y]->m_type = TYPE_FOUR;
						m_board[x][y]->m_score = SCORE_FOUR;
					}
					else // 17 - 20 ~ 20%
					{
						m_board[x][y] = Candy::createCandyWithFileName("candy/type_five.png");
						m_board[x][y]->m_type = TYPE_FIVE;
						m_board[x][y]->m_score = SCORE_FIVE;
					}
					m_board[x][y]->setScale(SCALE_OF_TILE);
					m_board[x][y]->m_coord = Coord(x, y);
					m_board[x][y]->setPosition(Utils::GetPositionInWorldMan(Coord(x, y)));
					m_layer->addChild(m_board[x][y], Z_INDEX_CANDY);
					//m_board[x][y]->FallDownTo(x, y);
					CCLOG("Refill (%d,%d) type = %d ", x, y, m_board[x][y]->m_type);
				}
			}
		}
	}

}

void	GameMgr::RemoveAllMatch3()
{
	m_isBoardFilled = true;
	if (m_allChainsHorizontal.size() > 0)
	{
		auto it = m_allChainsHorizontal.begin();
		auto endChain = m_allChainsHorizontal.end();
		
		for (; it != endChain; it++)
		{
			const int xBegin = (*it).m_firstX;
			const int xEnd = (*it).m_lastX;
			const int y = (*it).m_firstY;
			(*it).PrintClearChain();
			for (int x = xBegin; x <= xEnd; x++)
			{
				RemoveTile(x, y);
			}
		}
	}

	if (m_allChainsVertical.size() > 0)
	{
		auto it = m_allChainsVertical.begin();
		auto endChain = m_allChainsVertical.end();

		for (; it != endChain; it++)
		{
			const int yBegin = (*it).m_firstY;
			const int yEnd = (*it).m_lastY;
			const int x = (*it).m_firstX;
			(*it).PrintClearChain();
			for (int y = yBegin; y <= yEnd; y++)
			{
				RemoveTile(x, y);
			}
		}
	}
	m_isBoardFilled = false;
}



void	GameMgr::CheckAllSprite(Vec2 &p)
{
	for (int x = 0; x < NUM_OF_COL; x++)
	{
		for (int y = 0; y < NUM_OF_ROW; y++)
		{
			if (m_board[x][y] && m_board[x][y]->IsSelected(p))
			{
				if (m_firstPos == INIT_COORD)
				{
					m_firstPos = Coord(x, y);
#if DEBUGGABLE
					CCLOG("m_first dc chon %d;%d", x, y);
#endif // DEBUGGABLE
#if ENABLE_ANIMATION
					m_board[x][y]->SelectAnimation();
#endif

				}
				else
				{
					m_secondPos = Coord(x, y);
#if DEBUGGABLE
					CCLOG("m_second dc chon %d;%d", x, y);
#endif // DEBUGGABLE
				}
				return;
			}
		}
	}
}

bool		GameMgr::IsValidSwap()
{
	/*
	/ chỉ cho phép swap 2 tile cạnh nhau theo chiều ngang hoặc dọc.
	/ return true nếu thỏa mãn đk swap, ngược lại false.
	*/

	// check if these tiles are same row.
	if (m_firstPos.m_y == m_secondPos.m_y)
	{
		if (m_firstPos.m_x == (m_secondPos.m_x + 1) || (m_firstPos.m_x + 1) == m_secondPos.m_x)
		{
			return true;
		}
	}
	// check if these tiles are same column.
	else if (m_firstPos.m_x == m_secondPos.m_x)
	{
		if (m_firstPos.m_y == (m_secondPos.m_y + 1) || (m_firstPos.m_y + 1) == m_secondPos.m_y)
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

void GameMgr::SetupLabel(cocos2d::Layer * layer)
{
	m_layer = layer;

	m_labelScore = Label::createWithTTF(SCORE_LB, FONT_LABEL_PATH, FONT_SIZE);
	m_labelScore->setPosition(Vec2(600, 400));
	int halfWidthLbScore = m_labelScore->getBoundingBox().size.width / 2;
	int halfHeightLbScore = m_labelScore->getBoundingBox().size.height / 2;

	m_scoreLb = Label::createWithTTF(std::to_string(m_totalScore), FONT_LABEL_PATH, FONT_SIZE);
	m_scoreLb->setPosition(Vec2(m_labelScore->getPositionX() + OFFSET_LABEL + halfWidthLbScore, 400));

	m_labelTimer = Label::createWithTTF(TIMER_LB, FONT_LABEL_PATH, FONT_SIZE);
	m_labelTimer->setPosition(Vec2(m_labelScore->getPositionX(), m_labelScore->getPositionY() - OFFSET_LABEL - halfHeightLbScore));
	int halfWidthLbTimer = m_labelTimer->getBoundingBox().size.width / 2;

	m_timerLb = Label::createWithTTF(std::to_string(int(m_timer)), FONT_LABEL_PATH, FONT_SIZE);
	m_timerLb->setPosition(Vec2(m_labelTimer->getPositionX() + OFFSET_LABEL + halfWidthLbTimer, m_labelTimer->getPositionY() ));

	m_layer->addChild(m_labelScore, Z_INDEX_LABEL);
	m_layer->addChild(m_scoreLb, Z_INDEX_LABEL);
	m_layer->addChild(m_labelTimer, Z_INDEX_LABEL);
	m_layer->addChild(m_timerLb, Z_INDEX_LABEL);
}

int GameMgr::CalculateScore()
{
	int score = 0;
	// tinh diem cho cac chain vertical
	if (m_allChainsVertical.size() > 0)
	{
		for (auto it = m_allChainsVertical.begin(); it != m_allChainsVertical.end(); it++)
		{
			score += (*it).GetScores();
		}
	}

	// tinh diem cho cac chain horizontal
	if (m_allChainsHorizontal.size() > 0)
	{
		for (auto it = m_allChainsHorizontal.begin(); it != m_allChainsHorizontal.end(); it++)
		{
			score += (*it).GetScores();
		}
	}
	return score;
}

void	GameMgr::UpdateScore()
{
	
	if (m_currScore > 0)
	{
		CCLOG("Score up !");
		m_totalScore += m_currScore;
		m_currScore = 0;
		m_scoreLb->setString(std::to_string(m_totalScore));
	}
	
}

void GameMgr::UpdateTimer(float dt)
{
	m_timer -= dt;
	m_timerLb->setString(std::to_string(int(m_timer)));
}

int		GameMgr::GetNumOfAllChains()
{
	return m_allChainsVertical.size() + m_allChainsHorizontal.size();
}

int		GameMgr::GetNumOfChainAfterSwap()
{
	return m_chainHorizontalAfterSwap.size() + m_chainVerticalAfterSwap.size();
}

bool GameMgr::CheckAllFalldownDone()
{
	for (int x = 0; x < NUM_OF_COL; x++)
	{
		for (int y = 0; y < NUM_OF_ROW; y++)
		{
			if (m_board[x][y] && m_board[x][y]->m_isFalling == false)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool GameMgr::CheckAllBoardFilled()
{
	int		counter = 0;
	for (int x = 0; x < NUM_OF_COL; x++)
	{
		for (int y = 0; y < NUM_OF_ROW; y++)
		{
			if (m_board[x][y] && m_board[x][y]->m_isFalling == false)
			{
				counter += 1;
			}
			else
			{
				break;
			}
		}
	}
	return counter == (NUM_OF_COL*NUM_OF_ROW);
}

// return y của ô null đầu tiên tìm thấy
int GameMgr::GetLowestYNull(int column)
{
	for (int y = 0; y < NUM_OF_ROW; y++)
	{
		if (m_board[column][y] == nullptr)
		{
			return y;
		}
	}
	return -1;
}

// return y của cái kẹo đầu tiên bên trên ô null.
int GameMgr::GetLowestYCandy(int column)
{
	int nullCellY = 0;
	for (int y = 0; y < NUM_OF_ROW; y++)
	{
		if (m_board[column][y] == nullptr)
		{
			nullCellY = y;
		}
		else
		{
			break;
		}
	}
	return nullCellY + 1;
}


void			GameMgr::SwapTiles()
{
	m_isSwaping = true; // disable touch from player
	CCLOG("--- giap: Swaping -----");
	// save coord
	auto coordA = m_board[m_firstPos.m_x][m_firstPos.m_y]->m_coord;
	auto coordB = m_board[m_secondPos.m_x][m_secondPos.m_y]->m_coord;

	// swap 2 pointer
	Candy*		temp = m_board[m_firstPos.m_x][m_firstPos.m_y];
	m_board[m_firstPos.m_x][m_firstPos.m_y] = m_board[m_secondPos.m_x][m_secondPos.m_y];
	m_board[m_secondPos.m_x][m_secondPos.m_y] = temp;

	// cập nhật lại tọa độ (m_coord) của mỗi pointer,
	// vì lúc này candyA sẽ mang nội dung của candyB,
	// nên phải set lại tọa độ cũ của mỗi sprite.
	m_board[m_firstPos.m_x][m_firstPos.m_y]->m_coord = coordA;
	m_board[m_secondPos.m_x][m_secondPos.m_y]->m_coord = coordB;
	// set lại position
	m_board[m_firstPos.m_x][m_firstPos.m_y]->setPosition(Utils::GetPositionInWorld(coordA));
	m_board[m_secondPos.m_x][m_secondPos.m_y]->setPosition(Utils::GetPositionInWorld(coordB));
	// lưu lại 2 vị trí vừa swap để ktra sau.
	m_firstPosAfterSwap = coordA;
	m_secondPosAfterSwap = coordB;
}

void GameMgr::SwapTilesMan()
{
	m_isSwaping = true; // disable touch from player
	CCLOG("--- giap: Swaping -----");
	// save coord
	auto coordA = m_board[m_firstPos.m_x][m_firstPos.m_y]->m_coord;
	auto coordB = m_board[m_secondPos.m_x][m_secondPos.m_y]->m_coord;

	// swap 2 pointer
	Candy*		temp = m_board[m_firstPos.m_x][m_firstPos.m_y];
	m_board[m_firstPos.m_x][m_firstPos.m_y] = m_board[m_secondPos.m_x][m_secondPos.m_y];
	m_board[m_secondPos.m_x][m_secondPos.m_y] = temp;

	// cập nhật lại tọa độ (m_coord) của mỗi pointer,
	// vì lúc này candyA sẽ mang nội dung của candyB,
	// nên phải set lại tọa độ cũ của mỗi sprite.
	m_board[m_firstPos.m_x][m_firstPos.m_y]->m_coord = coordA;
	m_board[m_secondPos.m_x][m_secondPos.m_y]->m_coord = coordB;
	// set lại position
	m_board[m_firstPos.m_x][m_firstPos.m_y]->setPosition(Utils::GetPositionInWorldMan(coordA));
	m_board[m_secondPos.m_x][m_secondPos.m_y]->setPosition(Utils::GetPositionInWorldMan(coordB));
	// lưu lại 2 vị trí vừa swap để ktra sau.
	m_firstPosAfterSwap = coordA;
	m_secondPosAfterSwap = coordB;
}

void			GameMgr::UndoSwapTiles()
{
	m_isSwaping = true; // disable touch from player
	CCLOG("--- giap: Undo Swaping -----");

}
