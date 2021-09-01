#pragma once

#include "figure.h"

class FigurePawn : public IFigure {
public:

	FigurePawn(Cell* cell, TeamColor teamColor, common::Scale scale) :
		IFigure(cell, teamColor, scale)
	{}

	void drawFigurPawn() {
		switch (m_teamColor)
		{
			case WHITE_TEAM: glColor3f(1.0, 1.0, 1.0); break;
			case BLACK_TEAM: glColor3f(0.0, 0.0, 0.0); break;
		} 
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(getXfigureCenterCoordinate(), getYfigureCenterCoordinate());
		glVertex2f(getXfigureCenterCoordinate() - 10, getYfigureCenterCoordinate() + 10);
		glVertex2f(getXfigureCenterCoordinate() - 10, getYfigureCenterCoordinate() + 0);
		glVertex2f(getXfigureCenterCoordinate() - 5, getYfigureCenterCoordinate() - 22);
		glVertex2f(getXfigureCenterCoordinate() + 5, getYfigureCenterCoordinate() - 22);
		glVertex2f(getXfigureCenterCoordinate() + 10, getYfigureCenterCoordinate() + 0);
		glVertex2f(getXfigureCenterCoordinate(), getYfigureCenterCoordinate() + 10);
		glVertex2f(getXfigureCenterCoordinate(), getYfigureCenterCoordinate() + 10);

		glEnd();
	}

	bool checkMoveFigures(std::shared_ptr<Cell> cell) {
		/*if (m_teamColor == TeamColor::WHITE) {
			if (getYfigurePosition() + 1 == cell->getYcellPosition() && getXfigurePosition() == cell->getXcellPosition()) {
				if (cell->getFigure() == nullptr) {
					this->muveFigure(cell);
					if (cell->getYcellPosition() == 7) {
						//pawnToQueen = true;
					}
					m_firstMovePawn = false;
					return true;
				}
				else {
					return false;
				}
			}
			else if (getYfigurePosition() + 2 == cell->getYcellPosition() && getXfigurePosition() == cell->getXcellPosition() && m_firstMovePawn == true) {
				if (cell->getFigure() == nullptr) {
					if (Board::getCell(cell->getCentrSizeCell_X(), cell->getCentrSizeCell_Y() - cell->getScale())->getFigure() != nullptr) {
						return false;
					}
					else {
						this->muveFigure(cell);
						m_firstMovePawn = false;
						return true;
					}
				}
				else {
					return false;
				}
			}
			else if (coordinateFigur_Y + 1 == cell->getCoordinateCell_Y() && (coordinateFigur_X + 1 == cell->getCoordinateCell_X() || coordinateFigur_X - 1 == cell->getCoordinateCell_X())) {
				if (cell->getFigure() != nullptr && cell->getFigure()->getTeamColor() != this->teamColor) {
					this->figureAttack(cell);
					if (cell->getCoordinateCell_Y() == 7) {
						pawnToQueen = true;
					}
					firstMovePawn = false;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			if (coordinateFigur_Y - 1 == cell->getCoordinateCell_Y() && coordinateFigur_X == cell->getCoordinateCell_X()) {
				if (cell->getFigure() == nullptr) {
					this->muveFigure(cell);
					if (cell->getCoordinateCell_Y() == 0) {
						pawnToQueen = true;
					}
					firstMovePawn = false;
					return true;
				}
				else {
					return false;
				}
			}
			else if (coordinateFigur_Y - 2 == cell->getCoordinateCell_Y() && firstMovePawn == true && coordinateFigur_X == cell->getCoordinateCell_X()) {
				if (cell->getFigure() == nullptr) {
					if (Board::getCell(cell->getCentrSizeCell_X(), cell->getCentrSizeCell_Y() + cell->getScale())->getFigure() != nullptr) {
						return false;
					}
					else {
						this->muveFigure(cell);
						firstMovePawn = false;
						return true;
					}
				}
				else {
					return false;
				}
			}
			else if (coordinateFigur_Y - 1 == cell->getCoordinateCell_Y() && (coordinateFigur_X + 1 == cell->getCoordinateCell_X() || coordinateFigur_X - 1 == cell->getCoordinateCell_X())) {
				if (cell->getFigure() != nullptr && cell->getFigure()->getTeamColor() != this->teamColor) {
					this->figureAttack(cell);
					if (cell->getCoordinateCell_Y() == 0) {
						//pawnToQueen = true;
					}
					firstMovePawn = false;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}*/
		return true;
	}

	private:

	bool m_firstMovePawn = true;
};
