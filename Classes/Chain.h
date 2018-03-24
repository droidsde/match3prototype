#pragma once

#include "defined.h"
#include "Candy.h"


class Chain {

public:
	int				m_firstX, m_firstY;
	int				m_lastX, m_lastY;
	int				m_length;
	bool			m_isVertical;
	int				m_typeOfChain;
	int				m_score;
	/// mặc định là chain theo chiều dọc.
	Chain(int type = 0, int firstX = -1, int firstY = -1, int lastX = -1, int lastY = -1, bool isVertical = true, int score = 0);
	~Chain();

	/// thêm 1 phần tử vào chuỗi nếu như cùng kiểu vs chuỗi.
	void		AddOneNodeToChain(int x, int y);

	/// đảm bảo ptu đầu chain luôn có tọa độ nhỏ hơn pt cuối chain.
	void		FixChain();

	bool		CheckIfInChain(int  type, int x, int y);
	
	void		PrintChain();
	void		PrintClearChain();
	int			GetLength() const;
	int			GetScores();
};