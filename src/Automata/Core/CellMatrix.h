#ifndef CELLMATRIX_H
#define CELLMATRIX_H

#pragma once

#include "Core.h"
#include "Element.h"
#include "Renderer/SpriteRenderer.h"

namespace Automata
{
    class CellMatrix
    {
    public:
        CellMatrix();
        ~CellMatrix();

        void DrawElements(SpriteRenderer* renderer);
        void Update(float deltaTime);
        void InitMatrix(Vector2 dimensions);

        // API
        template<typename T>
        void AddElement(Vector2 position)
        {
            // Define Bounds
            if (position.x > m_Dimensions.x || position.x < 0) { std::cout << "Out of Bounds X" << std::endl; return; }
            if (position.y > m_Dimensions.y || position.y < 0) { std::cout << "Out of Bounds Y" << std::endl; return; }

            Cell cell = m_Cells[position.x][position.y];
            if(!cell.m_isEmpty)
                return;

            T e{m_Cells, position};
            e.m_Position = position;
            m_Elements.push_back(std::make_unique<T>(e));
        }

        inline unsigned int m_nElements() {return m_Elements.size();}
    private:
        inline Vector2 GetMatrixDimensions() {return m_Dimensions;}
    private:
        std::vector<std::vector<Cell>> m_Cells;
        std::vector<std::unique_ptr<Element>> m_Elements;

        Vector2 CELL_SIZE{1.0f};
        Vector2 m_Dimensions;
    };
}

#endif