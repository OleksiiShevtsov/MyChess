#include "figure.h"

IFigure::IFigure(Cell* cell, TeamColor teamColor, common::Scale scale) :
	m_xPosition{ cell->getXcellPosition() },
	m_yPosition{ cell->getYcellPosition() },
	m_teamColor{ teamColor },
	m_scale{ scale }
{
	cell->setFigure( this );
}

void IFigure::muveFigure(Cell* cell) {
	m_xPosition = cell->getXcellPosition();
	m_yPosition = cell->getYcellPosition();
	cell->setFigure(this);
}

void IFigure::figureAttack(Cell* cell) {

	/*for (vector<IFigure>::const_iterator iter = figurs.begin(); iter != figurs.end(); iter++) {
		if (*iter == cell->getFigure()) {
			figurs.erase(iter);
			break;
		}
	}*/

	cell->setFigure(this);
	muveFigure(cell);
}

common::Position IFigure::getXfigurePosition() const {
	return m_xPosition;
}

common::Position IFigure::getYfigurePosition() const {
	return m_yPosition;
}

common::Coordinate IFigure::getXfigureCenterCoordinate() const {
	return m_xPosition * m_scale;
}

common::Coordinate IFigure::getYfigureCenterCoordinate() const {
	return m_yPosition * m_scale;
}

TeamColor IFigure::getTeamColor() {
	return m_teamColor;
}