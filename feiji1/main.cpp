#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <iomanip>

using namespace std;

int player_X, player_Y;
int bullet_X, bullet_Y;
int enemyBullet_X, enemyBullet_Y;
int enemy_X, enemy_Y;
int Height, Width;
int Score = 0;
int enemy_Count = 60;
bool cont = 1;

void moveTo(int x, int y) {
    COORD pos = { x, y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void hideCur() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void init() {
    Height = 35;
    Width = 55;
    player_X = Height / 2;
    player_Y = Width / 2;
    bullet_X = -1;
    bullet_Y = player_Y + 1;
    enemy_X = 0;
    enemy_Y = Width / 2;
    enemyBullet_X = enemy_X + 1;
    enemyBullet_Y = enemy_Y + 1;
    hideCur();
}

string symbolAt(int i, int j) {
    if ((i == player_X) && (j == player_Y))
        return "/=\\";
    if ((i == player_X + 1) && (j == player_Y - 1))
        return "<<*>>";
    if ((i == player_X + 2) && (j == player_Y))
        return "* *";
    if ((i == enemy_X) && (j == enemy_Y))
        return "\\+/";
    if ((i == enemy_X + 1) && (j == enemy_Y + 1))
        return "|";
    if ((i == enemyBullet_X) && (j == enemyBullet_Y))
        return "|";
    if ((i == bullet_X) && (j == bullet_Y))
        return "|";
    return " ";
}

void show() {
    system("cls");
    moveTo(0, 0);
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            cout << symbolAt(i, j);
        }
        cout << "\n";
    }
    cout << "Score: " << Score;
}

void update() {
    if ((bullet_X == enemy_X) && (bullet_Y == enemy_Y)) {
        Score++;
        enemy_Count--;
        enemy_X = 0;
        enemy_Y = rand() % Width;
        bullet_X = -1;
    }

    if ((enemyBullet_X == player_X) && (enemyBullet_Y == player_Y)) {
        Score--;
        if (Score <= 0) cont = 0;
        enemyBullet_X = enemy_X + 1;
        enemyBullet_Y = enemy_Y + 1;
    }

    static int fallSpeed = 0;
    static int enemyBulletSpeed = 0;

    if (bullet_X > -1) bullet_X--;

    if (fallSpeed < 20) {
        fallSpeed++;
    } else {
        enemy_X++;
        fallSpeed = 0;
    }

    if (enemyBulletSpeed < 3) {
        enemyBulletSpeed++;
    } else {
        enemyBullet_X++;
        if (enemyBullet_X > player_X) {
            enemyBullet_X = enemy_X + 1;
            enemyBullet_Y = enemy_Y + 1;
        }
        enemyBulletSpeed = 0;
    }

    if (enemy_X > Height) {
        enemy_X = 0;
        enemy_Y = rand() % Width;
    }
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 'w') player_X--;
        if (ch == 's') player_X++;
        if (ch == 'a') player_Y--;
        if (ch == 'd') player_Y++;
        if (ch == ' ') {
            bullet_X = player_X - 1;
            bullet_Y = player_Y;
        }
    }
}

int main() {
    init();
    while (enemy_Count > 0) {
        show();
        update();
        if (!cont) break;
        input();
        Sleep(50);
    }
    system("cls");
    cout << "Game Over! Final Score: " << Score << endl;
    return 0;
}