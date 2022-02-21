#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <vector>
#include <cstdlib>
#include <ctime>

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"


class CSnake:public CFramedWindow
{
private:
  bool menu = true;
  bool pause = true;
  bool help = false;
  bool died = false;
  int ticks_counter = 0;
  int points = 0;
  int speed = 20;
  int direction = KEY_RIGHT;
  CPoint food;
  std::vector <CPoint> SnakeBody;

  //Printing current game interface
  void printMenu();
  void printHelp();
  void printPause();
  void printGameOver();

  //Fuctions to handle game mechanics
  void startGame();
  void generateFood();
  bool ateFood();
  bool moveSnake();


  void printGame();

public:
  CSnake(CRect r, char _c = ' ') : CFramedWindow(r, _c)
{
  srand(time(NULL));
  startGame();
  menu = true;
  help = false;
  pause = true;
  printGame();
}
  bool eventHandler(int key);
  void Game();
};

#endif
