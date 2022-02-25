#include "snake.h"


void CSnake::startGame() {
    menu = false;
    help = false;
    died = false;
    game_ticks = 0;
    speed = 50;
    direction = KEY_RIGHT;
    level = 0;
    int startPosition_x = rand() % (geom.size.x - 5) + 1;
    int startPosition_y = rand() % (geom.size.y - 3) + 1;
    SnakeBody.clear();
    SnakeBody.push_back(CPoint(startPosition_x, startPosition_y));
    SnakeBody.push_back(CPoint(startPosition_x - 1, startPosition_y));
    SnakeBody.push_back(CPoint(startPosition_x - 2, startPosition_y));
    generateFood();
    paint();
}



void CSnake::generateFood() {
    CPoint newfood;
    do {
        newfood = CPoint((rand() % (geom.size.x - 2)) + 1, (rand() % (geom.size.y - 2)) + 1);
        bool s = true;
        for (auto &body:SnakeBody) {
            if (body.x == newfood.x && newfood.y == body.x) {
                s = false;
                break;
            }
        }
        if (s) break;
    } while (true);
    food = newfood;
}

bool CSnake::eatFood() {
    bool t = false;
    for (auto &part : SnakeBody) {
        if (part.x == food.x && part.y == food.y) {
            level++;
            t = true;
            break;
        }
    }
    if (t) {
        generateFood();
        if(speed > 1) speed--;
        return true;
    }
    return false;
}

bool CSnake::moveSnake() {
    if (menu) {
        return true;
    }
    CPoint tail = SnakeBody[SnakeBody.size() - 1];
    for (unsigned long i = SnakeBody.size() - 1; i > 0; i--) {
        SnakeBody[i] = SnakeBody[i - 1];
    }
    if (direction == KEY_DOWN) {
        SnakeBody[0] += CPoint(0, 1);
    } else if (direction == KEY_UP) {
        SnakeBody[0] += CPoint(0, -1);
    } else if (direction == KEY_RIGHT) {
        SnakeBody[0] += CPoint(1, 0);
    } else if (direction == KEY_LEFT) {
        SnakeBody[0] += CPoint(-1, 0);
    }
    for (unsigned int i = 1; i < SnakeBody.size(); i++) {
        if (SnakeBody[0].x == SnakeBody[i].x && SnakeBody[0].y == SnakeBody[i].y) {
            return false;
        }
    }
    if (SnakeBody[0].x == 0) {
        SnakeBody[0].x = geom.size.x - 2;
    }
    if (SnakeBody[0].x == geom.size.x - 1) {
        SnakeBody[0].x = 1;
    }
    if (SnakeBody[0].y == 0) {
        SnakeBody[0].y = geom.size.y - 2;
    }
    if (SnakeBody[0].y == geom.size.y - 1) {
        SnakeBody[0].y = 1;
    }
    if (eatFood()) {
        SnakeBody.push_back(tail);
    }
    return true;
}

void CSnake::draw() {
    if (game_ticks == 0 && !moveSnake()) {
        died = true;
        menu = true;
    }
    gotoyx(food.y + geom.topleft.y, food.x + geom.topleft.x);
    printc('O');
    for (unsigned int i = 1; i < SnakeBody.size(); i++) {
        gotoyx(SnakeBody[i].y + geom.topleft.y, SnakeBody[i].x + geom.topleft.x);
        printc('+');
    }
    gotoyx(SnakeBody[0].y + geom.topleft.y, SnakeBody[0].x + geom.topleft.x);
    printc('o');
}

void CSnake::printGameOver() {
    int x = geom.topleft.x, y = geom.topleft.y;
    gotoyx(y + 1, x + 1);
    printl("GAME OVER, result: %d", level);
}

void CSnake::printMenu() {
    int x = geom.topleft.x, y = geom.topleft.y;
    gotoyx(y + 2, x + 3);
    printl("p - toggle play/pause mode");
    gotoyx(y + 3, x + 3);
    printl("h - toggle help information");
    gotoyx(y + 4, x + 3);
    printl("r - restart game");
    gotoyx(y + 5, x + 3);
    printl("q - quit");
    gotoyx(y + 6, x + 3);
}

void CSnake::printHelp() {
    int x = geom.topleft.x, y = geom.topleft.y;
    gotoyx(y + 2, x + 2);
    printl("Use arrows to move snake");
    gotoyx(y + 4, x + 2);
    printl("Collect food and grow as much as you can.");
    gotoyx(y + 5, x + 2);
    printl("Be cautious to not eat yourself");
    gotoyx(y + 7, x + 2);
    printl("Controls: 'P' or 'R' - play || 'H' -help || 'Q' - quit game");
    gotoyx(y + 9, x + 2);
    printl("You can move the game window during pause mod using arrows");
}

bool CSnake::handleEvent(int key) {
    if (!menu && key == ERR) {
        game_ticks++;
        if (speed <= game_ticks) {
            game_ticks = 0;
        }
    }
    if (!died && tolower(key) == 'p') {
        menu = !menu;
        if (!menu) {
            help = false;
        }
        return true;
    }
    if (tolower(key) == 'h' && menu) {
        help = !help;
        return true;
    }
    if (menu && tolower(key) == 'q') {
        exit(0);
    }
    if (tolower(key) == 'r') {
        CSnake::startGame();
        return true;
    }
    if (!died && !menu) {
        if ((key == KEY_UP && direction != KEY_DOWN) || (key == KEY_DOWN && direction != KEY_UP) ||
            (key == KEY_LEFT && direction != KEY_RIGHT) || (key == KEY_RIGHT && direction != KEY_LEFT)) {
            direction = key;
            if(!moveSnake()) died = true;
            game_ticks = 0;
        }
        return true;
    }
    if (key == '\t') {
        menu = true;
    }
    return CFramedWindow::handleEvent(key);
}

void CSnake::paint() {
    CFramedWindow::paint();
    draw();
    if (!died) {
        gotoyx(geom.topleft.y - 1, geom.topleft.x);
        printl("| LEVEL: %d |", level);
        if (menu) {
            if (help) printHelp();
            else printMenu();
        }
    } else {
        printGameOver();
    }
}
