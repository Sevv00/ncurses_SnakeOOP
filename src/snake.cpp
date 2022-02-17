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

void CSnake::printGame()
{
  
}