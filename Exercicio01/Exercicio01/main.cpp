#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

float translacaoX, translacaoY, panX, panY, lft, rgt, bottom, top;

/**
*	Desenha os eixos x e y
*/
void drawAxis() {
	glColor3f(1, 1, 1);
	glLineWidth(1);

	glBegin(GL_LINES);
	glVertex2f(lft, 0.0);
	glVertex2f(rgt, 0.0);
	glVertex2f(0.0, bottom);
	glVertex2f(0.0, top);
	glEnd();
}

/**
*	Desenha uma casa na window
*/
void drawHouse() {
	// Define a cor de desenho para azul
	glColor3f(0, 0, 1);   // R, G, B
	glLineWidth(3);

	// Desenha um quadrado no centro da janela
	glBegin(GL_LINES);
	glVertex3f(-0.3, -0.3, 0);
	glVertex3f(-0.3, 0.3, 0);
	glVertex3f(0.3, -0.3, 0);
	glVertex3f(0.3, 0.3, 0);
	glVertex3f(-0.3, 0.3, 0);
	glVertex3f(0.3, 0.3, 0);
	glVertex3f(-0.3, -0.3, 0);
	glVertex3f(0.3, -0.3, 0);
	glEnd();

	// Desenha um triângulo em cima do quadrado
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-0.3, 0.3);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.0, 0.44);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.3, 0.3);
	glEnd();
}

/**
*	Função callback de redesenho da janela de visualização
*/
void display(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	// Limpa a pilha de matriz de transformação
	gluOrtho2D(lft + panX, rgt + panX, bottom + panY, top + panY);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0, 0, 0, 1);	// Limpa a janela de visualização com a cor branca
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();	// Tem o mesmo efeito de glLoadIdentity() mas salva o contexto ao invés de limpar a pilha
	glLoadIdentity();	// Limpa a pilha de matriz de transformação

	drawAxis();
	glPopMatrix();
	glLoadIdentity();	// Limpa a pilha de matriz de transformação
	glTranslatef(translacaoX, translacaoY, 0);    // Todas as transformações são acumuladas no OpenGL
	drawHouse();

	glFlush();	// Executa os comandos OpenGL
}

/**
*	Função callback chamada para gerenciar eventos de teclas
*/
void handleKeyboard(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

/**
*	Função callback chamada para gerenciar eventos de teclas especiais
*/
void handleSpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		translacaoX -= 0.01;
		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_RIGHT) {
		translacaoX += 0.01;
		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_UP) {
		translacaoY += 0.01;
		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_DOWN) {
		translacaoY -= 0.01;
		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_PAGE_UP) {
		lft = bottom -= 0.1;
		rgt = top += 0.1;
		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_PAGE_DOWN) {
		lft = bottom += 0.1;
		rgt = top -= 0.1;
		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_F5) {
		panX += 0.1;
		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_F6) {
		panX -= 0.1;
		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_F7) {
		panY += 0.1;
		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_F8) {
		panY -= 0.1;
		glutPostRedisplay();
	}
}

/**
*	Função responsável por inicializar parâmetros e variáveis
*/
void initialize(void) {
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	translacaoX = translacaoY = panX = panY = 0;
	lft = bottom = -1;
	rgt = top = 1;
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	// Define do modo de operação da GLUT
	glutInitWindowSize(500, 500);	// Especifica o tamanho inicial em pixels da janela GLUT
	glutCreateWindow("Desenho de um triângulo em 2D");	// Cria a janela passando como argumento o título da mesma
	glutDisplayFunc(display);	// Registra a função callback de redesenho da janela de visualização

	glutKeyboardFunc(handleKeyboard);	// Registra a função callback para tratamento das teclas ASCII
	glutSpecialFunc(handleSpecialKeys);

	initialize();	// Chama a função responsável por fazer as inicializações

	glutMainLoop();	// Inicia o processamento e aguarda interações do usuário

	return 0;
}
