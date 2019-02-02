#include "pch.h"
#include "Test.h"


Test::Test()
{
	file_in = "tsp_43";
	genetic = new Genetic();
	filename = { "first.txt","second.txt", "third.txt" };

	genetic->readFile("tsp_43");
	genetic->setParameters(60, 50, 0.05, 0.8, 1);
	genetic->execute(filename[0]);
	cout << "poprawnie wykonano test";

	genetic->readFile("tsp_171");
	genetic->setParameters(60, 50, 0.05, 0.8, 1);
	genetic->execute(filename[1]);
	cout << "poprawnie wykonano test";

	genetic->readFile("tsp_358");
	genetic->setParameters(60, 50, 0.05, 0.8, 1);
	genetic->execute(filename[2]);
	cout << "poprawnie wykonano test";
	system("pause");
}


Test::~Test()
{
}

