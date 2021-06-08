#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

int shoulderZ = 0, shoulderY = 0, elbow = 0, fingerBase = 0, fingerUp = 0;
int Right_FumerX = 0, Right_FumerZ = 0, Left_FumerX = 0, Left_FumerZ = 0, Right_Tibia = 0, Left_Tibia = 0;
int moving, startx, starty;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */


void init(void)

{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0,
		1.0,
		1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);

}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}



void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			moving = 1;
			startx = x;
			//starty = y;
		}
		if (state == GLUT_UP) {
			moving = 0;
		}
	}
}
void motion(int x, int y)
{
	if (moving) {

		angle = angle + (x - startx);
		//angle2 = angle2 + (y - starty);
		startx = x;
		//starty = y;
		glutPostRedisplay();
	}
}



#define PI 3.14

double eye[] = { 0.0, 0.0, 10.0 };
double center[] = { 0.0, 0.0, 0.0 };
double up[] = { 0.0, 1.0, 0.0 };

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta) * p[0];
	temp[1] += cos(theta) * p[1];
	temp[2] += cos(theta) * p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

// Rotation about vertical direction
void lookRight()
{
	rotatePoint(up, PI / 8, eye);
}

void lookLeft()
{
	//Write your code here
	rotatePoint(up, - PI / 8, eye);
}

// Rotation about horizontal direction

void lookUp()
{
	double horizontal[3];
	double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, PI / 8, eye);
	rotatePoint(horizontal, PI / 8, up);
}

void lookDown()
{
	//Write your code here

	double horizontal[3];
	double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, - PI / 8, eye);
	rotatePoint(horizontal, - PI / 8, up);

}

// Forward and Backward
void moveForward()
{
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	float speed = 0.1;
	eye[0] += direction[0] * speed;
	eye[1] += direction[1] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;
}

void moveBackword()
{
	//Write your code here
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	float speed = 0.1;
	eye[0] -= direction[0] * speed;
	eye[1] -= direction[1] * speed;
	eye[2] -= direction[2] * speed;

	center[0] -= direction[0] * speed;
	center[1] -= direction[1] * speed;
	center[2] -= direction[2] * speed;

}


