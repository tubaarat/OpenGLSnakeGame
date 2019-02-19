
#ifndef PEINTRE_H_
#define PEINTRE_H_

#include "unistd.h"
class Peintre
{
public:
  void snakeBox(int x1, int y1, int x2, int y2);
  void obstacleBox(int x1, int y1, int x2, int y2);
  void foodBox(int x1, int y1, int x2, int y2);
};


#endif /* PEINTRE_H_ */
