#pragma once

#include "cell.h"

namespace chess {

	struct ActivFigure {
		StateMouse m_stateeMouse = StateMouse::FREE;
		common::Coordinate m_xCoordinate = 0;
		common::Coordinate m_yCoordinate = 0;
		IFigure* m_currentFigure = nullptr;
		Cell* m_currentCell = nullptr;
		Cell* m_prevCell = nullptr;

		void clear() {
			m_stateeMouse = StateMouse::FREE;
			IFigure* m_currentFigure = nullptr;
			Cell* m_currentCell = nullptr;
			Cell* m_prevCell = nullptr;
		}
	};
}
