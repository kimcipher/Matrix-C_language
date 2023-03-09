#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int currentLevel = 1;
int score = 0;
int movesLeft = MAX_MOVES;
bool gameOver = false;


// Define the board dimensions
#define BOARD_WIDTH  6
#define BOARD_HEIGHT 6


// The Game modes
#define TIMED_MODE 1
#define ENDLESS_MODE 2
#define PUZZLE_MODE 3
#define CHALLENGE_MODE 4
#define BOSS_MODE 5
#define TOURNAMENT_MODE 6

// Define the game timer duration
#define GAME_DURATION 60

// Define the game board and other game variables
cell board[ROWS][COLS];
int score = 0;
int moves_remaining = 0;
int time_remaining = GAME_DURATION;

// Define the function to initialize the game board
void initialize_board() {
    // TODO: Write code to randomly generate a game board based on the game rules
}

// Define the function to update the game board after a match is made
void update_board(int row1, int col1, int row2, int col2) {
    // TODO: Write code to update the game board after a match is made
}

// Define the function to activate a power-up
void activate_power_up() {
    // TODO: Write code to activate a power-up
}

// Define the function to check if the game is over
int is_game_over() {
    // TODO: Write code to check if the game is over
}

// Define the function to handle user input
void handle_input() {
    // TODO: Write code to handle user input
}

// Define the function to update the game timer
void update_timer() {
    // Decrement the time remaining on the clock
    time_remaining--;

    // Check if the time has run out
    if (time_remaining == 0) {
        // End the game
        printf("Time's up! Game over.\n");
        exit(0);
    }
}

// Define the function to print the game board
void print_board() {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%d ", board[i][j].value);
        }
        printf("\n");
    }
}

//Function that generate the game board
void generateBoard(Cell board[BOARD_SIZE][BOARD_SIZE]) {
    int i, j;

    // initialize all cells to have a random value and no power-up
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j].value = rand() % NUM_COLORS;
            board[i][j].matched = false;
            board[i][j].powerUp = NONE;
        }
    }

    // ensure there are no initial matches
    while (checkMatches(board)) {
        // if there are matches, reshuffle the board
        shuffleBoard(board);
    }

    // randomly place power-ups on the board
    int numPowerUps = 0;
    while (numPowerUps < NUM_POWER_UPS) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        if (board[row][col].powerUp == NONE) {
            board[row][col].powerUp = rand() % NUM_POWER_UP_TYPES;
            numPowerUps++;
        }
    }
}


int main() {
    // Initialize the random number generator
    srand(time(NULL));

    // Initialize the game board
    initialize_board();

    // Start the game loop
    while (1) {
        // Print the game board
        print_board();

        // Handle user input
        handle_input();

        // Update the game timer
        update_timer();

        // Check if the game is over
        if (is_game_over()) {
            // End the game
            printf("Game over.\n");
            exit(0);
        }
    }

    return 0;
}

// Define the cell struct
typedef struct {
    int value;
    bool matched;
    bool hasPowerup;
} Cell;

typedef struct {
    Cell board[BOARD_WIDTH][BOARD_HEIGHT];
} Board;

Board levels[NUM_LEVELS];

