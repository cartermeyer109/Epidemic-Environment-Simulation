#include "Simulation.h"
#include <iostream>
#include <windows.h>

//Constructor that sets the board using number of children, adults, and elders, and a vector of placeholder humans
Simulation::Simulation(int c, int a, int e, vector<vector<Human>> &vect)
{
	//Initialize all variables
	children = c;
	adults = a;
	elders = e;
	childDead = 0;
	adultDead = 0;
	elderDead = 0;
	day = 0;

	//Plant a random seed at the start of the simulation for all function to use
	srand(time(NULL));

	//Places humans of different age classes on the board
	placeHumans(c, 1, vect);
	placeHumans(a, 2, vect);
	placeHumans(e, 3, vect);
}

//Moves every human 1 space or no spaces depending on a random number chosen 
void Simulation::movePeople(vector<vector<Human>> &vect)
{
	//Sets each humans "moved" variable to false, indicating that they have yet to move this day
	for (int row = 2; row < 12; row++) {
		for (int col = 2; col < 12; col++) {
			vect[row][col].setMoved(false);
		}
	}

	//Go through every Human on the playable grid
	for (int row = 2; row < 12; row++) {
		for (int col = 2; col < 12; col++){
			//If the human is not a placeholder human
			if (vect[row][col].getAge() != 0) {

				//generate random #
				int r = rand() % 100 + 1;

				//Only if the human hasn't moved, execute the following code
				if (vect[row][col].getMoved() == false) {
					
					//If the column to the left is not out of bounds
					if ((col - 1) != 1) {
						//If the random number is in this 25% range and the human to the left is only a placeholder
						if (r > 0 && r <= 25 && vect[row][col - 1].getAge() == 0) {
							//mark that this human has moved
							vect[row][col].setMoved(true);

							//Put this human in the spot to the left
							vect[row][col - 1] = vect[row][col];
							vect[row][col] = Human();
						}
					}
					//If the row above is not out of bounds
					if ((row - 1) != 1) {
						//If the random number is in this 25% range and the human above is only a placeholder
						if (r > 25 && r <= 50 && vect[row - 1][col].getAge() == 0) {
							//mark that this human has moved
							vect[row][col].setMoved(true);

							//Put this human in the spot above
							vect[row - 1][col] = vect[row][col];
							vect[row][col] = Human();
						}
					}
					//If the column to the right is not out of bounds
					if ((col + 1) != 12) {
						//If the random number is in this 25% range and the human to the right is only a placeholder
						if (r > 50 && r <= 75 && vect[row][col + 1].getAge() == 0) {
							//mark that this human has moved
							vect[row][col].setMoved(true);

							//Put this human in the spot to the right
							vect[row][col + 1] = vect[row][col];
							vect[row][col] = Human();
						}
					}
					//If the row below is not out of bounds
					if ((row + 1) != 12) {
						//If the random number is in this 25% range and the human below is only a placeholder
						if (r > 75 && r <= 100 && vect[row + 1][col].getAge() == 0) {
							//mark that this human has moved
							vect[row][col].setMoved(true);
							
							//Put this human in the spot to the bottom
							vect[row + 1][col] = vect[row][col];
							vect[row][col] = Human();
						}
					}
				}
			}
		}
	}
}

//Uses the levelIncrease function from Human.h on all Humans in the vector
void Simulation::levelIncreaseAll(vector<vector<Human>>& vect)
{
	for (int row = 2; row < 12; row++) {
		for (int col = 2; col < 12; col++) {
			vect[row][col].levelIncrease();
		}
	}
}

