#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#pragma once

#include "Shader.h"
#include "Core.h"

namespace Automata
{
    class SpriteRenderer
    {
    public:
        SpriteRenderer(Shader& shader, Vector2 resolution);
        ~SpriteRenderer();

        void DrawSprite(Matrix4* positionMatrices, 
                        Vector2 size = Vector2(1.0f, 1.0f), 
                        Vector3 color = Vector3(1.0f),
                        unsigned int n_instances = 0);
    private:
        Shader m_Shader;
        unsigned int VAO;
		unsigned int positionsBuffer;

        Vector2 m_Resolution;
        void InitRenderData();

		unsigned int indices[6]{
			0,1,2,0,3,1
		};
    };
}

#endif