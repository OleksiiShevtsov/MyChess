#pragma once

#include "types.h"
#include "enum.h"
#include "cell.h"

class IFigure {
public:
	IFigure(Cell* cell, TeamColor teamColor, common::Scale scale);
	virtual ~IFigure() = 0;

	virtual void drawFigur() = 0;
	virtual bool checkMoveFigures(Cell& cell) = 0;

	void muveFigure(Cell* cell);
	void figureAttack(Cell* cell);

	common::Position getXfigurePosition() const;
	common::Position getYfigurePosition() const;
	common::Coordinate getXfigureCenterCoordinate() const;
	common::Coordinate getYfigureCenterCoordinate() const;
	TeamColor getTeamColor();

protected:

	common::Position m_xPosition;
	common::Position m_yPosition;
	common::Scale m_scale;
	TeamColor m_teamColor;
};
