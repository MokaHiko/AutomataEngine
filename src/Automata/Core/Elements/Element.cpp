#include "Element.h"

namespace Automata
{
	Element::~Element() {}

	Element::Element(std::vector<std::vector<Cell>>& cells, Vector2 position, Vector2 size, Vector3 color)
		:m_MatrixCells(cells),m_Position(position), m_Size(size), m_Color(color) {}
	
	Vector2 Element::Gravity(Vector2 desiredCoordinate)
	{
		if(m_isUpdated) return desiredCoordinate;

		Vector2 gravityStep = desiredCoordinate + Vector2(0, 1);

		// check if out of bounds
		if (gravityStep.y > m_MatrixCells[0].size() - 1)
			return desiredCoordinate;

		// check if on top of another cell
		Cell& nextCell = m_MatrixCells[gravityStep.x][gravityStep.y];
		if (!nextCell.m_isEmpty)
			return desiredCoordinate;

		m_isUpdated = true;
		return gravityStep;
	}

	Vector2 Element::Roll(Vector2 desiredCoordinate)
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