#include "CellMatrix.h"

namespace Automata
{
	CellMatrix::CellMatrix() {}

    Shader* automataShader; // Main Engine Automata Shader

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

		// Init Renderer
		automataShader = new Shader("resources/shaders/automata_instanced_vertex.shader", "resources/shaders/automata_instanced_fragment.shader");
		m_Renderer = new AutomataRenderer(*automataShader, Vector2(dimensions.x, dimensions.y));
	}

	void CellMatrix::Update(float deltaTime)
	{
		// Update Each Active Element
		for(unsigned int i = 0; i < m_Elements.size(); i++)
		{
			m_Elements[i]->Step();
			if (m_Elements[i]->m_isUpdated)
				m_Renderer->UpdateInstance(i, m_Elements[i]->m_Position, m_Elements[i]->m_Color);
		}
	}

    void CellMatrix::DrawElements()
	{
		m_Renderer->DrawSprites();
	}

	CellMatrix::~CellMatrix()
	{
		delete automataShader;
		delete m_Renderer;
	}
	
}