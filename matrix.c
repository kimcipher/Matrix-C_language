#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 3
#define COLS 3


int main() {
  int board[ROWS][COLS] = { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9} };
  int x, y, temp, count = 0;
  srand(time(NULL));
  
  while(count < 5) {
    printf("Current board:\n");
    for(int i = 0; i < ROWS; i++) {
      for(int j = 0; j < COLS; j++) {
        printf("%d ", board[i][j]);
      }
      printf("\n");
    }
    
    x = rand() % ROWS;
    y = rand() % COLS;
    printf("Select a cell to swap with (%d, %d): ", x+1, y+1);
    scanf("%d", &temp);
    
    for(int i = 0; i < ROWS; i++) {
      for(int j = 0; j < COLS; j++) {
        if(board[i][j] == temp) {
          board[x][y] = temp;
          board[i][j] = board[x][y];
          count++;
          break;
        }
      }
      if(count == 5) break;
    }
  }
  
  printf("Final board:\n");
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }
  
  return 0;
}