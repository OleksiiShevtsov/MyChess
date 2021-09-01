#include "cell.h"

chess::Cell::Cell(common::Position xPosition, common::Position yPosition, common::Scale scale, bool colorCell) :
	m_xPosition{ xPosition },
	m_yPosition{ yPosition },
	m_scale{ scale },
	m_colorCell{ colorCell }
{
}

chess::common::Position chess::Cell::getXcellPosition() const {
	return m_xPosition;
}

chess::common::Position chess::Cell::getYcellPosition() const {
	return m_yPosition;
}

chess::common::Coordinate chess::Cell::getXcellCoordinate() const {
	return m_xPosition * m_scale;
}

chess::common::Coordinate chess::Cell::getYcellCoordinate() const {
	return m_yPosition * m_scale;
}

chess::common::Coordinate chess::Cell::getXcellCenterCoordinate() const {
	return getXcellCoordinate() + m_scale / 2;
}

chess::common::Coordinate chess::Cell::getYcellCenterCoordinate() const {
	return getYcellCoordinate() + m_scale / 2;
}

bool chess::Cell::getColorCell() const {
	return m_colorCell;
}

chess::IFigure* chess::Cell::getFigure() const {
	return m_figure;
}

void chess::Cell::setBorderColorCells(BorderColorCell borderColorCell) {
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

void chess::Cell::setFigure(IFigure* figure) {
	m_figure = figure;
}