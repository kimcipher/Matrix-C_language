#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>



// Define the board dimensions
#define BOARD_WIDTH  6
#define BOARD_HEIGHT 6

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

