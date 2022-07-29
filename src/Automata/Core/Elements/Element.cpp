#include "Element.h"
namespace Automata
{
	Element::~Element() {}

	Element::Element(unsigned int elementID, std::vector<std::vector<Cell>>& cells, Vector2 position, Vector2 size, Vector3 color)
		:m_elementID(elementID), m_MatrixCells(cells),m_Position(position), m_Size(size), m_Color(color){}
	
	Vector2 Element::Gravity(Vector2 desiredCoordinate)
	{
		if(m_isUpdated) return desiredCoordinate;
		
		Vector2 gravityStep = desiredCoordinate;
		Vector2 pathStep;  // step along the falling path 

		m_cyclesFalling += 1; 
		for(unsigned int i = 0; i < m_cyclesFalling ; i++) // check each cell along gravity path
		{
			pathStep = gravityStep + Vector2(0, 1); // current acceleration

			// check if out of bounds y or grounded
			if (pathStep.y > m_MatrixCells[0].size() - 1)
			{
				m_cyclesFalling = 0;
				break;
			}

			// check if path collides with another cell
			Cell& nextCell = m_MatrixCells[pathStep.x][pathStep.y];
			if (!nextCell.IsEmpty())
			{
				// only go dormant if cell on bottom is also dormant
				if(m_cyclesFalling > 1 && nextCell.m_Element->m_dormant)
					m_dormant = true;
				m_cyclesFalling = 0;
				break;
			}

			// proceed if otherwise 
			gravityStep = pathStep;
		}

		// go dormant if grounded
		if(gravityStep.y >= m_MatrixCells[0].size())
		{
			m_cyclesAlive = 0;
			m_dormant = true;
			
			EndUpdate(true);
			return gravityStep;
		}

		// check desired cell is empty/available
		Cell& nextCell = m_MatrixCells[gravityStep.x][gravityStep.y];
		if (!nextCell.IsEmpty())
		{
			m_cyclesFalling = 0;
			return desiredCoordinate;
		}

		EndUpdate(true);
		return gravityStep;
	}

	Vector2 Element::Roll(Vector2 desiredCoordinate)
	{
		if(m_isUpdated) return desiredCoordinate;
		if(m_Position.y >= m_MatrixCells[0].size() - 1) return desiredCoordinate; // check if in boundary

		// Check if Bottom Left is available
		Vector2 BottomLeft(m_Position.x - 1, m_Position.y + 1);
		if(BottomLeft.x > 0)
		{
			Cell& bottomLeftCell = m_MatrixCells[BottomLeft.x][BottomLeft.y];
			if (bottomLeftCell.IsEmpty())
			{
				EndUpdate(true);
				return BottomLeft;
			}
		}

		// Check if Bottom Right is available
		Vector2 BottomRight(m_Position.x + 1, m_Position.y + 1);
		if(BottomRight.x < m_MatrixCells.size())
		{
			Cell& bottomRightCell = m_MatrixCells[BottomRight.x][BottomRight.y];
			if (bottomRightCell.IsEmpty())
			{
				EndUpdate(true);
				return BottomRight;
			}
		}

		EndUpdate(false);
		return desiredCoordinate;
	}

}