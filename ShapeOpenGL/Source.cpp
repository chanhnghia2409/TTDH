#include<glut.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<math.h>


#define PI 3.141592653589323846
#define STEPS 40
#define MAX_STARS 300
//==========================================================================================
//Khai báo khởi tạo
const int screenWidth = 640;
const int screenHeight = 480;

//Cấu trúc ngôi sao
typedef struct star
{
	GLint x, y;
	GLint radius;
	GLint velocity;
	GLfloat insenity;
}STAR;

STAR sky[MAX_STARS];

static GLfloat spin = 0.0;


void init(void)
{
	//glClearColor(1.0, 1.0, 1.0, 1.0);//clear white
	glClearColor(0.0, 0.0, 0.0, 0.0 );//clear black
	glShadeModel(GL_FLAT);

}


//============================================================================================
//Các hàm vẽ
void FourPoints()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0);

	glBegin(GL_POINTS);
		glVertex3f(200.0, 120.0, 0.0);
		glVertex3f(440.0, 120.0, 0.0);
		glVertex3f(440.0, 360.0, 0.0);
		glVertex3f(200.0, 360.0, 0.0);
	glEnd();
}
//============================================Hình tam giác====================================
void Triangle()
{
	glBegin(GL_TRIANGLES);
		glVertex2i(160, 80);
		glVertex2i(480, 80);
		glVertex2i(320, 400);
	glEnd();
}
void TriangleRed()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(160, 80);
	glVertex2i(480, 80);
	glVertex2i(320, 400);
	glEnd();
}

void TriangleRainbow()
{
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(160, 80);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(480, 80);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2i(320, 400);
	glEnd();
}

void TwoTriangle()
{
	glBegin(GL_TRIANGLES);
		glVertex2i(50, 50);
		glVertex2i(200, 50);
		glVertex2i(100, 150);

		glVertex2i(300, 100);
		glVertex2i(450, 100);
		glVertex2i(350, 250);
		glEnd();
	glEnd();
}

void TrianglStrip()
{
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2i(50, 50);
		glVertex2i(100, 150);
		glVertex2i(200, 50);

		glVertex2i(350, 250);
		glVertex2i(300, 100);
		glVertex2i(450, 150);
		glEnd();
	glEnd();
}
//============================================Hình vuông========================================

void drawSquare(GLint x, GLint y, GLint a)
{
	glBegin(GL_POLYGON);
		glVertex2i(x, y);
		glVertex2i(x + a, y);
		glVertex2i(x + a, y + a);
		glVertex2i(x, y + a);
	glEnd();
}
//============================================Hình chữ nhật======================================
void drawRectangle(GLint x, GLint y, GLint width, GLint height)
{
	glBegin(GL_POLYGON);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glVertex2i(x + width, y + height);
		glVertex2i(x, y + height);
	glEnd();
}
//============================================Hình tròn===========================================
void drawCircle(GLint x, GLint y, GLint radius)
{
	GLfloat twicePi = (GLfloat)2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(x, y);
	for (int i = 0;i <= STEPS; i++)
	{
		glVertex2i((GLint)(x + (radius * cos(i * twicePi / STEPS)) + 0.5),
			(GLint)(y + (radius * sin(i * twicePi / STEPS)) + 0.5));
	}
	glEnd();
}


//================================================================================================
//Các hàm hiển thị
void displayTriangle()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//FourPoints();
		//Triangle();
		//TriangleRed();
		//TriangleRainbow();
		//TwoTriangle();
		TrianglStrip();

	glFlush();

}

void displaySquare()
{
	glClear(GL_COLOR_BUFFER_BIT);
		GLint size = 200;
		GLint x = (screenWidth - size) / 2;
		GLint y = (screenHeight - size) / 2;
		drawSquare(x, y, size);
	glFlush();
}

void displayRectangle()
{
	glClear(GL_COLOR_BUFFER_BIT);
		GLint w = 400, h = 200;
		GLint x = (screenWidth - w) / 2;
		GLint y = (screenHeight - h) / 2;
		drawRectangle(x, y, w, h);
	glFlush();
}

void displayCircle()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	drawCircle(320, 240, 150);

	glFlush();
	
}

void spinDisplay(void)
{
	spin = spin + 2.0;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void reshapeSpin(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("lab1");
	init();
	//glutDisplayFunc(displayRectangle);
	glutDisplayFunc(displaySquare);
	//glutDisplayFunc(displayTriangle);
	//glutDisplayFunc(displayCircle);
	glutReshapeFunc(reshape);
	//glutReshapeFunc(reshapeSpin);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;

}
