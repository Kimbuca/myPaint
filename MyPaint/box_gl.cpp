#include <GL\glew.h>
#include <GL\freeglut.h>
#include <cmath>
#include <list>

#include "box_gl.h"
#include "quad_gl.h"


BoxGL::BoxGL() : ObjectGL(){
	//en el origen
	glPushMatrix();
	this->q1 = new QuadGL();
	this->q1->setColor(1.f, 1.f, 0.f);
	this->q1->frontFaceMode = GL_LINE;
	this->q1->backFaceMode = GL_LINE;
	glPopMatrix();

	glPushMatrix();
	this->q2 = new QuadGL();
	this->q2->setColor(1.f, 0.f, 0.f);
	this->q2->frontFaceMode = GL_LINE;
	this->q2->backFaceMode = GL_LINE;
	this->q2->translate(.5f, .5f, 0);
	this->q2->rotate(90, 0, 0, 1);
	glPopMatrix();

	glPushMatrix();
	this->q3 = new QuadGL();
	this->q3->setColor(1.f, 0.f, 0.f);
	this->q3->frontFaceMode = GL_LINE;
	this->q3->backFaceMode = GL_LINE;
	this->q3->translate(.0f, 1.f, 0);
	glPopMatrix();

	this->q4 = new QuadGL();
	this->q4->setColor(1.f, 0.f, 0.f);
	this->q4->frontFaceMode = GL_LINE;
	this->q4->backFaceMode = GL_LINE;
	this->q4->translate(.5f, .5f, 0);
	this->q4->rotate(90, 1, 0, 0);

}

BoxGL::~BoxGL(){

}

void BoxGL::render(){

	this->q1->render();
	this->q2->render();
	this->q3->render();
	this->q4->render();
}