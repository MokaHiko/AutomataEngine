#include "Water.h"

namespace Automata
{
	Water::Water(unsigned int elementID, std::vector<std::vector<Cell>>& cells, Vector2 position)
		: Element(elementID, cells, position, Vector2(1.0f), Vector3(0.184, 0.854, 0.776))
	{
	}

	Water::~Water()
	{
	}

	void Water::Step()
	{
		if(m_dormant) return; 
		Vector2 prevCoordinate = m_Position;

		m_isUpdated = false;
		Vector2 desiredCoordinate = m_Position;

		// element rules
		desiredCoordinate = Gravity(desiredCoordinate);
		desiredCoordinate = Roll(desiredCoordinate);
		desiredCoordinate =	Slide(desiredCoordinate);

		// change cell pointer of effected cells
		Cell& currentCell = m_MatrixCells[prevCoordinate.x][prevCoordinate.y];
		Cell& nextCell = m_MatrixCells[desiredCoordinate.x][desiredCoordinate.y];
		currentCell.m_Element = nullptr;
		nextCell.m_Element = this;

		// reposition for rendering
		m_Position = desiredCoordinate;
	}


	Vector2 Water::Slide(Vector2 desiredCoordinate)
	{
		if(m_isUpdated) return desiredCoordinate;

		Vector2 Left(m_Position.x - 1, m_Position.y);
		if(Left.x > 0)
		{
			Cell& LeftCell = m_MatrixCells[Left.x][Left.y];
			if (LeftCell.IsEmpty())
			{
				EndUpdate(true);
				return Left;
			}
		}

		Vector2 Right(m_Position.x + 1, m_Position.y);
		if(Right.x < m_MatrixCells.size())
		{
			Cell& RightCell = m_MatrixCells[Right.x][Right.y];
			if (RightCell.IsEmpty())
			{
				EndUpdate(true);
				return Right;
			}
		}

		EndUpdate(false);
		return desiredCoordinate;
	}
}