

#ifndef JEU_H_
#define JEU_H_

#include "snake.h"
#include "champ.h"

class Peintre;

class Jeu {
public:
	int tick(); //Yılanın bir engele mi çarptığını yoksa yiyecek nesnesini mi yediğini döndürür.

	void draw(Peintre &) const; //Yılan, yiyecek ve engel kutucuklarının çizilmesini sağlar.

	void keyEvent(Snake::Direction); //Yılanın yönünü değiştirir.

	void constructor(); // 1. seviye için gerekli ayarlamalar yapılır.

	int lengthOfSnake(); //Yılanın uzunluğunu döndürür.

	void setlevel2(); //2. seviyedeki engelleri ekrana çizdirir.

private:
	Champ champ;
	Snake snakeObj;
};




#endif /* JEU_H_ */
