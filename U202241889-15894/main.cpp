//
// Created by DELL on 2023/6/5.
//
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
void updateWithoutInput()
{
    if ((bulletX == enemyX) && (bulletY == enemyY))
    {
        gameScore++;
        enemyCount--;
        enemyX = 0;
        enemyY = rand() % gameWidth;
        bulletX = -1;
    }
    if ((enemyBulletX == playerX) && (enemyBulletY == playerY))
    {
        gameScore--;
        if (gameScore == 0) continueGame = 0;
        enemyBulletX = enemyX + 1;
        enemyBulletY = enemyY+1;
    }
    static int fallSpeed = 0;
    static int enemyBulletSpeed = 0;
    if (bulletX > -1) bulletX--;
    if (fallSpeed < 20)
    {
        fallSpeed++;
    }
    if (enemyBulletSpeed < 3)
    {
        enemyBulletSpeed++;
    }
    if (enemyX > gameHeight)
    {
        enemyX = 0;
        enemyY = rand() % gameWidth;
    }
    if (fallSpeed == 20)
    {
        enemyX++;
        fallSpeed = 0;
    }
    if (enemyBulletSpeed == 3)
    {
        enemyBulletX++;
        if (enemyBulletX > playerX)
        {
            enemyBulletX = enemyX + 1;
            enemyBulletY = enemyY + 1;
        }
        enemyBulletSpeed = 0;
    }
}
void updateWithInput()
{
    char userInput;

    if (_kbhit())
    {
        userInput = _getch();
        if (userInput == 's') playerX++;
        if (userInput == 'w') playerX--;
        if (userInput == 'a') playerY--;
        if (userInput == 'd') playerY++;
        if (userInput == ' ')
        {
            bulletX = playerX - 1;
            bulletY = playerY;
        }
    }
}
int main()
{
    initData();
    while (enemyCount != 0)
    {
        display();
        updateWithoutInput();
        if (continueGame == 0) break;
        updateWithInput();
    }

    return 0;
}