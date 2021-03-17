#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define tileW 4
#define tileH 4

struct Tile
{
    int num = 0;
    bool check = false;
};

Tile tile[tileW][tileH];
int maxNum = 1;

void init();
void tileDraw();
void mergeDraw(char& dir);
void moveDraw(char& dir);
void randomTile();
void move(char& dir);
void merge(char dir);

int main()
{
    
    srand(time(NULL));

    for (int j = 0; j < tileH; j++)
    {
        for (int i = 0; i < tileW; i++)
        {
            if (i == j)
                tile[j][i].num = 1;
        }
    }
    tileDraw();

    char dir;
    printf("move : ");
    scanf("%c", &dir);
    move(dir);
    randomTile();
    tileDraw();

    for (int i = 0; i < 4; i++)
    {
        printf("merge : ");
        mergeDraw(dir);

        printf("move : ");
        moveDraw(dir);
    }
    return 0;
}

void mergeDraw(char& dir)
{
    getchar();
    scanf("%c", &dir);
    merge(dir);
    randomTile();
    tileDraw();
    init();
}

void moveDraw(char& dir)
{
    getchar();
    scanf("%c", &dir);
    move(dir);
    randomTile();
    tileDraw();
}

void randomTile()
{
    for (;;)
    {
    int w = rand() % tileW;
    int h = rand() % tileH;

    int randNum = pow(2,rand() % maxNum);

    if (tile[h][w].num == 0)
    {
        tile[h][w].num = randNum;
        break;
    }
    }
}

void init()
{
    for (int j = 0; j < tileH; j++)
    {
        for (int i = 0; i < tileW; i++)
        {
            tile[j][i].check = false;
        }
    }
}

void tileDraw()
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            printf("%d ", tile[j][i].num);
        }
        printf("\n");
    }
    printf("------\n");
}

void move(char& dir)
{
    if (dir == 'w' || dir == 'W') //up
    {
        printf("up\n");

        //아래에서 위로
        for (int j = tileH - 1; j > -1; j--)
        {
            //좌에서 우로
            for (int i = 0; i < tileW; i++)
            {
                if (tile[j][i].num != 0 && j > 0)
                {
                    Tile tmp = tile[j][i];
                    tile[j][i] = tile[j - 1][i];
                    tile[j - 1][i] = tmp;
                }
            }
        }
    }

    else if (dir == 's' || dir == 'S') //down
    {
        printf("down\n");

        //위에서 아래로
        for (int j = 0; j < tileH - 1; j++)
        {
            //좌에서 우로
            for (int i = 0; i < tileW; i++)
            {
                if (tile[j][i].num != 0 && j < tileH - 1)
                {
                    Tile tmp = tile[j][i];
                    tile[j][i] = tile[j + 1][i];
                    tile[j + 1][i] = tmp;
                }
            }
        }
    }
    else if (dir == 'a' || dir == 'A') //left
    {
        printf("left\n");
        //위에서 아래로
        for (int j = 0; j < tileH; j++)
        {
            //우에서 좌로
            for (int i = tileW - 1; i > -1; i--)
            {
                if (tile[j][i].num != 0 && i > 0)
                {
                    Tile tmp = tile[j][i];
                    tile[j][i] = tile[j][i - 1];
                    tile[j][i - 1] = tmp;
                }
            }
        }
    }
    else if (dir == 'd' || dir == 'D') //right
    {
        printf("right\n");
        //위에서 아래로
        for (int j = 0; j < tileH; j++)
        {
            //좌에서 우로
            for (int i = 0; i < tileW - 1; i++)
            {
                if (tile[j][i].num != 0 && i < tileW - 1)
                {
                    Tile tmp = tile[j][i];
                    tile[j][i] = tile[j][i + 1];
                    tile[j][i + 1] = tmp;
                }
            }
        }
    }
    else
    {
        printf("no dir one more input\n");
        getchar(); //\n 제거용
        scanf("%c", &dir);
        move(dir);
    }
}

//#issue 합병시 덧셈로직 다시 생각하기
void merge(char dir)
{
    if (dir == 'w' || dir == 'W') //up
    {
        //아래에서 위로
        for (int j = tileH - 1; j > -1; j--)
        {
            //좌에서 우로
            for (int i = 0; i < tileW; i++)
            {
                if (tile[j][i].num != 0 && tile[j - 1][i].num != 0 && j > 0) //합병
                {
                    if (tile[j][i].check == false)
                    {
                        tile[j - 1][i].num += tile[j][i].num;
                        tile[j][i].num -= tile[j][i].num;
                        tile[j - 1][i].check = true;

                        if (tile[j - 1][i].num > maxNum)
                            maxNum = tile[j - 1][i].num;
                    }
                }
            }
        }
    }

    else if (dir == 's' || dir == 'S') //down
    {
        //위에서 아래로
        for (int j = 0; j < tileH - 1; j++)
        {
            //좌에서 우로
            for (int i = 0; i < tileW; i++)
            {
                if (tile[j][i].num != 0 && tile[j + 1][i].num != 0 && j < tileH - 1) //합병
                {
                    if (tile[j][i].check == false)
                    {
                        tile[j + 1][i].num += tile[j][i].num;
                        tile[j][i].num -= tile[j][i].num;
                        tile[j + 1][i].check = true;

                        if (tile[j - 1][i].num > maxNum)
                            maxNum = tile[j - 1][i].num;
                    }
                }
            }
        }
    }
    else if (dir == 'a' || dir == 'A') //left
    {
        printf("left\n");
        //위에서 아래로
        for (int j = 0; j < tileH; j++)
        {
            //우에서 좌로
            for (int i = tileW - 1; i > -1; i--)
            {
                if (tile[j][i].num != 0 && tile[j][i - 1].num != 0 && i > 0) //합병
                {
                    if (tile[j][i].check == false)
                    {
                        tile[j][i - 1].num += tile[j][i].num;
                        tile[j][i].num -= tile[j][i].num;
                        tile[j][i - 1].check = true;

                        if (tile[j - 1][i].num > maxNum)
                            maxNum = tile[j - 1][i].num;
                    }
                }
            }
        }
    }
    else if (dir == 'd' || dir == 'D') //right
    {
        printf("right\n");
        //위에서 아래로
        for (int j = 0; j < tileH; j++)
        {
            //좌에서 우로
            for (int i = 0; i < tileW - 1; i++)
            {
                if (tile[j][i].num != 0 && tile[j][i + 1].num != 0 && i < tileW - 1) //합병
                {
                    if (tile[j][i].check == false)
                    {
                        tile[j][i + 1].num += tile[j][i].num;
                        tile[j][i].num -= tile[j][i].num;
                        tile[j][i + 1].check = true;

                        if (tile[j - 1][i].num > maxNum)
                            maxNum = tile[j - 1][i].num;
                    }
                }
            }
        }
    }
}