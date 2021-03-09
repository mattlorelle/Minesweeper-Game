#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <queue>
#include "Tile.h"
#include "TextureManager.h"
#include "BoardTemplate.h"

using namespace sf;

int main() {

	/*
	 * ====================== Defining all textures used thru game =======================
	 * ===================================================================================
	*/

	TextureManager *textureList; //initialize a new texture container object

	//fill the map with created textures for reference
	textureList->loadTexture("tile_hidden", "images/tile_hidden.png"); //tile_hidden
	Texture &tile_hidden = *textureList->getTexture("tile_hidden");
	textureList->loadTexture("tile_revealed", "images/tile_revealed.png"); //tile_revealed
	Texture &tile_revealed = *textureList->getTexture("tile_revealed");

	textureList->loadTexture("flag", "images/flag.png"); //flag
	Texture &flag = *textureList->getTexture("flag");
	textureList->loadTexture("mine", "images/mine.png"); //mine
	Texture &mine = *textureList->getTexture("mine");
	textureList->loadTexture("debug", "images/debug.png"); //debug
	Texture &debug = *textureList->getTexture("debug");

	textureList->loadTexture("number_1", "images/number_1.png"); //number_1
	Texture &number_1 = *textureList->getTexture("number_1");
	textureList->loadTexture("number_2", "images/number_2.png"); //number_2
	Texture &number_2 = *textureList->getTexture("number_2");
	textureList->loadTexture("number_3", "images/number_3.png"); //number_3
	Texture &number_3 = *textureList->getTexture("number_3");
	textureList->loadTexture("number_4", "images/number_4.png"); //number_4
	Texture &number_4 = *textureList->getTexture("number_4");
	textureList->loadTexture("number_5", "images/number_5.png"); //number_5
	Texture &number_5 = *textureList->getTexture("number_5");
	textureList->loadTexture("number_6", "images/number_6.png"); //number_6
	Texture &number_6 = *textureList->getTexture("number_6");
	textureList->loadTexture("number_7", "images/number_7.png"); //number_7
	Texture &number_7 = *textureList->getTexture("number_7");
	textureList->loadTexture("number_8", "images/number_8.png"); //number_8
	Texture &number_8 = *textureList->getTexture("number_8");

	textureList->loadTexture("test_1", "images/test_1.png"); //test_1
	Texture &test_1 = *textureList->getTexture("test_1");
	textureList->loadTexture("test_2", "images/test_2.png"); //test_2
	Texture &test_2 = *textureList->getTexture("test_2");
	textureList->loadTexture("test_3", "images/test_3.png"); //test_3
	Texture &test_3 = *textureList->getTexture("test_3");

	
	textureList->loadTexture("digits", "images/digits.png"); //digits
	Texture &digits = *textureList->getTexture("digits");

	textureList->loadTexture("face_happy", "images/face_happy.png"); //face_happy
	Texture &face_happy = *textureList->getTexture("face_happy");
	textureList->loadTexture("face_lose", "images/face_lose.png"); //face_lose
	Texture &face_lose = *textureList->getTexture("face_lose");
	textureList->loadTexture("face_win", "images/face_win.png"); //face_win
	Texture &face_win = *textureList->getTexture("face_win");


	/*
	 * ================== Defining all the test board layouts =========================
	 * ================================================================================
	*/
	BoardTemplate boardList;
	boardList.loadBoard("test1", "boards/testboard1.brd");
	boardList.loadBoard("test2", "boards/testboard2.brd");
	boardList.loadBoard("test3", "boards/testboard3.brd");
	boardList.loadBoard("rand");

	std::vector<int> boardLayout = boardList.getBoard("rand");

	

	Tile tile; //default tile that will be manipulated throughout the game

	/*
	 * ======================== Making the actual boards =============================
	 * ===============================================================================
	*/
	Tile topBoard[WIDTH][HEIGHT]; //top layer board (default tile: hidden)
	tile.sprite.setTexture(tile_hidden);
	tile.setName("tile_hidden");
	for (unsigned int i = 0; i < WIDTH; i++) {
    	for (unsigned int j = 0; j < HEIGHT; j++) {
    		topBoard[i][j] = tile;
    	}
    }
    Tile topBoard2[WIDTH][HEIGHT]; //top layer board (default tile: hidden)
	tile.sprite.setTexture(tile_hidden);
	tile.setName("tile_hidden");
	for (unsigned int i = 0; i < WIDTH; i++) {
    	for (unsigned int j = 0; j < HEIGHT; j++) {
    		topBoard[i][j] = tile;
    	}
    }
	Tile bottomBoard[WIDTH][HEIGHT]; //bottom layer board (default tile: revealed)
    tile.sprite.setTexture(tile_revealed);
    tile.setName("tile_revealed");
    for (unsigned int i = 0; i < WIDTH; i++) {
    	for (unsigned int j = 0; j < HEIGHT; j++) {
    		bottomBoard[i][j] = tile;
    	}
    }

    Tile middleBoard[WIDTH][HEIGHT]; //main game board


    bool gameStatus = true; //in progress
    bool isInDebug = false; //debug mode enabled/disabled
    int numOfMines = 50; //number of mines

    Tile buttonTile;
    std::vector<Tile> buttons;

    buttonTile.sprite.setTexture(face_happy);
   	buttonTile.setName("face_happy");
    buttons.push_back(buttonTile);

    buttonTile.sprite.setTexture(face_win);
   	buttonTile.setName("face_win");
    buttons.push_back(buttonTile);

   	buttonTile.sprite.setTexture(face_lose);
   	buttonTile.setName("face_lose");
    buttons.push_back(buttonTile);

    buttonTile.sprite.setTexture(test_1);
   	buttonTile.setName("test_1");
    buttons.push_back(buttonTile);

    buttonTile.sprite.setTexture(test_2);
   	buttonTile.setName("test_2");
    buttons.push_back(buttonTile);

    buttonTile.sprite.setTexture(test_3);
   	buttonTile.setName("test_3");
    buttons.push_back(buttonTile);

    buttonTile.sprite.setTexture(debug);
   	buttonTile.setName("debug");
    buttons.push_back(buttonTile);



    RenderWindow app(VideoMode(800, 600), "Minesweeper"); //new window

	app.clear(Color::White); //clears window once, with white

	while (app.isOpen()) { //starts game/while game is running

		int referenceBoard[HEIGHT][WIDTH]; //the status of the game board
		int index = 0;
		for (unsigned int i = 0; i < HEIGHT; i++) {
			for (unsigned int j = 0; j < WIDTH; j++) {

				referenceBoard[i][j] = boardLayout.at(index);
				index++;
			}
		}

		

   		for (unsigned int i = 0; i < WIDTH; i++) {
    		for (unsigned int j = 0; j < HEIGHT; j++) {
				
				switch (referenceBoard[j][i]) {
					case 0:
						tile.sprite.setTexture(tile_revealed);
    					tile.setName("tile_revealed");
    					middleBoard[i][j] = tile;
						break;
					case 1:
						tile.sprite.setTexture(mine);
    					tile.setName("mine");
    					middleBoard[i][j] = tile;
						break;
					case 2:
						tile.sprite.setTexture(number_1);
    					tile.setName("number_1");
    					middleBoard[i][j] = tile;
						break;
					case 3:
						tile.sprite.setTexture(number_2);
    					tile.setName("number_2");
    					middleBoard[i][j] = tile;
						break;
					case 4:
						tile.sprite.setTexture(number_3);
    					tile.setName("number_3");
    					middleBoard[i][j] = tile;
						break;
					case 5:
						tile.sprite.setTexture(number_4);
    					tile.setName("number_4");
    					middleBoard[i][j] = tile;
						break;
					case 6:
						tile.sprite.setTexture(number_5);
    					tile.setName("number_5");
    					middleBoard[i][j] = tile;
						break;
					case 7:
						tile.sprite.setTexture(number_6);
	    				tile.setName("number_6");
	    				middleBoard[i][j] = tile;
						break;
					case 8:
						tile.sprite.setTexture(number_7);
    					tile.setName("number_7");
    					middleBoard[i][j] = tile;
						break;
					case 9:
						tile.sprite.setTexture(number_8);
    					tile.setName("number_8");
    					middleBoard[i][j] = tile;
						break;
				}
    		}
   	 	}

		Vector2i mPos = Mouse::getPosition(app); //mouse coordinates inside window
    	int mPosX = mPos.x / 32; //x coor of mouse
    	int mPosY = mPos.y / 32; //y coor of mouse
	
		bool gameOver = false;
		int mineCount = 0;
		int revealedCount = 0;

		Event e;
		while (app.pollEvent(e)) {
			
			if (e.type == Event::Closed)
				app.close();

			//if left mouse button is clicked
			if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {

				if (mPosX < 25 && mPosY < 16 && gameStatus == true && topBoard2[mPosX][mPosY].name != "flag") { //if click is inside game board

					middleBoard[mPosX][mPosY].isVisited = true;
					topBoard[mPosX][mPosY] = middleBoard[mPosX][mPosY];
					topBoard2[mPosX][mPosY] = middleBoard[mPosX][mPosY];

					if (middleBoard[mPosX][mPosY].name == "mine") { //if a mine is clicked, reveal the entire board
						
						gameStatus = false; //game over
						for (unsigned int i = 0; i < WIDTH; i++) {
    						for (unsigned int j = 0; j < HEIGHT; j++) {

    							if (middleBoard[i][j].name == "mine") {

    								buttons.at(0).sprite.setTexture(face_lose);
    								buttons.at(0).setName("face_lose");
    								topBoard[i][j] = middleBoard[i][j];
									topBoard2[i][j] = middleBoard[i][j];
    							}
    						}
    					}
						tile.setName("mine");
					}
					else if (middleBoard[mPosX][mPosY].name == "tile_revealed" && gameStatus == true) {
						
						for (unsigned int i = 0; i < WIDTH; i++) {
    						for (unsigned int j = 0; j < HEIGHT; j++) {

    							middleBoard[i][j].isVisited == false;
    						}
    					}

    					Vector2i temp;
    					Vector2i coor;
    					coor.x = mPosX;
    					coor.y = mPosY;
						std::queue<Vector2i> queue;
						queue.push(coor);

						while (!queue.empty()) {

							temp = queue.front();

							if (temp.x > 0 && temp.x < 24 && temp.y > 0 && temp.y < 15) { //if not on the edge

								if (middleBoard[temp.x - 1][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y + 1].isVisited) { //top left
									
									queue.push(Vector2i(temp.x - 1, temp.y + 1));
									topBoard[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									topBoard2[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									middleBoard[temp.x - 1][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y + 1].isVisited) {

									topBoard[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									topBoard2[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									middleBoard[temp.x - 1][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) { //top
									
									queue.push(Vector2i(temp.x, temp.y + 1));
									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) {

									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y + 1].isVisited) { //top riht
									
									queue.push(Vector2i(temp.x + 1, temp.y + 1));
									topBoard[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									topBoard2[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									middleBoard[temp.x + 1][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y + 1].isVisited) {

									topBoard[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									topBoard2[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									middleBoard[temp.x + 1][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x - 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) { //left
									
									queue.push(Vector2i(temp.x - 1, temp.y));
									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) {

									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) { //riht
									
									queue.push(Vector2i(temp.x + 1, temp.y));
									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) {

									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}

								if (middleBoard[temp.x - 1][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y - 1].isVisited) { //bottom left
									
									queue.push(Vector2i(temp.x - 1, temp.y - 1));
									topBoard[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									topBoard2[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									middleBoard[temp.x - 1][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y - 1].isVisited) {

									topBoard[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									topBoard2[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									middleBoard[temp.x - 1][temp.y - 1].isVisited = true;
								}

								if (middleBoard[temp.x][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) { //bottom
									
									queue.push(Vector2i(temp.x, temp.y - 1));
									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) {

									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y - 1].isVisited) { //bottom riht
									
									queue.push(Vector2i(temp.x + 1, temp.y - 1));
									topBoard[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									topBoard2[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									middleBoard[temp.x + 1][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y - 1].isVisited) {

									topBoard[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									topBoard2[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									middleBoard[temp.x + 1][temp.y - 1].isVisited = true;
								}
							}

							else if (temp.x == 0 && temp.y == 15) { //top left corner

								if (middleBoard[temp.x + 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) { //riht
									
									queue.push(Vector2i(temp.x + 1, temp.y));
									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) {

									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}

								if (middleBoard[temp.x][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) { //bottom
									
									queue.push(Vector2i(temp.x, temp.y - 1));
									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) {

									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y - 1].isVisited) { //bottom riht
									
									queue.push(Vector2i(temp.x + 1, temp.y - 1));
									topBoard[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									topBoard2[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									middleBoard[temp.x + 1][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y - 1].isVisited) {

									topBoard[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									topBoard2[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									middleBoard[temp.x + 1][temp.y - 1].isVisited = true;
								}
							}

							else if (temp.x == 24 && temp.y == 0) { //bottom right corner
								if (middleBoard[temp.x - 1][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y + 1].isVisited) { //top left
									
									queue.push(Vector2i(temp.x - 1, temp.y + 1));
									topBoard[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									topBoard2[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									middleBoard[temp.x - 1][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y + 1].isVisited) {

									topBoard[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									topBoard2[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									middleBoard[temp.x - 1][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) { //top
									
									queue.push(Vector2i(temp.x, temp.y + 1));
									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) {

									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x - 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) { //left
									
									queue.push(Vector2i(temp.x - 1, temp.y));
									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) {

									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}
							}

							else if (temp.x == 0 && temp.y == 0) { //bottom left
								
								if (middleBoard[temp.x][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) { //top
									
									queue.push(Vector2i(temp.x, temp.y + 1));
									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) {

									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y + 1].isVisited) { //top riht
									
									queue.push(Vector2i(temp.x + 1, temp.y + 1));
									topBoard[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									topBoard2[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									middleBoard[temp.x + 1][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y + 1].isVisited) {

									topBoard[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									topBoard2[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									middleBoard[temp.x + 1][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) { //riht
									
									queue.push(Vector2i(temp.x + 1, temp.y));
									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) {

									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}
							}

							else if (temp.x == 24 && temp.y == 15) { //top right

								if (middleBoard[temp.x - 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) { //left
									
									queue.push(Vector2i(temp.x - 1, temp.y));
									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) {

									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}

								if (middleBoard[temp.x - 1][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y - 1].isVisited) { //bottom left
									
									queue.push(Vector2i(temp.x - 1, temp.y - 1));
									topBoard[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									topBoard2[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									middleBoard[temp.x - 1][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y - 1].isVisited) {

									topBoard[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									topBoard2[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									middleBoard[temp.x - 1][temp.y - 1].isVisited = true;
								}

								if (middleBoard[temp.x][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) { //bottom
									
									queue.push(Vector2i(temp.x, temp.y - 1));
									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) {

									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}
							}

							else if (temp.x == 0 && (temp.y != 0 || temp.y != 15)) {

								if (middleBoard[temp.x][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) { //top
									
									queue.push(Vector2i(temp.x, temp.y + 1));
									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) {

									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y + 1].isVisited) { //top riht
									
									queue.push(Vector2i(temp.x + 1, temp.y + 1));
									topBoard[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									topBoard2[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									middleBoard[temp.x + 1][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y + 1].isVisited) {

									topBoard[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									topBoard2[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									middleBoard[temp.x + 1][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) { //riht
									
									queue.push(Vector2i(temp.x + 1, temp.y));
									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) {

									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}

								if (middleBoard[temp.x][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) { //bottom
									
									queue.push(Vector2i(temp.x, temp.y - 1));
									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) {

									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y - 1].isVisited) { //bottom riht
									
									queue.push(Vector2i(temp.x + 1, temp.y - 1));
									topBoard[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									topBoard2[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									middleBoard[temp.x + 1][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y - 1].isVisited) {

									topBoard[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									topBoard2[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									middleBoard[temp.x + 1][temp.y - 1].isVisited = true;
								}
							}

							else if (temp.x == 24 && (temp.y != 0 || temp.y != 15)) {
								if (middleBoard[temp.x - 1][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y + 1].isVisited) { //top left
									
									queue.push(Vector2i(temp.x - 1, temp.y + 1));
									topBoard[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									topBoard2[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									middleBoard[temp.x - 1][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y + 1].isVisited) {

									topBoard[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									topBoard2[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									middleBoard[temp.x - 1][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) { //top
									
									queue.push(Vector2i(temp.x, temp.y + 1));
									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) {

									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x - 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) { //left
									
									queue.push(Vector2i(temp.x - 1, temp.y));
									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) {

									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}

								if (middleBoard[temp.x - 1][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y - 1].isVisited) { //bottom left
									
									queue.push(Vector2i(temp.x - 1, temp.y - 1));
									topBoard[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									topBoard2[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									middleBoard[temp.x - 1][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y - 1].isVisited) {

									topBoard[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									topBoard2[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									middleBoard[temp.x - 1][temp.y - 1].isVisited = true;
								}

								if (middleBoard[temp.x][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) { //bottom
									
									queue.push(Vector2i(temp.x, temp.y - 1));
									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) {

									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}
							}

							else if (temp.y == 0 && (temp.x != 0 || temp.x != 24)) {
								if (middleBoard[temp.x - 1][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y + 1].isVisited) { //top left
									
									queue.push(Vector2i(temp.x - 1, temp.y + 1));
									topBoard[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									topBoard2[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									middleBoard[temp.x - 1][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y + 1].isVisited) {

									topBoard[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									topBoard2[temp.x - 1][temp.y + 1] = middleBoard[temp.x - 1][temp.y + 1];
									middleBoard[temp.x - 1][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) { //top
									
									queue.push(Vector2i(temp.x, temp.y + 1));
									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y + 1].isVisited) {

									topBoard[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									topBoard2[temp.x][temp.y + 1] = middleBoard[temp.x][temp.y + 1];
									middleBoard[temp.x][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y + 1].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y + 1].isVisited) { //top riht
									
									queue.push(Vector2i(temp.x + 1, temp.y + 1));
									topBoard[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									topBoard2[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									middleBoard[temp.x + 1][temp.y + 1].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y + 1].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y + 1].isVisited) {

									topBoard[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									topBoard2[temp.x + 1][temp.y + 1] = middleBoard[temp.x + 1][temp.y + 1];
									middleBoard[temp.x + 1][temp.y + 1].isVisited = true;
								}

								if (middleBoard[temp.x - 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) { //left
									
									queue.push(Vector2i(temp.x - 1, temp.y));
									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) {

									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) { //riht
									
									queue.push(Vector2i(temp.x + 1, temp.y));
									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) {

									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}
							}

							else if (temp.y == 15 && (temp.x != 0 || temp.x != 24)) {
							
								if (middleBoard[temp.x - 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) { //left
									
									queue.push(Vector2i(temp.x - 1, temp.y));
									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y].isVisited) {

									topBoard[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									topBoard2[temp.x - 1][temp.y] = middleBoard[temp.x - 1][temp.y];
									middleBoard[temp.x - 1][temp.y].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) { //riht
									
									queue.push(Vector2i(temp.x + 1, temp.y));
									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y].isVisited) {

									topBoard[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									topBoard2[temp.x + 1][temp.y] = middleBoard[temp.x + 1][temp.y];
									middleBoard[temp.x + 1][temp.y].isVisited = true;
								}

								if (middleBoard[temp.x - 1][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x - 1][temp.y - 1].isVisited) { //bottom left
									
									queue.push(Vector2i(temp.x - 1, temp.y - 1));
									topBoard[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									topBoard2[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									middleBoard[temp.x - 1][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x - 1][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x - 1][temp.y - 1].isVisited) {

									topBoard[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									topBoard2[temp.x - 1][temp.y - 1] = middleBoard[temp.x - 1][temp.y - 1];
									middleBoard[temp.x - 1][temp.y - 1].isVisited = true;
								}

								if (middleBoard[temp.x][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) { //bottom
									
									queue.push(Vector2i(temp.x, temp.y - 1));
									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x][temp.y - 1].isVisited) {

									topBoard[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									topBoard2[temp.x][temp.y - 1] = middleBoard[temp.x][temp.y - 1];
									middleBoard[temp.x][temp.y - 1].isVisited = true;
								}

								if (middleBoard[temp.x + 1][temp.y - 1].name == "tile_revealed" && !middleBoard[temp.x + 1][temp.y - 1].isVisited) { //bottom riht
									
									queue.push(Vector2i(temp.x + 1, temp.y - 1));
									topBoard[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									topBoard2[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									middleBoard[temp.x + 1][temp.y - 1].isVisited = true;
								}
								else if (middleBoard[temp.x + 1][temp.y - 1].name != "tile_revealed" && !middleBoard[temp.x + 1][temp.y - 1].isVisited) {

									topBoard[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									topBoard2[temp.x + 1][temp.y - 1] = middleBoard[temp.x + 1][temp.y - 1];
									middleBoard[temp.x + 1][temp.y - 1].isVisited = true;
								}
							}

							queue.pop();
						}
					}
				}


				else if (mPos.x > 368 && mPos.x < 432 && mPos.y > 512 && mPos.y < 576) { //game restart button

					gameStatus = true;
					numOfMines = 50;

					buttons.at(0).sprite.setTexture(face_happy);
    				buttons.at(0).setName("face_happy");

					tile.sprite.setTexture(tile_hidden);
					tile.setName("tile_hidden");
					for (unsigned int i = 0; i < WIDTH; i++) {
    					for (unsigned int j = 0; j < HEIGHT; j++) {

    						topBoard[i][j] = tile;
    						topBoard2[i][j] = tile;
    					}
    				}

    				boardList.loadBoard("rand");
					boardLayout = boardList.getBoard("rand");
				}


				else if (mPos.x > 496 && mPos.x < 560 && mPos.y > 512 && mPos.y < 576) { //debug button

					if (isInDebug == false) {

						for (unsigned int i = 0; i < WIDTH; i++) {
    						for (unsigned int j = 0; j < HEIGHT; j++) {

    							if (middleBoard[i][j].name == "mine" && topBoard2[i][j].name != "flag") {
    								
									topBoard2[i][j] = middleBoard[i][j];
    							}

    						}
    					}

    					isInDebug = true;
    				}
    				else if (isInDebug) {

    					for (unsigned int i = 0; i < WIDTH; i++) {
    						for (unsigned int j = 0; j < HEIGHT; j++) {

    							if (middleBoard[i][j].name == "mine") {
    								tile.sprite.setTexture(tile_hidden);
    								tile.setName("tile_hidden");
    								topBoard[i][j] = tile;
									topBoard2[i][j] = tile;
    							}
    						}
    					}
    					isInDebug = false;
    				}
				}


				else if (mPos.x > 560 && mPos.x < 624 && mPos.y > 512 && mPos.y < 576) { //testboard1 button

					numOfMines = 0;
					for (unsigned int i = 0; i < WIDTH; i++) {
    					for (unsigned int j = 0; j < HEIGHT; j++) {

    						if (middleBoard[i][j].name == "mine") 
    							numOfMines++;
    					}
    				}

					if (gameStatus) {

						boardLayout = boardList.getBoard("test1");
					} else {
						gameStatus = true;

						buttons.at(0).sprite.setTexture(face_happy);
    					buttons.at(0).setName("face_happy");

						boardLayout = boardList.getBoard("test1");
					}
					for (unsigned int i = 0; i < WIDTH; i++) {
    					for (unsigned int j = 0; j < HEIGHT; j++) {

    						tile.sprite.setTexture(tile_hidden);
    						tile.setName("tile_hidden");
    						topBoard[i][j] = tile;
							topBoard2[i][j] = tile;
    					} 
    				}
				}


				else if (mPos.x > 624 && mPos.x < 688 && mPos.y > 512 && mPos.y < 576) { //testboard2 button

					numOfMines = 0;
					for (unsigned int i = 0; i < WIDTH; i++) {
    					for (unsigned int j = 0; j < HEIGHT; j++) {

    						if (middleBoard[i][j].name == "mine") 
    							numOfMines++;
    					}
    				}

					if (gameStatus) {

						boardLayout = boardList.getBoard("test2");
					} else {
						gameStatus = true;

						buttons.at(0).sprite.setTexture(face_happy);
    					buttons.at(0).setName("face_happy");

						boardLayout = boardList.getBoard("test2");
					}
					for (unsigned int i = 0; i < WIDTH; i++) {
    					for (unsigned int j = 0; j < HEIGHT; j++) {

    						tile.sprite.setTexture(tile_hidden);
    						tile.setName("tile_hidden");
    						topBoard[i][j] = tile;
							topBoard2[i][j] = tile;
    					} 
    				}
				}


				else if (mPos.x > 688 && mPos.x < 752 && mPos.y > 512 && mPos.y < 576) { //testboard3 button

					numOfMines = 0;
					for (unsigned int i = 0; i < WIDTH; i++) {
    					for (unsigned int j = 0; j < HEIGHT; j++) {

    						if (middleBoard[i][j].name == "mine") 
    							numOfMines++;
    					}
    				}

					if (gameStatus) {

						boardLayout = boardList.getBoard("test3");
					} else {

						gameStatus = true;

						buttons.at(0).sprite.setTexture(face_happy);
    					buttons.at(0).setName("face_happy");

						boardLayout = boardList.getBoard("test3");
					}
					for (unsigned int i = 0; i < WIDTH; i++) {
    					for (unsigned int j = 0; j < HEIGHT; j++) {

    						tile.sprite.setTexture(tile_hidden);
    						tile.setName("tile_hidden");
    						topBoard[i][j] = tile;
							topBoard2[i][j] = tile;
    					} 
    				}
				}

				for (int i = 0; i < WIDTH; i++) {
					for (int j = 0; j < HEIGHT; j++) {

						if (middleBoard[i][j].name == "mine")
							mineCount++;

						if (topBoard2[i][j].name == middleBoard[i][j].name && topBoard[i][j].name == middleBoard[i][j].name)
							revealedCount++;

					}
				}


				if (400 - revealedCount == mineCount) {

					gameStatus = false;
					buttons.at(0).sprite.setTexture(face_win);
					buttons.at(0).setName("face_win");

					for (int i = 0; i < WIDTH; i++) {
						for (int j = 0; j < HEIGHT; j++) {

							if (middleBoard[i][j].name == "mine") {

								tile.sprite.setTexture(flag);
    							tile.setName("flag");
								topBoard2[i][j] = tile;
							}
						}
					}
				}
			}

			//if right mouse button is pressed
			if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Right) {

				if (mPosX < 25 && mPosY < 16) { //if click is inside game board

					if (topBoard2[mPosX][mPosY].name == "tile_hidden") { //if tile is not a flag, change to flag
						
						tile.sprite.setTexture(flag);
						tile.setName("flag");
						topBoard2[mPosX][mPosY] = tile;
						numOfMines--;
					}
					else if (topBoard2[mPosX][mPosY].name == "flag") { //if tile is a flag, change back to hidden
						
						tile.sprite.setTexture(tile_hidden);
						tile.setName("tile_hidden");
						topBoard2[mPosX][mPosY] = tile;
						numOfMines++;
					}
				}
			}
		}

		Sprite digit;
		digit.setTexture(digits);



		int firstDigit = numOfMines / 10;
		int secondDigit = numOfMines % 10;

		if (numOfMines < 0) {
			digit.setTextureRect(IntRect(210, 0, 21, 32)); //-
		} else {
			digit.setTextureRect(IntRect(0, 0, 21, 32)); //0
		}
		digit.setPosition(0, 16*32);
		app.draw(digit);

		switch(firstDigit) {
			case 0:
				digit.setTextureRect(IntRect(0, 0, 21, 32));
				break;
			case 1:
				digit.setTextureRect(IntRect(21, 0, 21, 32));
				break;
			case -1:
				digit.setTextureRect(IntRect(21, 0, 21, 32));
				break;
			case 2:
				digit.setTextureRect(IntRect(42, 0, 21, 32));
				break;
			case -2:
				digit.setTextureRect(IntRect(42, 0, 21, 32));
				break;
			case 3:
				digit.setTextureRect(IntRect(63, 0, 21, 32));
				break;
			case -3:
				digit.setTextureRect(IntRect(63, 0, 21, 32));
				break;
			case 4:
				digit.setTextureRect(IntRect(84, 0, 21, 32));
				break;
			case -4:
				digit.setTextureRect(IntRect(84, 0, 21, 32));
				break;
			case 5:
				digit.setTextureRect(IntRect(105, 0, 21, 32));
				break;
			case -5:
				digit.setTextureRect(IntRect(105, 0, 21, 32));
				break;
			case 6:
				digit.setTextureRect(IntRect(126, 0, 21, 32));
				break;
			case -6:
				digit.setTextureRect(IntRect(126, 0, 21, 32));
				break;
			case 7:
				digit.setTextureRect(IntRect(147, 0, 21, 32));
				break;
			case -7:
				digit.setTextureRect(IntRect(147, 0, 21, 32));
				break;
			case 8:
				digit.setTextureRect(IntRect(168, 0, 21, 32));
				break;
			case -8:
				digit.setTextureRect(IntRect(168, 0, 21, 32));
				break;
			case 9:
				digit.setTextureRect(IntRect(189, 0, 21, 32));
				break;
			case -9:
				digit.setTextureRect(IntRect(189, 0, 21, 32));
				break;
		}
		digit.setPosition(21, 16*32);
		app.draw(digit);

		switch(secondDigit) {
			case 0:
				digit.setTextureRect(IntRect(0, 0, 21, 32));
				break;
			case 1:
				digit.setTextureRect(IntRect(21, 0, 21, 32));
				break;
			case -1:
				digit.setTextureRect(IntRect(21, 0, 21, 32));
				break;
			case 2:
				digit.setTextureRect(IntRect(42, 0, 21, 32));
				break;
			case -2:
				digit.setTextureRect(IntRect(42, 0, 21, 32));
				break;
			case 3:
				digit.setTextureRect(IntRect(63, 0, 21, 32));
				break;
			case -3:
				digit.setTextureRect(IntRect(63, 0, 21, 32));
				break;
			case 4:
				digit.setTextureRect(IntRect(84, 0, 21, 32));
				break;
			case -4:
				digit.setTextureRect(IntRect(84, 0, 21, 32));
				break;
			case 5:
				digit.setTextureRect(IntRect(105, 0, 21, 32));
				break;
			case -5:
				digit.setTextureRect(IntRect(105, 0, 21, 32));
				break;
			case 6:
				digit.setTextureRect(IntRect(126, 0, 21, 32));
				break;
			case -6:
				digit.setTextureRect(IntRect(126, 0, 21, 32));
				break;
			case 7:
				digit.setTextureRect(IntRect(147, 0, 21, 32));
				break;
			case -7:
				digit.setTextureRect(IntRect(147, 0, 21, 32));
				break;
			case 8:
				digit.setTextureRect(IntRect(168, 0, 21, 32));
				break;
			case -8:
				digit.setTextureRect(IntRect(168, 0, 21, 32));
				break;
			case 9:
				digit.setTextureRect(IntRect(189, 0, 21, 32));
				break;
			case -9:
				digit.setTextureRect(IntRect(189, 0, 21, 32));
				break;
		}
		digit.setPosition(42, 16*32);
		app.draw(digit);

        for (unsigned int i = 0; i < WIDTH; i++) {
    		for (unsigned int j = 0; j < HEIGHT; j++) {

    			//setting position of all of the tiles in each board
    			bottomBoard[i][j].setSpritePosition(i * 32, j * 32);
    			middleBoard[i][j].setSpritePosition(i * 32, j * 32);
    			topBoard[i][j].setSpritePosition(i * 32, j * 32);
    			topBoard2[i][j].setSpritePosition(i * 32, j * 32);
					
				app.draw(bottomBoard[i][j].sprite); //draw bottom board first
    			app.draw(middleBoard[i][j].sprite); //layer middle
    			app.draw(topBoard[i][j].sprite); //layer top
    			app.draw(topBoard2[i][j].sprite); //layer top
    		}
    	}

    	buttons.at(0).setSpritePosition(368, 512);
    	app.draw(buttons.at(0).sprite);
    	buttons.at(6).setSpritePosition(496, 512);
    	app.draw(buttons.at(6).sprite);
    	buttons.at(3).setSpritePosition(560, 512);
    	app.draw(buttons.at(3).sprite);
    	buttons.at(4).setSpritePosition(624, 512);
    	app.draw(buttons.at(4).sprite);
    	buttons.at(5).setSpritePosition(688, 512);
    	app.draw(buttons.at(5).sprite);
        
        app.display();
    }

    return 0;
}