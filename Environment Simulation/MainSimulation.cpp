#include "Human.h"
#include "Simulation.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <string>
using namespace std;

int main() {
	//Initiates consol to allow text color chance
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//Incubation period is just for show. It is the period of time between getting a disease to possible showing symptoms. The virus is incubating inside you, rly its just for show

	//Introduces User
	cout << "Welcome to the epidemic simulation (Lasts for 300 days)!" << endl;
	cout << "Keep in mind this is a simulation of a disease that has NO vaccine" << endl;
	cout << "All humans start as uninfected except for 1 human from each age class" << endl;
	cout << "Humans may move each day and the infected will spread based on age/distance" << endl;
	cout << "from the infected / if the virus was previously had" << endl;
	cout << "Uninfected: Can't spread the virus, suseptibilty to obtaining virus depends on if it was previously had" << endl;
	cout << "Incubation: The time between virus contact and symptoms. Capable of spreading the virus, can only turn symptomatic/asymptomatic" << endl;
	cout << "Symptomatic/Asympotmatic: Capable of spreading the virus, can die or turn uninfected again" << endl;


	//Asks user for number of children
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Select number of children (3-10): ";
	int children;
	cin >> children;
	while (cin.fail() || children < 3 || children > 10) {
		cout << "The number of children can only be between 3-10: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> children;
	}

	//asks user for number of adults
	SetConsoleTextAttribute(hConsole, 6);
	cout << "Select number of adults (3-10): ";
	int adults;
	cin >> adults;
	while (cin.fail() || adults < 3 || adults > 10) {
		cout << "The number of adults can only be between 3-10: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> adults;
	}

	//asks user for number of elders
	SetConsoleTextAttribute(hConsole, 13);
	cout << "Select number of elders (3-10): ";
	int elders;
	cin >> elders;
	while (cin.fail() || elders < 3 || elders > 10) {
		cout << "The number of elders can only be between 3-10: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> elders;
	}

	//The Playable grid is 10x10, but a 2d vector of 14x14 is created so
	//checking spots of the grid out of bounds wont result in an error
	vector<vector<Human>> grid(14, vector<Human>(14, Human()));

	//Simulation Grid is created with the selected number of children, adults, elders,
	//and the vector that was just created
	Simulation simulation(children, adults, elders, grid);

	//Reads the stats of day 0, after placement of humans but before infection spread/movements
	simulation.readStats(grid);
	cin.ignore();

	//Goes through 300 days of infection
	int i = 0;
	while (i < 300) {
		
		//User is able to press enter to proceed to next day mnaually
		cout << "Continue to next day: PRESS ENTER";
		cin.ignore();

		//The day moves forward then stats are read again
		simulation.dayForward(grid);
		simulation.readStats(grid);
		i++;
	}

	cout << "The Simulation is over!" << endl;
}