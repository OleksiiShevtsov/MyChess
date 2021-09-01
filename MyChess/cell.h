#pragma once

#include "enum.h"
#include "figure.h"
#include "types.h"

#include <glut.h>

#pragma warning (disable: 2238)

namespace chess {

	class Cell {
	public:

		Cell(common::Position xPosition, common::Position yPosition, common::Scale scale, bool colorCell);

		common::Position getXcellPosition() const;
		common::Position getYcellPosition() const;
		common::Coordinate getXcellCoordinate() const;
		common::Coordinate getYcellCoordinate() const;
		common::Coordinate getXcellCenterCoordinate() const;
		common::Coordinate getYcellCenterCoordinate() const;
		bool getColorCell() const;
		IFigure* getFigure() const;

		void setBorderColorCells(BorderColorCell cellColor);
		void setFigure(IFigure* figure);

	private:
		common::Position m_xPosition;
		common::Position m_yPosition;
		common::Scale m_scale;
		bool m_colorCell;
		IFigure* m_figure;
	};
}
