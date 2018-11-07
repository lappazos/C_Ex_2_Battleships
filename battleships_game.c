/**
* @file battleships_game.c
* @author Lior Paz <lior.paz1@mail.huji.ac.il>
* @version 1.0
* @date 16 Aug 2018
*
* @brief Game of battleships.
*
* @section DESCRIPTION
* Program to play battleships.
* Input : No argument, only inside the game.
* Process: Playing the game.
* Output : None.
*/

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "battleships.h"

// -------------------------- const definitions -------------------------
/**
* @brief Messages to be printed
*/
#define BOARD_SIZE_MSG "Enter Board Size:"
#define SIZE_ERR_MSG "board size not fitting!"
#define GAME_OVER_MSG "Game over"
#define INVALID_MOVE_MSG "Invalid move, try again."
#define BEGIN_PLAY "Ready to play\n"
#define MOVE_INPUT "enter coordinates:"

/**
* @brief Err Messages to be printed
*/
#define SIZE_FORMAT_ERR "not valid board size!"
#define MEM_ERR "Memory Error"

/**
* @brief Size of input array
*/
#define EXIT_SIZE 5

/**
* @brief exit input
*/
#define EXIT_INPUT "exit"

/**
* @brief Num of col chars
*/
#define COL_INPUT_SIZE 1

/**
* @brief Min max board size
*/
#define MIN_BOARD_SIZE 5
#define MAX_BOARD_SIZE 26

/**
* @brief Min row index
*/
#define MIN_ROW_INDEX 1

/**
* @brief Num of chars to read from input
*/
#define RAND_NUM_TO_READ 1000

#define SPACE " "
#define NEW_LINE "\n"

// ------------------------------ functions -----------------------------
/**
 * @brief print the board
 * @param board board to be printed
 */
void printBoard(Board *board)
{
    printf(SPACE);
    int i;
    for (i = 1; i <= board->size; i ++)
    {
        printf(",%d", i);
    }
    printf(NEW_LINE);
    int k;
    for (k = 0; k < board->size; k ++)
    {
        printf("%c", 'a' + k);
        int j;
        for (j = 0; j < board->size; j ++)
        {
            printf(" %c", board->boardTiles[k][j]->boardStatus);
        }
        printf(NEW_LINE);
    }
}

/**
 * @brief exits the game
 * @param board board to clean
 * @return exit successfully int
 */
int exitGame(Board *board)
{
    printf("%s\n", GAME_OVER_MSG);
    freeMem(board);
    return EXIT_SUCCESS;
}

/**
 * @brief handles with wrong move input
 * @param input pointer to an input array of chars
 */
void inputErr(char *input)
{
    fprintf(stderr, "%s\n", INVALID_MOVE_MSG);
    fgets(input, RAND_NUM_TO_READ, stdin); //in order to clean the stdin remains
}

/**
 * @brief the main function which runs the game
 * @return 1 or 0 according to exit status
 */
int main()
{
    //handles with board size input
    printf(BOARD_SIZE_MSG);
    int boardSize;
    if (scanf("%d", &boardSize) == 0)
    {
        fprintf(stderr, "%s\n", SIZE_FORMAT_ERR);
        return EXIT_FAILURE;
    }
    if (boardSize > MAX_BOARD_SIZE || boardSize < MIN_BOARD_SIZE)
    {
        fprintf(stderr, "%s\n", SIZE_ERR_MSG);
        return EXIT_FAILURE;
    }
    Board *board = createBoard(boardSize);
    if (board == NULL)
    {
        fprintf(stderr, "%s\n", MEM_ERR);
        return EXIT_FAILURE;
    }
    printf(BEGIN_PLAY);
    //game iterations
    while (board->alive)
    {
        printBoard(board);
        int moveCheck = TRUE;
        char row;
        int col;
        //receiving turn input
        while (moveCheck)
        {
            printf("%s", MOVE_INPUT);
            char input[EXIT_SIZE] = {'\0'};
            scanf("%s", input);
            if (! strcmp(input, EXIT_INPUT))
            {
                return exitGame(board);
            }
            else if (strlen(input) > COL_INPUT_SIZE)
            {
                inputErr(input);
                continue;
            }
            else if (scanf("%d", &col) == 0)
            {
                inputErr(input);
                continue;
            }
            row = input[0];
            if (col > boardSize || col < MIN_ROW_INDEX || (A_LOWERCASE + boardSize - 1) <
                                                          input[0] || input[0] < A_LOWERCASE)
            {
                inputErr(input);
                continue;
            }
            moveCheck = FALSE;
        }
        //play the turn
        printf("%s\n", play(row, col, board));
        checkBoard(board);
    }
    //end game in case of victory
    printBoard(board);
    return exitGame(board);
}