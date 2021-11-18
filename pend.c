#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900

const float PI = 3.1415;
const float BOB_RADIUS = .5;
const int NAIL_SCREW_X = 0;
const int NAIL_SCREW_Y = 10;

float bob_x, bob_y;
float angle;
float a_length;
float angular_velocity;
float drag = .01;
float f_gravity = -.98;


void init(){
	glClearColor(0,0,0,1);
}

void drawBob(){
	int i;
	int triangleAmount = 300;
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(bob_x, bob_y); 
		for(i = 0; i <= triangleAmount;i++)
			glVertex2f(bob_x + (BOB_RADIUS * cos(i *  twicePi / triangleAmount)),
					   bob_y + (BOB_RADIUS * sin(i * twicePi / triangleAmount)));
	glEnd();
}

void drawArm(){
	glBegin(GL_LINES);
	glVertex2f(NAIL_SCREW_X, NAIL_SCREW_Y);
	glVertex2f(bob_x, bob_y);
	glEnd();
}

void render_func(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	drawBob();
	drawArm();
	glutSwapBuffers();
}

void reshape_func(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

void clock(){
	glutPostRedisplay();
	glutTimerFunc(1000/60, clock, 0);
	bob_x = NAIL_SCREW_X + a_length * sin( PI / 180 * (angle));
	bob_y = NAIL_SCREW_Y - a_length * cos( PI / 180 * (angle));

	float angular_acceleration = f_gravity * sin(PI / 180 * (angle));
	angular_velocity += angular_acceleration;
	angle += angular_velocity;
	angular_velocity *= (1 - drag);
}

void mouse_click(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		angle = 57 * atan((x - ((float) SCREEN_WIDTH / 2)) / y);
	glutPostRedisplay();
}


int main(int argc, char **argv) {
	a_length = 8 - BOB_RADIUS;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("pendulum");

	glutDisplayFunc(render_func);
	glutReshapeFunc(reshape_func);
	glutTimerFunc(0, clock, 0);
	glutMouseFunc(mouse_click); 

	init();
	glutMainLoop();
}

