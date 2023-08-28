#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include <cctype>

struct Board {
private: 
	std::vector<std::vector<int>> pole;
	int size;
	
public:
	Board(int size) {
		this->size = size;
		pole = std::vector<std::vector<int>>(size, std::vector<int>(size));
	}

	void setElement(int b, int a, int value) {
		pole[b][a] = value;
	}

	int getValue(int b, int a) {
		return pole[b][a];
	}

	std::vector<std::vector<int>>& getBoard() {
		return pole;
	}

};

struct BoardChar {
private:
	std::vector<std::vector<char>> pole;
	int size;

public:
	BoardChar(int size) {
		this->size = size;
		pole = std::vector<std::vector<char>>(size, std::vector<char>(size));
	}

	void setElement(int b, int a, int value) {
		pole[b][a] = value;
	}

	char getValue(int b, int a) {
		return pole[b][a];
	}

	std::vector<std::vector<char>>& getBoard() {
		return pole;
	}

};

class game {

private:
	int numberPlacedMines=0;
	int numberMines = 15;
	int size = 15;
	Board* gamePlace;
	BoardChar* userGameplace;
public:
	bool startgame = true;
	bool endBool = false;
	game();
	void createUserGamePlace();
	int randomNumber();
	void create();
	void select(int first, int second);
	void print();
	void endWin();
	bool random();
	void play();
	void welcome();
	void printUserGamePlace();
	void end();
	void nullScan(int xv, int yv);
	void fillGamePlace();
	void placeMine(int xv, int yv);
	void options();
	bool isComplete();

	void setNumberMines(){
		int number;
		bool help = true;

		while (help == true) {
			std::cout << "Write number of Mines: ";
			std::cin >> number;
			if (std::cin.fail()) {
				system("cls");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Bad choose please repeat.. \n";
			}
			else if (number <= 0 || number > size*size-1){
				help = true;
				system("cls");
				std::cout << "Number must be bigger than 0 or smaller than " << size*size-1 << "\n";
			}
			else {
				help = false;
			}
		}
		numberMines = number;
		system("cls");
		std::cout << "Number of Mines has been change to " << number << std::endl;
		return;
	}

	void setSize() {
		int number;
		bool help = true;

		while (help == true) {
			std::cout << "Maximal Size (20) \n Write number of Size: ";
			std::cin >> number;
			if (std::cin.fail()) {
				system("cls");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Bad choose please repeat.. \n";
			}
			else if (number <= 0 || number > 19) {
				help = true;
				system("cls");
				std::cout << "Number must be bigger than 0 or smaller than 20 \n";
			}
			else {
				help = false;
			}
		}
		size = number;
		system("cls");
		std::cout << "Size of Gameplace has been change to " << number << std::endl;
		delete gamePlace;
		delete userGameplace;
		gamePlace = new Board(size);
		userGameplace = new BoardChar(size);
		return;
	}

};