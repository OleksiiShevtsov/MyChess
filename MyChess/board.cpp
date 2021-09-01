#include "board.h"

chess::Board::Board(common::Scale scale) :
	m_scale{ scale } 
{
	bool colorCall = false;
	for (int yPosition = 0; yPosition < 8; yPosition++) {
		for (int xPosition = 0; xPosition < 8; xPosition++) {
			colorCall = !colorCall;
			m_cells.push_back(Cell(xPosition, yPosition, m_scale, colorCall));
		}
		colorCall = !colorCall;
	}
	boardStaticPtr = this;
}

chess::Cell* chess::Board::getCellByCoordinates(common::Coordinate xCoordinate, common::Coordinate yCoordinate) {
	for (auto cell : boardStaticPtr->m_cells) {
		if (xCoordinate / boardStaticPtr->m_scale == cell.getXcellCenterCoordinate() && yCoordinate / boardStaticPtr->m_scale == cell.getYcellCenterCoordinate()) {
			return &cell;
			break;
		}
	}
	return nullptr;
}

chess::Cell* chess::Board::getCellByPosition(int position) {
	return &(boardStaticPtr->m_cells[position]);
}

chess::common::Scale chess::Board::getScale() {
	return m_scale;
}

void chess::Board::drawBoard() {
	for (auto cell : m_cells) {
		cell.getColorCell() ? glColor3f(0.9, 0.7, 0.5) : glColor3f(0.25, 0.25, 0.25);
		glRectf(cell.getXcellCoordinate(), cell.getYcellCoordinate(), cell.getXcellCoordinate() + m_scale, cell.getYcellCoordinate() + m_scale);
	}
}

const int chess::Board::NUMBER_OF_CELLS = 64;