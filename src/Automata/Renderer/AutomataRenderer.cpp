#include "AutomataRenderer.h"

namespace Automata
{
	AutomataRenderer::AutomataRenderer(Shader& shader, Vector2 resolution)
		:m_Shader(shader), m_Resolution(resolution), m_currentInstance(0), m_instanceCount(0)
	{
		InitRenderData();
	}

	void AutomataRenderer::DrawSprites()
	{
		m_Shader.use();

		glBindVertexArray(VAO);
		glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(6), GL_UNSIGNED_INT, indices, m_instanceCount);
		glBindVertexArray(0);
	}

	void AutomataRenderer::AddInstance(const Vector2& coordinates, const Vector3& color)
	{
		glBindVertexArray(VAO);

		// Add Position
		glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vector2) * m_currentInstance, sizeof(Vector2),  &coordinates);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);

		// Add Color
		glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_currentInstance++, sizeof(Vector3), &color);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);

		m_instanceCount++;
	}
	
	void AutomataRenderer::RemoveInstance(unsigned int index)
	{
		glBindVertexArray(VAO);

		// Copy Data From Last Position to index of deletion
		glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
		glCopyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER, 
		(m_instanceCount - 1) * sizeof(Vector2),  // where to get data
		index * sizeof(Vector2), // where we will place the data
		sizeof(Vector2)); // size of data we are replacing
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
		glCopyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER, 
		(m_instanceCount - 1) * sizeof(Vector3),  // where to get data
		index * sizeof(Vector3), // where we will place the data
		sizeof(Vector3)); // size of data we are replacing
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);

		m_currentInstance--;
		m_instanceCount--;
	}

	void AutomataRenderer::UpdateInstance(unsigned int instanceID, const Vector2& coordinates, const Vector3& color)
	{
		glBindVertexArray(VAO);

		// update position
		glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vector2) * instanceID, sizeof(Vector2),  &coordinates);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);

		// update colors
		glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vector3) * instanceID, sizeof(Vector3), &color);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
	}

	AutomataRenderer::~AutomataRenderer()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &positionsBuffer);
		glDeleteBuffers(1, &colorsBuffer);
	}

	void AutomataRenderer::InitRenderData()
	{
		// configure VAO/VBO
		unsigned int VBO, EBO;

		float vertices[] = {
		// pos
		0.0f, 1.0f,
		1.0f, 0.0f, 
		0.0f, 0.0f, 
		1.0f, 1.0f,
		};

		// Initialize Screen Matrix
		unsigned int amount = m_Resolution.x * m_Resolution.y;
        Vector2* coordinates = new Vector2[amount];
        Vector3* colors = new Vector3[amount];

		unsigned int ctr = 0;
		for(unsigned int column = 0; column < m_Resolution.x; column++)
		{
			for(unsigned int row = 0;  row < m_Resolution.y; row++)
			{
				Vector2 coordinate(column, row);
				coordinates[ctr] = coordinate;
				colors[ctr++] = Vector3(1.0f);
			}
		}

		glGenBuffers(1, &colorsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * amount, colors, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &positionsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * amount, coordinates, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		// Coordinates represented as 2 16 bit integer values
		glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);

		// Colors represented as 3 16 bit integer calues
		glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
		
		// only update buffer data every instance 
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		// send 2D projection
		 m_Shader.use();
		 glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(m_Resolution.x), static_cast<float>(m_Resolution.y), 0.0f, -1.0f, 1.0f);
		 m_Shader.setMat4("projection", proj);
		 m_Shader.unuse();

		 // clean up
		 delete coordinates;
		 delete colors;
	}
}