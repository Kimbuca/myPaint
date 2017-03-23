// transf_instance_main.cpp
// Transformación de Instancias
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <list>

#include "triangle_gl.h"
#include "quad_gl.h"
#include "box_gl.h"

using namespace std;

// Geometries
list<ObjectGL *> scene;

//apuntador a un objeto de tipo poligono
PolygonGL *p1, *p2;
ObjectGL *o1;

// Tamaño de la ventana
GLint width = 800;
GLint height = 600;

// Parámetros de la cámara virtual
GLint mouseButton = 0;
GLboolean mouseRotate = false;
GLboolean mouseZoom = false;
GLboolean mousePan = false;
GLint xClick = 0;
GLint yClick = 0;
GLint xAux = 0;
GLint yAux = 0;
GLfloat rotX = 0.f;
GLfloat rotY = 0.f;
GLfloat panX = 0.f;
GLfloat panY = 0.f;
GLfloat zoomZ = -10.f;

GLfloat rot = 0.f;
GLfloat deltaR = 0.0001;

// Función que inicializa el Contexto OpenGL y la geometría de la escena
void init()
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glColor3f(1.f, 1.f, 1.f);

	TriangleGL * p1 = new TriangleGL();
	p1->setColor(.4f, 0.f, .6f);
	p1->frontFaceMode = GL_LINE;
	p1->backFaceMode = GL_FILL;
	//p1->translate(1.f, 0.f, 0.f);
	p1->rotate(-90.f, 1.f, 0.f, 0.f);
	p1->scale(2.f, 1.f, 1.f);

	//Second polygon
	TriangleGL * p2 = new TriangleGL();
	p2->setColor(1.f, 1.f, 0.f);
	p2->frontFaceMode = GL_FILL;
	p2->backFaceMode = GL_LINE;
	p2->translate(-1.f, 0.f, 0.f);
	p2->rotate(-90.f, 1.f, 0.f, 0.f);
	p2->scale(0.5f, 0.5f, 0.5f);

	//lO QUE HUBIERA HECHO SI ME HUBIERA DEJADO IMPORTAR EL .H AQUI
	/*
	QuadGL * p3 = new QuadGL();
	p3->setColor(1.f, 1.f, 0.f);
	p3->frontFaceMode = GL_LINE;
	p3->backFaceMode = GL_LINE;
	*/
	BoxGL * p4 = new BoxGL();
	p4->setColor(1.f, 1.f, 0.f);

	BoxGL * p5 = new BoxGL();
	p5->setColor(1.f, 1.f, 0.f);
	p5->translate(2, 0, 0);

	/*
	QuadGL * p4 = new QuadGL();
	p4->setColor(1.f, 1.f, 0.f);
	p4->frontFaceMode = GL_LINE;
	p4->backFaceMode = GL_LINE;
	p4->translate(0, 0, 1.f);


	QuadGL * p5 = new QuadGL();
	p5->setColor(1.f, 1.f, 0.f);
	p5->frontFaceMode = GL_LINE;
	p5->backFaceMode = GL_LINE;
	p5->translate(-.5f, 0.f, -.5f);
	p5->rotate(90, 0.f, 1.f, 0.f);

	QuadGL * p6 = new QuadGL();
	p6->setColor(1.f, 1.f, 0.f);
	p6->frontFaceMode = GL_LINE;
	p6->backFaceMode = GL_LINE;
	p6->translate(0.f, 0.f, 1.f);
	p6->rotate(180, 0.f, 1.f, 0.f);
	*/

	//o1 = new BoxGL();
	scene.push_back(p1);
	scene.push_back(p2);
	//scene.push_back(p3);
	scene.push_back(p4);
	scene.push_back(p5);


}

// Función que se invoca cada vez que se redimensiona la ventana
void resize(GLint w, GLint h)
{
	if (h == 0)
	{
		h = 1;
	}
	width = w;
	height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.f, (float)width / height, 0.1f, 1000.f);		// Transf. de Proyección en Perspectiva
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);								// Transf. de Viewport (mapeo al área de dibujo)
}

// Geometría sistema coordenado
void geomCoordSys(GLfloat size)
{
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);

	// Eje X (Rojo)
	glColor3f(1., 0., 0.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(size, 0., 0.);
	glEnd();

	// Eje Y (Verde))
	glColor3f(0., 1., 0.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., size, 0.);
	glEnd();

	// Eje Z (Azul)
	glColor3f(0., 0., 1.);
	glBegin(GL_LINES);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., 0., size);
	glEnd();

	glColor3f(currentColor[0], currentColor[1], currentColor[2]);
}


// Función que se invoca cada vez que se dibuja
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Se limpian los buffers con el color activo definido por glClearColor

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Transformación de vista
	glTranslatef(panX, panY, zoomZ);
	glRotatef(rotY, 1.0, 0.0, 0.0);
	glRotatef(rotX, 0.0, 1.0, 0.0);
	// Escena
	geomCoordSys(2.f);
	for (list<ObjectGL *> ::iterator it = scene.begin(); it != scene.end(); it++){
		(*it)->render();
	}
	glutSwapBuffers();			// Se intercambian buffers
}

void mouse(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseRotate = false;
	mouseZoom = false;
	mousePan = false;
	xClick = x;
	yClick = y;
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseRotate = true;
		xAux = rotX;
		yAux = rotY;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		mouseZoom = true;
		xAux = zoomZ;
	}
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		mousePan = true;
		xAux = panX;
		yAux = panY;
	}
}

void mouseMotion(int x, int y)
{
	if (mouseRotate == true)
	{
		if (mouseButton == GLUT_LEFT_BUTTON)
		{
			if ((x - xClick + xAux) > 360.0)
			{
				xAux = xAux - 360.0;
			}
			if ((x - xClick + xAux) < 0.0)
			{
				xAux = xAux + 360.0;
			}
			if ((y - yClick + yAux) > 360.0)
			{
				yAux = yAux - 360.0;
			}
			if ((y - yClick + yAux) < 0.0)
			{
				yAux = yAux + 360.0;
			}
			rotX = x - xClick + xAux;
			rotY = y - yClick + yAux;
		}
	}
	else if (mouseZoom == true)
	{
		if (mouseButton == GLUT_RIGHT_BUTTON)
		{
			zoomZ = ((x - xClick) / 10.0) + xAux;
		}
	}
	else if (mousePan == true)
	{
		if (mouseButton == GLUT_MIDDLE_BUTTON)
		{
			panX = ((x - xClick) / 63.0) + xAux;
			panY = ((y - yClick) / (-63.0)) + yAux;
		}
	}
	glutPostRedisplay();
}

int main(GLint argc, GLchar **argv)
{
	// 1. Se crea una ventana y un contexto OpenGL usando GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Instance Transformation");

	// 1.2 Se definen las funciones callback para el manejo de eventos
	glutReshapeFunc(resize);
	glutDisplayFunc(render);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);

	// 2. Se direcciona a las funciones correctas del API de OpenGL
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error");
		return false;
	}

	// 3. Se inicializa el contexto de OpenGL y la geometría de la escena
	init();

	// 4. Se inicia el ciclo de escucha de eventos
	glutMainLoop();
	return 0;
}