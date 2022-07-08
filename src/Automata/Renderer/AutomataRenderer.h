#ifndef AUTOMATARENDERER_H
#define AUTOMATARENDERER_H

#pragma once

#include "Shader.h"
#include "Core.h"

namespace Automata
{
    class AutomataRenderer
    {
    public:
        AutomataRenderer(Shader& shader, Vector2 resolution);
        ~AutomataRenderer();

        void DrawSprites();
	    void AddInstance(const Vector2& coordinates, const Vector3& color);
	    void UpdateInstance(unsigned int instanceID, const Vector2& coordinates, const Vector3& color);
    private:
        unsigned int m_currentInstance;
        unsigned int m_instanceCount;

    private:
        Shader m_Shader;
        unsigned int VAO;
		unsigned int positionsBuffer;
		unsigned int colorsBuffer;

        Vector2 m_Resolution;
        void InitRenderData();

		unsigned int indices[6]{
			0,1,2,0,3,1
		};
    };
}


#endif