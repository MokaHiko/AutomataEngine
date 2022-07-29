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

        void InitMatrix(Vector2 dimensions);
        void Update(float deltaTime);
        void DrawElements();

        // API T child of Element
        template<typename T>
        void AddElement(Vector2 position)
        {
            // Define Bounds
            if (position.x > m_Dimensions.x - 1 || position.x < 0) { std::cout << "Out of Bounds X: " << position.x << std::endl; return; }
            if (position.y > m_Dimensions.y - 1 || position.y < 0) { std::cout << "Out of Bounds Y: " << position.y << std::endl; return; }

            // Make Sure Cell is Available/Empty 
            Cell& cell = m_Cells[position.x][position.y];
            if (!cell.IsEmpty())
                return;

            // Add Element to Update Array
            T* e = new T{nElements++, m_Cells, position};
            e->m_Position = position;
            m_Elements.emplace_back(e);

            // Add Reference To Cell
            cell.m_Element = e;

            // Add Element Color to Renderer buffer
            m_Renderer->AddInstance(e->m_Position, e->m_Color);
        }

        template<typename T>
        void AddElementCircle(Vector2 position,  int radius)
        {
            for(Vector2& p : m_circlePoints)
            {
                AddElement<T>(position + p);
            }
        }

        template<typename T>
        void AddElementSquare(Vector2 position,  int radius)
        {
            for(Vector2& p : m_squarePoints)
            {
                AddElement<T>(position + p);
            }
        }

        void RemoveElement(Vector2 position)
        {
            // Define Bounds
            if (position.x > m_Dimensions.x - 1 || position.x < 0) { std::cout << "Out of Bounds X: " << position.x << std::endl; return; }
            if (position.y > m_Dimensions.y - 1 || position.y < 0) { std::cout << "Out of Bounds Y: " << position.y << std::endl; return; }

            // Make Sure Cell has Element
            Cell& cell = m_Cells[position.x][position.y];
            if (cell.IsEmpty())
                return;

            unsigned int elementIndex = cell.m_Element->GetID();

            // *memory leak : add delition queue 
            //delete m_Elements[elementIndex]; // delete element 

            // swap index of last element in array with deleted element
            std::iter_swap(m_Elements.begin() + elementIndex, m_Elements.end() - 1); // swap last element position to empty update array
            m_Elements[elementIndex]->SetID(elementIndex); // change id for swapped element
            m_Elements.pop_back(); // remove hanging pointer from array
            cell.m_Element = nullptr; // remove hanging pointer form array

            // do the same in buffer
            m_Renderer->RemoveInstance(elementIndex);
            nElements--;
        }
        void RemoveElementSquare(Vector2 position,  int radius)
        {
            for(Vector2& p : m_squarePoints)
            {
                RemoveElement(position + p);
            }
        }
        inline unsigned int m_nElements() {return nElements;}
    private:
        inline Vector2 GetMatrixDimensions() {return m_Dimensions;}
        AutomataRenderer* m_Renderer;
    private:
        std::vector<std::vector<Cell>> m_Cells;
        std::vector<Element*> m_Elements;

        Vector2 CELL_SIZE{1.0f};
        Vector2 m_Dimensions;
    private:
        // PreDefined Shapes
        std::vector<Vector2> m_circlePoints{};
        std::vector<Vector2> m_squarePoints{};
        unsigned int radius;
        
        void DefineCirclePoints(unsigned int radius);
        void DefineSquarePoints(unsigned int s); // side lenghth

        unsigned int nElements = 0;
    };
}

#endif