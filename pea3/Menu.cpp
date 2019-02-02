#include "pch.h"
#include "Menu.h"
#include "Test.h"

Menu::Menu()
{
	mutationProbability = 0.01;
	crossProbability = 0.8;
	runtime = 10;
	population = 10;
	mutationType = 1;
	genetic = new Genetic(runtime, population, mutationProbability, crossProbability, mutationType);

	mainMenu();
}


Menu::~Menu()
{

}

void Menu::mainMenu() {
	int choice = 0;
	do {
		cout << "1. Progran\n";
		cout << "2. Testy\n";
		cout << "3. Wyjscie\n";

		do {
			cin >> choice;
		} while (choice < 1 || choice > 3);

		if (choice == 1) {
			chooseOption();
		}
		else if (choice == 2) {
			Test *test = new Test();
		}
	} while (choice != 3);
}

void Menu::showMenu() {
	cout << "1. Wczytanie danych z pliku\n";
	cout << "2. Wyswietlenie wczytanych danych\n";
	cout << "3. Wprowadzenie kryterium stopu\n";
	cout << "4. Ustawienie wielkosci populacji poczatkowej\n";
	cout << "5. Ustawienie wspolczynnika mutacji\n";
	cout << "6. Ustawienia wspolczynnika krzyzowania\n";
	cout << "7. Wybor metody mutacji(opcjonalnie)\n";
	cout << "8. Uruchom\n";
	cout << "9. Wyjscie\n";
}

void Menu::chooseOption() {
	
	int choice = 0;

	do {
		system("cls");
		showParameters();
		showMenu();
		do {
			cin >> choice;
		} while (choice<1 || choice>9);

		switch (choice)
		{
		case 1:
			system("cls");
			cout << "Nazwa pliku: ";
			cin >> filename;
			genetic->readFile(filename);
			break;
		case 2:
			system("cls");
			genetic->showData();
			system("pause");
			break;
		case 3:
			system("cls");
			cout << "Podaj czas dzialania algorytmu (w sekundach): \n";
			cin >> runtime;
			break;
		case 4:
			system("cls");
			cout << "Podaj wielkosc populacji: ";
			cin >> population;
			break;
		case 5:
			system("cls");
			/*string temp;*/
			cout << "Podaj wspolczynnik mutacji: ";
			cin >> mutationProbability;

			break;
		case 6:
			system("cls");
			cout << "Podaj wspolczynnik krzyzowania: ";
			cin >> crossProbability;
			break;
		case 7:
			system("cls");
			cout << "Wybierz rodzaj mutacji: \n";
			cout << "1. Inwersja\n";
			cout << "2. Wstawienie\n";
			cout << "3. Transpozycja\n";
			cin >> mutationType;
			break;
		case 8:
			//genetic = new Genetic(runtime, population, mutationProbability, crossProbability);
			genetic->setParameters(runtime, population, mutationProbability, crossProbability, mutationType);
			genetic->execute("wynik.txt");
			cout << "\a";
			system("pause");
			break;
		default:
			break;
		}
	} while (choice!=9);
}

void Menu::showParameters() {
	cout << "Plik: " << filename << "\n";
	cout << "Czas: " << runtime << "\n";
	cout << "Wielkosc populacji: " << population << "\n";
	cout << "Wspolczynnik mutacji: " << mutationProbability << "\n";
	cout << "Wspolczynnik krzyzowania: " << crossProbability << "\n";
	
	if (mutationType == 1) {
		cout << "Metoda krzyzowania: inwersja\n";
	} 
	else if (mutationType == 2) {
		cout << "Metoda krzyzowania: wstawianie\n";
	}
	else if(mutationType == 3){
		cout << "Metoda krzyzowania: zamiana\n";
	}
	else {
		cout << "Metoda krzyzowania: Nie wybrano\n";
	}

	cout << "\n\n";
}
