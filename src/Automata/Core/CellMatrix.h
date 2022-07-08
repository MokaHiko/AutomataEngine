#ifndef CELLMATRIX_H
#define CELLMATRIX_H

#pragma once

#include "Core.h"
#include "Element.h"
#include "Renderer/AutomataRenderer.h"

namespace Automata
{
    class CellMatrix
    {
    public:
        CellMatrix();
        ~CellMatrix();

        void DrawElements();
        void Update(float deltaTime);
        void InitMatrix(Vector2 dimensions);

        // API T child of Element
        template<typename T>
        void AddElement(Vector2 position)
        {
            // Define Bounds
            if (position.x > m_Dimensions.x || position.x < 0) { std::cout << "Out of Bounds X" << std::endl; return; }
            if (position.y > m_Dimensions.y || position.y < 0) { std::cout << "Out of Bounds Y" << std::endl; return; }

            // Make Sure Cell is Available/Empty 
            Cell cell = m_Cells[position.x][position.y];
            if(!cell.m_isEmpty)
                return;
            cell.m_isEmpty = false;

            // Add Element to Update Array
            T e{m_Cells, position};
            e.m_Position = position;
            m_Elements.push_back(std::make_unique<T>(e));

            // Add Element Color to Renderer buffer
            m_Renderer->AddInstance(e.m_Position, e.m_Color);
        }

        template<typename T>
        void AddElementCircle(Vector2 position,  int radius)
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
        AutomataRenderer* m_Renderer;
    private:
        std::vector<std::vector<Cell>> m_Cells;
        std::vector<std::unique_ptr<Element>> m_Elements;

        Vector2 CELL_SIZE{1.0f};
        Vector2 m_Dimensions;
    };
}

#endif