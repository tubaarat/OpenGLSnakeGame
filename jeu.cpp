

#include "jeu.h"
#include "peintre.h"
#include "champ.h"

int Jeu::tick() {
	if (!snakeObj.tick(champ)) //yılan bir engele ya da kendine çarpmadıysa 1 döndürür. Yani yılanın yiyeceği yediği anlaşılır.
			{
		return 1;
	} else
		return 0; //yılan bir yere çarptıysa 0 döndürür.
}
int Jeu::lengthOfSnake() {
	return champ.snakeLength; //yılanın boyunu döndürür.
}

void Jeu::constructor() {
	snakeObj = Snake(); //yılana bir hareket yönü atayan Snake sınıfının constructor'ı.
	champ = Champ(); //Field sınıfının constructor'ı. 1. seviye için gerekli ayarlamaların yapıldığı fonksiyon.

}

void Jeu::draw(Peintre &p) const {
	champ.draw(p); //nesneleri çizdir.
}


void Jeu::setlevel2() //2. seviyeyi başlat.
{
	champ.newObstacle(); //ekrana engeller ekle.
}

//yılanın hareket yönünü belirle.
void Jeu::keyEvent(Snake::Direction d)
{
	snakeObj.keyEvent(d);
}

