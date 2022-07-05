#include "SpriteRenderer.h"

namespace Automata
{
	SpriteRenderer::SpriteRenderer(Shader& shader, Vector2 resolution)
		:m_Shader(shader), m_Resolution(resolution)
	{
		InitRenderData();
	}

	void SpriteRenderer::DrawSprite(Vector2 position, 
									Vector2 size,
									Vector3 color)
	{
		m_Shader.use();

		Matrix4 model = Matrix4(1.0f);
		model = MatrixTranslate(model, Vector3(position, 0.0));
		model = MatrixScale(model, Vector3(size, 1.0));

		m_Shader.setMat4("model", model);
		m_Shader.setVec3("spriteColor", color);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
		glBindVertexArray(0);
	}

	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteVertexArrays(1, &VAO);
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


		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		// 2D projection
		 m_Shader.use();
		 glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(m_Resolution.x), static_cast<float>(m_Resolution.y), 0.0f, -1.0f, 1.0f);
		 m_Shader.setMat4("projection", proj);
		 m_Shader.unuse();
	}
}