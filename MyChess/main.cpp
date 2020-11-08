﻿#include <iostream>
#include <glut.h>
#include <vector>
using namespace std;

const int Scale = 64;
int L = Scale * 8;
bool teamMove = true;
bool pawnToQueen = false;
bool deathWhiteKing = false;
bool deathBlackKing = false;

class Figure;
enum CellColor {
	GREEN, RED, BLUE, WHITE
};
class Board {
public:
	class Cell;
	Board(int scale) {
		this->scale = scale;
		bool colorCall = false;
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				this->cells.push_back(Cell(x * scale, y * scale, x, y, getOtherColorCall(colorCall), scale));
				colorCall = getOtherColorCall(colorCall);
			}
			colorCall = getOtherColorCall(colorCall);
		}
	}

	bool getOtherColorCall(bool colorCall) {
		if (colorCall) {
			return false;
		}
		else {
			return true;
		}
	}

	Cell* getCell(int x, int y) {
		for (int i = 0; i < 64; i++) {
			if (x / scale == cells[i].CoordinateÑell_X && y / scale == cells[i].CoordinateÑell_Y) {
				return &cells[i];
				break;
			}
		}
		return nullptr;
	}

	void drawBoard() {

		for (int i = 0; i < 64; i++) {
			if (cells[i].color) {
				glColor3f(0.9, 0.7, 0.5);
			}
			else {
				glColor3f(0.25, 0.25, 0.25);
			}
			glRectf(cells[i].SizeÑell_X, cells[i].SizeÑell_Y, cells[i].SizeÑell_X + scale, cells[i].SizeÑell_Y + scale);
		}
	}

	class Cell {
	public:
		Cell(const int xSize, const int ySize, int x, int y, bool color, int scale) {
			this->SizeÑell_X = xSize;
			this->SizeÑell_Y = ySize;
			this->CentrSizeÑell_X = this->SizeÑell_X + scale / 2;
			this->CentrSizeÑell_Y = this->SizeÑell_Y + scale / 2;
			CoordinateÑell_X = x;
			CoordinateÑell_Y = y;
			this->color = color;
			this->scale = scale;
		}

		void colorGetCell(CellColor cellColor) {
			switch (cellColor) {
			case GREEN:glColor3f(0.0, 1.0, 0.0); break;
			case RED:glColor3f(1.0, 0.0, 0.0); break;
			case BLUE:glColor3f(0.2, 0.2, 1.0); break;
			case WHITE:glColor3f(1.0, 1.0, 1.0); break;
			}

			glRectf(SizeÑell_X, SizeÑell_Y, SizeÑell_X + 2, SizeÑell_Y + scale);
			glRectf(SizeÑell_X, SizeÑell_Y + scale - 2, SizeÑell_X + scale, SizeÑell_Y + scale);
			glRectf(SizeÑell_X + scale - 2, SizeÑell_Y, SizeÑell_X + scale, SizeÑell_Y + scale);
			glRectf(SizeÑell_X, SizeÑell_Y, SizeÑell_X + scale, SizeÑell_Y + 2);
		}

		int CoordinateÑell_X;
		int CoordinateÑell_Y;
		int SizeÑell_X;
		int SizeÑell_Y;
		int CentrSizeÑell_X;
		int CentrSizeÑell_Y;
		bool color = true;
		int scale;
		Figure* figur = nullptr;
	};
	vector<Cell> cells;
	unsigned int scale;

}board(Scale);

vector<Figure*> figurs;
struct activFigureMouse {
	int g_state;
	float g_x = 0.0;
	float g_y = 0.0;
	Figure* figure_r = nullptr;
	Board::Cell* cell_r = nullptr;
	Board::Cell* prev_cell_r = nullptr;

	void nullData() {
		prev_cell_r = nullptr;
		cell_r = nullptr;
		figure_r = nullptr;
		g_x = 0;
		g_y = 0;
		g_state = 0;
	}
} afm;

class Figure {
public:
	Figure(Board::Cell* cell, bool command, int scale) {
		this->teamColor = command;
		cell->figur = this;
		CentrSizeFigur_X = cell->CentrSizeÑell_X;
		CentrSizeFigur_Y = cell->CentrSizeÑell_Y;
		CoordinateFigur_X = cell->CoordinateÑell_X;
		CoordinateFigur_Y = cell->CoordinateÑell_Y;
	}

