#include "cell.h"

Cell::Cell(common::Position xPosition, common::Position yPosition, common::Scale scale, bool colorCell) :
	m_xPosition{ xPosition },
	m_yPosition{ yPosition },
	m_scale{ scale },
	m_colorCell{ colorCell }
{
}

common::Position Cell::getXcellPosition() const {
	return m_xPosition;
}

common::Position Cell::getYcellPosition() const {
	return m_yPosition;
}

common::Coordinate Cell::getXcellCoordinate() const {
	return m_xPosition * m_scale;
}

common::Coordinate Cell::getYcellCoordinate() const {
	return m_yPosition * m_scale;
}

common::Coordinate Cell::getXcellCenterCoordinate() const {
	return getXcellCoordinate() + m_scale / 2;
}

common::Coordinate Cell::getYcellCenterCoordinate() const {
	return getYcellCoordinate() + m_scale / 2;
}

bool Cell::getColorCell() const {
	return m_colorCell;
}

IFigure* Cell::getFigure() const {
	return m_figure;
}

void Cell::setBorderColorCells(BorderColorCell borderColorCell) {
	switch (borderColorCell) {
	case BorderColorCell::GREEN:glColor3f(0.0, 1.0, 0.0); break;
	case BorderColorCell::RED:glColor3f(1.0, 0.0, 0.0); break;
	case BorderColorCell::BLUE:glColor3f(0.2, 0.2, 1.0); break;
	case BorderColorCell::WHITE:glColor3f(1.0, 1.0, 1.0); break;
	}

	glRectf(getXcellCoordinate(), getYcellCoordinate(), getXcellCoordinate() + 2, getYcellCoordinate() + m_scale);
	glRectf(getXcellCoordinate(), getYcellCoordinate() + m_scale - 2, getXcellCoordinate() + m_scale, getYcellCoordinate() + m_scale);
	glRectf(getXcellCoordinate() + m_scale - 2, getYcellCoordinate(), getXcellCoordinate() + m_scale, getYcellCoordinate() + m_scale);
	glRectf(getXcellCoordinate(), getYcellCoordinate(), getXcellCoordinate() + m_scale, getYcellCoordinate() + 2);
}

void Cell::setFigure(IFigure* figur) {
	m_figure = figur;
}