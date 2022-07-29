#ifndef CELL_H
#define CELL_H

#pragma once
#include "Core.h"
namespace Automata
{
    class Element; // Forward Declare Element

    struct Cell
    {
    public:
        Vector2 m_Position;
        Element* m_Element;

        Cell(Vector2 position, bool isEmpty = true)
            :m_Position(position), m_Element(nullptr){}
            
        inline bool IsEmpty() { return m_Element == nullptr;}
    };
}
#endif