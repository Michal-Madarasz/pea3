#include "pch.h"
#include "genetic.h"


Genetic::Genetic()
{
	population = 10;
	crossNumber = 3;
	mutationProbability = 0.01f;
	crossProbability = 0.8f;
	matrix.resize(1000);
	mutationType = 1;
}


Genetic::Genetic(time_t runtime,int population,float mutationProbability,float crossProbability, int mutationType) {
	this->population = population;
	this->mutationProbability = mutationProbability;
	this->runtime = runtime;
	this->crossProbability = crossProbability;
	this->mutationType = mutationType;
}


Genetic::~Genetic()
{
}

void Genetic::permutation() {
	vector<int> vec;
	vec.resize(cities);
	pathLength.resize(population);
	for (int i = 0; i < cities; i++) {
		vec[i] = i;
	}

	perm.resize(population);
	for (int i = 0; i < population; i++) {
		random_shuffle(vec.begin()+1, vec.end());
		perm[i] = vec;
	}
}


void Genetic::anotherPath() {
	int length = 0;
	pathLength.resize(perm.size());

	for (size_t i = 0; i < perm.size(); i++) {
		for (size_t j = 0; j < perm[i].size()-1; j++) {
			length += matrix[perm[i][j]][perm[i][j+1]];
		}
		length += matrix[perm[i][cities-1]][perm[i][0]];
		pathLength[i] = length;
		length = 0;
	}
}

void Genetic::crossing() {
	if (cities % 2 == 0) {
		crossEven();
	}
	else {
		crossOdd();
	}
}

void Genetic::crossEven() {
	vector<vector<int>> childrenPopulation;
	vector<pair<int, int>> crossed;
	int temp = 0;
	vector<float> probability(population);

	for (size_t j = 0; j < probability.size(); j++) {
		probability[j] = static_cast <float> ((rand()) / (RAND_MAX));
	}

	for (size_t i = 0; i < probability.size(); i++) {
		if (probability[i] < crossProbability) {
			do {
				temp = rand() % population;
			} while (temp == i);
			crossed.push_back(make_pair(i, temp));
		}
	}

	//do poprawy
	/*for (size_t i = 0; i < crossed.size(); i++) {
		if (crossed[i].first == 0 && crossed[i].second == 0) {
			crossed.erase(crossed.begin() + i);
		}
	}*/

	crossed.shrink_to_fit();

	for (size_t i = 0; i < crossed.size(); i++) {

		int father = crossed[i].first;
		int mother = crossed[i].second;

		//poni¿ej krzy¿owanie

		int half = (int)perm[father].size() / 2;
		vector<int> temp(cities / 2);
		vector<int> child(cities);
		for (int j = 0; j < half; j++) {
			child[j] = perm[crossed[i].first][j];
		}

		vector<int> temp2(half);
		for (int j = 0; j < half; j++) {
			for (int k = 0; k < cities; k++) {
				if (perm[father][j + half] == perm[mother][k]) {
					temp2[j] = k;
				}
			}
		}

		sort(temp2.begin(), temp2.end());
		for (int j = 0; j < cities / 2; j++) {
			child[j + cities / 2] = perm[crossed[i].second][temp2[j]];
		}

		childrenPopulation.push_back(child);
		//cout << "Skrosowano: " << crossed[i].first << " oraz " << crossed[i].second << "\n";
	}

	perm.resize(population + (int)childrenPopulation.size());

	for (size_t i = 0; i < (int)childrenPopulation.size(); i++) {
		perm[i + population] = childrenPopulation[i];
	}
}