void loadLevel(int levelNum) {
    // Load the board for the specified level
    // (Assuming the levels are stored in an external file called 'levels.txt')
    FILE* file = fopen("levels.txt", "r");
    if (file == NULL) {
        printf("Error: could not open levels file.\n");
        return;
    }
    int boardNum = levelNum - 1;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            int value;
            if (fscanf(file, "%d", &value) == 1) {
                levels[boardNum].board[i][j].value = value;
                levels[boardNum].board[i][j].matched = false;
                levels[boardNum].board[i][j].hasPowerup = false;
            } else {
                printf("Error: invalid levels file format.\n");
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
}

void loadNextLevel(int currentLevel) {
    if (currentLevel >= NUM_LEVELS) {
        printf("Congratulations, you've completed all the levels!\n");
        return;
    }
    loadLevel(currentLevel + 1);
    printf("Level %d\n", currentLevel + 1);
    // Reset the game state (e.g. score, number of turns left, etc.)
}



// Define the board array
Cell board[BOARD_WIDTH][BOARD_HEIGHT];

int main() {
  int rows, cols, score = 0, count = 0;
  printf("Enter the number of rows: ");
  scanf("%d", &rows);
  printf("Enter the number of columns: ");
  scanf("%d", &cols);
  int board[rows][cols];

  // Initialize board with random numbers
  srand(time(NULL));
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      board[i][j] = rand() % 10;
    }
  }

  // Print initial board
  printf("Initial board:\n");
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  // Game loop
  int x, y, temp;
  while(count < 10) { // User has 10 moves
    printf("Current score: %d\n", score);
    printf("Select a cell to swap with:\n");
    printf("Row (1-%d): ", rows);
    scanf("%d", &x);
    printf("Column (1-%d): ", cols);
    scanf("%d", &y);
    printf("Selected cell: (%d, %d)\n", x, y);

    // Check if chosen cell is out of bounds
    if(x < 1 || x > rows || y < 1 || y > cols) {
      printf("Invalid selection. Try again.\n");
      continue;
    }

    printf("Enter the number to swap with: ");
    scanf("%d", &temp);

    // Check if chosen number is not on the board
    int found = 0;
    for(int i = 0; i < rows; i++) {
      for(int j = 0; j < cols; j++) {
        if(board[i][j] == temp) {
          found = 1;
          break;
        }
      }
      if(found) break;
    }
    if(!found) {
      printf("Invalid selection. Try again.\n");
      continue;
    }

    // Swap the numbers and update score
    int temp_num = board[x-1][y-1];
    board[x-1][y-1] = temp;
    for(int i = 0; i < rows; i++) {
      for(int j = 0; j < cols; j++) {
        if(board[i][j] == temp) {
          board[i][j] = temp_num;
          score += abs(temp_num - temp);
          break;
        }
      }
    }

    // Print updated board
    printf("Updated board:\n");
    for(int i = 0; i < rows; i++) {
      for(int j = 0; j < cols; j++) {
        printf("%d ", board[i][j]);
      }
      printf("\n");
    }

    count++;
  }

  // Print final score and board
  printf("Final score: %d\n", score);
  printf("Final board:\n");
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }

  void generateBoard() {
    // Initialize the board to all zeros
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            board[i][j].value = 0;
            board[i][j].matched = false;
            board[i][j].hasPowerup = false;
        }
    }
    
    // Generate random numbers for each cell on the board
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            // Generate a random number between 1 and 6 (inclusive)
            board[i][j].value = rand() % 6 + 1;
            
            // Ensure that there are no initial matches
            while ((i >= 2 && board[i][j].value == board[i-1][j].value && board[i][j].value == board[i-2][j].value) ||
                   (j >= 2 && board[i][j].value == board[i][j-1].value && board[i][j].value == board[i][j-2].value)) {
                board[i][j].value = rand() % 6 + 1;
            }
        }
    }
    
    // Randomly place power-ups on the board
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            // Generate a random number between 1 and 10 (inclusive)
            int randNum = rand() % 10 + 1;
            
            // Place a power-up if the random number is 1
            if (randNum == 1) {
                board[i][j].hasPowerup = true;
            }
        }
    }
  }


// Shuffle power-up: shuffles the board
void shuffle() {
    // Shuffle the board by swapping the values of random cells
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            int randX = rand() % BOARD_WIDTH;
            int randY = rand() % BOARD_HEIGHT;
            int tempValue = board[i][j].value;
            board[i][j].value = board[randX][randY].value;
            board[randX][randY].value = tempValue;
        }
    }
}

// Swap power-up: swaps the values of two cells
void swap(int x1, int y1, int x2, int y2) {
    int tempValue = board[x1][y1].value;
    board[x1][y1].value = board[x2][y2].value;
    board[x2][y2].value = tempValue;
}

// Bonus points power-up: adds bonus points to the user's score
void bonusPoints(int points) {
    // Add bonus points to the user's score
    // (Assuming a global variable called 'score')
    score += points;
}

// Bomb power-up: removes all cells of a certain value from the board
void bomb(int value) {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            if (board[i][j].value == value) {
                board[i][j].value = 0;
                board[i][j].matched = true;
            }
        }
    }
}

// Multiplier power-up: multiplies the value of a cell by a certain amount
void multiplier(int x, int y, int multiplier) {
    board[x][y].value *= multiplier;
}

// Freeze power-up: freezes a row or column for a certain number of turns
void freeze(int x, int y, int turns) {
    // (Assuming a global variable called 'turnCounter')
    board[x][y].value = 0;
    board[x][y].matched = true;
    if (x == 0) {
        for (int i = 1; i < BOARD_HEIGHT; i++) {
            board[i][y].value = 0;
            board[i][y].matched = true;
        }
    } else {
        for (int i = 0; i < x; i++) {
            board[i][y].value = 0;
            board[i][y].matched = true;
        }
    }
    turnCounter += turns;
}

// Mystery Cell power-up: randomly selects a power-up to apply to the board
void mysteryCell() {
    // Generate a random number between 1 and 7 (inclusive)
    int powerupNum = rand() % 7 + 1;
    
    // Apply the corresponding power-up to the board
    switch (powerupNum) {
        case 1:
            shuffle();
            break;
        case 2:
            swap(rand() % BOARD_WIDTH, rand() % BOARD_HEIGHT, rand() % BOARD_WIDTH, rand() % BOARD_HEIGHT);
            break;
        case 3:
            bonusPoints(rand() % 101 + 100);
            break;
        case 4:
            bomb(rand() % 6 + 1);
            break;
        case 5:
            multiplier(rand() % BOARD_WIDTH, rand() % BOARD_HEIGHT, rand() % 4 + 2);
            break;

    }
}

// User input handling
void handleMouseClick(int x, int y) {
    int row = y / CELL_SIZE;
    int col = x / CELL_SIZE;
    if (isValidCell(row, col)) {
        // Handle selection of cell
        // ...
    }
}

