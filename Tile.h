#pragma once

#include <SFML/Graphics.hpp>
#include <string>

//const int SIZE = 32; //width and height for each tile (in pixels)

class Tile {
public:
	
	bool isVisited;
	std::string name; //name of tile
	sf::Texture tileTexture; //texture for tile
	sf::Sprite sprite; //sprite for tile

	Tile(); //default constructor

	void setName(std::string);
	void setSpritePosition(int x, int y); //sets the particular tile into the right tile in the 2d array

};