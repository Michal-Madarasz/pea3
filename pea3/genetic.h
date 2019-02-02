#pragma once
class Genetic
{
private:
	vector<vector<int>> matrix;
	vector<vector<int>> perm;
	vector<int> pathLength;
	int population;
	int generation;
	int crossNumber;
	float crossProbability;
	float mutationProbability;
	int mutationType;
	double duration;

	time_t runtime;
	__int64 counter = 0;
	double frequency = 1;

	int cities;
	int optimum;

public:
	Genetic();
	Genetic(time_t runtime, int population, float mutationProbability, float crossProbability, int mutationType);
	~Genetic();
	void permutation();
	void anotherPath();
	void crossing();
	void crossEven();
	void crossOdd();
	void mutation();
	void transposition(int chap);
	void inversion(int chap);
	void insertion(int chap);
	void showPopulation();
	void showData();
	void reducePopulation();
	bool readFile(std::string filename);
	void start();
	void setParameters(time_t runtime, int population, float mutationProbability, float crossProbability, int mutationType);
	double stop();
	void showResult();
	void execute(string filename);
};

