
#include "pch.h"
#include <windows.h> 
#include <GL/glut.h> 
#include <GL/gl.h>


/*
Acestasta instalatie are urmatorul comportament:
Sunt doua bazine cu apa(doua cuburi) si o cale de transmitere a apei (un dreptunghi).
Initial primul bazin este plin cu apa, la apasarea unui click stanga de la mouse, apa ajunge pe calea de transmitere a apei.
-La apasarea al doilea click, apa ajunge la bazinul 2 dar mai ramane apa pe calea de transmitere;
-La apasarea al 3-lea click, apa ajunge total la al doilea bazin acesta din urma fiind umplut, in timp ce bazinul 1 si calea
de transmitere vor fi goale, adica fara apa.
-La apasarea al 4-lea click, bazinul1 (cel gol) si calea de transmitere vor fi alungate de pe ecran,
bazinul 2 isi va schimba pozitia, se va apropia catre acesta si acesta se va roti in continu, fiind vizibil din toate unghiurile.

*/




//variabile globale

char title[] = "Final Project";
float cube1[6][3]; //Am creat aceasta matrice pentru a putea schimba si salva culoriile noi pe care le voi da cubului1
float cube2[6][3]; //Am creat aceasta matrice pentru a putea schimba si salva culoriile noi pe care le voi da cubului2
float rectangle[3]; //Am creat aceast vector pentru a putea schimba si salva culoriile noi pe care le voi da dreptunghiului

int actions_counter = 0; //Va numerota actiunile care se vor face cu click-ul de la mouse

float pozitia_cub2 = 2.0f; //pentru a putea schimba si salva pozitia pe care o voi da cubului2(cel din dreapta)
float marime_cub2 = -10.0f; //pentru a putea schimba si salva marimea pe care o voi da cubului2(cel din dreapta)

bool roteste = false; //pentru a seta cand sa porneasca cubul 2 sa se roteasca


GLfloat angleCube = 0.0f; // Rotational angle for cube [NEW]
int refreshMills = 1; // refresh interval in milliseconds [NEW]


/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and
	glClearDepth(1.0f); // Set background depth to farthest
	glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL); // Set the type of depth-test
	glShadeModel(GL_SMOOTH); // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);



	//Setez valorile care vor servi drept culori la cubul1
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j == 2)
				cube1[i][j] = 1.0f;

			else
				cube1[i][j] = 0.0f;
		}
	}

	//Setez valorile care vor servi drept culori la cubul2
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cube2[i][j] = 1.0f;
		}
	}

	//Setez valorile care vor servi drept culori la dreptunghi
	for (int i = 0; i < 3; i++)
	{
		rectangle[i] = 1.0f;
	}


}
/* Handler for window-repaint event. Called back when the window first appears
and
 whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and

	glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix

	glLoadIdentity(); // Reset the model-view matrix
	glTranslatef(5.0f, 0.2f, -9.0f); // Move left and into the screen

	glLoadIdentity();
	glTranslatef(-3.5f, 0.0f, -10.0f);


	glBegin(GL_QUADS); // Begin drawing the color cube with 6


	//Desenam Primul cub
	glColor3f(cube1[0][0], cube1[0][1], cube1[0][2]); // Blue
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glColor3f(cube1[1][0], cube1[1][1], cube1[1][2]); // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glColor3f(cube1[2][0], cube1[2][1], cube1[2][2]); // Blue
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(cube1[3][0], cube1[3][1], cube1[3][2]); // Blue
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glColor3f(cube1[4][0], cube1[4][1], cube1[4][2]); // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glColor3f(cube1[5][0], cube1[5][1], cube1[5][2]); // Blue
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd(); // End of drawing color-cube


	glLoadIdentity(); // Reset the model-view matrix
	glTranslatef(pozitia_cub2, 0.0f, marime_cub2); //move left and into the screen

	if (roteste)
		glRotatef(angleCube, 1.0f, 1.0f, 1.0f); // Rotate about (1,1,1)-axis [NEW]

	glBegin(GL_QUADS); // Begin drawing the color cube with 6

	//Desenez al doilea cub
	glColor3f(cube2[0][0], cube2[0][1], cube2[0][2]); //white
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glColor3f(cube2[1][0], cube2[1][1], cube2[1][2]); // white
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glColor3f(cube2[2][0], cube2[2][1], cube2[2][2]); // white
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(cube2[3][0], cube2[3][1], cube2[3][2]); // white
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glColor3f(cube2[4][0], cube2[4][1], cube2[4][2]);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glColor3f(cube2[5][0], cube2[5][1], cube2[5][2]); // white
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd(); // End of drawing color-cube


		/* desenează un dreptunghi */

	glColor3f(rectangle[0], rectangle[1], rectangle[2]);
	glBegin(GL_POLYGON);
	glVertex3f(-4.3, 0.5, 0.0);
	glVertex3f(-1.05, 0.5, 0.0);
	glVertex3f(-1.05, 0.0, 0.0);
	glVertex3f(-4.3, 0.0, 0.0);
	glEnd();
	/* forţează procesarea rutinelor de desenare*/
	glFlush();

	glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)

	angleCube -= 3.0f;

}



void timer(int value) {
	glutPostRedisplay(); // Post re-paint request to activate display()
	glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}



void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:

		if (state == GLUT_DOWN) { //Daca apasam butonul de la mouse din stanga

	//in partea aceasta tot schimb culoriile pentru a forma animatia dupa numarul de click-uri

			actions_counter++;

			if (actions_counter == 1) {

				for (int i = 0; i < 3; i++)
				{
					if (i == 2)
						rectangle[i] = 1.0f;
					else
					{
						rectangle[i] = 0.0f;
					}
				}

			}


			if (actions_counter == 2) {

				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						cube1[i][j] = 1.0f;
					}
				}

			}


			if (actions_counter == 2)
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (j == 2)
							cube2[i][j] = 1.0f;
						else
						{
							cube2[i][j] = 0.0f;
						}
					}
				}

			if (actions_counter == 3) {

				for (int i = 0; i < 3; i++)
				{
					rectangle[i] = 1.0f;
				}


			}

			if (actions_counter == 4) {
				for (int i = 0; i < 3; i++)
				{
					rectangle[i] = NULL; // //scoatem afara si pompa(dreptunghiul)
				}

				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						cube1[i][j] = NULL; //scoatem afara cubul1 (cel fara apa)

					}
				}

				pozitia_cub2 = -1.0f; //Repozitionam cubul 2(cubul cu apa)
				marime_cub2 = -7.0f; //(Il marim)
				roteste = true; //Rotim cubul plin cu apa pentru o animatie draguta

			}


		}


		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}




void reshape(GLsizei width, GLsizei height) {

	if (height == 0) height = 1; // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(640, 480); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left
	glutCreateWindow(title); // Create window with the given title
	glutDisplayFunc(display); // Register callback handler for window repaint event
	glutReshapeFunc(reshape); // Register callback handler for window resize event
	glutMouseFunc(mouse);
	initGL(); // Our own OpenGL initialization
	glutTimerFunc(0, timer, 0);
	glutMainLoop(); // Enter the infinite event-processing loop


	return 0;
}
