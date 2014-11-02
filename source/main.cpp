//the main
#include "filter.h"
#include "kinematics.h"
#include <time.h>
#include <GL\glew.h>
#include <GL\freeglut.h>

//constant values
const int DIM = 3, FPS = 48, WHITE = 0, BLACK = 1, RED = 2, BLUE = 3, GREEN = 4;
const float xThresh = 0.005f, yThresh = 0.01f;
const int WIDTH = 1600, HEIGHT = 900;
const float scaleA = 1.0, scaleV = 1.0, scaleS = 1.0, armLength = 2.0; //stores the  armlength of the person using the program
bool first = true;

void draw(float x, float y, float tipSize, int textColor, float pX, float pY, float cursorY, float yCursor, bool notSpread, bool erase) {
	//sets up the color for clearing the screen
	//glClearColor(1.0f, 1.0f, 1.0f, 0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//sets up the screen coordinates
	switch (textColor) {
	case WHITE:
		glColor3ub(255, 255, 255);
		break;
	case BLACK:
		glColor3ub(0, 0, 0);
		break;
	case RED:
		glColor3ub(255, 0, 0);
		break;
	case BLUE:
		glColor3ub(0, 0, 255);
		break;
	case GREEN:
		glColor3ub(0, 255, 0);
		break;
	default:
		glColor3ub(0, 0, 0);
		break;
	}

	if (notSpread && !first && !erase && fabs(pX - x) < 0.5f && fabs(pY - y) < 0.5f) {
		glPointSize(tipSize);
		glBegin(GL_LINES);
		glVertex2f(x, y);
		glVertex2f(pX, pY); //drawing point on the screen
		glEnd();
	}
	else if (erase) {
	glPointSize(tipSize);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	}
	first = false;
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	//clear the cursor
	glColor3ub(255, 255, 255);
	glVertex2f(pX, cursorY);
	//print new cursor
	glColor3ub(0, 0, 255);
	glVertex2f(x, yCursor);
	glEnd();
	glutSwapBuffers();
	glReadBuffer(GL_FRONT);
	glDrawBuffer(GL_BACK);
	glCopyPixels(0, 0, WIDTH, HEIGHT, GL_COLOR);
}

int main(int argc, char** argv)
{
	
	//int timeInt = 1000000 / FPS;
	//for storing the accelerometer data and the position vector data
	float tipSize = 2.5f, xScale = 2.0f, yScale = 4.0f;
	int textColor = BLACK;
	//set up the GUI
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("MyoPad");
	glClearColor(1.0f, 1.0f, 1.0f, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30, 30, -30, 30, -30, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	bool erase = false;
	bool write = true;
	
	// We catch any exceptions that might occur below -- see the catch statement for more details.
	try {

		// First, we create a Hub with our application identifier.
		myo::Hub hub("com.myohack.myopad");

		std::cout << "Attempting to find a Myo..." << std::endl;

		// Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
		// immediately.
		// waitForAnyMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
		// if that fails, the function will return a null pointer.
		myo::Myo* myo = hub.waitForMyo(10000);
		
		// If waitForAnyMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
		if (!myo) {
			throw std::runtime_error("Unable to find a Myo!");
		}

		// We've found a Myo.
		std::cout << "Connected to a Myo armband!" << std::endl << std::endl;

		// Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
		Filter collector;

		//Kinematic accToPos(DIM, scaleA, scaleV, scaleS); //adds the integral class 
		//sets the precision for floating points
		std::cout.precision(2);
		bool check = false;
		hub.addListener(&collector);
		int currentTime = clock();
		hub.run(1000 / FPS);
		float x = -1 * xScale * collector.roll - 25.0f;
		float y = -1 * yScale * collector.pitch + 20.0f; //up is positive
		float xi = x;
		float yi = y;
		float pastX = 0.0, pastY = 0.0, cursorY = 0.0;
		// loop keeps running and mapping the coordinates on the window
		while (true) {
			if (x < xi) {
				if (y < yi) {
					x = 19.9f;
					y += 10.0f;
					first = true;
				}
				else x = xi;
			}
			if (x < 20.0f) {
				//gets 48 packets of data every second
				hub.run(1000 / FPS);

				if (collector.currentPose.toString() == "waveIn")
					x -= 0.15f; //moves the cursor oto the left
				else if (collector.currentPose.toString() == "waveOut")
					x += 0.15f; //moves the cursor to the right

				if (collector.currentPose.toString() == "fist")
				{
					textColor = WHITE;
					tipSize = 100.0f; //for the eraser
					erase = true;
				}else{
					textColor = BLACK;
					tipSize = 2.5f;
				}
				std::cout << collector.currentPose.toString() << " " << tipSize;
				/*else if (collector.currentPose.toString() == "waveOut") {
					textColor++;
					if (textColor > 4)
					textColor = WHITE;
					}*/
				std::cout << '\r';
				if (!(collector.currentPose.toString() == "fingersSpread" || collector.currentPose.toString() == "waveOut" || collector.currentPose.toString() == "waveIn")) {
					check = true;
				}
				draw(x + collector.roll * xScale, y + collector.yaw * yScale, tipSize, textColor, pastX, pastY, cursorY, y - 5.0f, check, erase);
				//draw(pastX, pastY, 5.0f, WHITE);
				//draw(x - 7.5f, y - 5.0f, 5.0f, BLUE);
				pastX = x + collector.roll * xScale;
				pastY = y + collector.yaw * yScale;
				cursorY = y - 5.0f;
				 if (!erase) x += 0.01f;
				check = false;
				erase = false;
				//print the position
				//std::cout << collector.roll << " " << collector.yaw;
			}
			else {
				first = true;
				y -= 10.0f;
				x = xi; //switches the position of x to its initial position
			}
		}
	}
	// If a standard exception occurred, we print out its message and exit.
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Press enter to continue.";
		std::cin.ignore();
		return 1;
	}

	return 0;
}