// mixed display
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glcolor3f(0.0, 0.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		up[0], up[1], up[2]);
	glColor3f(1.0, 1.0, 1.0);



	
		//--------------------------------
		glRotatef(angle2, 1.0, 0.0, 0.0);
		glRotatef(angle, 0.0, 1.0, 0.0);
	
		//----Body----
		
		glTranslatef(0.0, 0.0, 0.0);

		glPushMatrix();
			glScalef(2.0, 4.0, 1.0);
			glutWireCube(1.0);
		glPopMatrix();

	//----Head----
		glPushMatrix();
			glTranslatef(0, 3.0, 0.0);
			glTranslatef(0.0, 0.0, 0.0);
	
			glScalef(0.25, 0.25, 0.25);
			glutWireSphere(3.0, 20, 20); // double radius , slices , stacks
		glPopMatrix();

		//----Right Arm----
	
		glPushMatrix();
			//----Right shoulder----
			glTranslatef(-1.2, 1.7, 0.0);
			glRotatef((GLfloat)shoulderZ, 0.0 , 0.0 , 1.0);
			glRotatef((GLfloat)shoulderY, 0.0 , 1.0 , 0.0);
			glTranslatef(-0.1, -0.5, 0.0);
		
			glPushMatrix();
				glScalef(0.5, 1.5, 1.0);
				glutWireCube(1.0);
			glPopMatrix();
			//----Right elbow----
			glPushMatrix();
				glTranslatef(0.0, -0.75, 0.0);
				glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
				glTranslatef(0.0, -0.75, 0.0);
				glPushMatrix();
					glScalef(0.5, 1.5, 1.0);
					glutWireCube(1.0);
				glPopMatrix();


			// ----Right 4 fingers----
			for (int i = 0; i < 4; i++)
			{
				glPushMatrix();
					glTranslatef(-0.2, -0.8, 0.45 - 0.3 * i);
					glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
					glTranslatef(0, -0.1, 0);
		
					glPushMatrix();
						glScalef(0.1, 0.3, 0.1);
						glutWireCube(1);
					glPopMatrix();
		
					glTranslatef(0, -0.2, 0);
					glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
					glTranslatef(0, -0.1, 0);
		
					glPushMatrix();
						glScalef(0.1, 0.3, 0.1);
						glutWireCube(1);
					glPopMatrix();
			
				glPopMatrix();	
			}
			// ----Right Thumb----
			glPushMatrix();
		
				glTranslatef(0.2, -0.8, 0.0);
				glRotatef((GLfloat)fingerBase, 0.0, 0.0, -1.0);
				glTranslatef(0, -0.1, 0);
					
				glPushMatrix();
					glScalef(0.1, 0.3, 0.1);
					glutWireCube(1);
				glPopMatrix();
			
				glTranslatef(0, -0.2, 0);
				glRotatef((GLfloat)fingerUp, 0.0, 0.0, -1.0);
				glTranslatef(0, -0.1, 0);
				
				glPushMatrix();
					glScalef(0.1, 0.3, 0.1);
					glutWireCube(1);
				glPopMatrix();
				
			glPopMatrix();
				
			glPopMatrix();

			glPopMatrix();

			//----Right Leg----
			glPushMatrix();

			glTranslatef(-0.72, -2.0, 0.0);
			glRotatef((GLfloat)Right_FumerX, -1.0, 0.0, 0.0);
			glRotatef((GLfloat)Right_FumerZ, 0, 0.0, 1.0);
			glTranslatef(0.0, -1.0, 0.0);


			glPushMatrix();
			glScalef(0.6, 2.0, 1.0);
			glutWireCube(1.0);
			glPopMatrix();

			//----Right Tibia----

			glPushMatrix();
			glTranslatef(0.0, -1.0, 0.0);
			glRotatef((GLfloat)Right_Tibia, 1.0, 0.0, 0.0);
			glTranslatef(0.0, -1.0, 0.0);

			glPushMatrix();
			glScalef(0.6, 2.0, 1.0);
			glutWireCube(1.0);
			glPopMatrix();


			// ----Right Foot----
			glPushMatrix();

			glTranslatef(-0.23, -1.6, 0.0);
			glTranslatef(0.2, 0.3, 0);

			glPushMatrix();
			glScalef(0.6, 0.5, 2.0);
			glutSolidCube(1);
			glPopMatrix();

			glPopMatrix();

			glPopMatrix();
			glPopMatrix();

		//----Left Arm----
	glPushMatrix();
		//----Left shoulder----
		glTranslatef(1.2, 1.7, 0.0);
		glRotatef((GLfloat)shoulderZ, 0.0, 0.0, -1.0);
		glRotatef((GLfloat)shoulderY, 0.0, -1.0, 0.0);
		glTranslatef(0.1, -0.5, 0.0);

		glPushMatrix();
			glScalef(0.5, 1.5, 1.0);
			glutWireCube(1.0);
		glPopMatrix();
		//----Left elbow----
		glPushMatrix();
			glTranslatef(0.0, -0.75, 0.0);
			glRotatef((GLfloat)elbow, 0.0, 0.0, -1.0);
			glTranslatef(0.0, -0.75, 0.0);
			glPushMatrix();
			glScalef(0.5, 1.5, -1.0);
			glutWireCube(1.0);
		glPopMatrix();


		// ----Left 4 fingers----
		for (int i = 0; i < 4; i++)
		{
			glPushMatrix();
				glTranslatef(0.2, -0.8, 0.45 - 0.3 * i);
				glRotatef((GLfloat)fingerBase, 0.0, 0.0, -1.0);
				glTranslatef(0, -0.1, 0);

				glPushMatrix();
					glScalef(0.1, 0.3, 0.1);
					glutWireCube(1);
				glPopMatrix();

				glTranslatef(0, -0.2, 0);
				glRotatef((GLfloat)fingerUp, 0.0, 0.0, -1.0);
				glTranslatef(0, -0.1, 0);

				glPushMatrix();
					glScalef(0.1, 0.3, 0.1);
					glutWireCube(1);
				glPopMatrix();

			glPopMatrix();
		}
		// ----Left Thumb----
		glPushMatrix();

			glTranslatef(-0.2, -0.8, 0.0);
			glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
			glTranslatef(0, -0.1, 0);

			glPushMatrix();
				glScalef(0.1, 0.3, 0.1);
				glutWireCube(1);
			glPopMatrix();

			glTranslatef(0, -0.2, 0);
			glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
			glTranslatef(0, -0.1, 0);

			glPushMatrix();
				glScalef(0.1, 0.3, 0.1);
				glutWireCube(1);
			glPopMatrix();

		glPopMatrix();

		glPopMatrix();
		glPopMatrix();
		
		//----Left Leg----	

		glPushMatrix();

		glTranslatef(0.72, -2.0, 0.0);
		glRotatef((GLfloat)Left_FumerX, -1.0, 0.0, 0.0);
		glRotatef((GLfloat)Left_FumerZ, 0, 0.0, -1.0);
		glTranslatef(0.0, -1.0, 0.0);


		glPushMatrix();
		glScalef(0.6, 2.0, 1.0);
		glutWireCube(1.0);
		glPopMatrix();
		//----Left Tibia----
		glPushMatrix();
		glTranslatef(0.0, -1.0, 0.0);
		glRotatef((GLfloat)Left_Tibia, 1.0, 0.0, 0.0);
		glTranslatef(0.0, -1.0, 0.0);

		glPushMatrix();
		glScalef(0.6, 2.0, 1.0);
		glutWireCube(1.0);
		glPopMatrix();


		// ----Left Foot----
		glPushMatrix();

		glTranslatef(0, -1.6, 0.0);
		glTranslatef(0.0, 0.3, 0);

		glPushMatrix();
		glScalef(0.6, 0.5, 2.0);
		glutSolidCube(1);
		glPopMatrix();

		glPopMatrix();

		glPopMatrix();
		glPopMatrix();
	
		//---------------------------------
	
	
	glutSwapBuffers();
}


