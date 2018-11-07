/**
* @file battleships.c
* @author Lior Paz <lior.paz1@mail.huji.ac.il>
* @version 1.0
* @date 16 Aug 2018
*
* @brief Game of battleships.
*
* @section DESCRIPTION
* Help functions for the game.
*/

// ------------------------------ includes ------------------------------
#include <stdlib.h>
#include <time.h>
#include "battleships.h"
#include <stdio.h>

// -------------------------- const definitions -------------------------
/**
 * @brief number of hits in the begining of every ship's life
 */
#define INITIALIZED_HITS 0

/**
 * @brief board marks
 */
#define UNCHECKED_TILE '_'
#define MISS_SIGN 'o'
#define HIT_SIGN 'x'

/**
 * @brief Messages to be printed
 */
#define MISS_MSG "Miss"
#define SUNK_MSG "Hit and sunk."
#define HIT_MSG "Hit!"

/**
 * @brief num of possible ship directions
 */
#define NUM_OF_DIR 2

/**
 * @brief enums for directions
 */
typedef enum Dir
{
    HOR,
    VER
} Dir;

// ------------------------------ functions -----------------------------
/**
 * @brief check if a certain tile already contains a ship or not
 * @param row tile row
 * @param col tile col
 * @param board board
 * @return bool
 */
int checkTile(int row, int col, Board *board)
{
    return (board->boardTiles[row][col]->ship != NULL);
}

/**
 * @brief a pointer to new Ship
 * @param k ship index in board array
 * @param shipSize ship size
 * @param board board
 * @return ship pointer
 */
Ship *newShip(int k, int shipSize, Board *board)
{
    Ship *ship = (Ship *) malloc(sizeof(Ship));
    if (ship == NULL)
    {
        return NULL;
    }
    ship->hits = INITIALIZED_HITS;
    ship->size = shipSize;
    ship->alive = TRUE;
    (*board).boardShips[k] = ship;
    return ship;
}

/**
 * @brief allocates all the necessary memory
 * @param size board size
 * @return pointer for new board
 */
Board *memAlloc(int size)
{
    Board *newBoard = (Board *) malloc(sizeof(Board));
    if (newBoard == NULL)
    {
        return NULL;
    }
    newBoard->boardTiles = (BoardTile ***) malloc(sizeof(BoardTile **) * size);
    if (newBoard->boardTiles == NULL)
    {
        freeMem(newBoard);
        return NULL;
    }
    int p;
    for (p = 0; p < size; p ++)
    {
        newBoard->boardTiles[p] = (BoardTile **) malloc(sizeof(BoardTile *) * size);
        if (newBoard->boardTiles[p] == NULL)
        {
            freeMem(newBoard);
            return NULL;
        }
        int i;
        for (i = 0; i < size; i ++)
        {
            newBoard->boardTiles[p][i] = (BoardTile *) malloc(sizeof(BoardTile));
            newBoard->boardTiles[p][i]->boardStatus = UNCHECKED_TILE;
            newBoard->boardTiles[p][i]->ship = NULL;
        }
    }
    newBoard->size = size;
    return newBoard;
}

/**
 * @brief free the ships memory
 * @param board board
 */
void freeShipsMem(const Board *board)
{
    int j;
    for (j = 0; j < NUM_OF_SHIPS; j ++)
    {
        free(board->boardShips[j]);
    }
}

/**
 * @brief free the tiles memory
 * @param board board
 * @param p row index
 */
void freeTilesMem(const Board *board, int p)
{
    int k;
    for (k = 0; k < board->size; k ++)
    {
        free(board->boardTiles[p][k]);
    }
}

/**
 * @brief free all of the memory allocations
 * @param board board to be free
 */
void freeMem(Board *board)
{
    if (board != NULL)
    {
        if (board->boardTiles != NULL)
        {
            int p;
            for (p = 0; p < board->size; p ++)
            {
                freeTilesMem(board, p);
                free(board->boardTiles[p]);
            }
            free(board->boardTiles);
        }
        freeShipsMem(board);
        free(board);
    }
}

/**
 * @brief Initializes new board
 * @param size board size
 * @return Board pointer
 */
Board *createBoard(int size)
{
    Board *newBoard = memAlloc(size); //create board
    if (newBoard == NULL)
    {
        return newBoard;
    }
    //creates and randomize the ships
    int ships[NUM_OF_SHIPS] = SHIPS_SIZES;
    int r;
    srand((unsigned int) time(NULL));
    for (r = 0; r < NUM_OF_SHIPS; r ++)
    {
        int flag = FALSE;
        while (flag != TRUE)
        {
            int currShipSize = ships[r];
            int randDir = (Dir) rand() % NUM_OF_DIR;
            int randRow;
            int randCol;
            if (randDir == VER)
            {
                randRow = rand() % (size - ships[r] + 1);
                randCol = rand() % size;
            }
            else
            {
                randRow = rand() % size;
                randCol = rand() % (size - ships[r] + 1);
            }
            int counter = 0;
            int continueFlag = TRUE;
            switch (randDir)
            {
                case VER:
                    for (counter = 0; counter < currShipSize; counter ++)
                    {
                        continueFlag = FALSE;
                        if (checkTile(randRow + counter, randCol, newBoard))
                        {
                            break;
                        }
                        continueFlag = TRUE;
                    }

                    if (continueFlag)
                    {
                        Ship *ship = newShip(r, currShipSize, newBoard);
                        if (ship == NULL)
                        {
                            freeMem(newBoard);
                            return NULL;
                        }
                        for (counter = 0; counter < currShipSize; counter ++)
                        {
                            newBoard->boardTiles[randRow + counter][randCol]->ship = ship;
                        }
                        newBoard->boardShips[r] = ship;
                        flag = TRUE;
                    }

                    break;
                case HOR:

                    for (counter = 0; counter < currShipSize; counter ++)
                    {
                        continueFlag = FALSE;

                        if (checkTile(randRow, randCol + counter, newBoard))
                        {
                            break;
                        }
                        continueFlag = TRUE;
                    }

                    if (continueFlag)
                    {
                        Ship *ship = newShip(r, currShipSize, newBoard);
                        if (ship == NULL)
                        {
                            freeMem(newBoard);
                            return NULL;
                        }
                        for (counter = 0; counter < currShipSize; counter ++)
                        {
                            newBoard->boardTiles[randRow][randCol + counter]->ship = ship;
                        }
                        flag = TRUE;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    newBoard->
            alive = TRUE;
    return
            newBoard;
}

/**
 * @brief Play every turn
 * @param row
 * @param col
 * @param board
 * @return Message
 */
char *play(char row, int col, Board *board)
{
    BoardTile *tile = board->boardTiles[row - A_LOWERCASE][col - 1];
    if (tile->ship == NULL)
    {
        tile->boardStatus = MISS_SIGN;
        return MISS_MSG;
    }
    if (tile->boardStatus == HIT_SIGN)
    {
        return "Already been Hit";
    }
    tile->ship->hits ++;
    tile->boardStatus = HIT_SIGN;
    if (tile->ship->hits == tile->ship->size)
    {
        tile->ship->alive = FALSE;
        return SUNK_MSG;
    }
    return HIT_MSG;
}

/**
 * @brief Checks if the board is dead or not
 * @param board board
 */
void checkBoard(Board *board)
{
    int i;
    int counter = 0;
    for (i = 0; i < NUM_OF_SHIPS; i ++)
    {
        if (board->boardShips[i]->alive == FALSE)
        {
            counter ++;
        }
    }
    if (counter == NUM_OF_SHIPS)
    {
        board->alive = FALSE;
    }
}