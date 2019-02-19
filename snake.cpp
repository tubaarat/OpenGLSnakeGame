#include "snake.h"
#include "champ.h"
#include <cstdlib>

Snake::Snake() :
	currentDirection(static_cast<Direction>(rand() % 4)), //yılanın başlangıç yönünü random olarak belirler.

	lastDirection(currentDirection) {
	boxes.push_back(std::pair<int, int>(Champ::WIDTH / 2, Champ::HEIGHT / 2)); //boxes listesinin en arkasına bir integer değer çifti(pair) ekler.

}

bool Snake::tick(Champ &champ) //yılanın hareket yönünü belirleyip kendisiyle yada bir engelle çarpıştıysa false çarpışmadıysa true döndür.
		{
	lastDirection = currentDirection; //random bir direction atıyor.

	std::pair<int, int> p = boxes.front(); //listenin en başındaki çifti alıyor.

	switch (currentDirection) {

	case LEFT:			//Yılanı sola hareket ettir.
		p.first--;
		break;
	case UP:				//yılanı yukarı hareket ettir.
		p.second--;
		break;
	case RIGHT:	 //yılanı sağa hareket ettir.
		p.first++;
		break;
	case DOWN:		//yılanı aşağı hareket ettir.
		p.second++;
		break;
	}

	if (p.first < 0 || p.first >= Champ::WIDTH || p.second < 0 || p.second >= Champ::HEIGHT)
	//Eğer yılan ekran sınırı ile çarpıştıysa false döndür.
		return false;

	if (champ.box(p.first, p.second) == Champ::SNAKE_BOX)	//yılan kendiyle çarpıştıysa false döndür.
		return false;

	if (champ.box(p.first, p.second) == Champ::OBSTACLE_BOX) //yılan dikey engellerle çarpıştıysa false döndür.
		return false;

	boxes.push_front(p); //Yılanın başını yine en öne koy.

	if (champ.box(p.first, p.second) != Champ::FOOD_BOX) { //Eski ve yeni lokasyonlara yeni bir alan set et.(yeni bir kutu ekle)

		champ.setBox(Champ::SNAKE_BOX, p.first, p.second);

		std::pair<int, int> p = boxes.back();

		champ.setBox(Champ::EMPTY, p.first, p.second);

		boxes.pop_back();
	}
	else  //Eğer yılan yiyeceği yediyse yeni bir yiyecek oluştur.
	{
		champ.setBox(Champ::SNAKE_BOX, p.first, p.second);

		champ.newFood();
	}
	if (boxes.size() >= Champ::WIDTH * Champ::HEIGHT - 1) //Eğer yılan tüm ekranı doldurursa false döndür.
		return false;

	//Diğer tüm durumlar için true döndür.
	return true;
}

void Snake::keyEvent(Direction d)		//Yılanın yönünü değiştirir.(Zıt yönde ilerlemesine engel olur.
//Örneğin sol tuşa basıldıktan sonra sağ tuşa basılsa bile yılan sola gitmeye devam eder.)
		{
	if (d == currentDirection)
		return;
	switch (d) {
	case LEFT:
		if (lastDirection == RIGHT)
			return;
		break;
	case UP:
		if (lastDirection == DOWN)
			return;
		break;
	case RIGHT:
		if (lastDirection == LEFT)
			return;
		break;
	case DOWN:
		if (lastDirection == UP)
			return;
		break;
	}
	currentDirection = d; //direction u ata.
}