	virtual void drawFigurPawn() = 0;
	virtual bool checkMoveFigures(Board::Cell* cell) = 0;

	void muveFigure(Board::Cell* cell) {
		CentrSizeFigur_X = cell->CentrSizeÑell_X;
		CentrSizeFigur_Y = cell->CentrSizeÑell_Y;
		CoordinateFigur_X = cell->CoordinateÑell_X;
		CoordinateFigur_Y = cell->CoordinateÑell_Y;
		cell->figur = this;
	}

	void figureAttack(Board::Cell* cell) {

		for (vector<Figure*>::const_iterator iter = figurs.begin(); iter != figurs.end(); iter++) {
			if (*iter == cell->figur) {
				figurs.erase(iter);
				break;
			}
		}

		cell->figur = this;
		this->muveFigure(cell);
	}

	virtual ~Figure() {}

	int CoordinateFigur_X;
	int CoordinateFigur_Y;
	int CentrSizeFigur_X;
	int CentrSizeFigur_Y;
	bool teamColor;
	bool active = true;
};
class FigureRook : public Figure {
public:
	FigureRook(Board::Cell* cell, bool command, int scale) :Figure(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((CentrSizeFigur_X), (CentrSizeFigur_Y));
		glVertex2f((CentrSizeFigur_X - 11), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 11), (CentrSizeFigur_Y - 10));
		glVertex2f((CentrSizeFigur_X - 15), (CentrSizeFigur_Y - 20));
		glVertex2f((CentrSizeFigur_X - 15), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X - 8), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X - 8), (CentrSizeFigur_Y - 20));
		glVertex2f((CentrSizeFigur_X - 4), (CentrSizeFigur_Y - 20));
		glVertex2f((CentrSizeFigur_X - 4), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X + 4), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X + 4), (CentrSizeFigur_Y - 20));
		glVertex2f((CentrSizeFigur_X + 8), (CentrSizeFigur_Y - 20));
		glVertex2f((CentrSizeFigur_X + 8), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X + 15), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X + 15), (CentrSizeFigur_Y - 20));
		glVertex2f((CentrSizeFigur_X + 11), (CentrSizeFigur_Y - 10));
		glVertex2f((CentrSizeFigur_X + 11), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 11), (CentrSizeFigur_Y + 10));
		glEnd();
	}

	bool checkMoveFigures(Board::Cell* cell) {
		if (CoordinateFigur_X == cell->CoordinateÑell_X && CoordinateFigur_Y > cell->CoordinateÑell_Y) {
			for (int iy = CoordinateFigur_Y - 1; iy > cell->CoordinateÑell_Y; iy--) {
				if (board.getCell(cell->CentrSizeÑell_X, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					cout << cell->scale*iy + cell->scale / 2 << endl;
					return false;
				}
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X < cell->CoordinateÑell_X && CoordinateFigur_Y == cell->CoordinateÑell_Y && (cell->CoordinateÑell_X < cell->scale * 8)) {

			for (int ix = CoordinateFigur_X + 1; ix < cell->CoordinateÑell_X; ix++) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->CentrSizeÑell_Y)->figur != nullptr) {
					cout << cell->scale*ix + cell->scale / 2 << endl;
					return false;
				}
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X == cell->CoordinateÑell_X && CoordinateFigur_Y < cell->CoordinateÑell_Y && (cell->CoordinateÑell_Y < cell->scale * 8)) {
			for (int iy = CoordinateFigur_Y + 1; iy < cell->CoordinateÑell_Y; iy++) {
				if (board.getCell(cell->CentrSizeÑell_X, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					cout << cell->scale*iy + cell->scale / 2 << endl;
					return false;
				}
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X > cell->CoordinateÑell_X && CoordinateFigur_Y == cell->CoordinateÑell_Y) {
			for (int ix = CoordinateFigur_X - 1; ix > cell->CoordinateÑell_X; ix--) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->CentrSizeÑell_Y)->figur != nullptr) {
					cout << cell->scale*ix + cell->scale / 2 << endl;
					return false;
				}
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
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

	virtual ~FigureRook() {}
};
class FigureKnight : public Figure {
public:
	FigureKnight(Board::Cell* cell, bool command, int scale) :Figure(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((CentrSizeFigur_X - 0), (CentrSizeFigur_Y - 12));
		glVertex2f((CentrSizeFigur_X - 12), (CentrSizeFigur_Y - 8));
		glVertex2f((CentrSizeFigur_X - 10), (CentrSizeFigur_Y - 20));
		glVertex2f((CentrSizeFigur_X - 0), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X + 10), (CentrSizeFigur_Y - 20));
		glVertex2f((CentrSizeFigur_X + 12), (CentrSizeFigur_Y - 10));
		glVertex2f((CentrSizeFigur_X + 10), (CentrSizeFigur_Y - 0));
		glVertex2f((CentrSizeFigur_X + 11), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 11), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 10), (CentrSizeFigur_Y + 0));

		glEnd();
	}

	bool checkMoveFigures(Board::Cell* cell) {
		if ((CoordinateFigur_X - 1 == cell->CoordinateÑell_X && CoordinateFigur_Y - 2 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X + 1 == cell->CoordinateÑell_X && CoordinateFigur_Y - 2 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X + 2 == cell->CoordinateÑell_X && CoordinateFigur_Y - 1 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X + 2 == cell->CoordinateÑell_X && CoordinateFigur_Y + 1 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X + 1 == cell->CoordinateÑell_X && CoordinateFigur_Y + 2 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X - 1 == cell->CoordinateÑell_X && CoordinateFigur_Y + 2 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X - 2 == cell->CoordinateÑell_X && CoordinateFigur_Y + 1 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X - 2 == cell->CoordinateÑell_X && CoordinateFigur_Y - 1 == cell->CoordinateÑell_Y)) {
			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
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

	virtual ~FigureKnight() {}
};
class FigureBishop : public Figure {
public:
	FigureBishop(Board::Cell* cell, bool command, int scale) :Figure(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((CentrSizeFigur_X), (CentrSizeFigur_Y));
		glVertex2f((CentrSizeFigur_X - 15), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 15), (CentrSizeFigur_Y + 5));
		glVertex2f((CentrSizeFigur_X - 6), (CentrSizeFigur_Y - 0));
		glVertex2f((CentrSizeFigur_X - 2), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X + 2), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X + 6), (CentrSizeFigur_Y - 0));
		glVertex2f((CentrSizeFigur_X + 15), (CentrSizeFigur_Y + 5));
		glVertex2f((CentrSizeFigur_X + 15), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 15), (CentrSizeFigur_Y + 10));

		glEnd();
	}

	bool checkMoveFigures(Board::Cell* cell) {
		if (cell->CoordinateÑell_X - CoordinateFigur_X == cell->CoordinateÑell_Y - CoordinateFigur_Y && cell->CoordinateÑell_X > CoordinateFigur_X && cell->CoordinateÑell_Y > CoordinateFigur_Y) {
			int iy = CoordinateFigur_Y + 1, ix = CoordinateFigur_X + 1;
			while (cell->CoordinateÑell_X > ix && cell->CoordinateÑell_Y > iy) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					return false;
				}
				++iy;
				++ix;
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X - cell->CoordinateÑell_X == CoordinateFigur_Y - cell->CoordinateÑell_Y && cell->CoordinateÑell_X < CoordinateFigur_X && cell->CoordinateÑell_Y < CoordinateFigur_Y) {
			int iy = CoordinateFigur_Y - 1, ix = CoordinateFigur_X - 1;
			while (cell->CoordinateÑell_X < ix && cell->CoordinateÑell_Y < iy) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					return false;
				}
				--iy;
				--ix;
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X - cell->CoordinateÑell_X == cell->CoordinateÑell_Y - CoordinateFigur_Y && cell->CoordinateÑell_X < CoordinateFigur_X && cell->CoordinateÑell_Y > CoordinateFigur_Y) {
			int iy = CoordinateFigur_Y + 1, ix = CoordinateFigur_X - 1;
			while (cell->CoordinateÑell_X < ix && cell->CoordinateÑell_Y > iy) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					return false;
				}
				++iy;
				--ix;
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (cell->CoordinateÑell_X - CoordinateFigur_X == CoordinateFigur_Y - cell->CoordinateÑell_Y && cell->CoordinateÑell_X > CoordinateFigur_X && cell->CoordinateÑell_Y < CoordinateFigur_Y) {
			int iy = CoordinateFigur_Y - 1, ix = CoordinateFigur_X + 1;
			while (cell->CoordinateÑell_X > ix && cell->CoordinateÑell_Y < iy) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					return false;
				}
				--iy;
				++ix;
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
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
	virtual ~FigureBishop() {}
};
class FigureQueen : public Figure {
public:
	FigureQueen(Board::Cell* cell, bool command, int scale) :Figure(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((CentrSizeFigur_X), (CentrSizeFigur_Y));
		glVertex2f((CentrSizeFigur_X - 10), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 17), (CentrSizeFigur_Y - 15));
		glVertex2f((CentrSizeFigur_X - 10), (CentrSizeFigur_Y - 8));
		glVertex2f((CentrSizeFigur_X - 12), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X - 4), (CentrSizeFigur_Y - 12));
		glVertex2f((CentrSizeFigur_X - 1), (CentrSizeFigur_Y - 30));
		glVertex2f((CentrSizeFigur_X + 1), (CentrSizeFigur_Y - 30));
		glVertex2f((CentrSizeFigur_X + 4), (CentrSizeFigur_Y - 12));
		glVertex2f((CentrSizeFigur_X + 12), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X + 10), (CentrSizeFigur_Y - 8));
		glVertex2f((CentrSizeFigur_X + 17), (CentrSizeFigur_Y - 15));
		glVertex2f((CentrSizeFigur_X + 10), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 10), (CentrSizeFigur_Y + 10));

		glEnd();
	}

	bool checkMoveFigures(Board::Cell* cell) {
		if (cell->CoordinateÑell_X - CoordinateFigur_X == cell->CoordinateÑell_Y - CoordinateFigur_Y && cell->CoordinateÑell_X > CoordinateFigur_X && cell->CoordinateÑell_Y > CoordinateFigur_Y) {
			int iy = CoordinateFigur_Y + 1, ix = CoordinateFigur_X + 1;
			while (cell->CoordinateÑell_X > ix && cell->CoordinateÑell_Y > iy) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					return false;
				}
				++iy;
				++ix;
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X - cell->CoordinateÑell_X == CoordinateFigur_Y - cell->CoordinateÑell_Y && cell->CoordinateÑell_X < CoordinateFigur_X && cell->CoordinateÑell_Y < CoordinateFigur_Y) {
			int iy = CoordinateFigur_Y - 1, ix = CoordinateFigur_X - 1;
			while (cell->CoordinateÑell_X < ix && cell->CoordinateÑell_Y < iy) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					return false;
				}
				--iy;
				--ix;
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X - cell->CoordinateÑell_X == cell->CoordinateÑell_Y - CoordinateFigur_Y && cell->CoordinateÑell_X < CoordinateFigur_X && cell->CoordinateÑell_Y > CoordinateFigur_Y) {
			int iy = CoordinateFigur_Y + 1, ix = CoordinateFigur_X - 1;
			while (cell->CoordinateÑell_X < ix && cell->CoordinateÑell_Y > iy) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					return false;
				}
				++iy;
				--ix;
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (cell->CoordinateÑell_X - CoordinateFigur_X == CoordinateFigur_Y - cell->CoordinateÑell_Y && cell->CoordinateÑell_X > CoordinateFigur_X && cell->CoordinateÑell_Y < CoordinateFigur_Y) {
			int iy = CoordinateFigur_Y - 1, ix = CoordinateFigur_X + 1;
			while (cell->CoordinateÑell_X > ix && cell->CoordinateÑell_Y < iy) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					return false;
				}
				--iy;
				++ix;
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X == cell->CoordinateÑell_X && CoordinateFigur_Y > cell->CoordinateÑell_Y) {
			for (int iy = CoordinateFigur_Y - 1; iy > cell->CoordinateÑell_Y; iy--) {
				if (board.getCell(cell->CentrSizeÑell_X, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					return false;
				}
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X < cell->CoordinateÑell_X && CoordinateFigur_Y == cell->CoordinateÑell_Y && (cell->CoordinateÑell_X < cell->scale * 8)) {

			for (int ix = CoordinateFigur_X + 1; ix < cell->CoordinateÑell_X; ix++) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->CentrSizeÑell_Y)->figur != nullptr) {
					return false;
				}
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X == cell->CoordinateÑell_X && CoordinateFigur_Y < cell->CoordinateÑell_Y && (cell->CoordinateÑell_Y < cell->scale * 8)) {
			for (int iy = CoordinateFigur_Y + 1; iy < cell->CoordinateÑell_Y; iy++) {
				if (board.getCell(cell->CentrSizeÑell_X, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
					return false;
				}
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
				return true;
			}
			else {
				return false;
			}
		}
		else if (CoordinateFigur_X > cell->CoordinateÑell_X && CoordinateFigur_Y == cell->CoordinateÑell_Y) {
			for (int ix = CoordinateFigur_X - 1; ix > cell->CoordinateÑell_X; ix--) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->CentrSizeÑell_Y)->figur != nullptr) {
					return false;
				}
			}

			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
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

	virtual ~FigureQueen() {}
};
class FigureKing : public Figure {
public:
	FigureKing(Board::Cell* cell, bool command, int scale) :Figure(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			deathWhiteKing = false;
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			deathBlackKing = false;
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((CentrSizeFigur_X), (CentrSizeFigur_Y));
		glVertex2f((CentrSizeFigur_X - 18), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 18), (CentrSizeFigur_Y + 2));
		glVertex2f((CentrSizeFigur_X - 10), (CentrSizeFigur_Y - 4));
		glVertex2f((CentrSizeFigur_X - 6), (CentrSizeFigur_Y - 20));
		glVertex2f((CentrSizeFigur_X - 6), (CentrSizeFigur_Y - 26));
		glVertex2f((CentrSizeFigur_X - 3), (CentrSizeFigur_Y - 26));
		glVertex2f((CentrSizeFigur_X - 3), (CentrSizeFigur_Y - 30));
		glVertex2f((CentrSizeFigur_X + 3), (CentrSizeFigur_Y - 30));
		glVertex2f((CentrSizeFigur_X + 3), (CentrSizeFigur_Y - 26));
		glVertex2f((CentrSizeFigur_X + 6), (CentrSizeFigur_Y - 26));
		glVertex2f((CentrSizeFigur_X + 6), (CentrSizeFigur_Y - 20));
		glVertex2f((CentrSizeFigur_X + 10), (CentrSizeFigur_Y - 4));
		glVertex2f((CentrSizeFigur_X + 18), (CentrSizeFigur_Y + 2));
		glVertex2f((CentrSizeFigur_X + 18), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 18), (CentrSizeFigur_Y + 10));
		glEnd();

		if (teamColor) {
			glColor3f(0.0, 0.0, 0.0);
		}
		else {
			glColor3f(1.0, 1.0, 1.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((CentrSizeFigur_X - 0), (CentrSizeFigur_Y - 22));
		glVertex2f((CentrSizeFigur_X - 2), (CentrSizeFigur_Y - 29));
		glVertex2f((CentrSizeFigur_X - 2), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X - 5), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X - 5), (CentrSizeFigur_Y - 21));
		glVertex2f((CentrSizeFigur_X - 2), (CentrSizeFigur_Y - 21));
		glVertex2f((CentrSizeFigur_X - 2), (CentrSizeFigur_Y - 18));
		glVertex2f((CentrSizeFigur_X + 2), (CentrSizeFigur_Y - 18));
		glVertex2f((CentrSizeFigur_X + 2), (CentrSizeFigur_Y - 21));
		glVertex2f((CentrSizeFigur_X + 5), (CentrSizeFigur_Y - 21));
		glVertex2f((CentrSizeFigur_X + 5), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X + 2), (CentrSizeFigur_Y - 25));
		glVertex2f((CentrSizeFigur_X + 2), (CentrSizeFigur_Y - 29));
		glVertex2f((CentrSizeFigur_X - 2), (CentrSizeFigur_Y - 29));
		glEnd();
	}

	bool checkMoveFigures(Board::Cell* cell) {
		if ((CoordinateFigur_X - 1 == cell->CoordinateÑell_X && CoordinateFigur_Y - 1 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X == cell->CoordinateÑell_X && CoordinateFigur_Y - 1 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X + 1 == cell->CoordinateÑell_X && CoordinateFigur_Y - 1 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X + 1 == cell->CoordinateÑell_X && CoordinateFigur_Y == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X + 1 == cell->CoordinateÑell_X && CoordinateFigur_Y + 1 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X == cell->CoordinateÑell_X && CoordinateFigur_Y + 1 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X - 1 == cell->CoordinateÑell_X && CoordinateFigur_Y + 1 == cell->CoordinateÑell_Y) ||
			(CoordinateFigur_X - 1 == cell->CoordinateÑell_X && CoordinateFigur_Y == cell->CoordinateÑell_Y)) {
			if (cell->figur == nullptr) {
				this->muveFigure(cell);
				return true;
			}
			else if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
				this->figureAttack(cell);
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

	virtual ~FigureKing() {}
};
class FigurePawn : public Figure {
public:

	FigurePawn(Board::Cell* cell, bool command, int scale) :Figure(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((CentrSizeFigur_X), (CentrSizeFigur_Y));
		glVertex2f((CentrSizeFigur_X - 10), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 10), (CentrSizeFigur_Y + 0));
		glVertex2f((CentrSizeFigur_X - 5), (CentrSizeFigur_Y - 22));
		glVertex2f((CentrSizeFigur_X + 5), (CentrSizeFigur_Y - 22));
		glVertex2f((CentrSizeFigur_X + 10), (CentrSizeFigur_Y + 0));
		glVertex2f((CentrSizeFigur_X + 10), (CentrSizeFigur_Y + 10));
		glVertex2f((CentrSizeFigur_X - 10), (CentrSizeFigur_Y + 10));

		glEnd();
	}

	bool checkMoveFigures(Board::Cell* cell) {
		if (teamColor) {
			if (CoordinateFigur_Y + 1 == cell->CoordinateÑell_Y && CoordinateFigur_X == cell->CoordinateÑell_X) {
				if (cell->figur == nullptr) {
					this->muveFigure(cell);
					if (cell->CoordinateÑell_Y == 7) {
						pawnToQueen = true;
					}
					firstMovePawn = false;
					return true;
				}
				else {
					return false;
				}
			}
			else if (CoordinateFigur_Y + 2 == cell->CoordinateÑell_Y && firstMovePawn == true && CoordinateFigur_X == cell->CoordinateÑell_X) {
				if (cell->figur == nullptr) {
					if (board.getCell(cell->CentrSizeÑell_X, cell->CentrSizeÑell_Y - cell->scale)->figur != nullptr) {
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
			else if (CoordinateFigur_Y + 1 == cell->CoordinateÑell_Y && (CoordinateFigur_X + 1 == cell->CoordinateÑell_X || CoordinateFigur_X - 1 == cell->CoordinateÑell_X)) {
				if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
					this->figureAttack(cell);
					if (cell->CoordinateÑell_Y == 7) {
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
			if (CoordinateFigur_Y - 1 == cell->CoordinateÑell_Y && CoordinateFigur_X == cell->CoordinateÑell_X) {
				if (cell->figur == nullptr) {
					this->muveFigure(cell);
					if (cell->CoordinateÑell_Y == 0) {
						pawnToQueen = true;
					}
					firstMovePawn = false;
					return true;
				}
				else {
					return false;
				}
			}
			else if (CoordinateFigur_Y - 2 == cell->CoordinateÑell_Y && firstMovePawn == true && CoordinateFigur_X == cell->CoordinateÑell_X) {
				if (cell->figur == nullptr) {
					if (board.getCell(cell->CentrSizeÑell_X, cell->CentrSizeÑell_Y + cell->scale)->figur != nullptr) {
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
			else if (CoordinateFigur_Y - 1 == cell->CoordinateÑell_Y && (CoordinateFigur_X + 1 == cell->CoordinateÑell_X || CoordinateFigur_X - 1 == cell->CoordinateÑell_X)) {
				if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
					this->figureAttack(cell);
					if (cell->CoordinateÑell_Y == 0) {
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
	}

	bool firstMovePawn = true;
};

void convertToQueen(Board::Cell* cell) {
	bool curCommand = cell->figur->teamColor;
	for (vector<Figure*>::const_iterator iter = figurs.begin(); iter != figurs.end(); iter++) {
		if (*iter == cell->figur) {
			figurs.erase(iter);
			break;
		}
	}
	delete cell->figur;
	cell->figur = nullptr;
	figurs.push_back(new FigureQueen(cell, curCommand, cell->scale));
	pawnToQueen = false;
}

void drawFigure() {
	for (int i = 0; i < figurs.size(); i++) {
		(*figurs[i]).drawFigurPawn();
	}
}
void createFigure() {
	figurs.push_back(new FigureRook(&(board.cells[0]), true, board.scale));
	figurs.push_back(new FigureRook(&(board.cells[7]), true, board.scale));
	figurs.push_back(new FigureKnight(&(board.cells[1]), true, board.scale));
	figurs.push_back(new FigureKnight(&(board.cells[6]), true, board.scale));
	figurs.push_back(new FigureBishop(&(board.cells[2]), true, board.scale));
	figurs.push_back(new FigureBishop(&(board.cells[5]), true, board.scale));
	figurs.push_back(new FigureKing(&(board.cells[3]), true, board.scale));
	figurs.push_back(new FigureQueen(&(board.cells[4]), true, board.scale));

	for (int i = 8; i < 16; i++) {
		figurs.push_back(new FigurePawn(&(board.cells[i]), true, board.scale));
	}

	for (int i = 48; i < 56; i++) {
		figurs.push_back(new FigurePawn(&(board.cells[i]), false, board.scale));
	}
	figurs.push_back(new FigureRook(&(board.cells[56]), false, board.scale));
	figurs.push_back(new FigureRook(&(board.cells[63]), false, board.scale));
	figurs.push_back(new FigureKnight(&(board.cells[57]), false, board.scale));
	figurs.push_back(new FigureKnight(&(board.cells[62]), false, board.scale));
	figurs.push_back(new FigureBishop(&(board.cells[58]), false, board.scale));
	figurs.push_back(new FigureBishop(&(board.cells[61]), false, board.scale));
	figurs.push_back(new FigureKing(&(board.cells[59]), false, board.scale));
	figurs.push_back(new FigureQueen(&(board.cells[60]), false, board.scale));
}

void movementFigure(bool team) {
	if (afm.g_state == 1) {
		afm.prev_cell_r = board.getCell(afm.g_x, afm.g_y);
		if (afm.prev_cell_r->figur != nullptr && afm.prev_cell_r->figur->teamColor == team) {
			afm.figure_r = afm.prev_cell_r->figur;
			afm.prev_cell_r->colorGetCell(BLUE);
		}
		else if (afm.prev_cell_r->figur != nullptr) {
			afm.prev_cell_r->colorGetCell(RED);
			afm.g_state = 0;
		}
		else {
			afm.prev_cell_r->colorGetCell(WHITE);
			afm.g_state = 0;
		}
	}
	if (afm.g_state == 2) {
		if (afm.g_x < 0 || afm.g_y < 0 || afm.g_x > Scale * 8 || afm.g_x > Scale * 8) {
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
				afm.prev_cell_r->figur = nullptr;
				afm.nullData();
				teamMove = !team;
			}
			else {
				afm.cell_r->colorGetCell(RED);
				afm.nullData();
			}
		}
	}
}

void game() {

	glClear(GL_COLOR_BUFFER_BIT);

	deathWhiteKing = true;
	deathBlackKing = true;

	board.drawBoard();
	drawFigure();

	if (teamMove) {
		movementFigure(true);
	}
	else {
		movementFigure(false);
	}

	glFlush();
}

void timer(int = 0) {

	game();

	if (deathWhiteKing == true || deathBlackKing == true) {
		if (deathWhiteKing == true) {
			glColor3f(0.1, 0.1, 0.1);
		}
		else {
			glColor3f(0.9, 0.9, 0.9);
		}
		glRectf(0, 0, 6, L);
		glRectf(0, 0, L, 6);
		glRectf(0, L - 6, L, L);
		glRectf(L - 6, 0, L, L);
		glFlush();
		return;
	}

	glutTimerFunc(100, timer, 0);
}

void MousePressed(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		afm.g_state = 1;
		afm.g_x = x;
		afm.g_y = y;
	}
	else {
		if (afm.g_state != 0) {
			afm.g_state = 2;
			afm.g_x = x;
			afm.g_y = y;
		}
	}
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(L, L);
	glutCreateWindow("MyChess");
	glClearColor(0.8, 0.6, 0.4, 0.0);

	glLoadIdentity();
	glutMouseFunc(MousePressed);
	gluOrtho2D(0, L, L, 0);

	glutTimerFunc(20, timer, 0);

	createFigure();

	glutDisplayFunc(game);
	glutMainLoop();
}