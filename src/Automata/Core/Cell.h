#ifndef CELL_H
#define CELL_H

#pragma once
#include "Core.h"
namespace Automata
{
    struct Cell
    {
    public:
        bool m_isEmpty = true;
        Vector2 m_Position;

        Cell(Vector2 position)
            :m_Position(position) {}
    };
}
#endif