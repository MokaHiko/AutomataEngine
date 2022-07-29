#include "Sand.h"

namespace Automata
{
	Sand::Sand(unsigned int elementID,std::vector<std::vector<Cell>>& cells, Vector2 position)
		: Element(elementID, cells, position, Vector2(1.0f), Vector3(0.776, 0.737, 0.384))
	{
	}

	Sand::~Sand()
	{
	}

	void Sand::Step()
	{
		if(m_dormant) return; 
		Vector2 prevCoordinate = m_Position;

		m_isUpdated = false;
		Vector2 desiredCoordinate = m_Position;

		// element rules
		desiredCoordinate = Gravity(desiredCoordinate);
		desiredCoordinate =  Roll(desiredCoordinate);

		// change cell pointer of effected cells
		Cell& currentCell = m_MatrixCells[prevCoordinate.x][prevCoordinate.y];
		Cell& nextCell = m_MatrixCells[desiredCoordinate.x][desiredCoordinate.y];
		currentCell.m_Element = nullptr;
		nextCell.m_Element = this;

		// reposition for rendering
		m_Position = desiredCoordinate;
	}

}