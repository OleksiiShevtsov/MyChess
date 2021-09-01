#pragma once

#include "cell.h"

struct ActivFigure {
	StateMouse m_stateeMouse = StateMouse::FREE;
	common::Coordinate m_xCoordinate = 0;
	common::Coordinate m_yCoordinate = 0;
	IFigure* m_currentFigure = nullptr;
	Cell* m_current—ell = nullptr;
	Cell* m_prevCell = nullptr;

	void clear() {
		m_stateeMouse = StateMouse::FREE;
		IFigure* m_currentFigure = nullptr;
		Cell* m_current—ell = nullptr;
		Cell* m_prevCell = nullptr;
	}
};
