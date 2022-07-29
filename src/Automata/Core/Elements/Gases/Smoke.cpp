#include "Smoke.h"
#include "Application.h"


namespace Automata{
	Smoke::Smoke(unsigned int elementID, std::vector<std::vector<Cell>>& cells, Vector2 position)
		: Element(elementID, cells, position, Vector2(1.0f), Vector3(0.92, 0.63, 0.32))
	{
	}

	Smoke::~Smoke()
	{
		
	}

	void Smoke::Die()
	{
		m_dormant = true;
		Application::GetInstance().GetCellMatrix()->RemoveElement(m_Position);
	}
	
	void Smoke::Step()
	{
		if (m_cyclesAlive > 20) 
			Die();
		if(m_dormant) return;
		Vector2 prevCoordinate = m_Position;

		m_isUpdated = false;
		Vector2 desiredCoordinate = m_Position;

		// element rules
		desiredCoordinate = Rise(desiredCoordinate);
		desiredCoordinate = RollUp(desiredCoordinate);
		desiredCoordinate = SlideUp(desiredCoordinate);
		m_Color -= Vector3(0.05);

		// change cell pointer of effected cells
		Cell& currentCell = m_MatrixCells[prevCoordinate.x][prevCoordinate.y];
		Cell& nextCell = m_MatrixCells[desiredCoordinate.x][desiredCoordinate.y];
		currentCell.m_Element = nullptr;
		nextCell.m_Element = this;

		// reposition for rendering
		m_Position = desiredCoordinate;
	}
	
	Vector2 Smoke::Rise(Vector2 desiredCoordinate)
	{
		if(m_isUpdated) return desiredCoordinate;
		
		Vector2 floatStep = desiredCoordinate;
		Vector2 pathStep;  // step along the falling path 

		// begin falling cycle
		m_cyclesRising += 1; 
		for(unsigned int i = 0; i < m_cyclesRising ; i++)
		{
			pathStep = floatStep - Vector2(0, 1); // current acceleration

			// check if out of bounds y or grounded
			if (pathStep.y < 0)
			{
				m_cyclesRising = 0;
				break;
			}

			// check if path collides with another cell
			Cell& nextCell = m_MatrixCells[pathStep.x][pathStep.y];
			if (!nextCell.IsEmpty())
			{
				// only go dormant if cell on top is also dormant
				if(m_cyclesRising > 1 && nextCell.m_Element->m_dormant)
					m_dormant = true;
				m_cyclesRising = 0;
				break;
			}

			// proceed if otherwise 
			floatStep = pathStep;
		}

		// go dormant if at border height
		if(floatStep.y < 0)
		{
			m_dormant = true;
			EndUpdate(true);
			return floatStep;
		}

		// check desired cell is empty/available
		Cell& nextCell = m_MatrixCells[floatStep.x][floatStep.y];
		if (!nextCell.IsEmpty())
		{
			m_cyclesRising= 0;
			return desiredCoordinate;
		}

		EndUpdate(true);
		return floatStep;
	}
	
	Vector2 Smoke::RollUp(Vector2 desiredCoordinate)
	{
		if(m_isUpdated) return desiredCoordinate;
		if(m_Position.y - 1 < 0) return desiredCoordinate; // check if in boundary

		// Check if Top Left is available
		Vector2 TopLeft(m_Position.x - 1, m_Position.y - 1);
		if(TopLeft.x > 0)
		{
			Cell& topLeftCell = m_MatrixCells[TopLeft.x][TopLeft.y];
			if (topLeftCell.IsEmpty())
			{
				EndUpdate(true);
				return TopLeft;
			}
		}

		// Check if Top Right is available
		Vector2 TopRight(m_Position.x + 1, m_Position.y - 1);
		if(TopRight.x < m_MatrixCells.size())
		{
			Cell& topRightCell = m_MatrixCells[TopRight.x][TopRight.y];
			if (topRightCell.IsEmpty())
			{
				EndUpdate(true);
				return TopRight;
			}
		}

		EndUpdate(false);
		return desiredCoordinate;
	}
	
	Vector2 Smoke::SlideUp(Vector2 desiredCoordinate)
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