#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <vector.h>
#include "winsys.h"


class CSnake:public CFramedWindow
{
private:
  bool menu = true;
  bool pause = true;
  bool help = false;
  bool died = false;
  int points = 0;
  int level = 1;
  Cpoint food;
  vector <Cpoint> SnakeBody;

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


  void Game();

public:
  CSnake(CRect r, char _c = ' ');
  bool eventHandler(int key);
  void paint();
};

#endif
