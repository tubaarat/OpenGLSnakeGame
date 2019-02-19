#include "champ.h"
#include "peintre.h"
#include <cstdlib>
#include<cstdio>
#include <GL/gl.h>

Champ::Champ() { //Constructor method. 1. seviye ayarlarını başlatır.

	for (int y = 0; y < HEIGHT; ++y)
		for (int x = 0; x < WIDTH; ++x)
			coordArray[y][x] = EMPTY;	//başlangıçta tüm alanları boş set et. yani coordArray içerisine herhangi bir koordinat koymaz.
	newFood();
	snakeLength = 1;

}

void Champ::setBox(Type type, int x, int y) //Yiyecek, yılan ve engeller için verilen koordinatlardaki kutucukların tipini belirler.
		{
	coordArray[y][x] = type;
}

Champ::Type Champ::box(int x, int y) const //belirli bir lokasyondaki(koordinattaki) kutuyu geri döndürür(return eder).
		{
	return coordArray[y][x];
}
void Champ::draw(Peintre &p) const { // Ekrana yılan, yiyecek ve engel bloklarını çizdirmeyi sağlayan fonksiyon.
	snakeLength = 0;
	for (int y = 0; y < HEIGHT; ++y)
		for (int x = 0; x < WIDTH; ++x) {
			switch (coordArray[y][x]) { //Koordinatları verilen kutunun tipine göre durumları çalıştırır.
			case EMPTY:							//Tipi EMPTY ise bişey çizdirmez.
				break;
			case SNAKE_BOX: //Tipi SNAKE_BOX ise yılana bir kutu oluşturur ve uzunluğunu arttırır.
				p.snakeBox(x * OBSTACLE_WIDTH, y * OBSTACLE_HEIGHT,
						(x + 1) * OBSTACLE_WIDTH - 1,
						(y + 1) * OBSTACLE_HEIGHT - 1);
				snakeLength++;
				break;
			case FOOD_BOX: //Tipi yiyecek ise yeni bir yiyecek nesnesi oluşturur.
				p.foodBox(x * OBSTACLE_WIDTH, y * OBSTACLE_HEIGHT,
						(x + 1) * OBSTACLE_WIDTH - 1,
						(y + 1) * OBSTACLE_HEIGHT - 1);
				break;
			case OBSTACLE_BOX: //Tipi engel ise yeni bir engel kutucuğu oluşturur.
				p.obstacleBox(x * OBSTACLE_WIDTH, y * OBSTACLE_HEIGHT,
						(x + 1) * OBSTACLE_WIDTH - 1,
						(y + 1) * OBSTACLE_HEIGHT - 1);
				break;
			}
		}
}

void Champ::newObstacle() //dikey engelleri çizdiren fonksiyon.
{
	int x = 4;

//Soldaki engel

	setBox(OBSTACLE_BOX, x + 1, 1);
	setBox(OBSTACLE_BOX, x + 1, 2);
	setBox(OBSTACLE_BOX, x + 1, 3);
	setBox(OBSTACLE_BOX, x + 1, 4);
	setBox(OBSTACLE_BOX, x + 1, 5);
	setBox(OBSTACLE_BOX, x + 1, 6);

//Sağdaki engel

	setBox(OBSTACLE_BOX, x + 12, 14);
	setBox(OBSTACLE_BOX, x + 12, 15);
	setBox(OBSTACLE_BOX, x + 12, 16);
	setBox(OBSTACLE_BOX, x + 12, 17);
	setBox(OBSTACLE_BOX, x + 12, 18);
	setBox(OBSTACLE_BOX, x + 12, 19);
}

void Champ::newFood()			// yeni bir yiyecek nesnesi üretmeyi sağlayan fonksiyon.
{
	int x;
	int y;

	do {
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
	} while (box(x, y) != EMPTY);
	setBox(FOOD_BOX, x, y);

}




