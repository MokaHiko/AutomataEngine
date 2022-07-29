#ifndef WATER_H
#define WATER_H

#pragma once

#include "Element.h"
namespace Automata
{
    class Water: public Element
    {
    public:
        Water(unsigned int elementID, std::vector<std::vector<Cell>>& cells, Vector2 position = Vector2(0.0f));
        ~Water();

    	void Step() override;
    protected:
	    Vector2 Slide(Vector2 desiredCoordinate);
    };
}

#endif