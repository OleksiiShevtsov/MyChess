#include "figure.h"

chess::IFigure::IFigure(Cell& cell, TeamColor teamColor, common::Scale scale) :
	m_xPosition{ cell.getXcellPosition() },
	m_yPosition{ cell.getYcellPosition() },
	m_teamColor{ teamColor },
	m_scale{ scale }
{
	cell.setFigure(this);
}

void chess::IFigure::muveFigure(Cell& cell) {
	m_xPosition = cell.getXcellPosition();
	m_yPosition = cell.getYcellPosition();
	cell.setFigure(this);
}

void chess::IFigure::figureAttack(Cell& cell) {

	/*for (vector<IFigure>::const_iterator iter = figurs.begin(); iter != figurs.end(); iter++) {
		if (*iter == cell->getFigure()) {
			figurs.erase(iter);
			break;
		}
	}*/

	muveFigure(cell);
}

chess::common::Position chess::IFigure::getXfigurePosition() const {
	return m_xPosition;
}

chess::common::Position chess::IFigure::getYfigurePosition() const {
	return m_yPosition;
}

chess::common::Coordinate chess::IFigure::getXfigureCenterCoordinate() const {
	return m_xPosition * m_scale;
}

chess::common::Coordinate chess::IFigure::getYfigureCenterCoordinate() const {
	return m_yPosition * m_scale;
}

chess::TeamColor chess::IFigure::getTeamColor() {
	return m_teamColor;
}