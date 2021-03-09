#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <ctime>

const int WIDTH = 25;
const int HEIGHT = 16;

class BoardTemplate {
public:
	static std::map<std::string, std::vector<int>> boards;

	BoardTemplate();

	static int getLength();

	static std::vector<int> getBoard(std::string);

	static std::vector<int> loadBoard(std::string);

	static std::vector<int> loadBoard(std::string, std::string);
};