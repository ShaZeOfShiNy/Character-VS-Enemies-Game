/*
   Copyright 2020 Matteo Galletta

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
class Player {
	public:
		Player(GameField &a);
		Player(GameField &a, char toPrint);
		Player(GameField &a, int _x, int _y);
		bool moveToXY(int x, int y);
		void moveUp(void);
		void moveDown(void);
		void moveLeft(void);
		void moveRight(void);
		void print(void);
		void clearLast(void);
		void randomMove(void);
		Coords getCoords();
		
	private:
		void initialize(GameField *a, int _x, int _y);
		void incrementX(void);
		void incrementY(void);
		void decrementX(void);
		void decrementY(void);		
		
	protected:
		int x, y;
		Coords topLeft, last;
		int width, height;
		char toPrint;
		
};
Player::Player(GameField &a, int _x, int _y) {
	initialize(&a, _x, _y);
}
Player::Player(GameField &a, char toPrint) {
	initialize(&a, -1, -1);
	this->toPrint = toPrint;
}
Player::Player(GameField &a) {
	initialize(&a, -1, -1);
	this->toPrint = '#';
}
void Player::randomMove(void) {
	int randomValue = rand_r(x+y) % 4;
	switch(randomValue) {
		case 0:
			moveDown(); break;
		case 1:
			moveUp(); break;
		case 2:
			moveLeft(); break;
		case 3:
			moveRight(); break;
	}
}
void Player::initialize(GameField *a, int _x, int _y) {
	Coords var;
	var = a->getWidthHeight();
	width = var.x;
	height = var.y;
	
	topLeft = a->getTopLeft();
	if(!moveToXY(topLeft.x + _x, topLeft.y + _y)) {
		x = topLeft.x + rand_r(x+y) % (width-1)+ 1;
		y = topLeft.y + rand_r(x+y) % (height-1) + 1;
	}
	
	last.x = x;
	last.y = y;
}
Coords Player::getCoords(void) {
	Coords a;
	a.x = x; a.y = y;
	return a;
}

void Player::moveUp(void) {
	last.y = y;
	last.x = x;
	decrementY();
}
void Player::moveDown(void) {
	last.y = y;
	last.x = x;
	incrementY();
}
void Player::moveLeft(void) {
	last.x = x;
	last.y = y;
	decrementX();
}
void Player::moveRight(void) {
	last.x = x;
	last.y = y;
	incrementX();
}

void Player::print(void) {
	pthread_mutex_lock(&mutex);
	gotoxy(x, y);
	printf("%c", toPrint);
	pthread_mutex_unlock(&mutex);
}
void Player::clearLast(void) {
	pthread_mutex_lock(&mutex);
	gotoxy(last.x, last.y);
	printf(" ");
	pthread_mutex_unlock(&mutex);
}

bool Player::moveToXY(int x, int y) {
	
	if(x < topLeft.x + 1 || x > topLeft.x + width) return false;
	if(y < topLeft.y + 1 || y > topLeft.y + height) return false;
	
	this->x = x;
	this->y = y;
	last.x = x;
	last.y = y;
	
	return true;
}
void Player::incrementX(void) {
	if(x == topLeft.x + width - 1) x = topLeft.x + 1;
	else x++;
}
void Player::incrementY(void) {
	if(y == topLeft.y + height - 1) y = topLeft.y + 1;
	else y++;
}
void Player::decrementX(void) {
	if(x == topLeft.x + 1) x = topLeft.x + width - 1;
	else x--;
}
void Player::decrementY(void) {
	if(y == topLeft.y + 1) y = topLeft.y + height - 1;
	else y--;
}

