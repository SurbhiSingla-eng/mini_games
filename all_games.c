#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char board[3][3];
char player = 'X';

void initBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void drawBoard() {
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

int checkWin() {
    char p;
    for (p = 'X'; p <= 'O'; p++) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == p && board[i][1] == p && board[i][2] == p) {
                return p == 'X' ? 1 : 2;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (board[0][i] == p && board[1][i] == p && board[2][i] == p) {
                return p == 'X' ? 1 : 2;
            }
        }
        if (board[0][0] == p && board[1][1] == p && board[2][2] == p) {
            return p == 'X' ? 1 : 2;
        }
        if (board[0][2] == p && board[1][1] == p && board[2][0] == p) {
            return p == 'X' ? 1 : 2;
        }
    }
    bool tie = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                tie = false;
                break;
            }
        }
    }

    return tie ? 3 : 0;
}

void playTicTacToe() {
    initBoard();
    int row, col;
    bool gameOver = false;
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Instructions:\n");
    printf("1. The game is played on a 3x3 grid.\n");
    printf("2. Players take turns marking a cell with their symbol ('X' or 'O').\n");
    printf("3. The first player to get three of their symbols in a row (horizontally, vertically, or diagonally) wins.\n");
    printf("4. If all cells are filled without any player achieving three in a row, the game ends in a tie.\n");
    printf("5. The first row and column begins with '0' and the number for last row and column is '2'\n");
    printf("Let's start!\n\n");

    while (!gameOver) {
        drawBoard();
        printf("Player %c's turn. Enter row and column: ", player);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            printf("Invalid move. Try again.\n");
            continue;
        }

        board[row][col] = player;

        int winner = checkWin();
        if (winner != 0) {
            drawBoard();
            if (winner == 3) {
                printf("It's a tie!\n");
            } else {
                printf("Player %c wins!\n", winner == 1 ? 'X' : 'O');
            }
            gameOver = true;
        } else {
            player = player == 'X' ? 'O' : 'X';
        }
    }
}
#define WIDTH 20
#define HEIGHT 20

typedef struct {
    int x, y;
} Point;

typedef enum {
    UP, DOWN, LEFT, RIGHT
} Direction;

void playSnake() {
    Point snake[100];
    int length = 1;
    Direction dir = RIGHT;
    Point food = {rand() % WIDTH, rand() % HEIGHT};
    bool gameOver = false;

    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;

    printf("Welcome to Snake!\n");
    printf("Instructions:\n");
    printf("1. Use 'w', 's', 'a', and 'd' keys to move the snake up, down, left, and right respectively.\n");
    printf("2. Eat the '@' symbol to grow the snake and earn points.\n");
    printf("3. Avoid running into the walls or the snake's body to prevent game over.\n");
    printf("Let's start!\n\n");

    while (!gameOver) {
        // system("cls"); 
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                bool isSnake = false;
                for (int k = 0; k < length; k++) {
                    if (snake[k].x == j && snake[k].y == i) {
                        isSnake = true;
                        break;
                    }
                }

                if (isSnake) {
                    printf("O");
                } else if (j == food.x && i == food.y) {
                    printf("@");
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
        Point newHead;
        switch (dir) {
            case UP:
                newHead.x = snake[0].x;
                newHead.y = snake[0].y - 1;
                break;
            case DOWN:
                newHead.x = snake[0].x;
                newHead.y = snake[0].y + 1;
                break;
            case LEFT:
                newHead.x = snake[0].x - 1;
                newHead.y = snake[0].y;
                break;
            case RIGHT:
                newHead.x = snake[0].x + 1;
                newHead.y = snake[0].y;
                break;
        }
        if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT) {
            gameOver = true;
            continue;
        }

        for (int i = 0; i < length; i++) {
            if (newHead.x == snake[i].x && newHead.y == snake[i].y) {
                gameOver = true;
                break;
            }
        }
        for (int i = length - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
        snake[0] = newHead;
        if (newHead.x == food.x && newHead.y == food.y) {
            food.x = rand() % WIDTH;
            food.y = rand() % HEIGHT;
            length++;
        }
        char input;
        scanf("%c", &input);
        switch (input) {
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
        }
    }

    printf("Game Over!\n");
}
void playHangman() {
    char* words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    char* word = words[rand() % 5];
    int len = strlen(word);
    char guessed[26] = {0};
    int tries = 0;
    bool gameOver = false;
    for (int i = 0; i < len; i++) {
        guessed[i] = '-';
    }
    guessed[len] = '\0';

    printf("Welcome to Hangman!\n");
    printf("Instructions:\n");
    printf("1. You have 6 tries to guess the hidden word.\n");
    printf("2. Enter a letter to guess it.\n");
    printf("3. If the letter is correct, it will be revealed in the word.\n");
    printf("4. If the letter is wrong, you will lose a try.\n");
    printf("Let's start!\n\n");


    while (!gameOver && tries < 6) {
        printf("Tries left: %d\n", 6 - tries);
        printf("Word: %s\n", guessed);

        char letter;
        printf("Enter a letter: ");
        scanf(" %c", &letter); 
        bool found = false;
        for (int i = 0; i < len; i++) {
            if (word[i] == letter) {
                guessed[i] = letter;
                found = true;
            }
        }

        if (!found) {
            tries++;
            printf("Wrong guess!\n");
        }
        bool wordGuessed = true;
        for (int i = 0; i < len; i++) {
            if (guessed[i] == '-') {
                wordGuessed = false;
                break;
            }
        }

        if (wordGuessed) {
            printf("Congratulations! You guessed the word: %s\n", word);
            gameOver = true;
        } else if (tries == 6) {
            printf("Sorry, you ran out of tries. The word was: %s\n", word);
            gameOver = true;
        }
        printf("Press Enter to continue...");
        while (getchar() != '\n');
    }
}
#define SIZE 9

int grid[SIZE][SIZE];

void initGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

bool isSafe(int row, int col, int num) {
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }
    int boxRow = row - row % 3;
    int boxCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[boxRow + i][boxCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int row, int col) {
    if (row == SIZE - 1 && col == SIZE) {
        return true;
    }

    if (col == SIZE) {
        row++;
        col = 0;
    }

    if (grid[row][col] != 0) {
        return solveSudoku(row, col + 1);
    }

    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(row, col + 1)) {
                return true;
            }

            grid[row][col] = 0;
        }
    }

    return false;
}

void playSudoku() {
    initGrid();
    printf("Welcome to Sudoku Solver!\n");
    printf("Instructions:\n");
    printf("1. Enter numbers from 1 to 9 to fill the Sudoku grid.\n");
    printf("2. Use '0' to represent empty cells.\n");
    printf("3. Rows, columns, and 3x3 boxes must contain unique numbers.\n");
    printf("Let's start!\n\n");
    printf("Enter the Sudoku puzzle (use '0' for empty cells):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    if (solveSudoku(0, 0)) {
        printf("Sudoku puzzle solved:\n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", grid[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("No solution exists for this Sudoku puzzle.\n");
    }
}

void displayMenu() {
    printf("Welcome to the Game Collection!\n");
    printf("Choose a game to play:\n");
    printf("1. Tic-Tac-Toe\n");
    printf("2. Snake\n");
    printf("3. Hangman\n");
    printf("4. Sudoku\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    srand(time(NULL)); 

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playTicTacToe();
                break;
            case 2:
                playSnake();
                break;
            case 3:
                playHangman();
                break;
            case 4:
                playSudoku();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}