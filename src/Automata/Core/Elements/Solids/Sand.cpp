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
}