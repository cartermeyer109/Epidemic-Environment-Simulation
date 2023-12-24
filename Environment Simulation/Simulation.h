#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Human.h"

using namespace std;

class Simulation {
private:
	//Fields
	int childDead;
	int adultDead;
	int elderDead;
	int day;
	int children;
	int adults;
	int elders;

public:
	//Constructors
	Simulation(int c, int a, int e, vector<vector<Human>> &vect );

	//Public Methods
	void movePeople(vector<vector<Human>> &vect);
	void levelIncreaseAll(vector < vector < Human>>& vect);
	void proceedInfection(vector<vector<Human>>& vect);
	void dayForward(vector<vector<Human>> &vect);
	void readStats(vector<vector<Human>> &vect);
	void placeHumans(int humanCount, int humanClass, vector<vector<Human>>& vect);
	string spaceDecider(int stat);
};
