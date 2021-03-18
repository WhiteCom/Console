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
int tmp_maxNum;

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
    printf("input : ");
    scanf("%c", &dir);
    merge(dir);
    tileDraw();
    init();
    move(dir);
    randomTile();
    tileDraw();

    for (int i = 0; i < 4; i++)
    {
        printf("input : ");
        getchar();
        scanf("%c", &dir);
        merge(dir);
        tileDraw();
        init();
        move(dir);
        randomTile();
        tileDraw();
    }
    return 0;
}

void mergeDraw(char& dir)
{
    getchar();
    scanf("%c", &dir);
    merge(dir);
    tileDraw();
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

        int randNum = pow(2, rand() % tmp_maxNum);

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
        printf("up move\n");

        for (int i = 0; i < tileW; i++)
        {
            for (int j = 0; j < tileH - 1; j++)
            {
                if (tile[j][i].num != 0) continue;

                for (int k = j + 1; k < tileH; k++)
                {
                    if (tile[k][i].num != 0)
                    {
                        tile[j][i].num = tile[k][i].num;
                        tile[k][i].num = 0;
                        break;
                    }
                }
            }
        }
    }

    else if (dir == 's' || dir == 'S') //down
    {
        printf("down move\n");

        for (int i = 0; i < tileW; i++)
        {
            for (int j = tileH - 1; j > 0; j--)
            {
                if (tile[j][i].num != 0)
                    continue;

                for (int k = j - 1; k > -1; k--)
                {
                    if (tile[k][i].num != 0)
                    {
                        tile[j][i].num = tile[k][i].num;
                        tile[k][i].num = 0;
                        break;
                    }
                }
            }
        }
       
    }
    else if (dir == 'a' || dir == 'A') //left
    {
        printf("left move\n");
        //위에서 아래로
        for (int j = 0; j < tileH; j++)
        {
            for (int i = 0; i < tileW-1; i++)
            {
                if (tile[j][i].num != 0)
                    continue;
                for (int k = i + 1; k < tileW; k++)
                {
                    if (tile[j][k].num != 0)
                    {
                        tile[j][i].num = tile[j][k].num;
                        tile[j][k].num = 0;
                        break;
                    }

                }
            }
        }
    }
    else if (dir == 'd' || dir == 'D') //right
    {
        printf("right move\n");
        //위에서 아래로
        for (int j = 0; j < tileH; j++)
        {
            for (int i = tileW - 1; i > 0; i--)
            {
                if (tile[j][i].num != 0)
                    continue;

                for (int k = i - 1; k > 0; k--)
                {
                    if (tile[j][k].num != 0)
                    {
                        tile[j][i].num = tile[j][k].num;
                        tile[j][k].num = 0;
                    }
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

void merge(char dir)
{
    tmp_maxNum = maxNum;

    if (dir == 'w' || dir == 'W') //up
    {
        printf("up merge\n");
        //아래에서 위로
        for (int j = tileH - 1; j > -1; j--)
        {
            //좌에서 우로
            for (int i = 0; i < tileW; i++)
            {
                if (tile[j][i].num != 0 && 
                    tile[j - 1][i].num == tile[j][i].num && 
                    j > 0) //합병
                {
                    if (tile[j][i].check == false)
                    {
                        tile[j - 1][i].num *= 2;
                        tile[j][i].num = 0;
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
        printf("down merge\n");
        //위에서 아래로
        for (int j = 0; j < tileH - 1; j++)
        {
            //좌에서 우로
            for (int i = 0; i < tileW; i++)
            {
                if (tile[j][i].num != 0 && 
                    tile[j + 1][i].num == tile[j][i].num &&
                    j < tileH - 1) //합병
                {
                    if (tile[j][i].check == false)
                    {
                        tile[j + 1][i].num *= 2;
                        tile[j][i].num = 0;
                        tile[j + 1][i].check = true;

                        if (tile[j + 1][i].num > maxNum)
                            maxNum = tile[j + 1][i].num;
                    }
                }
            }
        }
    }
    else if (dir == 'a' || dir == 'A') //left
    {
        printf("left merge\n");
        //위에서 아래로
        for (int j = 0; j < tileH; j++)
        {
            //우에서 좌로
            for (int i = tileW - 1; i > -1; i--)
            {
                if (tile[j][i].num != 0 && 
                    tile[j][i - 1].num == tile[j][i].num && 
                    i > 0) //합병
                {
                    if (tile[j][i].check == false)
                    {
                        tile[j][i - 1].num *= 2;
                        tile[j][i].num = 0;
                        tile[j][i - 1].check = true;

                        if (tile[j][i-1].num > maxNum)
                            maxNum = tile[j][i-1].num;
                    }
                }
            }
        }
    }
    else if (dir == 'd' || dir == 'D') //right
    {
        printf("right merge\n");
        //위에서 아래로
        for (int j = 0; j < tileH; j++)
        {
            //좌에서 우로
            for (int i = 0; i < tileW - 1; i++)
            {
                if (tile[j][i].num != 0 &&
                    tile[j][i + 1].num == tile[j][i].num &&
                    i < tileW - 1) //합병
                {
                    if (tile[j][i].check == false)
                    {
                        tile[j][i + 1].num *= 2;
                        tile[j][i].num = 0;
                        tile[j][i + 1].check = true;

                        if (tile[j][i+1].num > maxNum)
                            maxNum = tile[j][i+1].num;
                    }
                }
            }
        }
    }
}