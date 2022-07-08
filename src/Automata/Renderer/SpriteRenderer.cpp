#include "SpriteRenderer.h"

namespace Automata
{
	SpriteRenderer::SpriteRenderer(Shader& shader, Vector2 resolution)
		:m_Shader(shader), m_Resolution(resolution)
	{
		InitRenderData();
	}

	void SpriteRenderer::DrawSprite(Vector2* coordinates,
									Vector2 size,
									Vector3 color,
									unsigned int n_instances)
	{
		m_Shader.use();
		m_Shader.setVec3("spriteColor", color);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * m_Resolution.x * m_Resolution.y, coordinates, GL_DYNAMIC_DRAW);

		// Coordinates represented as 2 16 bit integer values
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);

		glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(6), GL_UNSIGNED_INT, indices, n_instances);
		glBindVertexArray(0);
	}

	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &positionsBuffer);
	}

	void SpriteRenderer::InitRenderData()
	{
		// configure VAO/VBO
		unsigned int VBO, EBO;
		float vertices[] = {
		// pos		// tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		};

		// Initialize Screen Matrix
		unsigned int amount = m_Resolution.x * m_Resolution.y;
        Vector2* coordinates = new Vector2[amount];
		unsigned int ctr = 0;
		for(unsigned int column = 0; column < m_Resolution.x; column++)
		{
			for(unsigned int row = 0;  row < m_Resolution.y; row++)
			{
				Vector2 coordinate(column, row);
				coordinates[ctr++] = coordinate;
			}
		}

		glGenBuffers(1, &positionsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * amount, coordinates, GL_STATIC_DRAW);
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
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

		// Coordinates represented as 2 16 bit integer values
		glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);

		// only update buffer data every instance 
		glVertexAttribDivisor(1, 1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		// 2D projection
		 m_Shader.use();
		 glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(m_Resolution.x), static_cast<float>(m_Resolution.y), 0.0f, -1.0f, 1.0f);
		 m_Shader.setMat4("projection", proj);
		 m_Shader.unuse();
	}
}