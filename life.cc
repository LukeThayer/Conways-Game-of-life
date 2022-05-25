// game of life rules
// 1) live cell with fewer than two neighbors dies
// 2) live cell with two or three neighbors lives
// 3) live cell with more than three neighbors dies
// 4) dead cell with three live neighbors is now alive

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

const int WORLD_WIDTH = 50;
const int WORLD_HEIGHT = 50;
const int ITERATIONS = 10000;

void printWorld(int *world, int width, int height)
{
    for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
                {
                    printf("%c", world[y * width + x] ? 'X' : ' ');
                }
            printf("\n");
        }
}
int getCell(int *world, int x, int y)
{
    int i = y * WORLD_WIDTH + x;
    if (i < 0)
        {
            i = 0;
        }
    if (i > WORLD_WIDTH * WORLD_HEIGHT)
        {
            i = WORLD_WIDTH * WORLD_HEIGHT;
        }
    if (x > WORLD_HEIGHT | y > WORLD_HEIGHT)
        {
            return 0;
        }
    else
        {
            return world[i];
        }
}
void setCell(int *world, int x, int y, int val)
{
    int i = y * WORLD_WIDTH + x;
    if (i < 0)
        {
            i = 0;
        }
    if (i > WORLD_WIDTH * WORLD_HEIGHT)
        {
            i = WORLD_WIDTH * WORLD_HEIGHT;
        }
    world[i] = val;
}
int countNeighbor(int *world, int x, int y)
{
    int counter = 0;
    for (int yChange = -1; yChange < 2; yChange++)
        {
            for (int xChange = -1; xChange < 2; xChange++)
                {
                    if (!(xChange == 0 && yChange == 0))
                        {
                            int status =
                                getCell(world, (x + xChange), (y + yChange));

                            if (status == 1)
                                {
                                    counter++;
                                }
                        }
                }
        }

    return counter;
}
int main(int arc, char *argp[])
{

    int *oldWorld = (int *)calloc(WORLD_WIDTH * WORLD_HEIGHT, sizeof(int));
    // Draw glider at top left setCell
    setCell(oldWorld, 3, 2, 1);
    setCell(oldWorld, 4, 3, 1);
    setCell(oldWorld, 2, 4, 1);
    setCell(oldWorld, 3, 4, 1);
    setCell(oldWorld, 4, 4, 1);

    // Other Starting Conditions
    setCell(oldWorld, 10, 12, 1);
    setCell(oldWorld, 10, 13, 1);
    setCell(oldWorld, 11, 13, 1);
    setCell(oldWorld, 9, 13, 1);
    setCell(oldWorld, 12, 13, 1);
    setCell(oldWorld, 14, 14, 1);
    setCell(oldWorld, 10, 14, 1);
    setCell(oldWorld, 13, 14, 1);
    setCell(oldWorld, 12, 14, 1);
    setCell(oldWorld, 15, 14, 1);

    printf("\033[2J");
    printWorld(oldWorld, WORLD_WIDTH, WORLD_HEIGHT);

    for (int i = 0; i < ITERATIONS; i++)
        {
            int *newWorld =
                (int *)calloc(WORLD_WIDTH * WORLD_HEIGHT, sizeof(int));

            for (int y = 0; y < WORLD_HEIGHT; y++)
                {
                    for (int x = 0; x < WORLD_WIDTH; x++)
                        {
                            int currentCellVal = getCell(oldWorld, x, y);
                            int aliveAmount = 0;
                            aliveAmount = countNeighbor(oldWorld, x, y);
                            if (currentCellVal == 1)
                                {
                                    if (aliveAmount == 2 || aliveAmount == 3)
                                        {
                                            setCell(newWorld, x, y, 1);
                                        }
                                    else
                                        {
                                            setCell(newWorld, x, y, 0);
                                        }
                                }
                            else if (aliveAmount == 3)
                                {
                                    setCell(newWorld, x, y, 1);
                                }

                            {
                            }
                        }
                }

            printf("\033[2J");
            printWorld(newWorld, WORLD_WIDTH, WORLD_HEIGHT);
            usleep(100000);
            free(oldWorld);
            oldWorld = newWorld;
        }

    free(oldWorld);

    return 0;
}
