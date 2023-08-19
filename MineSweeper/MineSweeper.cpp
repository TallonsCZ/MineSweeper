#include "Game.h"


int main()
{
	bool continues = true;
	while (continues == true) {
		game* directGame = new game();
		directGame->welcome();
		if (directGame->startgame == false) {
			continues = false;
		}
		delete directGame;
		
	}


}



