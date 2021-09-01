#pragma once
#include "cell.h"

#include <vector>
#include <memory>
#include <glut.h>

namespace chess {

	class Board {
	public:
		Board(common::Scale scale);

		static Cell* getCellByCoordinates(common::Coordinate xCoordinate, common::Coordinate yCoordinate);
		static Cell* getCellByPosition(int position);

		common::Scale getScale();

		void drawBoard();

	private:
		std::vector<Cell> m_cells;
		common::Scale m_scale;

		static const int NUMBER_OF_CELLS;
		static Board* boardStaticPtr;
	};
}