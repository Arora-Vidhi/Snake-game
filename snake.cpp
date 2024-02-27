#include<iostream>
#include<unistd.h>
#include<conio.h>

using namespace std;

bool gameOver;

int h = 20, w = 50;
int x, y, fx, fy, score, len, level, fruits;
int tailX[10], tailY[10];
float speed;

enum eDir{
    stop = 0, Up, Down, Left, Right
};

eDir dir;

void setup()
{
    gameOver = false;
    score = 0;
    len = 0;
    dir = stop;
    x = w / 2;
    y = h / 2;
    fx = rand() % (w - 1) + 1;
    fy = rand() % (h - 1) + 1;
    level = 1;
    fruits = 0;
    speed = 1.0;

    return;
}

void draw()
{
    //clearing
    system("CLS");

    //score board
    cout << "LEVEL: " << level << endl;
    cout << "SCORE = " << score << endl;

    //top border
    for(int i = 0; i <= w + 1; i++)
    cout << "_";
    cout << endl;

    //left and right walls
    for(int i = 0; i <= h + 1; i++)
    {
        for(int j = 0; j <= w + 1; j++)
        {
            if(j == 0 || j == w + 1)
            cout << "|";
            else if(j == x && i == y)
            cout << "O";
            else if(j == fx && i == fy)
            cout << "*";
            else
            {
                int c = 1;
                for(int k = 0; k < len; k++)
                {
                    if(i == tailY[k] && j == tailX[k])
                    {
                        cout << "o";
                        c--;
                        break;
                    }
                }
                if(c)
                cout << " ";
            }
        }
        cout << endl;
    }

    //bottom border
    for(int i = 0; i <= w + 1; i++)
    cout << "T";
    cout << endl;

    return;
}

void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a' : dir = Left; break;
            case 's' : dir = Down; break;
            case 'd' : dir = Right; break;
            case 'w' : dir = Up; break;
        }
    }

    return;
}

void run()
{
    //hitting wall
    if(x == 0 || x == w + 1 || y == 0 || y == h + 1)
    gameOver = true;

    //propagating tail
    int prevX, prevY, prev2X, prev2Y;
    prevX = tailX[0];
    prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    for(int k = 1; k < len; k++)
    {
        prev2X = tailX[k];
        prev2Y = tailY[k];
        tailX[k] = prevX;
        tailY[k] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    //move
    switch(dir)
    {
        case Up : y--; break;
        case Down : y++; break;
        case Left : x--; break;
        case Right : x++; break;
    }

    //hitting fruit
    if(x == fx && y == fy)
    {
        score += 10;
        fx = rand() % (w - 1) + 1;
        fy = rand() % (h - 1) + 1;
        len++;
        fruits++;
    }

    //increasing level
    if(fruits == 5)
    {
        fruits = 0;
        level++;
        speed = speed * 0.9;
    }

    //hitting itself
    {
        for(int k = 0; k < len; k++)
        {
            if(x == tailX[k] && y == tailY[k])
            gameOver = true;
        }
    }

    return;
}

int main()
{
    setup();

    while(!gameOver)
    {
        draw();
        input();
        run();
        sleep(speed);
    }

    cout << "GAME OVER!\nSCORE = " << score << endl;

    return(0);
}