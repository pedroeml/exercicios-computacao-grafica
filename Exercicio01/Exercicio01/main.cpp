#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

GLfloat translacaoX, translacaoY, panX, panY, lft, rgt, bottom, top;

/**
*	Desenha os eixos x e y
*/
void drawAxis() {
	glColor3f(1, 1, 1);
	glLineWidth(1);

	glBegin(GL_LINES);
	glVertex2f(lft + panX, 0.0);
	glVertex2f(rgt + panX, 0.0);
	glVertex2f(0.0, bottom + panY);
	glVertex2f(0.0, top + panY);
	glEnd();
}

/**
 *	Desenha um quadrado dado o comprimento da aresta
 */
void drawSquare(float edge_length) {
	float half_edge = edge_length / 2.0;
	glBegin(GL_LINES);
	glVertex3f(-half_edge, -half_edge, 0);
	glVertex3f(-half_edge, half_edge, 0);
	glVertex3f(half_edge, -half_edge, 0);
	glVertex3f(half_edge, half_edge, 0);
	glVertex3f(-half_edge, half_edge, 0);
	glVertex3f(half_edge, half_edge, 0);
	glVertex3f(-half_edge, -half_edge, 0);
	glVertex3f(half_edge, -half_edge, 0);
	glEnd();
}

/**
 *	Desenha um tri�ngulo dado sua altura e comprimento da base
 */
void drawTriangle(float base_length, float height) {
	float half_base = base_length / 2.0;
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-half_base, half_base);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.0, height);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(half_base, half_base);
	glEnd();
}

/**
*	Desenha uma casa na window
*/
void drawHouse(float edge_length, float roof_height) {
	// Define a cor de desenho para azul
	glColor3f(0, 0, 1);   // R, G, B
	glLineWidth(3);

	drawSquare(edge_length); // Desenha um quadrado no centro da janela
	drawTriangle(edge_length, roof_height);	// Desenha um tri�ngulo em cima do quadrado
}

/**
*	Fun��o callback de redesenho da janela de visualiza��o
*/
void display(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	// Limpa a pilha de matriz de transforma��o
	gluOrtho2D(lft + panX, rgt + panX, bottom + panY, top + panY);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0, 0, 0, 1);	// Limpa a janela de visualiza��o com a cor branca
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();	// Tem o mesmo efeito de glLoadIdentity() mas salva o contexto ao inv�s de limpar a pilha
	glLoadIdentity();	// Limpa a pilha de matriz de transforma��o

	drawAxis();
	glPopMatrix();
	glLoadIdentity();	// Limpa a pilha de matriz de transforma��o
	glTranslatef(translacaoX, translacaoY, 0);    // Todas as transforma��es s�o acumuladas no OpenGL
	drawHouse(0.6, 0.44);

	glFlush();	// Executa os comandos OpenGL
}

/**
*	Fun��o callback chamada para gerenciar eventos de teclas
*/
void handleKeyboard(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

/**
*	Fun��o callback chamada para gerenciar eventos de teclas especiais
*/
void handleSpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		translacaoX -= 0.01;
		glutPostRedisplay();
	} else if (key == GLUT_KEY_RIGHT) {
		translacaoX += 0.01;
		glutPostRedisplay();
	} else if (key == GLUT_KEY_UP) {
		translacaoY += 0.01;
		glutPostRedisplay();
	} else if (key == GLUT_KEY_DOWN) {
		translacaoY -= 0.01;
		glutPostRedisplay();
	} else if (key == GLUT_KEY_PAGE_DOWN) {
		lft = bottom -= 0.1;
		rgt = top += 0.1;
		glutPostRedisplay();
	} else if (key == GLUT_KEY_PAGE_UP) {
		lft = bottom += 0.1;
		rgt = top -= 0.1;
		glutPostRedisplay();
	} else if (key == GLUT_KEY_F5) {
		panX += 0.1;
		glutPostRedisplay();
	} else if (key == GLUT_KEY_F6) {
		panX -= 0.1;
		glutPostRedisplay();
	} else if (key == GLUT_KEY_F7) {
		panY += 0.1;
		glutPostRedisplay();
	} else if (key == GLUT_KEY_F8) {
		panY -= 0.1;
		glutPostRedisplay();
	}
}

/**
*	Fun��o respons�vel por inicializar par�metros e vari�veis
*/
void initialize(void) {
	translacaoX = translacaoY = panX = panY = 0;
	lft = bottom = -1;
	rgt = top = 1;
	
	// Define a janela de visualiza��o 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

/**
*	Programa principal
*/
int main() {
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	// Define do modo de opera��o da GLUT
	glutInitWindowSize(500, 500);	// Especifica o tamanho inicial em pixels da janela GLUT
	glutCreateWindow("Desenho de um tri�ngulo em 2D");	// Cria a janela passando como argumento o t�tulo da mesma
	glutDisplayFunc(display);	// Registra a fun��o callback de redesenho da janela de visualiza��o

	glutKeyboardFunc(handleKeyboard);	// Registra a fun��o callback para tratamento das teclas ASCII
	glutSpecialFunc(handleSpecialKeys);

	initialize();	// Chama a fun��o respons�vel por fazer as inicializa��es

	glutMainLoop();	// Inicia o processamento e aguarda intera��es do usu�rio

	return 0;
}
