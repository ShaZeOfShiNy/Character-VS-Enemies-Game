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
struct Coords {
	int x, y;
};

class GameField {
	public:
		GameField(void);
		GameField(Coords topLeft, int x, int y);
		void print(void);
		Coords getWidthHeight(void);
		Coords getTopLeft(void);
	private:
	protected:
		Coords topLeft;
		int width;
		int height;
};

GameField::GameField(void) {
	
	this->topLeft = {2, 2};
	this->width = 20;
	this->height = 10;
}

GameField::GameField(Coords topLeft, int width, int height) {
	
	this->topLeft = topLeft;
	this->width = width;
	this->height = height;
}

Coords GameField::getTopLeft(void) {
	Coords a;
	a.x = topLeft.x;
	a.y = topLeft.y;
	
	return a;
}

Coords GameField::getWidthHeight(void) {
	Coords a;
	a.x = width; a.y = height;
	
	return a;
}

void GameField::print(void) {
	pthread_mutex_lock(&mutex);
	// TOP LEFT CORNER
	gotoxy(topLeft.x, topLeft.y);
	printf("%c", 201);
	// TOP RIGHT CORNER
	gotoxy(topLeft.x + width, topLeft.y);
	printf("%c", 187);
	// BOTTOM LEFT CORNER
	gotoxy(topLeft.x, topLeft.y + height);
	printf("%c", 200);
	// BOTTOM RIGHT CORNER
	gotoxy(topLeft.x + width, topLeft.y + height);
	printf("%c", 188);
	
	// ### --- ###
	
	// TOP SIDE
	for(int i = topLeft.x + 1; i <= width + 1; i++) {
		gotoxy(i, topLeft.y);
		printf("%c", 205);
	}
	// BOTTOM SIDE
	for(int i = topLeft.x + 1; i <= width + 1; i++) {
		gotoxy(i, topLeft.y + height);
		printf("%c", 205);
	}
	
	// LEFT SIDE
	for(int i = topLeft.y + 1; i <= height + 1; i++) {
		gotoxy(topLeft.x, i);
		printf("%c", 186);
	}
	// RIGHT SIDE
	for(int i = topLeft.y + 1; i <= height + 1; i++) {
		gotoxy(topLeft.x + width, i);
		printf("%c", 186);
	}
	pthread_mutex_unlock(&mutex);
}

