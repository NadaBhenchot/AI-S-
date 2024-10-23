#include <stdio.h>

#define HUMAN 'X'
#define COMPUTER 'O'
#define EMPTY ' '

char board[3][3] = {
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY}
};

// Function to print the board
void printBoard() {
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            printf("%c | ", board[i][j]);
        }
        printf("\n-------------\n");
    }
}

// Function to check if there are any empty cells
int isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return 1;
    return 0;
}

// Evaluate the board and return a score
int evaluate() {
    // Check rows for a win
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == COMPUTER)
                return +10;
            else if (board[row][0] == HUMAN)
                return -10;
        }
    }

    // Check columns for a win
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == COMPUTER)
                return +10;
            else if (board[0][col] == HUMAN)
                return -10;
        }
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER)
            return +10;
        else if (board[0][0] == HUMAN)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER)
            return +10;
        else if (board[0][2] == HUMAN)
            return -10;
    }

    // Return 0 if no one has won
    return 0;
}

// Minimax function
int minimax(int depth, int isMax) {
    int score = evaluate();

    // If the computer has won, return the score
    if (score == 10)
        return score;

    // If the human has won, return the score
    if (score == -10)
        return score;

    // If there are no more moves and no winner, it's a tie
    if (!isMovesLeft())
        return 0;

    // If it's the computer's turn (maximizing player)
    if (isMax) {
        int best = -1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    // Make the move
                    board[i][j] = COMPUTER;

                    // Call minimax recursively and choose the maximum value
                    best = (best > minimax(depth + 1, 0)) ? best : minimax(depth + 1, 0);

                    // Undo the move
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
    // If it's the human's turn (minimizing player)
    else {
        int best = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    // Make the move
                    board[i][j] = HUMAN;

                    // Call minimax recursively and choose the minimum value
                    best = (best < minimax(depth + 1, 1)) ? best : minimax(depth + 1, 1);

                    // Undo the move
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the computer
void findBestMove(int bestMove[2]) {
    int bestVal = -1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                // Make the move
                board[i][j] = COMPUTER;

                // Compute the evaluation function for this move
                int moveVal = minimax(0, 0);

                // Undo the move
                board[i][j] = EMPTY;

                // If the value of the current move is more than the best value, update best
                if (moveVal > bestVal) {
                    bestMove[0] = i;
                    bestMove[1] = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

// Check if the game is over (win or draw)
int isGameOver() {
    return evaluate() != 0 || !isMovesLeft();
}

int main() {
    printf("Welcome to Tic-Tac-Toe!\n");
    printBoard();

    while (!isGameOver()) {
        // Human move
        int row, col;
        printf("Your turn! Enter row and column (1-3): ");
        scanf("%d %d", &row, &col);
        row--; col--;

        if (board[row][col] == EMPTY) {
            board[row][col] = HUMAN;
        } else {
            printf("Invalid move. Try again.\n");
            continue;
        }

        printBoard();

        // Check if game is over
        if (isGameOver()) {
            break;
        }

        // Computer move
        printf("Computer's turn:\n");
        int bestMove[2] = {-1, -1};
        findBestMove(bestMove);
        board[bestMove[0]][bestMove[1]] = COMPUTER;

        printBoard();
    }

    // Check for winner
    int score = evaluate();
    if (score == 10) {
        printf("Computer wins!\n");
    } else if (score == -10) {
        printf("You win!\n");
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}
