#include "CellMatrix.h"

namespace Automata
{
	CellMatrix::CellMatrix() {}

	void CellMatrix::InitMatrix(Vector2 dimensions)
	{
		// Save Matrix Dimensions
		m_Dimensions = dimensions;

		// Initialize Empty Cell Matrix
		for(unsigned int column = 0; column < dimensions.x; column++)
		{
			std::vector<Cell> colCells;
			for(unsigned int row = 0;  row < dimensions.y; row++)
			{
				colCells.push_back(Cell{Vector2(column * CELL_SIZE.x,  row * CELL_SIZE.y)});
			}
			m_Cells.push_back(colCells);
		}
	}

	void CellMatrix::Update(float deltaTime)
	{
		// Update Each Active Element
		for(unsigned int i = 0; i < m_Elements.size(); i++)
		{
			m_Elements[i]->Step();
		}
	}


    void CellMatrix::DrawElements(SpriteRenderer* renderer)
	{
		for(unsigned int i = 0; i < m_Elements.size(); i++)
		{
			renderer->DrawSprite(m_Elements[i]->m_Position, m_Elements[i]->m_Size, m_Elements[i]->m_Color);
		}
	}
	CellMatrix::~CellMatrix()
	{
	}
	
}