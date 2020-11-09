#include <iostream>
#include <glut.h>
#include <vector>
using namespace std;

bool teamMove = true;
bool pawnToQueen = false;
bool deathWhiteKing = false;
bool deathBlackKing = false;

class Figur;
enum CellColor {
	GREEN, RED, BLUE, WHITE
};
class Board {
public:
	class Ñell;
	Board(int scale) {
		this->scale = scale;
		bool colorCall = false;
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				this->cells.push_back(Ñell(x * scale, y * scale, x, y, getOtherColorCall(colorCall), scale));
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

	Ñell* getCell(int x, int y) {
		for (int i = 0; i < 64; i++) {
			if (x / scale == cells[i].coordinateCell_X && y / scale == cells[i].coordinateCell_Y) {
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
			glRectf(cells[i].sizeCell_X, cells[i].sizeCell_Y, cells[i].sizeCell_X + scale, cells[i].sizeCell_Y + scale);
		}
	}

	class Ñell {
	public:
		Ñell(const int xSize, const int ySize, int x, int y, bool color, int scale) {
			this->sizeCell_X = xSize;
			this->sizeCell_Y = ySize;
			this->centrSizeCell_X = this->sizeCell_X + scale / 2;
			this->centrSizeCell_Y = this->sizeCell_Y + scale / 2;
			coordinateCell_X = x;
			coordinateCell_Y = y;
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

			glRectf(sizeCell_X, sizeCell_Y, sizeCell_X + 2, sizeCell_Y + scale);
			glRectf(sizeCell_X, sizeCell_Y + scale - 2, sizeCell_X + scale, sizeCell_Y + scale);
			glRectf(sizeCell_X + scale - 2, sizeCell_Y, sizeCell_X + scale, sizeCell_Y + scale);
			glRectf(sizeCell_X, sizeCell_Y, sizeCell_X + scale, sizeCell_Y + 2);
		}

		int coordinateCell_X;
		int coordinateCell_Y;
		int sizeCell_X;
		int sizeCell_Y;
		int centrSizeCell_X;
		int centrSizeCell_Y;
		bool color = true;
		int scale;
		Figur* figur = nullptr;
	};
	vector<Ñell> cells;
	unsigned int scale;

}board(64);

vector<Figur*> figurs;
struct activFigureMouse {
	int g_state;
	float g_x = 0.0;
	float g_y = 0.0;
	Figur* figure_r = nullptr;
	Board::Ñell* cell_r = nullptr;
	Board::Ñell* prev_cell_r = nullptr;

	void nullData() {
		prev_cell_r = nullptr;
		cell_r = nullptr;
		figure_r = nullptr;
		g_x = 0;
		g_y = 0;
		g_state = 0;
	}
} afm;

class Figur {
public:
	Figur(Board::Ñell* cell, bool command, int scale) {
		this->teamColor = command;
		cell->figur = this;
		centrSizeFigur_X = cell->centrSizeCell_X;
		centrSizeFigur_Y = cell->centrSizeCell_Y;
		coordinateFigur_X = cell->coordinateCell_X;
		coordinateFigur_Y = cell->coordinateCell_Y;
	}

	virtual void drawFigurPawn() = 0;
	virtual bool checkMoveFigures(Board::Ñell* cell) = 0;

	void muveFigure(Board::Ñell* cell) {
		centrSizeFigur_X = cell->centrSizeCell_X;
		centrSizeFigur_Y = cell->centrSizeCell_Y;
		coordinateFigur_X = cell->coordinateCell_X;
		coordinateFigur_Y = cell->coordinateCell_Y;
		cell->figur = this;
	}

	void figureAttack(Board::Ñell* cell) {

		for (vector<Figur*>::const_iterator iter = figurs.begin(); iter != figurs.end(); iter++) {
			if (*iter == cell->figur) {
				figurs.erase(iter);
				break;
			}
		}

		cell->figur = this;
		this->muveFigure(cell);
	}

	virtual ~Figur() {}

	int coordinateFigur_X;
	int coordinateFigur_Y;
	int centrSizeFigur_X;
	int centrSizeFigur_Y;
	bool teamColor;
	bool active = true;
};
class FigurRook : public Figur {
public:
	FigurRook(Board::Ñell* cell, bool command, int scale) :Figur(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((centrSizeFigur_X), (centrSizeFigur_Y));
		glVertex2f((centrSizeFigur_X - 11), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 11), (centrSizeFigur_Y - 10));
		glVertex2f((centrSizeFigur_X - 15), (centrSizeFigur_Y - 20));
		glVertex2f((centrSizeFigur_X - 15), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X - 8), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X - 8), (centrSizeFigur_Y - 20));
		glVertex2f((centrSizeFigur_X - 4), (centrSizeFigur_Y - 20));
		glVertex2f((centrSizeFigur_X - 4), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X + 4), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X + 4), (centrSizeFigur_Y - 20));
		glVertex2f((centrSizeFigur_X + 8), (centrSizeFigur_Y - 20));
		glVertex2f((centrSizeFigur_X + 8), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X + 15), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X + 15), (centrSizeFigur_Y - 20));
		glVertex2f((centrSizeFigur_X + 11), (centrSizeFigur_Y - 10));
		glVertex2f((centrSizeFigur_X + 11), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 11), (centrSizeFigur_Y + 10));
		glEnd();
	}

	bool checkMoveFigures(Board::Ñell* cell) {
		if (coordinateFigur_X == cell->coordinateCell_X && coordinateFigur_Y > cell->coordinateCell_Y) {
			for (int iy = coordinateFigur_Y - 1; iy > cell->coordinateCell_Y; iy--) {
				if (board.getCell(cell->centrSizeCell_X, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
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
		else if (coordinateFigur_X < cell->coordinateCell_X && coordinateFigur_Y == cell->coordinateCell_Y && (cell->coordinateCell_X < cell->scale * 8)) {

			for (int ix = coordinateFigur_X + 1; ix < cell->coordinateCell_X; ix++) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->centrSizeCell_Y)->figur != nullptr) {
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
		else if (coordinateFigur_X == cell->coordinateCell_X && coordinateFigur_Y < cell->coordinateCell_Y && (cell->coordinateCell_Y < cell->scale * 8)) {
			for (int iy = coordinateFigur_Y + 1; iy < cell->coordinateCell_Y; iy++) {
				if (board.getCell(cell->centrSizeCell_X, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
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
		else if (coordinateFigur_X > cell->coordinateCell_X && coordinateFigur_Y == cell->coordinateCell_Y) {
			for (int ix = coordinateFigur_X - 1; ix > cell->coordinateCell_X; ix--) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->centrSizeCell_Y)->figur != nullptr) {
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

	virtual ~FigurRook() {}
};
class FigurKnight : public Figur {
public:
	FigurKnight(Board::Ñell* cell, bool command, int scale) :Figur(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((centrSizeFigur_X - 0), (centrSizeFigur_Y - 12));
		glVertex2f((centrSizeFigur_X - 12), (centrSizeFigur_Y - 8));
		glVertex2f((centrSizeFigur_X - 10), (centrSizeFigur_Y - 20));
		glVertex2f((centrSizeFigur_X - 0), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X + 10), (centrSizeFigur_Y - 20));
		glVertex2f((centrSizeFigur_X + 12), (centrSizeFigur_Y - 10));
		glVertex2f((centrSizeFigur_X + 10), (centrSizeFigur_Y - 0));
		glVertex2f((centrSizeFigur_X + 11), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 11), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 10), (centrSizeFigur_Y + 0));

		glEnd();
	}

	bool checkMoveFigures(Board::Ñell* cell) {
		if ((coordinateFigur_X - 1 == cell->coordinateCell_X && coordinateFigur_Y - 2 == cell->coordinateCell_Y) ||
			(coordinateFigur_X + 1 == cell->coordinateCell_X && coordinateFigur_Y - 2 == cell->coordinateCell_Y) ||
			(coordinateFigur_X + 2 == cell->coordinateCell_X && coordinateFigur_Y - 1 == cell->coordinateCell_Y) ||
			(coordinateFigur_X + 2 == cell->coordinateCell_X && coordinateFigur_Y + 1 == cell->coordinateCell_Y) ||
			(coordinateFigur_X + 1 == cell->coordinateCell_X && coordinateFigur_Y + 2 == cell->coordinateCell_Y) ||
			(coordinateFigur_X - 1 == cell->coordinateCell_X && coordinateFigur_Y + 2 == cell->coordinateCell_Y) ||
			(coordinateFigur_X - 2 == cell->coordinateCell_X && coordinateFigur_Y + 1 == cell->coordinateCell_Y) ||
			(coordinateFigur_X - 2 == cell->coordinateCell_X && coordinateFigur_Y - 1 == cell->coordinateCell_Y)) {
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

	virtual ~FigurKnight() {}
};
class FigurBishop : public Figur {
public:
	FigurBishop(Board::Ñell* cell, bool command, int scale) :Figur(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((centrSizeFigur_X), (centrSizeFigur_Y));
		glVertex2f((centrSizeFigur_X - 15), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 15), (centrSizeFigur_Y + 5));
		glVertex2f((centrSizeFigur_X - 6), (centrSizeFigur_Y - 0));
		glVertex2f((centrSizeFigur_X - 2), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X + 2), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X + 6), (centrSizeFigur_Y - 0));
		glVertex2f((centrSizeFigur_X + 15), (centrSizeFigur_Y + 5));
		glVertex2f((centrSizeFigur_X + 15), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 15), (centrSizeFigur_Y + 10));

		glEnd();
	}

	bool checkMoveFigures(Board::Ñell* cell) {
		if (cell->coordinateCell_X - coordinateFigur_X == cell->coordinateCell_Y - coordinateFigur_Y && cell->coordinateCell_X > coordinateFigur_X && cell->coordinateCell_Y > coordinateFigur_Y) {
			int iy = coordinateFigur_Y + 1, ix = coordinateFigur_X + 1;
			while (cell->coordinateCell_X > ix && cell->coordinateCell_Y > iy) {
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
		else if (coordinateFigur_X - cell->coordinateCell_X == coordinateFigur_Y - cell->coordinateCell_Y && cell->coordinateCell_X < coordinateFigur_X && cell->coordinateCell_Y < coordinateFigur_Y) {
			int iy = coordinateFigur_Y - 1, ix = coordinateFigur_X - 1;
			while (cell->coordinateCell_X < ix && cell->coordinateCell_Y < iy) {
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
		else if (coordinateFigur_X - cell->coordinateCell_X == cell->coordinateCell_Y - coordinateFigur_Y && cell->coordinateCell_X < coordinateFigur_X && cell->coordinateCell_Y > coordinateFigur_Y) {
			int iy = coordinateFigur_Y + 1, ix = coordinateFigur_X - 1;
			while (cell->coordinateCell_X < ix && cell->coordinateCell_Y > iy) {
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
		else if (cell->coordinateCell_X - coordinateFigur_X == coordinateFigur_Y - cell->coordinateCell_Y && cell->coordinateCell_X > coordinateFigur_X && cell->coordinateCell_Y < coordinateFigur_Y) {
			int iy = coordinateFigur_Y - 1, ix = coordinateFigur_X + 1;
			while (cell->coordinateCell_X > ix && cell->coordinateCell_Y < iy) {
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
	virtual ~FigurBishop() {}
};
class FigurQueen : public Figur {
public:
	FigurQueen(Board::Ñell* cell, bool command, int scale) :Figur(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((centrSizeFigur_X), (centrSizeFigur_Y));
		glVertex2f((centrSizeFigur_X - 10), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 17), (centrSizeFigur_Y - 15));
		glVertex2f((centrSizeFigur_X - 10), (centrSizeFigur_Y - 8));
		glVertex2f((centrSizeFigur_X - 12), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X - 4), (centrSizeFigur_Y - 12));
		glVertex2f((centrSizeFigur_X - 1), (centrSizeFigur_Y - 30));
		glVertex2f((centrSizeFigur_X + 1), (centrSizeFigur_Y - 30));
		glVertex2f((centrSizeFigur_X + 4), (centrSizeFigur_Y - 12));
		glVertex2f((centrSizeFigur_X + 12), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X + 10), (centrSizeFigur_Y - 8));
		glVertex2f((centrSizeFigur_X + 17), (centrSizeFigur_Y - 15));
		glVertex2f((centrSizeFigur_X + 10), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 10), (centrSizeFigur_Y + 10));

		glEnd();
	}

	bool checkMoveFigures(Board::Ñell* cell) {
		if (cell->coordinateCell_X - coordinateFigur_X == cell->coordinateCell_Y - coordinateFigur_Y && cell->coordinateCell_X > coordinateFigur_X && cell->coordinateCell_Y > coordinateFigur_Y) {
			int iy = coordinateFigur_Y + 1, ix = coordinateFigur_X + 1;
			while (cell->coordinateCell_X > ix && cell->coordinateCell_Y > iy) {
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
		else if (coordinateFigur_X - cell->coordinateCell_X == coordinateFigur_Y - cell->coordinateCell_Y && cell->coordinateCell_X < coordinateFigur_X && cell->coordinateCell_Y < coordinateFigur_Y) {
			int iy = coordinateFigur_Y - 1, ix = coordinateFigur_X - 1;
			while (cell->coordinateCell_X < ix && cell->coordinateCell_Y < iy) {
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
		else if (coordinateFigur_X - cell->coordinateCell_X == cell->coordinateCell_Y - coordinateFigur_Y && cell->coordinateCell_X < coordinateFigur_X && cell->coordinateCell_Y > coordinateFigur_Y) {
			int iy = coordinateFigur_Y + 1, ix = coordinateFigur_X - 1;
			while (cell->coordinateCell_X < ix && cell->coordinateCell_Y > iy) {
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
		else if (cell->coordinateCell_X - coordinateFigur_X == coordinateFigur_Y - cell->coordinateCell_Y && cell->coordinateCell_X > coordinateFigur_X && cell->coordinateCell_Y < coordinateFigur_Y) {
			int iy = coordinateFigur_Y - 1, ix = coordinateFigur_X + 1;
			while (cell->coordinateCell_X > ix && cell->coordinateCell_Y < iy) {
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
		else if (coordinateFigur_X == cell->coordinateCell_X && coordinateFigur_Y > cell->coordinateCell_Y) {
			for (int iy = coordinateFigur_Y - 1; iy > cell->coordinateCell_Y; iy--) {
				if (board.getCell(cell->centrSizeCell_X, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
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
		else if (coordinateFigur_X < cell->coordinateCell_X && coordinateFigur_Y == cell->coordinateCell_Y && (cell->coordinateCell_X < cell->scale * 8)) {

			for (int ix = coordinateFigur_X + 1; ix < cell->coordinateCell_X; ix++) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->centrSizeCell_Y)->figur != nullptr) {
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
		else if (coordinateFigur_X == cell->coordinateCell_X && coordinateFigur_Y < cell->coordinateCell_Y && (cell->coordinateCell_Y < cell->scale * 8)) {
			for (int iy = coordinateFigur_Y + 1; iy < cell->coordinateCell_Y; iy++) {
				if (board.getCell(cell->centrSizeCell_X, cell->scale*iy + cell->scale / 2)->figur != nullptr) {
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
		else if (coordinateFigur_X > cell->coordinateCell_X && coordinateFigur_Y == cell->coordinateCell_Y) {
			for (int ix = coordinateFigur_X - 1; ix > cell->coordinateCell_X; ix--) {
				if (board.getCell(cell->scale*ix + cell->scale / 2, cell->centrSizeCell_Y)->figur != nullptr) {
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

	virtual ~FigurQueen() {}
};
class FigurKing : public Figur {
public:
	FigurKing(Board::Ñell* cell, bool command, int scale) :Figur(cell, command, scale) {}

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
		glVertex2f((centrSizeFigur_X), (centrSizeFigur_Y));
		glVertex2f((centrSizeFigur_X - 18), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 18), (centrSizeFigur_Y + 2));
		glVertex2f((centrSizeFigur_X - 10), (centrSizeFigur_Y - 4));
		glVertex2f((centrSizeFigur_X - 6), (centrSizeFigur_Y - 20));
		glVertex2f((centrSizeFigur_X - 6), (centrSizeFigur_Y - 26));
		glVertex2f((centrSizeFigur_X - 3), (centrSizeFigur_Y - 26));
		glVertex2f((centrSizeFigur_X - 3), (centrSizeFigur_Y - 30));
		glVertex2f((centrSizeFigur_X + 3), (centrSizeFigur_Y - 30));
		glVertex2f((centrSizeFigur_X + 3), (centrSizeFigur_Y - 26));
		glVertex2f((centrSizeFigur_X + 6), (centrSizeFigur_Y - 26));
		glVertex2f((centrSizeFigur_X + 6), (centrSizeFigur_Y - 20));
		glVertex2f((centrSizeFigur_X + 10), (centrSizeFigur_Y - 4));
		glVertex2f((centrSizeFigur_X + 18), (centrSizeFigur_Y + 2));
		glVertex2f((centrSizeFigur_X + 18), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 18), (centrSizeFigur_Y + 10));
		glEnd();

		if (teamColor) {
			glColor3f(0.0, 0.0, 0.0);
		}
		else {
			glColor3f(1.0, 1.0, 1.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((centrSizeFigur_X - 0), (centrSizeFigur_Y - 22));
		glVertex2f((centrSizeFigur_X - 2), (centrSizeFigur_Y - 29));
		glVertex2f((centrSizeFigur_X - 2), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X - 5), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X - 5), (centrSizeFigur_Y - 21));
		glVertex2f((centrSizeFigur_X - 2), (centrSizeFigur_Y - 21));
		glVertex2f((centrSizeFigur_X - 2), (centrSizeFigur_Y - 18));
		glVertex2f((centrSizeFigur_X + 2), (centrSizeFigur_Y - 18));
		glVertex2f((centrSizeFigur_X + 2), (centrSizeFigur_Y - 21));
		glVertex2f((centrSizeFigur_X + 5), (centrSizeFigur_Y - 21));
		glVertex2f((centrSizeFigur_X + 5), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X + 2), (centrSizeFigur_Y - 25));
		glVertex2f((centrSizeFigur_X + 2), (centrSizeFigur_Y - 29));
		glVertex2f((centrSizeFigur_X - 2), (centrSizeFigur_Y - 29));
		glEnd();
	}

	bool checkMoveFigures(Board::Ñell* cell) {
		if ((coordinateFigur_X - 1 == cell->coordinateCell_X && coordinateFigur_Y - 1 == cell->coordinateCell_Y) ||
			(coordinateFigur_X == cell->coordinateCell_X && coordinateFigur_Y - 1 == cell->coordinateCell_Y) ||
			(coordinateFigur_X + 1 == cell->coordinateCell_X && coordinateFigur_Y - 1 == cell->coordinateCell_Y) ||
			(coordinateFigur_X + 1 == cell->coordinateCell_X && coordinateFigur_Y == cell->coordinateCell_Y) ||
			(coordinateFigur_X + 1 == cell->coordinateCell_X && coordinateFigur_Y + 1 == cell->coordinateCell_Y) ||
			(coordinateFigur_X == cell->coordinateCell_X && coordinateFigur_Y + 1 == cell->coordinateCell_Y) ||
			(coordinateFigur_X - 1 == cell->coordinateCell_X && coordinateFigur_Y + 1 == cell->coordinateCell_Y) ||
			(coordinateFigur_X - 1 == cell->coordinateCell_X && coordinateFigur_Y == cell->coordinateCell_Y)) {
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

	virtual ~FigurKing() {}
};
class FigurPawn : public Figur {
public:

	FigurPawn(Board::Ñell* cell, bool command, int scale) :Figur(cell, command, scale) {}

	void drawFigurPawn() {
		if (teamColor) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((centrSizeFigur_X), (centrSizeFigur_Y));
		glVertex2f((centrSizeFigur_X - 10), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 10), (centrSizeFigur_Y + 0));
		glVertex2f((centrSizeFigur_X - 5), (centrSizeFigur_Y - 22));
		glVertex2f((centrSizeFigur_X + 5), (centrSizeFigur_Y - 22));
		glVertex2f((centrSizeFigur_X + 10), (centrSizeFigur_Y + 0));
		glVertex2f((centrSizeFigur_X + 10), (centrSizeFigur_Y + 10));
		glVertex2f((centrSizeFigur_X - 10), (centrSizeFigur_Y + 10));

		glEnd();
	}

	bool checkMoveFigures(Board::Ñell* cell) {
		if (teamColor) {
			if (coordinateFigur_Y + 1 == cell->coordinateCell_Y && coordinateFigur_X == cell->coordinateCell_X) {
				if (cell->figur == nullptr) {
					this->muveFigure(cell);
					if (cell->coordinateCell_Y == 7) {
						pawnToQueen = true;
					}
					firstMovePawn = false;
					return true;
				}
				else {
					return false;
				}
			}
			else if (coordinateFigur_Y + 2 == cell->coordinateCell_Y && firstMovePawn == true && coordinateFigur_X == cell->coordinateCell_X) {
				if (cell->figur == nullptr) {
					if (board.getCell(cell->centrSizeCell_X, cell->centrSizeCell_Y - cell->scale)->figur != nullptr) {
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
			else if (coordinateFigur_Y + 1 == cell->coordinateCell_Y && (coordinateFigur_X + 1 == cell->coordinateCell_X || coordinateFigur_X - 1 == cell->coordinateCell_X)) {
				if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
					this->figureAttack(cell);
					if (cell->coordinateCell_Y == 7) {
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
			if (coordinateFigur_Y - 1 == cell->coordinateCell_Y && coordinateFigur_X == cell->coordinateCell_X) {
				if (cell->figur == nullptr) {
					this->muveFigure(cell);
					if (cell->coordinateCell_Y == 0) {
						pawnToQueen = true;
					}
					firstMovePawn = false;
					return true;
				}
				else {
					return false;
				}
			}
			else if (coordinateFigur_Y - 2 == cell->coordinateCell_Y && firstMovePawn == true && coordinateFigur_X == cell->coordinateCell_X) {
				if (cell->figur == nullptr) {
					if (board.getCell(cell->centrSizeCell_X, cell->centrSizeCell_Y + cell->scale)->figur != nullptr) {
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
			else if (coordinateFigur_Y - 1 == cell->coordinateCell_Y && (coordinateFigur_X + 1 == cell->coordinateCell_X || coordinateFigur_X - 1 == cell->coordinateCell_X)) {
				if (cell->figur != nullptr && cell->figur->teamColor != this->teamColor) {
					this->figureAttack(cell);
					if (cell->coordinateCell_Y == 0) {
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

void convertToQueen(Board::Ñell* cell) {
	bool curCommand = cell->figur->teamColor;
	for (vector<Figur*>::const_iterator iter = figurs.begin(); iter != figurs.end(); iter++) {
		if (*iter == cell->figur) {
			figurs.erase(iter);
			break;
		}
	}
	delete cell->figur;
	cell->figur = nullptr;
	figurs.push_back(new FigurQueen(cell, curCommand, cell->scale));
	pawnToQueen = false;
}

void drawFigure() {
	for (int i = 0; i < figurs.size(); i++) {
		(*figurs[i]).drawFigurPawn();
	}
}
void createFigure() {
	figurs.push_back(new FigurRook(&(board.cells[0]), true, board.scale));
	figurs.push_back(new FigurRook(&(board.cells[7]), true, board.scale));
	figurs.push_back(new FigurKnight(&(board.cells[1]), true, board.scale));
	figurs.push_back(new FigurKnight(&(board.cells[6]), true, board.scale));
	figurs.push_back(new FigurBishop(&(board.cells[2]), true, board.scale));
	figurs.push_back(new FigurBishop(&(board.cells[5]), true, board.scale));
	figurs.push_back(new FigurKing(&(board.cells[3]), true, board.scale));
	figurs.push_back(new FigurQueen(&(board.cells[4]), true, board.scale));

	for (int i = 8; i < 16; i++) {
		figurs.push_back(new FigurPawn(&(board.cells[i]), true, board.scale));
	}

	for (int i = 48; i < 56; i++) {
		figurs.push_back(new FigurPawn(&(board.cells[i]), false, board.scale));
	}
	figurs.push_back(new FigurRook(&(board.cells[56]), false, board.scale));
	figurs.push_back(new FigurRook(&(board.cells[63]), false, board.scale));
	figurs.push_back(new FigurKnight(&(board.cells[57]), false, board.scale));
	figurs.push_back(new FigurKnight(&(board.cells[62]), false, board.scale));
	figurs.push_back(new FigurBishop(&(board.cells[58]), false, board.scale));
	figurs.push_back(new FigurBishop(&(board.cells[61]), false, board.scale));
	figurs.push_back(new FigurKing(&(board.cells[59]), false, board.scale));
	figurs.push_back(new FigurQueen(&(board.cells[60]), false, board.scale));
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
		if (afm.g_x < 0 || afm.g_y < 0 || afm.g_x > board.scale * 8 || afm.g_x > board.scale * 8) {
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

	//î÷åðåäü êîìàíäû
	if (teamMove) {
		movementFigure(true);
	}
	else {
		movementFigure(false);
	}

	glFlush();
}

//öûêë ïðîãðàììû
void timer(int = 0) {

	game();

	if (deathWhiteKing == true || deathBlackKing == true) {
		if (deathWhiteKing == true) {
			glColor3f(0.1, 0.1, 0.1);
		}
		else {
			glColor3f(0.9, 0.9, 0.9);
		}
		glRectf(0, 0, 6, board.scale * 8);
		glRectf(0, 0, board.scale * 8, 6);
		glRectf(0, board.scale * 8 - 6, board.scale * 8, board.scale * 8);
		glRectf(board.scale * 8 - 6, 0, board.scale * 8, board.scale * 8);
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
	glutInitWindowSize(board.scale * 8, board.scale * 8);
	glutCreateWindow("MyChess");
	glClearColor(0.8, 0.6, 0.4, 0.0);

	glLoadIdentity();
	glutMouseFunc(MousePressed);
	gluOrtho2D(0, board.scale * 8, board.scale * 8, 0);

	glutTimerFunc(20, timer, 0);

	createFigure();

	glutDisplayFunc(game);
	glutMainLoop();
}
