#include "snake.h"



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
  if(!pause && !menu && !moveSnake())
  {
    died = true;
    pause = true;
  }
  gotoyx(geom.topleft.y + food.y, geom.topleft.x + food.x);
  printc('0');
  for(unsigned int i = 1; i < SnakeBody.size(); i++)
  {
    gotoyx(geom.topleft.y + SnakeBody[i].y, geom.topleft.x + SnakeBody[i].x);
    printc('+');
  }
      gotoyx(geom.topleft.y + SnakeBody[0].y, geom.topleft.x + SnakeBody[0].x);
    printc('o');
}

bool CSnake::eventHandler(int key)
{
  if(!pause && key == ERR)
  {
    ticks_counter++;
    if(speed <= ticks_counter) ticks_counter = 0;
  }
  if(!died && tolower(key) == 'p')
  {
    pause = !pause;
    if(!pause) help = false;
    return true;
  }
  if(pause && tolower(key) == 'h')
  {
    help = !help;
    return true;
  }
  if(pause && !menu && tolower(key) == 'q')
  {
    menu = !menu;
    return true;
  }
  if(pause && menu && tolower(key) == 'q')
  {
    exit(0);
  }
  if(tolower(key) == 'r')
  {
    startGame();
    return true;
  }
  if(!died && !pause && (key == KEY_DOWN || key == KEY_UP || key == KEY_LEFT || key == KEY_RIGHT))
  {
    if((key == KEY_DOWN && direction != KEY_UP) || (key == KEY_UP && direction != KEY_DOWN) || (key == KEY_RIGHT && direction != KEY_LEFT) || (key == KEY_LEFT && direction != KEY_RIGHT))
    {
      direction = key;
    }
    return true;
  }
  if (key == '\t') 
  {
    pause = true;
  }
  return CFramedWindow::handleEvent(key);
}

void CSnake::Game() 
{
  CFramedWindow::paint();
  printGame();
  if (!died)
  {
    gotoyx(geom.topleft.y - 1, geom.topleft.x);
    printl("| SCORE: %d |", points);
    if (pause) 
    {
      if (menu) printMenu();
      else if (help) printHelp();
      else printPause();
    }
  } 
  else 
  {
    printGameOver();
  }
}