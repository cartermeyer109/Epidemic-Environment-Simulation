#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Human {
private:
	//Fields
	bool infected = false;
	int level = 0;
	int age = 0;
	bool moved = false;
	bool antibodies = false;

public:
	//Constructors
	Human();
	Human(bool infected, int age);

	//Public Methods
	void setInfected(bool i);
	void setLevel(int l);
	void setAge(int a);
	void setMoved(bool m);
	void setAntibodies(bool ab);
	bool getInfected();
	int getLevel();
	int getAge();
	bool getMoved();
	bool getAntibodies();
	void levelIncrease();
	void receiveInfectionOneSpace();
	void receiveInfectionTwoSpace();
	
};