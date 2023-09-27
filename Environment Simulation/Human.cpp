#include "Human.h"
#include <cstdlib>

//Default constructor that sets all feilds to false/0 (serves as a placeholder human)
Human::Human()
{
}

//Constructor that takes in age demographic and if they are infected
Human::Human(bool inf, int age)
{
	
	infected = inf;
	//if the new human is infected, set the level to 1 (Incubation period)
	if (infected == true) {
		level = 1;
	}
	this->age = age;
}

void Human::setInfected(bool i)
{
	infected = i;
}

void Human::setLevel(int l)
{
	level = l;
}

void Human::setAge(int a)
{
	age = a;
}

void Human::setMoved(bool m)
{
	moved = m;
}

void Human::setAntibodies(bool ab) {
	antibodies = ab;
}

bool Human::getInfected()
{
	return infected;
}

int Human::getLevel()
{
	return level;
}

int Human::getAge()
{
	return age;
}

bool Human::getMoved()
{
	return moved;
}

bool Human::getAntibodies()
{
	return antibodies;
}

//May or may not increase the level stat of a human depending on different percentage chances
void Human::levelIncrease() {

	//Only execute the code in the function of the human is infected
	if (infected == true) {
		//Generate random number from 1-100
		int r = rand() % 100 + 1;

		//If level is in incubation period (1)
		if (level == 1) {
			//5% chance it will go up to asymptomatic(2)
			if (5 >= r) {
				level = 2;
			}
			//15% chance it will go up to symptomatic(3)
			if (r > 5 && r <= 20) {
				level = 3;
			}
			//Otherwise level will stay in incubation period (1)
		}

		//Incubation period is constant among all demographics

		//If level is asymptomatic or symptomatic (2/3)
		else if (level == 2 || level == 3) {
			//If the human's age is 1 (child)
			if (age == 1) {
				//50% chance it will stay at current level
				if (r <= 60) {
				}
				//30% chance it will go back to uninfected now with antibodies
				if (r > 50 && r <= 97) {
					level = 0;
					infected = false;
					antibodies = true;
				}
				//4% chance it will go to death
				if (r <= 100 && r > 96) {
					level = 4;
				}
			}
			//If the human's age is 2 (adult)
			else if (age == 2) {
				//50% chance it will stay at current level
				if (r <= 50) {
				}
				//48% chance it will go back to uninfected now with antibodies
				else if (r > 50 && r <= 98) {
					level = 0;
					infected = false;
					antibodies = true;
				}
				//2% chance it will go to death
				else if (r <= 100 && r > 98) {
					level = 4;
				}
			}
			//If the human's age is 3 (elder)
			else if (age == 3) {
				//50% chance it will stay at current level
				if (r <= 50) {
				}
				//45% chance it will go back to uninfected now with antibodies
				if (r > 50 && r <= 95) {
					level = 0;
					infected = false;
					antibodies = true;
				}
				//5% chance it will go to death
				if (r <= 100 && r > 95) {
					level = 4;
				}
			}
		}
	}
}

//Causes a human to become infected based on different percentages
//if an infected person is one space away from them using a random 
//number as the parameter
void Human::receiveInfectionOneSpace() {
	//generate random #
	int r = rand() % 100 + 1;

	//If human's is a child (age is 1)
	if (age == 1) {
		//80 percent chance to be infected without antibodies
		if (antibodies == false) {
			if (r > 0 && r <= 80) {
				infected = true;
				level = 1;
			}
		}
		//25 percent chance to be infected with antibodies
		else if (antibodies == true) {
			if (r > 0 && r <= 25) {
				infected = true;
				level = 1;
			}
		}
	}
	//If human's age is adult (age is 2)
	else if (age == 2) {
		//70 percent chance to be infected without antibodies
		if (antibodies == false) {
			if (r > 0 && r <= 70) {
				infected = true;
				level = 1;
			}
		}
		//20 percent chance to be infected with antibodies
		else if (antibodies == true) {
			if (r > 0 && r <= 20) {
				infected = true;
				level = 1;
			}
		}
	}
	//If human's age is elder (age is 3)
	else if (age == 3) {
		//90 percent chance to be infected without antibodies
		if (antibodies == false) {
			if (r > 0 && r <= 90) {
				infected = true;
				level = 1;
			}
		}
		//30 percent chance to be infected with antibodies
		else if (antibodies == true) {
			if (r > 0 && r <= 30) {
				infected = true;
				level = 1;
			}
		}
	}
}

//Causes a human to become infected based on different percentages
//if an infected person is two space away from them using a random 
//number as the parameter
void Human::receiveInfectionTwoSpace() {
	//generate random #
	int r = rand() % 100 + 1;
	
	//If human's age is child (age is 1)
	if (age == 1) {
		//60 percent chance to be infected without antibodies
		if (antibodies == false) {
			if (r > 0 && r <= 60) {
				infected = true;
				level = 1;
			}
		}
		//15 percent chance to be infected without antibodies
		else if (antibodies == true) {
			if (r > 0 && r <= 15) {
				infected = true;
				level = 1;
			}
		}
	}
	//If human's age is adult (age is 2)
	else if (age == 2) {
		//50 percent chance to be infected without antibodies
		if (antibodies == false) {
			if (r > 0 && r <= 50) {
				infected = true;
				level = 1;
			}
		}
		//10 percent chance to be infected without antibodies
		else if (antibodies == true) {
			if (r > 0 && r <= 10) {
				infected = true;
				level = 1;
			}
		}
	}
	//If human's age is elder (age is 3)
	else if (age == 3) {
		//70 percent chance to be infected without antibodies
		if (antibodies == false) {
			if (r > 0 && r <= 70) {
				infected = true;
				level = 1;
			}
		}
		//20 percent chance to be infected without antibodies
		else if (antibodies == true) {
			if (r > 0 && r <= 20) {
				infected = true;
				level = 1;
			}
		}
	}
}
