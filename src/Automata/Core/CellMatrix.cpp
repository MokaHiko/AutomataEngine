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
				colCells.push_back(Cell{Vector2(column * CELL_SIZE.x,  row * CELL_SIZE.y)});
			m_Cells.push_back(colCells);
		}

		// Init Renderer
		automataShader = new Shader("resources/shaders/automata_instanced_vertex.shader", "resources/shaders/automata_instanced_fragment.shader");
		m_Renderer = new AutomataRenderer(*automataShader, Vector2(dimensions.x, dimensions.y));

		// Define Shapes For Brushes
		unsigned int radius = 3;
		DefineCirclePoints(radius);
		DefineSquarePoints(30);
	}

	void CellMatrix::Update(float deltaTime)
	{
		// Update Each Element
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
		// Delete Elements
		for(Element* e : m_Elements)
			delete e;
		
		delete automataShader;
		delete m_Renderer;
	}

	void CellMatrix::DefineCirclePoints(unsigned int radius)
	{
		unsigned int resolution = 2; // by how much do we skip
		int x, y;
		for(int i = 0; i < 360; i += resolution)
		{
			for(int j = 0; j < radius; j++)
			{
				x =   j *  (int)glm::cos(glm::radians((float)i));
				y =   j *  (int)glm::sin(glm::radians((float)i)); // y is reversed in our world
				m_circlePoints.push_back({x, y});
			}
		}

		std::cout << "Defining Circle..." << std::endl;
	}
	
	void CellMatrix::DefineSquarePoints(unsigned int s)
	{
		int halfLength = s / 2;
		for(int i = 0; i < s; i++) 
		{
			for(int j = 0; j < s; j++)
			{
				m_squarePoints.push_back(Vector2(j - halfLength, i - halfLength));  // points ordered from top to bottom
			}
		}

		std::reverse(m_squarePoints.begin(), m_squarePoints.end()); // points ordered bottom to top
		
		std::cout << "Defining Square..." << std::endl;
	}
	
}