#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <vector>
#include <ctime>
#include <cstdlib>


#include "winsys.h"
#include "cpoint.h"
#include "screen.h"


class CSnake:public CFramedWindow
{
private:
  bool menu = true;
  bool help = true;
  bool died = false;
  int direction = KEY_RIGHT;
  int level = 0;
  CPoint food;
  vector <CPoint> SnakeBody;

  //Printing current game interface
  //void drawMenu();
  void printHelp();
  void printMenu();
  void printGameOver();

  //Fuctions to handle game mechanics
  void startGame();
  void generateFood();
  bool eatFood();
  bool moveSnake();


  void draw();

public:
  CSnake(CRect r, char _c = ' ') : CFramedWindow(r, _c)
{
  srand(time(NULL));
  startGame();
  help = false;
  menu = true;
  draw();
}
  bool handleEvent(int key);
  void paint();
};

#endif