void handleKeyPress(char key) {
    switch (key) {
        case 's':
            activateShuffle();
            break;
        case 'b':
            activateBomb();
            break;
        // Handle other power-ups
        // ...
        default:
            printf("Invalid key pressed.\n");
            break;
    }
}

// function that handles user input
void handleInput(Cell board[BOARD_SIZE][BOARD_SIZE], int *selectedRow, int *selectedCol, bool *swappingCells, int *swapRow, int *swapCol, bool *usingPowerUp, int *powerUpRow, int *powerUpCol, PowerUp *selectedPowerUp) {
    // check if user has clicked a cell to select it
    if (isClicked()) {
        int row = getClickedRow();
        int col = getClickedCol();

        // check if user is selecting a cell to swap
        if (*swappingCells) {
            if (row == *selectedRow && col == *selectedCol) {
                // user clicked the same cell twice, cancel swapping
                *swappingCells = false;
            } else if (isAdjacent(*selectedRow, *selectedCol, row, col)) {
                // user has selected two adjacent cells to swap
                swapCells(board, *selectedRow, *selectedCol, row, col);
                *swappingCells = false;
            } else {
                // user clicked a non-adjacent cell, deselect first cell
                *selectedRow = row;
                *selectedCol = col;
            }
        } else {
            // user is not currently swapping cells, check for power-up activation
            if (board[row][col].powerUp != NONE && !board[row][col].matched) {
                *usingPowerUp = true;
                *powerUpRow = row;
                *powerUpCol = col;
                *selectedPowerUp = board[row][col].powerUp;
            } else {
                // user has clicked a cell to select it for swapping
                *swappingCells = true;
                *selectedRow = row;
                *selectedCol = col;
            }
        }
    }
}


//a function that listens for mouse clicks and converts the coordinates of the click into board coordinates (i.e. the row and column of the cell that was clicked). 
// eparate function to handle key presses, such as activating power-ups. 


// Game logic
// function that checks for matches on the board and updates the score accordingly.
void checkMatches() {
    bool hasMatches = false;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            if (!board[i][j].matched) {
                int numMatches = countMatches(i, j);
                if (numMatches >= MIN_MATCH_SIZE) {
                    hasMatches = true;
                    markMatches(i, j, numMatches);
                    updateScore(numMatches);
                }
            }
        }
    }
    if (!hasMatches) {
        printf("No more matches, please try another move.\n");
        // Decrement the number of turns left, or end the game if zero
    }
}

bool checkMatches(Cell board[BOARD_SIZE][BOARD_SIZE]) {
    bool hasMatches = false;

    // check for horizontal matches
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE - 2; j++) {
            if (board[i][j].value == board[i][j+1].value && board[i][j+1].value == board[i][j+2].value) {
                // three horizontal cells in
            }
        }
    }
}

void checkGameOver() {
    if (numTurnsLeft <= 0) {
        printf("Out of turns, game over.\n");
        // End the game
    } else if (!isBoardSolvable()) {
        printf("Board is not solvable, please try again.\n");
        // Reset the board
    } else if (isBoardComplete()) {
        printf("Congratulations, you've completed the level!\n");
        // Load the next level
        loadNextLevel(currentLevel);
    }
}

// adding obstacles to the game

typedef enum {
    CELL_EMPTY,
    CELL_BLOCKED,
    CELL_STONE,
    CELL_POWERUP,
    CELL_NUM_TYPES
} CellType;

typedef struct {
    CellType type;
    int value;
    bool matched;
    bool containsPowerUp;
    bool isObstacle;
} Cell;

void generateBoard() {
    // Initialize all cells to empty
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            board[i][j].type = CELL_EMPTY;
            board[i][j].value = 0;
            board[i][j].matched = false;
            board[i][j].containsPowerUp = false;
            board[i][j].isObstacle = false;
        }
    }

    // Place cells with values and power-ups
    // ...

    // Place obstacles
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        int row, col;
        do {
            row = rand() % BOARD_HEIGHT;
            col = rand() % BOARD_WIDTH;
        } while (board[row][col].isObstacle || !isCellAccessible(row, col));
        board[row][col].isObstacle = true;
        board[row][col].type = CELL_BLOCKED; // Or CELL_STONE, depending on the obstacle type
    }
}


bool isCellAccessible(int row, int col) {
    if (board[row][col].isObstacle) {
        return false;
    }
    if (row > 0 && board[row-1][col].isObstacle) {
        return false;
    }
    // Check other neighboring cells
    // ...
    return true;
}

bool canCellsBeSwapped(int row1, int col1, int row2, int col2) {
    if (board[row1][col1].isObstacle || board[row2][col2].isObstacle) {
        return false;
    }
    // Check other conditions for swapping
    // ...
    return true;
}

void checkMatches() {
    // Modify match checking algorithm to account for blocked cells
    // ...
}

void activateStoneDestroyer(int row, int col) {
    if (board[row][col].type == CELL_STONE) {
        board[row][col].type = CELL_EMPTY;
        board[row][col].isObstacle = false;
        // Update score, or activate other effects
        // ...
    }
}

