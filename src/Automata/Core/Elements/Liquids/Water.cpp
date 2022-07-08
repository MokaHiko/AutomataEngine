#include "Water.h"

namespace Automata
{
	Water::Water(std::vector<std::vector<Cell>>& cells, Vector2 position)
		: Element(cells, position, Vector2(1.0f), Vector3(0.184, 0.854, 0.776))
	{

	}

	Water::~Water()
	{
	}

	void Water::Step()
	{
		m_isUpdated = false;

		Vector2 desiredCoordinate = Vector2(m_Position.x, m_Position.y);

		// element rules
		desiredCoordinate = Gravity(desiredCoordinate);
		desiredCoordinate =  Roll(desiredCoordinate);
		desiredCoordinate = Slide(desiredCoordinate);

		Cell& nextCell = m_MatrixCells[desiredCoordinate.x][desiredCoordinate.y];
		if(!nextCell.m_isEmpty)
			return;

		Cell& currentCell = m_MatrixCells[m_Position.x][m_Position.y];
		currentCell.m_isEmpty = true;
		nextCell.m_isEmpty = false;

		m_Position = desiredCoordinate;
	}


	Vector2 Water::Slide(Vector2 desiredCoordinate)
	{
		if(m_isUpdated) return desiredCoordinate;

		Vector2 Left(m_Position.x - 1, m_Position.y);
		if(Left.x > 0 && Left.y < m_MatrixCells[0].size())
		{
			Cell& LeftCell = m_MatrixCells[Left.x][Left.y];
			if (LeftCell.m_isEmpty)
			{
				m_isUpdated = true;
				return Left;
			}
		}

		Vector2 Right(m_Position.x + 1, m_Position.y + 1);
		if(Right.x > 0 && Right.y < m_MatrixCells[0].size())
		{
			Cell& RightCell = m_MatrixCells[Right.x][Right.y];
			if (RightCell.m_isEmpty)
			{
				m_isUpdated = true;
				return Right;
			}
		}

		return desiredCoordinate;
	}
}