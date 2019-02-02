#pragma once
#include "genetic.h"
class Menu
{
	Genetic *genetic;
	string filename;
	time_t runtime;
	int population;
	float mutationProbability;
	float crossProbability;
	int mutationType;

public:
	Menu();
	~Menu();
	void mainMenu();
	void showMenu();
	void chooseOption();
	void showParameters();
};

