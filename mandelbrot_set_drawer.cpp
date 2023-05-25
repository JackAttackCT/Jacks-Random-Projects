/*
Mandelbrot set drawer
Made by Jack Morrison, Germantown Computer Science Cohort 2020

This Program draws the Mandelbrot set, with varying levels of zoom.
You can change how the set looks by changing the constants from line 27 to line 32
Feel free to play around with it, you can get some pretty cool results
I recommend starting with ENABLESEMISTABLE off, and then turning it on once you know what the normal set looks like

Some recommended combinations:
	ASTEPSIZE	BSTEPSIZE	HORIZOFFSET

	0.01        0.02        0.2
	0.0025      0.005       0.5
	0.005       0.01         1.5
*/

#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

const double AXISTOLERANCY = 0.00000001;//deals with floating point weirdness for graphing axes
const int CHARSPERLINE = 236;//how many characters fit on a line before wrapping around
const int MAXITERATIONS = 200;//how many times z iterates before a point is considered stable

const double ASTEPSIZE = 0.0025;//x scaling factor - how far between samples of a - should go evenly into 3
const double BSTEPSIZE = 0.005;//y scaling factor - how far between samples of b - should go evenly into 2
const double HORIZOFFSET = 0.5;//how far the set should be shifted left - should be multiple of ASTEPSIZE

//0 -> simple, 1 -> complex
const bool ENABLESEMISTABLE = 1;//1 if unstable points should be ranked on instability, 0 if it should be stable/unstable

const vector<char>SEMISTABLECHARS = {'.', '~', ',', '^', '!', '*', ';', '?'};//characters to represent each level of semistability (the closer to stable the denser the text should be). ' ' should be item 0

//given a complex number c where c_a is the real component and c_b is the imaginary, return -1 if the point lies within
//the mandelbrot set, return the number of iterations it takes to leave a radius 2 otherwise
int calcpoint(double c_a, double c_b)
{
	double z_a = 0, z_b = 0, temp;//p is a complex number that keeps track of where the orbit lies.
	//temp holds the previous value of z_a temporarily while calculations happen
	for (int i = 0; i < MAXITERATIONS; i++) {
		//update z
		temp = z_a;						//
		z_a = pow(z_a, 2) - pow(z_b, 2);//Square z
		z_b = 2 * temp * z_b;			//
		z_a += c_a;//add c
		z_b += c_b;//

		//check to see if z is farther than 2 away from origin with pythagorean theorum
		//if the distance from the origin is greater than 2, we know that the orbit will never stabilize
		if (sqrt(pow(z_a, 2) + pow(z_b, 2)) > 2)
			return i;//if the orbit leaves the stable zone, return how many iterations it took
	}
	//if function has not yet returned 0, the point can be considered stable and 1 is returned
	return -1;
}

int main()
{
	//user needs to be in fullscreen so the text doesn't wrap weirdly
	cout << "Go into fullscreen, then enter any key to start.\n";
	cin.get();

	int result;//stores output from function
	int charcount;//keeps track of how many characters have beeb outputted to the current line
	for (double b = 1; b >= -1; b -= BSTEPSIZE) {//start at b = 1, move down towards b = -1, move by specified distance

		charcount = 0;//reset character counter
		
		for (double a = -2 + HORIZOFFSET; a <= 1; a += ASTEPSIZE) {//move from -2 to 1, move by specified distance, start point can be shifted with horizoffset
			
			if (charcount >= CHARSPERLINE) 
				break;//if the line is full, end calculation for this a value to prevent text from wrapping
			
			result = calcpoint(a, b);//find whether or not the complex number a+bi is in the set
			
			if (result == -1)//if the number is in the set, output #
				cout << '#';

			else if (b > -AXISTOLERANCY && b < AXISTOLERANCY)//if b is 0 within some tollerance, draw horizontal axis
				cout << '-';                                 //tolerance negates floating point rounding errors when a or b become 0
			
			else if (a > -AXISTOLERANCY && a < AXISTOLERANCY)//if a is 0 within some tollerance, draw vertical axis
				cout << '|';
			
			else if (ENABLESEMISTABLE && result > 0)//if plotting semistable values is enabled
				cout << SEMISTABLECHARS[(result - 1) % SEMISTABLECHARS.size()];//each semistability level uses the next symbol in the vecot; when it reaches the end of the vector, it loops back to the start and reuses characters
			
			else
				cout << ' ';//if there is nothing at the point, draw empty space
			
			charcount++;//increase the character count by 1
		}
		cout << endl;//put a line break after a b value has been fully calculated to  move to next line
	}
	return 0;
}