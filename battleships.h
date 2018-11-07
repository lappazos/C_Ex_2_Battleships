/**
* @file battleships.h
* @author Lior Paz <lior.paz1@mail.huji.ac.il>
* @version 1.0
* @date 16 Aug 2018
*
* @brief Game of battleships header file.
*
* @section DESCRIPTION
* Header file.
*/

#ifndef EX2_BATTLESHIPS_H
#define EX2_BATTLESHIPS_H

// -------------------------- const definitions -------------------------
/**
 * @brief bool
 */
#define TRUE 1
#define FALSE 0

/**
 * @brief Ships data
 */
#define NUM_OF_SHIPS 5
#define SHIPS_SIZES {5, 4, 3, 3, 2}

#define A_LOWERCASE 'a'
/**
 * Ship Struct - size, hits, and bool alive
 */
typedef struct Ship
{
    int size;
    int hits;
    int alive; //bool
} Ship;

/**
 * BoardTile Struct - contains Ship, and board printed status
 */
typedef struct BoardTile
{
    Ship *ship;
    char boardStatus;
} BoardTile;

/**
 * Board Struct - contains board size, tiles 2D array, Ships array, and bool alive
 */
typedef struct Board
{
    BoardTile ***boardTiles;
    Ship *boardShips[5];
    int size;
    int alive; //bool
} Board;

// ------------------------------ functions -----------------------------
/**
 * @brief Initializes new board
 * @param size board size
 * @return Board pointer
 */
Board *createBoard(int size);

/**
 * @brief free all of the memory allocations
 * @param board board to be free
 */
void freeMem(Board *board);

/**
 * @brief Play every turn
 * @param row
 * @param col
 * @param board
 * @return Message
 */
char *play(char row, int col, Board *board);

/**
 * @brief Checks if the board is dead or not
 * @param board board
 */
void checkBoard(Board *board);

#endif //EX2_BATTLESHIPS_H