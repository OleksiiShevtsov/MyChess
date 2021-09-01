#include <iostream>
#include <glut.h>

#include "game.h"

int main(int argc, char **argv) {

	Game gameOnChess(100);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(gameOnChess.getBoard()->getScale() * 8, gameOnChess.getBoard()->getScale() * 8);
	glutCreateWindow("MyChess");
	glClearColor(0.8, 0.6, 0.4, 0.0);

	glLoadIdentity();
	glutMouseFunc(Game::mouseClick);
	gluOrtho2D(0, gameOnChess.getBoard()->getScale() * 8, gameOnChess.getBoard()->getScale() * 8, 0);

	glutTimerFunc(20, Game::timer, 0);

	gameOnChess.createFigure();

	glutDisplayFunc(Game::game);
	glutMainLoop();
}
