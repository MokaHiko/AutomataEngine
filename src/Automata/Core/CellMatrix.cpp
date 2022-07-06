#include "CellMatrix.h"

namespace Automata
{
	CellMatrix::CellMatrix() {}
    Matrix4* m_ElementsPositions;

	void CellMatrix::InitMatrix(Vector2 dimensions)
	{
		// Save Matrix Dimensions
		m_Dimensions = dimensions;

		// Initialize Positions Array To Send To Renderer
		m_ElementsPositions = new Matrix4[dimensions.x * dimensions.y];

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
		Matrix4 model(1.0f);
		for(unsigned int i = 0; i < m_Elements.size(); i++)
		{
			m_Elements[i]->Step();
			m_ElementsPositions[i] = MatrixTranslate(model, Vector3(m_Elements[i]->m_Position, 0.0));
		}
	}


    void CellMatrix::DrawElements(SpriteRenderer* renderer)
	{
		renderer->DrawSprite(m_ElementsPositions, Vector2(1.0f), Vector3(0.4, 0.1, 0.2), m_Elements.size());
	}
	CellMatrix::~CellMatrix()
	{
		delete m_ElementsPositions;
	}
	
}