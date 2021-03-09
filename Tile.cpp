#include "Tile.h"

Tile::Tile() { //default constructor

	setName("tile_hidden");
}

void Tile::setName(std::string name) {
	this->name = name;
}

void Tile::setSpritePosition(int x, int y) {
	sprite.setPosition(x, y);
}
