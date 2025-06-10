#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <easyx.h>
#include <stdio.h>
#include <math.h>
#pragma comment(lib,"Winmm.lib")

#define WIDTH 500
#define HEIGHT 650

using namespace std;

class FeijiGame {
private:
    IMAGE img_bj;
    IMAGE img_fj1, img_fj2;
    IMAGE img_dj1, img_dj2;
    IMAGE img_zd1, img_zd2;
    IMAGE img_fjbz1, img_fjbz2;

    int fj_x, fj_y;
    int dj_x, dj_y;
    int zd_x, zd_y;

    int explode;
    int score;
    int speed;
    bool running;
    bool paused;  // 是否暂停

public:
    FeijiGame() : explode(0), score(0), speed(50), running(true), paused(false) {}

    void init() {
        initgraph(WIDTH, HEIGHT);
        loadimage(&img_bj, _T("resource\\bj.jpg"));
        loadimage(&img_fj1, _T("resource\\fj1.jpg"));
        loadimage(&img_fj2, _T("resource\\fj2.jpg"));
        loadimage(&img_dj1, _T("resource\\dj1.jpg"));
        loadimage(&img_dj2, _T("resource\\dj2.jpg"));
        loadimage(&img_zd1, _T("resource\\zd1.jpg"));
        loadimage(&img_zd2, _T("resource\\zd2.jpg"));
        loadimage(&img_fjbz1, _T("resource\\fjbz1.jpg"));
        loadimage(&img_fjbz2, _T("resource\\fjbz2.jpg"));

        mciSendString(_T("open resource\\music.mp3 alias bjmusic"), NULL, 0, NULL);
        mciSendString(_T("play bjmusic repeat"), NULL, 0, NULL);

        fj_x = WIDTH / 2;
        fj_y = HEIGHT * 2 / 3;
        dj_x = rand() % (WIDTH - 52);
        dj_y = 50;
        zd_x = fj_x + 44;
        zd_y = fj_y - 24;

        BeginBatchDraw();
    }

    void draw() {
        if (paused) return;

        putimage(0, 0, &img_bj);

        if (!explode) {
            putimage(fj_x, fj_y, &img_fj1, NOTSRCERASE);
            putimage(fj_x, fj_y, &img_fj2, SRCINVERT);
            putimage(dj_x, dj_y, &img_dj1, NOTSRCERASE);
            putimage(dj_x, dj_y, &img_dj2, SRCINVERT);
            putimage(zd_x, zd_y, &img_zd1, NOTSRCERASE);
            putimage(zd_x, zd_y, &img_zd2, SRCINVERT);
        } else {
            putimage(fj_x, fj_y, &img_fjbz1, NOTSRCERASE);
            putimage(fj_x, fj_y, &img_fjbz2, SRCINVERT);
            running = false;
        }

        outtextxy(WIDTH * 0.5, HEIGHT * 0.9, _T("分数:"));
        TCHAR s[10];
        _stprintf_s(s, _T("%d"), score);
        outtextxy(WIDTH * 0.6, HEIGHT * 0.9, s);

        FlushBatchDraw();
        Sleep(speed);
    }

    void input() {
        if (_kbhit()) {
            char in = _getch();
            switch (in) {
            case 'a':
                if (!paused && fj_x > 0) fj_x -= 20;
                break;
            case 'd':
                if (!paused && fj_x < WIDTH - 117) fj_x += 20;
                break;
            case 'w':
                if (!paused && fj_y > 0) fj_y -= 20;
                break;
            case 's':
                if (!paused && fj_y < HEIGHT - 120) fj_y += 20;
                break;
            case ' ':
                if (!paused) {
                    zd_x = fj_x + 44;
                    zd_y = fj_y - 24;
                }
                break;
            case 0x1b:  // ESC
                paused = !paused;
                if (paused) {
                    outtextxy(WIDTH / 2 - 40, HEIGHT / 2, _T("游戏已暂停"));
                    FlushBatchDraw();
                } else {
                    draw();  // 继续时刷新界面
                }
                break;
            }
        }
    }

    void update() {
        if (paused) return;

        if (zd_y > -20) zd_y -= 20;

        if (dj_y < HEIGHT) {
            dj_y++;
        } else {
            dj_x = rand() % (WIDTH - 52);
            dj_y = 50;
        }

        if ((zd_x > dj_x - 19) && (zd_x < dj_x + 33) && (zd_y < dj_y + 39)) {
            score += 100;
            dj_x = rand() % (WIDTH - 52);
            dj_y = 50;
            if (score >= 1000)
                speed = 10;
        }

        if ((fj_x > dj_x - 19) && (fj_x < dj_x + 33) && (fj_y < dj_y + 39)) {
            explode = 1;
        }
    }

    void end() {
        EndBatchDraw();
        _getch();
        closegraph();
    }

    void run() {
        init();

        while (running) {
            input();
            draw();
            update();
        }

        outtextxy(WIDTH * 0.5, HEIGHT * 0.5, _T("是否继续"));
        outtextxy(WIDTH * 0.5, HEIGHT * 0.55, _T("继续请按Y,结束请按N"));

        char a;
        cin >> a;

        if (a == 'Y' || a == 'y') {
            running = true;
            explode = 0;
            score = 0;
            speed = 50;
            paused = false;
            run();
        } else {
            end();
        }
    }
};

int main() {
    FeijiGame game;
    game.run();
    return 0;
}