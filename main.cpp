/*
	Made by: Matteo Galletta
	
	on date: 15/11/2020
	
	File's name: main.cpp
	Headers' name: Player.h     // Manages the character movement and behaviour
				   GameField.h  // Manages the game field
				   
	Version: v1.0
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <conio2.h>
#include <windows.h>
#include <time.h>
#include <pthread.h>

// Macros just used in the main.cpp file
#define TOP_LEFT_X 2
#define TOP_LEFT_Y 2
#define WIDTH 60
#define HEIGHT 20
#define ENEMIES_AMOUNT 20

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#include "GameField.h"
#include "Player.h"

bool manageInput(Player &player, char buttonPressed);
void updateScreen(void);
void printAndClearPast(Player &player);
void hideConsoleCursor(void);
void* manageEnemy(void* gameFieldAndEnemies);
void generateEnemies(GameField &gameField, Player **enemies, int enemiesAmount);
bool isPlayerTouchingEnemy(Player &player, Player *enemies, int enemiesAmount);

bool gameRunning = true;

int main(void) {
	
	srand(time(NULL));
	hideConsoleCursor();
	
	GameField gameField({TOP_LEFT_X, TOP_LEFT_Y}, WIDTH, HEIGHT); gameField.print();
	Player player(gameField, '@'); player.print();
	
	Player *enemies;
	generateEnemies(gameField, &enemies, ENEMIES_AMOUNT);
	
	char buttonPressed;
	while(gameRunning) {
		
		if(kbhit()) {
			buttonPressed = getch();
			
			gameRunning = manageInput(player, buttonPressed);
		}
		
		printAndClearPast(player); // Partial Double buffer
		
		if(isPlayerTouchingEnemy(player, enemies, ENEMIES_AMOUNT))
			gameRunning = false;
		
		Sleep(10);
	}
	
	free(enemies);
	clrscr();
	return 0;
}

bool isPlayerTouchingEnemy(Player &player, Player *enemies, int enemiesAmount) {
	
	for(int i = 0; i < enemiesAmount; i++)
		if(player.getCoords().x == enemies[i].getCoords().x &&
		   player.getCoords().y == enemies[i].getCoords().y
			) return true;
	
	return false;
}

void generateEnemies(GameField &gameField, Player **enemies, int enemiesAmount) {
	
	*enemies = (Player *) malloc(sizeof(Player) * enemiesAmount);
	for(int i = 0; i < enemiesAmount; i++)
		(*enemies)[i] = Player(gameField);
	
	pthread_t id;
	
	for(int i = 0; i < enemiesAmount; i++) {
		pthread_create(&id, NULL, &manageEnemy, *enemies+i);
	}
}

void printAndClearPast(Player &player) {
	
	player.clearLast();
	player.print();
}

bool manageInput(Player &player, char buttonPressed) {
	
	if(buttonPressed >= 'a' && buttonPressed <= 'z')
		buttonPressed -= 'a' - 'A';
	
	switch(buttonPressed) {
		
		case 'A':
			player.moveLeft();
			break;
		case 'S':
			player.moveDown();
			break;
		case 'D':
			player.moveRight();
			break;
		case 'W':
			player.moveUp();
			break;
		case 27: // ESC
			return false;
	}
	
	return true;
}

void* manageEnemy(void* _enemy) {
	Player *enemy = (Player*)_enemy;
	
	// Every player has to initialize his own seed
	int sum = enemy->getCoords().x + enemy->getCoords().y;
	srand(time(NULL)+sum);
	
	while(gameRunning) {
		
		enemy->randomMove();
		
		enemy->clearLast();
		enemy->print();
		
		Sleep(1000);
	}
}

void hideConsoleCursor(void) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

