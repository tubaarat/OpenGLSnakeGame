/*
 * snake.h
 *
 *  Created on: 9 Ara 2018
 *      Author: Asus
 */

#ifndef SNAKE_H_
#define SNAKE_H_



#include <list>

class Champ;

class Snake
{
public:
  enum Direction { LEFT, UP, RIGHT, DOWN }; //direction yönlerini tutar.

  Snake();

  bool tick(Champ &);

  void keyEvent(Direction);

private:
  typedef std::list<std::pair<int, int> > Boxes;
  Boxes boxes;				//integer sayı çiftlerinden oluşan; yılanın koordinatlarını tutmaya yarayan bir liste oluşturur.
  Direction currentDirection;				// yılanın o anki yönünü tutar.
  Direction lastDirection;				//yılanın son yön bilgisini tutar.
};



#endif /* SNAKE_H_ */
