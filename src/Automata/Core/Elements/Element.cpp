#include "Element.h"

namespace Automata
{
	Element::~Element() {}

	Element::Element(std::vector<std::vector<Cell>>& cells, Vector2 position, Vector2 size, Vector3 color)
		:m_MatrixCells(cells),m_Position(position), m_Size(size), m_Color(color) {}
}