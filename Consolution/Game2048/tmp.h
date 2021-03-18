#pragma once

#if 0
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
#endif