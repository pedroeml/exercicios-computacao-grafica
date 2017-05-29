#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>

GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX = 0, obsY = 10, obsZ = 200, obsX_ini, obsY_ini, obsZ_ini;
GLfloat fAspect = 1, angle = 44;
int x_ini, y_ini, bot;

#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	30.0

void PosicionaObservador(void) {
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// glTranslatef(-obsX,-obsY,-obsZ);

	// glRotatef(rotX,1,0,0);
	// glRotatef(rotY,0,1,0);

	//void gluLookAt(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ)
	/*
	eyeX, eyeY, eyeZ: Specifies the position of the eye point.
	centerX, centerY, centerZ: Specifies the position of the reference point.
	upX, upY, upZ: Specifies the direction of the up vector.
	*/

	gluLookAt(obsX, obsY, obsZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// Definindo upY = -1 o mundo todo fica de ponta cabe�a
	// Variando o upX de valores positivos aos negativos o �ngulo da c�mera muda
}

void EspecificaParametrosVisualizacao(void) {
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
	/*
	fovy � o �ngulo, em graus, na dire��o y (usada para determinar a "altura" do volume de visualiza��o);
	aspect � a raz�o de aspecto que determina a �rea de visualiza��o na dire��o x, e seu valor � a raz�o em x (largura) e y (altura);
	zNear, que sempre tem que ter um valor positivo maior do que zero, � a dist�ncia do observador at� o plano de corte mais pr�ximo (em z);
	zFar, que tamb�m sempre tem que ter um valor positivo maior do que zero, � a dist�ncia do observador at� o plano de corte mais afastado (em z).
	*/
	gluPerspective(angle, fAspect, 0.5, 700);

	PosicionaObservador();
}

void desenhaChao() {
	glColor3f(1, 0, 1);
	glLineWidth(3);
	glBegin(GL_LINES);

	for (float z = -1000; z <= 1000; z += 10) {
		glVertex3f(-1000, -0.1f, z);
		glVertex3f(1000, -0.1f, z);
	}

	for (float x = -1000; x <= 1000; x += 10) {
		glVertex3f(x, -0.1f, -1000);
		glVertex3f(x, -0.1f, 1000);
	}

	glEnd();
	glLineWidth(1);
}

void Desenha(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	EspecificaParametrosVisualizacao();

	glColor3f(0.0f, 0.0f, 1.0f);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(-90, 1, 0, 0);
	glEnable(GL_DEPTH_TEST);    // Desenha na ordem certa

	//glutWireTeapot(35);
	//void glutWireCone(double base, double height, int slices, int stacks);
	glutWireCone(10, 20, 15, 10);
	/*
	slices � o n�mero de lados do cone, quanto maior mais o cone ficar� arrendondado
	stacks � o n�mero de n�veis em rela��o � altura da figura
	*/

	glPopMatrix();
	desenhaChao();

	glFlush();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	// Para previnir uma divis�o por zero
	if (h == 0) h = 1;

	// Especifica as dimens�es da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}


void Teclado(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

void TeclasEspeciais(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		obsX -= 5;
		break;
	case GLUT_KEY_RIGHT:
		obsX += 5;
		break;
	case GLUT_KEY_UP:
		obsY += 5;
		break;
	case GLUT_KEY_DOWN:
		obsY -= 5;
		break;
	case GLUT_KEY_HOME:
		obsZ += 3;
		break;
	case GLUT_KEY_END:
		obsZ -= 3;
		break;
	}

	glutPostRedisplay();
}

void Inicializa(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLineWidth(2.0);
}

void GerenciaMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		// Salva os par�metros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

void GerenciaMovim(int x, int y) {
	if (bot == GLUT_LEFT_BUTTON) {
		int deltax = x_ini - x;
		int deltay = y_ini - y;

		rotY = rotY_ini - deltax / SENS_ROT;
		rotX = rotX_ini - deltay / SENS_ROT;
	}

	else if (bot == GLUT_RIGHT_BUTTON) {
		int deltaz = y_ini - y;

		obsZ = obsZ_ini + deltaz / SENS_OBS;
	}

	else if (bot == GLUT_MIDDLE_BUTTON) {
		int deltax = x_ini - x;
		int deltay = y_ini - y;

		obsX = obsX_ini + deltax / SENS_TRANSL;
		obsY = obsY_ini - deltay / SENS_TRANSL;
	}

	PosicionaObservador();
	glutPostRedisplay();
}

int main(void) {
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(5, 5);

	glutInitWindowSize(450, 450);

	glutCreateWindow("Camera, Projecao");

	glutDisplayFunc(Desenha);

	glutReshapeFunc(AlteraTamanhoJanela);

	glutKeyboardFunc(Teclado);
	glutSpecialFunc(TeclasEspeciais);

	glutMotionFunc(GerenciaMovim);

	glutMouseFunc(GerenciaMouse);

	Inicializa();

	glutMainLoop();

	return 0;
}
