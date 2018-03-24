#include "Chain.h"


Chain::Chain(int type, int firstX, int firstY, int lastX, int lastY, bool isVertical, int score)
{
	m_typeOfChain = type;

	m_firstX = firstX;
	m_firstY = firstY;

	m_lastX = lastX;
	m_lastY = lastY;

	m_length = 1;
	m_score = score;
	m_isVertical = isVertical;
}

Chain::~Chain()
{
}

void Chain::AddOneNodeToChain(int x, int y)
{
	FixChain();
	if (m_isVertical)
	{
		if (y < m_firstY)
		{
			// them ptu vao dau chain
			m_firstY = y;
		}
		else if (y > m_lastY)
		{
			// them ptu vao cuoi chain
			m_lastY = y;
		}
	}
	else
	{
		// them ptu sang ben phai
		if (x < m_firstX)
		{
			// them ptu vao phia ben trai
			m_firstX = x;
		}
		else if (x > m_lastX)
		{
			// them ptu vao phai ben phai
			m_lastX = x;
		}
	}
	m_length += 1;
}

void Chain::FixChain()
{
	// ham dam bao toa do cua chain luon tu first -> last
	if (m_isVertical)
	{
		// ptu dau tien phai o ben duoi
		if (m_firstY > m_lastY)
		{
			int temp = m_firstY;
			m_firstY = m_lastY;
			m_lastY = temp;
		}
	}
	else
	{
		// ptu dau tien phai o ben trai
		if (m_firstX > m_lastX)
		{
			int temp = m_firstX;
			m_firstX = m_lastX;
			m_lastX = temp;
		}
	}
}

bool Chain::CheckIfInChain(int type, int x, int y)
{
	if (m_typeOfChain != type)
	{
		return false;
	}

	if (m_isVertical)
	{
		if (x == m_firstX)
		{
			if ((m_firstY <= y) && (y <= m_lastY))
			{
				return true;
			}
			return false;
		}
		return false;
	}
	else
	{
		if (y == m_firstY)
		{
			if ((m_firstX <= x) && (x <= m_lastX))
			{
				return true;
			}
			return false;
		}
		return false;
	}
}

int Chain::GetLength() const
{
	return m_length;
}

void Chain::PrintChain()
{
	CCLOG("--- giap: first(%d, %d) - last(%d, %d) type = %d", m_firstX, m_firstY, m_lastX, m_lastY, m_typeOfChain);
}

void Chain::PrintClearChain()
{
	if (m_isVertical)
	{
		CCLOG("Clear chain Vertical first(%d,%d) last(%d,%d) type = %d ", m_firstX, m_firstY, m_lastX, m_lastY, m_typeOfChain);
	}
	else
	{
		CCLOG("Clear chain Horizontal first(%d,%d) last(%d,%d) type = %d ", m_firstX, m_firstY, m_lastX, m_lastY, m_typeOfChain);
	}
}

int Chain::GetScores()
{
	return m_length * m_score;
}
