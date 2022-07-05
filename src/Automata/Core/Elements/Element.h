#ifndef ELEMENT_H
#define ELEMENT_H

#pragma once

#include "Core.h"
#include "Cell.h"

namespace Automata
{
    class Element
    {
    public:
        Element(std::vector<std::vector<Cell>>& cells, Vector2 position = Vector2(0.0f), Vector2 size = Vector2(1.0f), Vector3 color = Vector3(1.0f));
        ~Element();

        virtual void Step() = 0;

        Vector2 m_Position;
        Vector2 m_Size;
        Vector3 m_Color;

        bool m_isUpdated;
    protected:
        std::vector<std::vector<Cell>>& m_MatrixCells;
    };
}

#endif