void reset()
{
	double e[] = { 0.0, 0.0, 10.0 };
	double c[] = { 0.0, 0.0, 0.0 };
	double u[] = { 0.0, 1.0, 0.0 };
	for (int i = 0; i < 3; i++)
	{
		eye[i] = e[i];
		center[i] = c[i];
		up[i] = u[i];
	}
}
void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		lookLeft();
		break;
	case GLUT_KEY_RIGHT:
		lookRight();
		break;
	case GLUT_KEY_UP:
		lookUp();
		break;
	case GLUT_KEY_DOWN:
		lookDown();
		break;
	}
	glutPostRedisplay();
}

void keyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		moveForward();
		break;
	case '2':
		moveBackword();
		break;
	case '0':
		reset();
		break;
	


	case 'Q':
		if (shoulderZ == 0)
			break;
		shoulderZ = (shoulderZ + 5) % 360;
		glutPostRedisplay();
		break;
	case 'q':
		if (shoulderZ == -145)
			break;
		shoulderZ = (shoulderZ - 5) % 360;
		glutPostRedisplay();
		break;
	case 'W':
		if (shoulderY == 0)
			break;
		shoulderY = (shoulderY + 5) % 360;
		glutPostRedisplay();
		break;
	case 'w':
		if (shoulderY == -90)
			break;
		shoulderY = (shoulderY - 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		if (elbow == 120)
			break;
		elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 'E':
		if (elbow == 0)
			break;
		elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 'f':
		if (fingerBase == 60)
			break;
		fingerBase = (fingerBase + 5) % 360;
		glutPostRedisplay();
		break;
	case 'F':
		if (fingerBase == 0)
			break;
		fingerBase = (fingerBase - 5) % 360;
		glutPostRedisplay();
		break;
	case 'g':
		if (fingerUp == 60)
			break;
		fingerUp = (fingerUp + 5) % 360;
		glutPostRedisplay();
		break;
	case 'G':
		if (fingerUp == 0)
			break;
		fingerUp = (fingerUp - 5) % 360;
		glutPostRedisplay();
		break;
		
	case 'a':
		if (Right_FumerX == 100)
			break;
		Right_FumerX = (Right_FumerX + 5) % 360;
		glutPostRedisplay();
		break;
	case 'A':
		if (Right_FumerX == -45)
			break;
		Right_FumerX = (Right_FumerX - 5) % 360;
		glutPostRedisplay();
		break;
	case 'S':
		if (Right_FumerZ == 0)
			break;
		Right_FumerZ = (Right_FumerZ + 5) % 360;
		glutPostRedisplay();
		break;
	case 's':
		if (Right_FumerZ == -100)
			break;
		Right_FumerZ = (Right_FumerZ - 5) % 360;
		glutPostRedisplay();
		break;
	case 'd':
		if (Right_Tibia == 120)
			break;
		Right_Tibia = (Right_Tibia + 5) % 360;
		glutPostRedisplay();
		break;
	case 'D':
		if (Right_Tibia == 0)
			break;
		Right_Tibia = (Right_Tibia - 5) % 360;
		glutPostRedisplay();
		break;
	case 'z':
		if (Left_FumerX == 100)
			break;
		Left_FumerX = (Left_FumerX + 5) % 360;
		glutPostRedisplay();
		break;
	case 'Z':
		if (Left_FumerX == -45)
			break;
		Left_FumerX = (Left_FumerX - 5) % 360;
		glutPostRedisplay();
		break;
	case 'X':
		if (Left_FumerZ == 0)
			break;
		Left_FumerZ = (Left_FumerZ + 5) % 360;
		glutPostRedisplay();
		break;
	case 'x':
		if (Left_FumerZ == -100)
			break;
		Left_FumerZ = (Left_FumerZ - 5) % 360;
		glutPostRedisplay();
		break;
	case 'c':
		if (Left_Tibia == 120)
			break;
		Left_Tibia = (Left_Tibia + 5) % 360;
		glutPostRedisplay();
		break;
	case 'C':
		if (Left_Tibia == 0)
			break;
		Left_Tibia = (Left_Tibia - 5) % 360;
		glutPostRedisplay();
		break;
		
	case 27:
		exit(0);
		break;
	default:
		break;
 





	}
		glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600); // width ,height
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Full body");
	init();
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyBoard);
	glutSpecialFunc(specialKeys);
	glutMainLoop();


	return 0;
}
