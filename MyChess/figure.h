#pragma once

#include "types.h"
#include "enum.h"
#include "cell.h"

namespace chess {

	class IFigure {
	public:
		IFigure(Cell& cell, TeamColor teamColor, common::Scale scale);
		virtual ~IFigure() {};

		virtual void drawFigur() = 0;
		virtual bool checkMoveFigure(Cell*) {}

		void muveFigure(Cell&);
		void figureAttack(Cell&);

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
}
