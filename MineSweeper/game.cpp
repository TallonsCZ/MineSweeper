#include "Game.h"


game::game() {
	gamePlace = new Board(size);
	userGameplace = new BoardChar(size);
}

void game::create() {
	std::vector<std::vector<int>> mineSweeper(size, std::vector<int>(size));

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			gamePlace->setElement(i, j, 0);
		}
	}

}

int game::randomNumber() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, 99);
	return dist(gen);
	
}

void game::print() {
	std::cout << "    |";
	for (int b = 0; b < size; b++) {
		std::cout << "[" << b + 1 << "]|";
	}
	std::cout << std::endl;
	for (int i = 0; i < size; i++) {
		if (i < 9) {
			std::cout << "[" << i + 1 << "] | ";
		}
		else if (i < 20) {
			std::cout << "[" << i + 1 << "]| ";
		}
		for (int j = 0; j < size; j++) {
			if (j < 9) {
				std::cout << gamePlace->getValue(i,j) << " | ";
			}
			else if (j < 19) {
				std::cout << gamePlace->getValue(i, j) << "  | ";
			}
		}
		std::cout << std::endl;
	}
}

void game::placeMine(int xv, int yv) {
	if (gamePlace->getValue(xv-1, yv-1) == 9) {
		return;
	}
	else {
		gamePlace->setElement(xv-1, yv-1, 9);
		numberPlacedMines++;
	}

	int x = xv - 1;
	int y = yv - 1;
	for (int i = x-1; i < xv + 1; i++) {
		if (i < 0 || i > size-1) {
			continue;
		}
		else {
			for (int j = y - 1; j < yv + 1; j++) {
				if (j < 0 || j > size-1) {
					continue;
				}
				else {
					if ((i == xv - 1 && j == yv - 1) || gamePlace->getValue(i, j) == 9) {
						continue;
					}
					else {
						int help = gamePlace->getValue(i, j);
						help++;
						gamePlace->setElement(i, j, help);
					}
				}


		}
}
	}
}

void game::createUserGamePlace() {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			userGameplace->setElement(i, j, 'H');
		}
	}

}

bool game::random() {
	int random = randomNumber();
	if (random < 10) {
		return true;
	}
	else
	{
		return false;
	}
}

void game::fillGamePlace() {
	while (numberPlacedMines != numberMines) {
		for (int i = 1; i < size+1; i++) {
			for (int j = 1; j < size+1; j++) {
				if (numberPlacedMines == numberMines) {

				}
				else {
					if (random()) {
						placeMine(i, j);
					}
				}

			}
		}
	}


}

void game::printUserGamePlace() {
	std::cout << "    |";
	for (int b = 0; b < size; b++) {
		std::cout << "[" << b + 1 << "]|";
	}
	std::cout << std::endl;
	for (int i = 0; i < size; i++) {
		if (i < 9) {
			std::cout << "[" << i + 1 << "] | ";
		}
		else if (i < 20) {
			std::cout << "[" << i + 1 << "]| ";
		}
		for (int j = 0; j < size; j++) {
			if (j < 9) {
				std::cout << userGameplace->getValue(i,j) << " | ";
			}
			else if (j < 19) {
				std::cout << userGameplace->getValue(i,j) << "  | ";
			}
		}
		std::cout << std::endl;
	}
}

void game::nullScan(int xv, int yv) {
	userGameplace->setElement(xv, yv, gamePlace->getValue(xv, yv) + '0');
	for (int i = xv - 1; i <= xv + 1; i++) {
		for (int j = yv - 1; j <= yv + 1; j++) {
			if (j == yv && i == xv || j > size-1 || i > size-1 || j < 0 || i < 0) {
				continue;
			}
			if ((gamePlace->getValue(i,j) == 0) && userGameplace->getValue(i,j) != 48) {
				nullScan(i, j);
			}
			else if(userGameplace->getValue(i,j) == 48){
				continue;
				
			}
			else {
				userGameplace->setElement(i,j, gamePlace->getValue(i, j) + '0');
			}
		}
	}
}


void game::select(int first, int second) {
	int firstTake = first - 1; int secondTake = second - 1;
	int selected = gamePlace->getValue(firstTake, secondTake);
	if (selected == 0) {
		nullScan(firstTake, secondTake);
		system("cls");
		printUserGamePlace();

	}
	else if (selected == 9) {
		end();
	}
	else {
		userGameplace->setElement(firstTake, secondTake, gamePlace->getValue(firstTake, secondTake) + '0');
		system("cls");
		printUserGamePlace();
	}
}

void game::end() {
	system("cls");
	print();
	delete userGameplace;
	delete gamePlace;
	endBool = true;
	bool next = false;
	while (next == false) {
		std::cout << "You Lost, Want to play again? (Y/N) ";
		char choose;
		std::cin >> choose;
		if (choose == 'Y') {
			next = true;
			return;
		}
		else if (choose == 'N') {
			startgame = false;
			next = true;
			return;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Bad choose please repeat.. \n";
		}
	}

		
}


void game::options() {
	bool badChoose = true;
	int choose = 0;
	while (badChoose == true) {
		std::cout << "Options: \n \n 1. Number of Mines \n 2. Size of Gameplace \n 3. Back \n \n Your Choose: ";
		std::cin >> choose;
		if (std::cin.fail()) {
			system("cls");
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Bad choose please repeat.. \n";
		}
		else if (choose > 0 && choose < 4) {
			badChoose = false;
		}
		else {
			system("cls");
			std::cout << "Bad choose please repeat.. \n";
		}
	}
	system("cls");
	if (choose == 1) {
		setNumberMines();
	}
	else if (choose == 2) {
		setSize();
	}
	else if (choose == 3) {
		system("cls");
		return;
	}

}

void game::welcome() {
	std::cout << "Welcome in my game MineSweeper. \n \n 1. Start Game \n 2. Options \n 3. Help \n 4. End Game\n Your choose: ";
	int choose = 0; 
	std::cin >> choose;
	if (std::cin.fail()) {
		system("cls");
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Bad choose please repeat.. \n";
	}
	else if(choose == 1) {
		system("cls");
		create();
		fillGamePlace();
		createUserGamePlace();
		play();
	}
	else if (choose == 2) {
		system("cls");
		options();
	}else if (choose == 3) {
		system("cls");
		std::cout << "Help: \n This is a standard Minesweeper game where the goal is to find all the squares that do not have mines. \n";
		std::cout << " Explanations: \n H: Hidden \n 0: No mine nearby \n 1-8: Number of mines nearby \n 9: Mines \n \n If you choose mines, game over \n \n \n";
	}
	else if (choose == 4) {
		startgame = false;
		return;
	}
	else {
		system("cls");
		std::cout << "Bad choose please repeat.. \n";
	}

}

void game::play(){
	printUserGamePlace();

	while (endBool == false) {
		int args[3];
		std::cout << "(For exit write 99) Select vertical and horizontal: ";
		for (int helpR = 1; helpR < 3; helpR++) {
			int help;
			bool playBool = true;

			while (playBool == true) {
				std::cin >> help;
				if (std::cin.fail()) {
					system("cls");
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Bad choose please repeat.. \n";
				}
				else if (help == 99) {
					end();
					return;
				}

				else if(help > size || help < 0)
				{
					system("cls");
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Bad choose (out of border) please repeat.. \n";
				}
				else
				{
					playBool = false;
				}
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			std::cout << " , ";
			args[helpR] = help;

		}
		select(args[1], args[2]);
	}
}
