// main.cpp
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<iomanip>
using namespace std;

int playerX, playerY;
int bulletX, bulletY;
int enemyBulletX, enemyBulletY;
int enemyX, enemyY;
int gameHeight, gameWidth;
int gameScore = 0;
int enemyCount = 50;
bool continueGame = 1;

void moveCursorTo(int x, int y)
{
    COORD pos = { x,y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}
void hideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void initData()
{
    gameHeight = 35;
    gameWidth = 55;
    playerX = gameHeight / 2;
    playerY = gameWidth / 2;
    bulletX = -1;
    bulletY = playerY+1;
    enemyX = 0;
    enemyY = gameWidth / 2;
    enemyBulletX = enemyX+1;
    enemyBulletY = enemyY+1;
    hideCursor();
}
void display()
{
    system("cls");
    int i, j;
    moveCursorTo(0, 0);
    for (i = 0; i < gameHeight; i++)
    {
        for (j = 0; j < gameWidth; j++)
        {
            if ((i == playerX) && (j == playerY))
            {
                cout << "/=\\";
            }
            else if ((i == playerX + 1) && (j == playerY-1))
            {
                cout <<"<<*>>";
            }
            else if ((i == playerX + 2) && (j == playerY))
            {
                cout << "* *";
            }
            else if ((i == enemyX) && (j == enemyY))
            {
                cout << "\\+/";
            }
            else if ((i == enemyX + 1) && (j == enemyY + 1))
            {
                cout << "|";
            }
            else if ((i == enemyBulletX) && (j == enemyBulletY))
            {
                cout << "|";
            }
            else if ((i == bulletX) && (j == bulletY))
            {
                cout << "|";
            }
            else cout << " ";
        }
        cout << "\n";
    }
    cout << "Score: " << gameScore;
}
int main()
{
    initData();
    return 0;
}