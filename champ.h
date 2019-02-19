#ifndef CHAMP_H_
#define CHAMP_H_

class Peintre;

class Champ {
public:
	enum {
		WIDTH = 21, HEIGHT = 21
	};

	enum {
		OBSTACLE_WIDTH = 8, OBSTACLE_HEIGHT = 8
	};

	enum Type {
		EMPTY, SNAKE_BOX, FOOD_BOX, OBSTACLE_BOX
	};

	Champ();
	void setBox(Type type, int x, int y);
	Type box(int x, int y) const;

	void draw(Peintre &) const;
	void newFood();

	void newObstacle();

	mutable int snakeLength;

private:
	Type coordArray[HEIGHT][WIDTH];	//tüm kutucukların koordinatlarını tutar.
};

#endif /* CHAMP_H_ */


