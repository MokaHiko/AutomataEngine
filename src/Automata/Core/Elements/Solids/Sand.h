#ifndef SAND_H
#define SAND_H

#pragma once

#include "Element.h"
#include "Core.h"

namespace Automata
{
    class Sand : public Element
    {
    public:
	    Sand(std::vector<std::vector<Cell>>& cells, Vector2 position = Vector2(0.0f));
        ~Sand();

    	void Step() override;
    };
}

#endif