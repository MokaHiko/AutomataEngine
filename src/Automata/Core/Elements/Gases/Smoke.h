#ifndef SMOKE_H
#define SMOKE_H

#pragma once

#include "Element.h"

namespace Automata{
    class Smoke : public Element
    {
    public:
	    Smoke(unsigned int elementID, std::vector<std::vector<Cell>>& cells, Vector2 position = Vector2(0.0f));
        ~Smoke();

        void Step() override;
        void Die() override;
    protected:
        Vector2 Rise(Vector2 desiredCoordinate);
        Vector2 RollUp(Vector2 desiredCoordinate);
        Vector2 SlideUp(Vector2 desiredCoordinate);
        unsigned int m_cyclesRising = 0;
    };
}

#endif