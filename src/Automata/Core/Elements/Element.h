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
        Element(unsigned int elementID, std::vector<std::vector<Cell>>& cells, Vector2 position = Vector2(0.0f), Vector2 size = Vector2(1.0f), Vector3 color = Vector3(1.0f));
        ~Element();

        virtual void Step() = 0;
	    virtual void Die() {};

        Vector2 m_Position;
        Vector2 m_Size;
        Vector3 m_Color;

        bool m_isUpdated = false;   // position or color changed by cell rules
        bool m_dormant = false;     // current and previous state are the same

        inline unsigned int GetID() const {return m_elementID;}
        inline void SetID(unsigned int id) {m_elementID = id;}
    protected:
        std::vector<std::vector<Cell>>& m_MatrixCells;

        // Common Cell Rules
	    Vector2 Gravity(Vector2 desiredCoordinate);
	    Vector2 Roll(Vector2 desiredCoordinate);

        inline void EndUpdate(bool isChanged) { m_isUpdated = isChanged; m_cyclesAlive++;}
    protected:
        unsigned int m_cyclesAlive = 0;
        unsigned int m_cyclesFalling = 0;

    private:
        unsigned int m_elementID;
    };
}

#endif