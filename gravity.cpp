/*
Runs a 2-dimensional N-body gravity sim
Initial conditions specified in main
*/

#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;

struct Body {
	double xPos, yPos, xv, yv, mass, newXPos, newYPos;
};

const double G = 2;

void calcChanges(vector<Body>& bodies) {//calculates new values for all bodies
	double g;
	double theta;
	for (int i = 0; i < bodies.size(); i++) {//loop through every body
		bodies[i].newXPos = bodies[i].xPos;
		bodies[i].newYPos = bodies[i].yPos;
		for (int j = 0; j < bodies.size(); j++) {//loop through every interaction that body has with others
			if (i == j)//ignore interactions between a body and itself
				continue;
			//only calculate new velocities if the bodies are in different locations, avoid dividing by 0
			if (bodies[i].xPos != bodies[j].xPos || bodies[i].yPos != bodies[j].yPos) {
				//calculate acceleration from gravity, g. a = f/m = (G*m1m2/r^2)/m1=G*m2/sqrt((x1-x2)^2 + (y1-y2)^2)^2 = G*m2/((x1-x2)^2+(y1-y2)^2)
				g = G * bodies[j].mass / (pow(bodies[i].xPos - bodies[j].xPos, 2.0) + pow(bodies[i].yPos - bodies[j].yPos, 2.0));
				//calculate angle of force vector in radians
				theta = atan2(bodies[j].yPos - bodies[i].yPos, bodies[j].xPos - bodies[i].xPos);
				//split force vector into x and y components and add to the current velocity
				bodies[i].xv +=  g * cos(theta);
				bodies[i].yv +=  g * sin(theta);
			}
		}
		//calculate new positions from new velocities
		bodies[i].newXPos += bodies[i].xv;
		bodies[i].newYPos += bodies[i].yv;
	}
}

void update(vector<Body>& bodies) {//updates all positions of bodies
	for (int i = 0; i < bodies.size(); i++) {//loop through bodies in list
		//update positions
		bodies[i].xPos = bodies[i].newXPos;
		bodies[i].yPos = bodies[i].newYPos;
	}
}

string display(vector<Body>& bodies) {//calculates string to draw bodies
	bool found;
	string output;
	for (int y = 23; y >= -23; y--) {
		for (int x = -40; x <= 40; x++) {
			found = 0;
			for (int i = 0; i < bodies.size(); i++) {
				if (floor(bodies[i].xPos) == x && floor(bodies[i].yPos) == y) {
					output += 'O';
					found = 1;
					break;
				}
			}
			if (!found) {
				if (x == 0 || y == 0)
					output += '*';
				else
					output += ' ';
			}
		}
		output += '\n';
	}
	output += "\n\n\n\n";
	return output;
}

int main() {
	vector<Body>bodies = {
		{-20, 0.5, 0, -0.05, 0.1, 0, 0},
		{20, 0.5, 0, 0.02, 0.2, 0, 0},
		{20, 20, -0.2, 0, 0.1, 0, 0}
	};
	string output;
	while (1) {
		output = display(bodies);
		//system("CLS");
		cout << output;// << "Press ENTER to continue";
		calcChanges(bodies);
		update(bodies);
		//cin.get();
	}
}