void Genetic::crossOdd() {
	vector<vector<int>> childrenPopulation;
	vector<pair<int, int>> crossed;
	int temp = 0;
	vector<float> probability(population);

	for (size_t j = 0; j < probability.size(); j++) {
		probability[j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}

	for (size_t i = 0; i < probability.size(); i++) {
		if (probability[i] < crossProbability) {
			do {
				temp = rand() % population;
			} while (temp == i);
			crossed.push_back(make_pair(i, temp));
		}
	}

	crossed.shrink_to_fit();

	for (size_t i = 0; i < crossed.size(); i++) {

		int father = crossed[i].first;
		int mother = crossed[i].second;

		//poni¿ej krzy¿owanie

		int half = (int)perm[father].size() / 2;
		vector<int> temp(cities / 2);
		vector<int> child(cities);
		for (int j = 0; j < half + 1; j++) {
			child[j] = perm[crossed[i].first][j];
		}

		vector<int> temp2(half);
		for (int j = 0; j < half; j++) {
			for (int k = 0; k < cities; k++) {
				if (perm[father][j + half + 1] == perm[mother][k]) {
					temp2[j] = k;
				}
			}
		}

		sort(temp2.begin(), temp2.end());
		for (int j = 0; j < cities / 2; j++) {
			child[j + cities / 2 + 1] = perm[crossed[i].second][temp2[j]];
		}

		childrenPopulation.push_back(child);
		//cout << "Skrosowano: " << crossed[i].first << " oraz " << crossed[i].second << "\n";
	}

	perm.resize(population + (int)childrenPopulation.size());

	for (size_t i = 0; i < childrenPopulation.size(); i++) {
		perm[i + population] = childrenPopulation[i];
	}

	////liczenie drog dla nowych czlonkow populacji
	//pathLength.resize(population + crossNumber);
	//for (int i = 0; i < population + crossNumber; i++) {
	//	pathLength[i] = computePath(perm[i]);
	//}
}

void Genetic::mutation() {
	vector<float> probability(perm.size());

	for (int i = 0; i < population; i++) {
		probability[i] = static_cast <float> (rand()) / (RAND_MAX);
	}

	for (int i = 0; i < population; i++) {
		if (probability[i] < mutationProbability) {
			if (mutationType == 1) {
				inversion(i);
			}
			else if (mutationType == 2) {
				insertion(i);
			}
			else if (mutationType == 3) {
				transposition(i);
			}
			else {
				return;
			}
		}
	}
}

void Genetic::transposition(int chap) {
	int first = perm[chap][+1 + (rand() % cities-1)];
	int last = 0;
	do {
		last = perm[chap][1+(rand() % cities-1)];
	} while ( first == last );

	swap(first, last);

}

void Genetic::inversion(int chap) {
	int first = rand() % (cities-1) + 1;
	int second = 0;

	do {
		second = rand() % (cities-1) + 1;
	} while (first == second);

	if (second < first) {
		swap(first, second);
	}

	reverse(perm[chap].begin() + first, perm[chap].begin() + second);
}

void Genetic::insertion(int chap) {
	auto first = perm[chap].begin() + 1 + (rand() % cities - 1);
	auto last = perm[chap].begin() + 1 + (rand() % cities - 1);

	perm[chap].insert(first, *last);
	perm[chap].erase(last);
}

void Genetic::showPopulation() {

	for (size_t i = 0; i < perm.size(); i++) {
		cout << i+1 << ". ";
		for (int j = 0; j < cities; j++) {
			cout << perm[i][j] << " ";
		}
		cout << "Length: " << pathLength[i] << "\n";
		cout << "\n\n";
	}
}

void Genetic::showData() {
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = 0; j < matrix.size(); j++) {
			cout.width(5);
			cout << matrix[i][j] << " ";
		}

		cout << "\n";
	}
}

void Genetic::reducePopulation() {
	vector<int> temp(population);

	for (size_t i = 0; i < (int)perm.size()-1; i++) {
		for (size_t j = 0; j < perm.size() - 1; j++) {
			if (pathLength[j] > pathLength[j + 1]) {
				swap(pathLength[j], pathLength[j + 1]);
				swap(perm[j], perm[j + 1]);
			}
		}
	}

	/*for (int i = 0; i < perm.size()-1; i++) {
		if (pathLength[i] == pathLength[i + 1]) {
			perm.erase(perm.begin() + i);
			pathLength.erase(pathLength.begin() + i);
		}
	}*/

	if((int)perm.size() > population) {
		perm.erase(perm.begin() + population, perm.end());
		pathLength.erase(pathLength.begin() + population, pathLength.end());
	}
}

bool Genetic::readFile(std::string filename) {
	std::fstream file;
	file.open((filename + ".txt").c_str(), std::ios::in);

	if (file.good()) {

		file >> cities >> optimum;

		matrix.resize(cities);

		for (int i = 0; i < cities; ++i) {
			matrix[i].resize(cities);
			for (int j = 0; j < cities; ++j) {

				file >> matrix[i][j];

			}
		}

		matrix.shrink_to_fit();

		std::cout << "Plik odczytany poprawnie." << std::endl;
		std::cout << std::endl;

		file.close();
		return true;

	}
	else {
		std::cout << "Blad. " << std::endl;
		system("pause");
		file.close();
		return false;
	}
}

void Genetic::start()
{
	LARGE_INTEGER l_int;

	QueryPerformanceFrequency(&l_int);
	frequency = double(l_int.QuadPart);

	QueryPerformanceCounter(&l_int);
	counter = l_int.QuadPart;
}

void Genetic::setParameters(time_t runtime, int population, float mutationProbability, float crossProbability, int mutationType) {
	this->runtime = runtime;
	this->population = population;
	this->mutationProbability = mutationProbability;
	this->crossProbability = crossProbability;
}

double Genetic::stop()
{
	LARGE_INTEGER l_int;
	QueryPerformanceCounter(&l_int);
	return double(l_int.QuadPart - counter) / frequency;
}

void Genetic::showResult() {
	system("cls");
	cout << "Najlepsze znane rozwiazanie: " << optimum << "\n";
	cout << "Najlepsze znalezione rozwiazanie: " << pathLength[0] << "\n";
	cout << "Blad: " << (double)(pathLength[0] - optimum) / optimum << "\n";
	cout << "Czas wykonywania programu: " << duration << "\n";
}

void Genetic::execute(string filename) {

	int counter = 0;
	time_t finish;
	time_t start1 = time(NULL);
	finish = start1 + runtime;

	int oldSolution = INT_MAX;
	int newSolution = INT_MAX;
	std::ofstream outFile(filename, std::ofstream::out);

	this->permutation();
	start();

	while ( start1<finish) {
		this->crossing();
		this->mutation();
		this->anotherPath();
		oldSolution = pathLength[0];
		this->reducePopulation();
		newSolution = pathLength[0];
		if (newSolution < oldSolution && (double)(newSolution - optimum) / optimum != 0) {
			outFile << (double)stop() << " " << (double)(newSolution - optimum) / optimum << "\n";
		}
		start1 = time(NULL);
		stop();
		counter++;
	}
	duration = stop();
	outFile << duration << " " << (double)(newSolution - optimum) / optimum << "\n";
	outFile.close();
	cout << counter << "\n";

	showResult();
}
