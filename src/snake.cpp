#include "snake.h"




CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
}

void CSnake::printMenu()
{
  int y = geom.topleft.y;
  int x = geom.topleft.x;
  gotoyx(y + 4, x + (geom.size.x/2));
  attron(A_BOLD);
  printl("Snake");
  attroff(A_BOLD);
  gotoyx(y + 7, x + 3);
  printl("R -- Play");
  gotoyx(y + 8, x + 3);
  printl("H -- Help");
  gotoyx(y + 9, x + 3);
  printl("Q -- Exit");
}

void CSnake::printPause()
{
  int y = geom.topleft.y;
  int x = geom.topleft.x;
  gotoyx(y + 4, x + (geom.size.x/2));
  attron(A_BOLD);
  printl("Snake");
  attroff(A_BOLD);
  gotoyx(y + 7, x + 3);
  printl("P -- Continue");
  gotoyx(y + 8, x + 3);
  printl("R -- Reset");
  gotoyx(y + 9, x + 3);
  printl("H -- Help");
  gotoyx(y + 10, x + 3);
  printl("Q -- Exit");
}

void CSnake::printHelp()
{
  int y = geom.topleft.y;
  int x = geom.topleft.x;
  gotoyx(y + 4, x + (geom.size.x/2));
  attron(A_BOLD);
  printl("Snake");
  gotoyx(y + 7, x + 3);
  printl("How to play");
  attroff(A_BOLD);
  gotoyx(y + 8, x + 3);
  printl("Collect food from the map.");
  gotoyx(y + 9, x + 3);
  printl("Be careful to not hit your body");
  attron(A_BOLD);
  gotoyx(y + 10, x + 3);
  printl("Key Bindings");
  attroff(A_BOLD);
  gotoyx(y + 11, x + 3);
  printl("Move: Arrows");
  gotoyx(y + 12, x + 3);
  printl("R - Play/Reset");
  gotoyx(y + 13, x + 3);
  printl("H - Help");
  gotoyx(y + 14, x + 3);
  printl("P -- Pause/Continue");
  gotoyx(y + 15, x + 3);
  printl("Q -- Exit");
}

void CSnake::printGameOver()
{
  int y = geom.size.y/2;
  int x = geom.size.x/2;
  attron(A_REVERSE);
  gotoyx(y-1,x-4);
  printl("GAME OVER");
  gotoyx(y,x-8);
  printl("YOUR RESULT: %d", points);
  attroff(A_REVERSE);
}

void CSnake::generateFood()
{
  CPoint newFood;
  while(true){
    int XnewFood = 1 + rand()% (geom.size.x - 2);
    int YnewFood = 1 + rand()% (geom.size.y - 2);
    bool overlaping = false;
    newFood = CPoint(XnewFood, YnewFood);
    for(auto &snakebody:SnakeBody)
    {
      if(snakebody.x == newFood.x && snakebody.y == newFood.y){
        overlaping = true;
        break;
      }
    }
    if(!overlaping){
      break;
    }
  }
  food = newFood;
}

bool CSnake::ateFood()
{
  bool ate = false;
  if(SnakeBody.front().x == food.x && SnakeBody.front().y == food.y){
    points++;
    ate = true;
  }
  if(ate)
  {
    generateFood();
    return true;
  }
  return false;
}

bool CSnake::moveSnake()
{
  if(pause || menu){
    return true;
  }
  CPoint tail = SnakeBody[SnakeBody.size()-1];
  for (unsigned int i = SnakeBody.size()-1; i > 0; i--)
  {
    SnakeBody[i] = SnakeBody[i-1];
  } 
  if(direction == KEY_LEFT)
  {
    SnakeBody[0] += CPoint(-1,0);
  } 
  else if(direction == KEY_RIGHT)
  {
    SnakeBody[0] += CPoint(1,0);
  }
  else if(direction == KEY_UP)
  {
    SnakeBody[0] += CPoint(0,-1);
  }
  else if(direction == KEY_DOWN)
  {
    SnakeBody[0] += CPoint(0,1);
  }
  for(unsigned int i = 1; i < SnakeBody.size(); i++)
  {
    if(SnakeBody[0].x == SnakeBody[i].x && SnakeBody[0].y == SnakeBody[i].y)
    {
      return false;
    }
  }
  if(SnakeBody[0].x == 0){
    SnakeBody[0].x = geom.size.x-2;
  }
  if(SnakeBody[0].x == geom.size.x-1){
    SnakeBody[0].x = 1;
  }
  if(SnakeBody[0].y == 0){
    SnakeBody[0].x = geom.size.y-2;
  }
  if(SnakeBody[0].y == geom.size.x-1){
    SnakeBody[0].y = 1;
  }
  if(ateFood())
  {
    SnakeBody.push_back(tail);
  }
  return true;
}

void CSnake::startGame()
{
  menu = false;
  pause = false;
  died = false;
  help = false;
  direction = KEY_LEFT;
  points = 0;
  int x_start_position = geom.size.x/2;
  int y_start_position = geom.size.y/2;
  SnakeBody.clear();
  SnakeBody.push_back(CPoint(x_start_position, y_start_position));
  SnakeBody.push_back(CPoint(x_start_position + 1, y_start_position));
  SnakeBody.push_back(CPoint(x_start_position + 2, y_start_position));
  generateFood();
  Game();
}

void CSnake::printGame()
{
  
}