//Goes through all humans in the vector and decide if they receive an infection based on difference percentages
void Simulation::proceedInfection(vector<vector<Human>>& vect) {
	//Go through whole vector
	for (int row = 2; row < 12; row++) {
		for (int col = 2; col < 12; col++) {
			//If the human is not infected and the age is any other than 0
			if (vect[row][col].getInfected() == false && vect[row][col].getAge() > 0) {

				//If there is no infected human 1 or 2 spaces away do nothing
				if (vect[row - 1][col - 1].getInfected() == false && vect[row - 1][col].getInfected() == false && vect[row - 1][col + 1].getInfected() == false
					&& vect[row][col - 1].getInfected() == false && vect[row][col + 1].getInfected() == false && vect[row + 1][col - 1].getInfected() == false
					&& vect[row + 1][col].getInfected() == false && vect[row + 1][col + 1].getInfected() == false && vect[row - 2][col].getInfected() == false
					&& vect[row + 2][col].getInfected() == false && vect[row][col + 2].getInfected() == false && vect[row][col - 2].getInfected() == false) {

				}

				//If there is any number of infected humans 1 space away activate receiveInfectionOneSpace function
				// with random #
				else if (vect[row - 1][col].getInfected() == true || vect[row][col - 1].getInfected() == true || vect[row][col + 1].getInfected() == true
					|| vect[row + 1][col].getInfected() == true) { 
					vect[row][col].receiveInfectionOneSpace();
				}

				//If there is any number of infected humans 2 spaces away activate receiveInfectionTwoSpace function
				// with random #
				else if (vect[row + 1][col + 1].getInfected() == true || vect[row - 2][col].getInfected() == true
					|| vect[row + 2][col].getInfected() == true || vect[row][col + 2].getInfected() == true || vect[row][col - 2].getInfected() == true
					|| vect[row - 1][col - 1].getInfected() == true || vect[row - 1][col + 1].getInfected() == true
					|| vect[row + 1][col - 1].getInfected() == true) {
					vect[row][col].receiveInfectionTwoSpace();
				}
			}
		}
	}
}

//Moves, gives infections a chance to progress, and gives a chance to become infected to all humans
//and increases day counter
void Simulation::dayForward(vector<vector<Human>> &vect)
{
	day++;
	movePeople(vect);
	levelIncreaseAll(vect);
	proceedInfection(vect);
}

