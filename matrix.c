#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

 
