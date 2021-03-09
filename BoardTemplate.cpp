#include "BoardTemplate.h"

BoardTemplate::BoardTemplate() {};

std::map<std::string, std::vector<int>> BoardTemplate::boards;

int BoardTemplate::getLength() { //get length of boards array
	return boards.size();
}

std::vector<int> BoardTemplate::getBoard(std::string name) {

	return boards[name];
	
}

std::vector<int> BoardTemplate::loadBoard(std::string name) {

	srand ((unsigned)time(0));
	std::vector<int> board(400);
	int rMineIndex;
	int index = 0;
    while (index < 50) {

    	rMineIndex = rand() % 400;
    	if (board.at(rMineIndex) != 1) {
    		board.at(rMineIndex) = 1;
    		index++;
    	}
    }

	for (unsigned int i = 0; i < board.size(); i++) {
		
		if (board.at(i) == 0) {
			int numOfBombs = 0;
			
			if (i == 0) { //if tile is the top left corner
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (board.at(i + 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}

			else if (i == 24) { //if tile is the top riht corner
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i + 24) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			
			else if (i == 374) {
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 24) == 1)
					numOfBombs++;
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else if (i == 399) {
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else if (i < 25 && i > 0) { //if tile is in top row
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (board.at(i + 24) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (board.at(i + 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else if (i > 374 && i < board.size()) { //if tile is in bottom row
				if (board.at(i - 26) == 1)
					numOfBombs++;
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 24) == 1)
					numOfBombs++;
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else if (i % 25 == 0) { //if tile is in left column
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 24) == 1)
					numOfBombs++;
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (board.at(i + 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else if (i % 25 == 24) { //if tile is in right column
				if (board.at(i - 26) == 1)
					numOfBombs++;
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (board.at(i + 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else {
				if (board.at(i - 26) == 1)
					numOfBombs++;
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 24) == 1)
					numOfBombs++;
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (board.at(i + 24) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (board.at(i + 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
		}
	}
	boards[name] = board;
	return boards[name];
}

std::vector<int> BoardTemplate::loadBoard(std::string name, std::string path) {

	std::vector<int> board;
	std::ifstream file(path);
	if (file.is_open()) {
		char c;
		while (file.get(c)) {
			board.push_back(c - 48);
		}
	}

	for (unsigned int i = 0; i < board.size(); i++) {
		if (board.at(i) == -38)
			board.erase(board.begin() + i);
	}


	for (unsigned int i = 0; i < board.size(); i++) {
		
		if (board.at(i) == 0) {
			int numOfBombs = 0;
			
			if (i == 0) { //if tile is the top left corner
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (board.at(i + 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}

			else if (i == 24) { //if tile is the top riht corner
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i + 24) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			
			else if (i == 374) {
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 24) == 1)
					numOfBombs++;
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else if (i == 399) {
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else if (i < 25 && i > 0) { //if tile is in top row
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (board.at(i + 24) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (board.at(i + 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else if (i > 374 && i < board.size()) { //if tile is in bottom row
				if (board.at(i - 26) == 1)
					numOfBombs++;
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 24) == 1)
					numOfBombs++;
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else if (i % 25 == 0) { //if tile is in left column
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 24) == 1)
					numOfBombs++;
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (board.at(i + 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else if (i % 25 == 24) { //if tile is in right column
				if (board.at(i - 26) == 1)
					numOfBombs++;
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (board.at(i + 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
			else {
				if (board.at(i - 26) == 1)
					numOfBombs++;
				if (board.at(i - 25) == 1)
					numOfBombs++;
				if (board.at(i - 24) == 1)
					numOfBombs++;
				if (board.at(i - 1) == 1)
					numOfBombs++;
				if (board.at(i + 1) == 1)
					numOfBombs++;
				if (board.at(i + 24) == 1)
					numOfBombs++;
				if (board.at(i + 25) == 1)
					numOfBombs++;
				if (board.at(i + 26) == 1)
					numOfBombs++;
				if (numOfBombs > 0)
					board.at(i) = numOfBombs + 1;
			}
		}
	}

	boards[name] = board;
	return boards[name];
}