//Calculates and displays all the stats in the vector
void Simulation::readStats(vector<vector<Human>> &vect)
{
	//Initiates consol to allow text color chance
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//Keeps track of all stats
	//Stats are initialized within the function because
	//they are re-evaluated every time function is called
	int childIncubation = 0;
	int adultIncubation = 0;
	int elderIncubation = 0;
	int childAsymptomatic = 0;
	int adultAsymptomatic = 0;
	int elderAsymptomatic = 0;
	int childSymptomatic = 0;
	int adultSymptomatic = 0;
	int elderSymptomatic = 0;
	int childUninfected = 0;
	int adultUninfected = 0;
	int elderUninfected = 0;

	//Goes through entire vector
	for (int row = 2; row < 12; row++) {
		for (int col = 2; col < 12; col++) {

			//If the human is a child and has one of the following conditions
			//add one to their respective condition's counter
			if (vect[row][col].getAge() == 1) {
				if (vect[row][col].getInfected() == false) {
					childUninfected++;
				}
				if (vect[row][col].getLevel() == 1) {
					childIncubation++;
				}
				if (vect[row][col].getLevel() == 2) {
					childAsymptomatic++;
				}
				if (vect[row][col].getLevel() == 3) {
					childSymptomatic++;
				}
				if (vect[row][col].getLevel() == 4) {
					childDead++;

					//Removes the human from the vector with a placeholder human
					vect[row][col] = Human();
				}
			}

			//If the human is an adult and has one of the following conditions
			//add one to their respective condition's counter
			if (vect[row][col].getAge() == 2) {
				if (vect[row][col].getInfected() == false) {
					adultUninfected++;
				}
				if (vect[row][col].getLevel() == 1) {
					adultIncubation++;
				}
				if (vect[row][col].getLevel() == 2) {
					adultAsymptomatic++;
				}
				if (vect[row][col].getLevel() == 3) {
					adultSymptomatic++;
				}
				if (vect[row][col].getLevel() == 4) {
					adultDead++;

					//Removes the human from the vector with a placeholder human
					vect[row][col] = Human();
				}
			}

			//If the human is an elder and has one of the following conditions
			//add one to their respective condition's counter
			if (vect[row][col].getAge() == 3) {
				if (vect[row][col].getInfected() == false) {
					elderUninfected++;
				}
				if (vect[row][col].getLevel() == 1) {
					elderIncubation++;
				}
				if (vect[row][col].getLevel() == 2) {
					elderAsymptomatic++;
				}
				if (vect[row][col].getLevel() == 3) {
					elderSymptomatic++;
				}
				if (vect[row][col].getLevel() == 4) {
					elderDead++;

					//Removes the human from the vector with a placeholder human
					vect[row][col] = Human();
				}
			}
		}
	}

	//Displays all the stats and information
	cout << "******************************************************************************************" << endl;
	SetConsoleTextAttribute(hConsole, day % 15 + 1);
	cout << "DAY " << day;
	SetConsoleTextAttribute(hConsole, 3);
	cout << "      CHILDREN";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "****";
	SetConsoleTextAttribute(hConsole, 6);
	cout << "ADULTS";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "****";
	SetConsoleTextAttribute(hConsole, 13);
	cout << "ELDERS" << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Total:        " << children << spaceDecider(children) << adults << spaceDecider(adults) << elders << endl;
	cout << "Alive:        " << children - childDead << spaceDecider(children - childDead) << adults - adultDead << spaceDecider(adults - adultDead) << elders - elderDead << endl;
	cout << "Uninfected:   " << childUninfected << spaceDecider(childUninfected) << adultUninfected << spaceDecider(adultUninfected) << elderUninfected << endl;
	
	SetConsoleTextAttribute(hConsole, 10);
	cout << "Incubation:   " << childIncubation << spaceDecider(childIncubation) << adultIncubation << spaceDecider(adultIncubation) << elderIncubation << endl;
	cout << "Asymptomatic: " << childAsymptomatic << spaceDecider(childAsymptomatic) << adultAsymptomatic << spaceDecider(adultAsymptomatic) << elderAsymptomatic << endl;
	cout << "Symptomatic:  " << childSymptomatic << spaceDecider(childSymptomatic) << adultSymptomatic << spaceDecider(adultSymptomatic) << elderSymptomatic << endl;
	
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Dead:         " << childDead << spaceDecider(childDead) << adultDead << spaceDecider(adultDead) << elderDead << endl;
	
	
	
	//Displays the grid visually with each human on it, identifying if they are infected as well
	SetConsoleTextAttribute(hConsole, 10);
	cout << "-------------------------------" << endl;
	SetConsoleTextAttribute(hConsole, 7);
	for (int row = 2; row < 12; row++) {
		for (int col = 2; col < 12; col++) {
			SetConsoleTextAttribute(hConsole, 10);
			cout << "|";
			SetConsoleTextAttribute(hConsole, 7);
			if (vect[row][col].getInfected() == true) {
				SetConsoleTextAttribute(hConsole, 71);
				cout << "I";
				SetConsoleTextAttribute(hConsole, 7);
			}
			else {
				cout << " ";
			}
			if (vect[row][col].getAge() == 1) {
				SetConsoleTextAttribute(hConsole, 3);
				cout << "C";
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (vect[row][col].getAge() == 2) {
				SetConsoleTextAttribute(hConsole, 6);
				cout << "A";
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (vect[row][col].getAge() == 3) {
				SetConsoleTextAttribute(hConsole, 13);
				cout << "E";
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (vect[row][col].getAge() == 0) {
				cout << " ";
			}
		}
		SetConsoleTextAttribute(hConsole, 10);
		cout << "|" << endl;
		cout << "-------------------------------" << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
}

//Places humans of a certain age class on the board
void Simulation::placeHumans(int humanCount, int humanClass, vector<vector<Human>>& vect)
{
	//Set this to false until 1 infected of this human class
	//is placed on the board
	bool infectedHuman = false;

	//While not all of this human class has been placed
	while (humanCount > 0) {
		//Create random x and y coordinates (Ignoring rows/columns 0,1,12,13)
		int x = rand() % 10 + 2;
		int y = rand() % 10 + 2;

		//If there is currently a placeholder human in the chosen spot,
		//and the infected human hasn't been placed yet
		if (vect[x][y].getAge() == 0 && infectedHuman == false) {

			//Places infected human in spot
			vect[x][y] = Human(true, humanClass);

			//Sets bool to true so no more infected humans will be placed
			infectedHuman = true;

			humanCount--;
		}
		//If there is currently a placeholder human in the chosen spot,
		// and an infected human has already been placed
		else if (vect[x][y].getAge() == 0) {

			//Places non-infected human in spot
			vect[x][y] = Human(false, humanClass);

			humanCount--;
		}
	}
}

string Simulation::spaceDecider(int stat)
{
	string spaces;

	//Creates one less space if the stat is in the double digits
	//This creates a better looking start chart
	for (int i = 0; i < 9 - (stat / 10); i++) {
		spaces += " ";
	}

	return spaces;
}
