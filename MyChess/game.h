#pragma once

#include "board.h"
#include "active_figure.h"
#include "figure_pawn.h"

#include <functional>

namespace chess {

	class Game {

	public:

		Game(int scale) :
			m_board{ std::make_shared<Board>(scale) },
			m_activFigure{ std::make_unique<ActivFigure>() }
		{
			gameStaticPtr = this;
		}

		std::shared_ptr<Board> getBoard() {
			return m_board;
		}

		void createFigure() {

			//delete
			m_figurs.push_back(std::make_shared<FigurePawn>((Board::getCellByPosition(0)), true, m_board->getScale()));

			//figurs.push_back(FigureRook(&(board.getCells()[0]), true, board.getScale()));
			/*figurs.push_back(FigureRook(&(board.getCells()[7]), true, board.getScale()));
			figurs.push_back(FigureKnight(&(board.getCells()[1]), true, board.getScale()));
			figurs.push_back(FigureKnight(&(board.getCells()[6]), true, board.getScale()));
			figurs.push_back(FigureBishop(&(board.getCells()[2]), true, board.getScale()));
			figurs.push_back(FigureBishop(&(board.getCells()[5]), true, board.getScale()));
			figurs.push_back(FigureKing(&(board.getCells()[3]), true, board.getScale()));
			figurs.push_back(FigureQueen(&(board.getCells()[4]), true, board.getScale()));

			for (int i = 8; i < 16; i++) {
				figurs.push_back(FigurePawn(&(board.getCells()[i]), true, board.getScale()));
			}

			for (int i = 48; i < 56; i++) {
				figurs.push_back(FigurePawn(&(board.getCells()[i]), false, board.getScale()));
			}

			figurs.push_back(FigureRook(&(board.getCells()[56]), false, board.getScale()));
			figurs.push_back(FigureRook(&(board.getCells()[63]), false, board.getScale()));
			figurs.push_back(FigureKnight(&(board.getCells()[57]), false, board.getScale()));
			figurs.push_back(FigureKnight(&(board.getCells()[62]), false, board.getScale()));
			figurs.push_back(FigureBishop(&(board.getCells()[58]), false, board.getScale()));
			figurs.push_back(FigureBishop(&(board.getCells()[61]), false, board.getScale()));
			figurs.push_back(FigureKing(&(board.getCells()[59]), false, board.getScale()));
			figurs.push_back(FigureQueen(&(board.getCells()[60]), false, board.getScale()));*/
		}

		void drawFigure() {
			for (auto figur : m_figurs) {
				figur->drawFigur();
			}
		}

		static void game() {

			glClear(GL_COLOR_BUFFER_BIT);

			gameStaticPtr->m_board->drawBoard();
			gameStaticPtr->drawFigure();

			switch (gameStaticPtr->m_currentTeamMove)
			{
			case CurrentTeamMove::WHITE: gameStaticPtr->movementFigure(gameStaticPtr->m_currentTeamMove); break;
			case CurrentTeamMove::BLACK: gameStaticPtr->movementFigure(gameStaticPtr->m_currentTeamMove); break;
			}

			glFlush();
		}

		void movementFigure(CurrentTeamMove currentTeamMove) {

			//delete
			m_activFigure->m_prevCell->getFigure();

			/*if (activFigure->m_stateeMouse == StateMouse::PUSH) {
				activFigure->m_prevCell = board->getCell(activFigure->m_xCoordinate, activFigure->m_yCoordinate);

				if (afm.prev_cell_r->getFigure() != nullptr && afm.prev_cell_r->getFigure()->getTeamColor() == team) {
					afm.figure_r = afm.prev_cell_r->getFigure();
					afm.prev_cell_r->colorGetCell(BLUE);
				}
				else if (afm.prev_cell_r->getFigure() != nullptr) {
					afm.prev_cell_r->colorGetCell(RED);
					afm.g_state = 0;
				}
				else {
					afm.prev_cell_r->colorGetCell(WHITE);
					afm.g_state = 0;
				}
			}
			else if (activFigure->m_stateeMouse == StateMouse::RELEASE) {
				if (afm.g_x < 0 || afm.g_y < 0 || afm.g_x > board.getScale() * 8 || afm.g_x > board.getScale() * 8) {
					afm.nullData();
				}
				else {
					afm.cell_r = board.getCell(afm.g_x, afm.g_y);
					bool checkMove = afm.figure_r->checkMoveFigures(afm.cell_r);
					if (checkMove) {
						afm.cell_r->colorGetCell(GREEN);
						if (pawnToQueen) {
							convertToQueen(afm.cell_r);
						}
						afm.prev_cell_r->setFigure(nullptr);
						afm.nullData();
						teamMove = !team;
					}
					else {
						afm.cell_r->colorGetCell(RED);
						afm.nullData();
					}
				}
			}*/
		}

		static void timer(int = 0) {

			gameStaticPtr->game();

			switch (gameStaticPtr->m_killingKing) {
			case KillingKing::WHITE: glColor3f(0.1, 0.1, 0.1); break;
			case KillingKing::BLACK: glColor3f(0.9, 0.9, 0.9); break;
			case KillingKing::LIVE: glutTimerFunc(100, timer, 0); return;
			}

			glRectf(0, 0, 6, gameStaticPtr->m_board->getScale() * 8);
			glRectf(0, 0, gameStaticPtr->m_board->getScale() * 8, 6);
			glRectf(0, gameStaticPtr->m_board->getScale() * 8 - 6, gameStaticPtr->m_board->getScale() * 8, gameStaticPtr->m_board->getScale() * 8);
			glRectf(gameStaticPtr->m_board->getScale() * 8 - 6, 0, gameStaticPtr->m_board->getScale() * 8, gameStaticPtr->m_board->getScale() * 8);
			glFlush();
		}

		static void mouseClick(int button, int state, int x, int y) {
			if (state == GLUT_DOWN) {
				gameStaticPtr->m_activFigure->m_stateeMouse = StateMouse::PUSH;
				gameStaticPtr->m_activFigure->m_xCoordinate = x;
				gameStaticPtr->m_activFigure->m_yCoordinate = y;
			}
			else if (gameStaticPtr->m_activFigure->m_stateeMouse != StateMouse::FREE) {
				gameStaticPtr->m_activFigure->m_stateeMouse = StateMouse::RELEASE;
				gameStaticPtr->m_activFigure->m_xCoordinate = x;
				gameStaticPtr->m_activFigure->m_yCoordinate = y;
			}
		}

	private:
		std::shared_ptr<Board> m_board;
		std::unique_ptr<ActivFigure> m_activFigure;
		std::vector<std::shared_ptr<IFigure>> m_figurs;
		CurrentTeamMove m_currentTeamMove = CurrentTeamMove::WHITE;
		KillingKing m_killingKing = KillingKing::LIVE;

		static Game* gameStaticPtr;
	};
}