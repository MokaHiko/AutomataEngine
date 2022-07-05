#include "Sand.h"

namespace Automata
{
	Sand::Sand(std::vector<std::vector<Cell>>& cells, Vector2 position)
		: Element(cells, position, Vector2(1.0f), Vector3(0.776, 0.737, 0.384))
	{

	}

	Sand::~Sand()
	{
		
	}

	void Sand::Step()
	{
		m_isUpdated = false;

		Vector2 desiredCoordinate = Vector2(m_Position.x, m_Position.y);

		// element rules
		desiredCoordinate = Gravity(desiredCoordinate);
		desiredCoordinate =  Roll(desiredCoordinate);

		Cell& nextCell = m_MatrixCells[desiredCoordinate.x][desiredCoordinate.y];
		if(!nextCell.m_isEmpty)
			return;

		Cell& currentCell = m_MatrixCells[m_Position.x][m_Position.y];
		currentCell.m_isEmpty = true;
		nextCell.m_isEmpty = false;

		m_Position = desiredCoordinate;
	}

	Vector2 Sand::Gravity(Vector2 desiredCoordinate)
	{
		if(m_isUpdated) return desiredCoordinate;

		Vector2 gravityStep = desiredCoordinate + Vector2(0, 1);

		// check if out of bounds
		if (gravityStep.y > m_MatrixCells[0].size() - 1)
		{
			m_isUpdated = true;
			return desiredCoordinate;
		}

		// check if on top of another cell
		Cell& nextCell = m_MatrixCells[gravityStep.x][gravityStep.y];
		if (!nextCell.m_isEmpty)
			return desiredCoordinate;

		m_isUpdated = true;
		return gravityStep;
	}

	Vector2 Sand::Roll(Vector2 desiredCoordinate)
	{
		if(m_isUpdated) return desiredCoordinate;

		Vector2 BottomLeft(m_Position.x - 1, m_Position.y + 1);
		if(BottomLeft.x > 0 && BottomLeft.y < m_MatrixCells[0].size())
		{
			Cell& bottomLeftCell = m_MatrixCells[BottomLeft.x][BottomLeft.y];
			if (bottomLeftCell.m_isEmpty)
			{
				m_isUpdated = true;
				return BottomLeft;
			}
		}

		Vector2 BottomRight(m_Position.x + 1, m_Position.y + 1);
		if(BottomRight.x > 0 && BottomRight.y < m_MatrixCells[0].size())
		{
			Cell& bottomRightCell = m_MatrixCells[BottomRight.x][BottomRight.y];
			if (bottomRightCell.m_isEmpty)
			{
				m_isUpdated = true;
				return BottomRight;
			}
		}

		return desiredCoordinate;
	}
}