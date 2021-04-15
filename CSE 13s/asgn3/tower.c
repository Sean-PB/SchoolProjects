#include "stack.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "srn:"

int stack_way(int disks);
int recursive_way(int disks, char start, char end, char spare);

int moves = 0;

int main(int argc, char **argv) {
  char choice;
  int disks = 5;
  bool stack = false;
  bool recursion = false;
  while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
    switch (choice) {
    case 's':
      stack = true;
      break;
    case 'r':
      recursion = true;
      break;
    case 'n':
      disks = atoi(optarg);
      break;
    default:
      printf("Only these arguements are allowed:\n-r : recursive\n-s : "
             "stack\n-n : (optional) set number of disks. Requires number "
             "arguement after.\n");
      return 0;
    }
  }

  if (stack) {
    printf("================================\n");
    printf("----------   STACKS   ----------\n");
    printf("================================\n");
    printf("\nNumber of moves: %d\n", stack_way(disks));
    moves = 0;
  }
  if (recursion) {
    printf("================================\n");
    printf("--------   RECURSION   ---------\n");
    printf("================================\n");
    printf("\nNumber of moves: %d\n", recursive_way(disks, 'A', 'B', 'C'));
    moves = 0;
  }
  return 0;
}

int stack_way(int disks) {
  Stack *A = stack_create(disks, 'A'); // Creating stacks
  Stack *B = stack_create(disks, 'B');
  Stack *C = stack_create(disks, 'C');
  for (int i = disks; i > 0; i--) { // Filling stack_A up with disks
    stack_push(A, i);
  }

  if (disks % 2 == 1) { // If number of disks is odd, move AB, AC, BC
    while (1) { // Game loop
      if ((stack_peek(A) < stack_peek(B) && !stack_empty(A))
          || stack_empty(B)) { // AB
        // A to B
        printf("Move disk %d from peg A to peg B\n", stack_peek(A));
        stack_push(B, stack_pop(A));
      } else {
        // B to A
        printf("Move disk %d from peg B to peg A\n", stack_peek(B));
        stack_push(A, stack_pop(B));
      }
      moves++;
      if (stack_empty(A) && stack_empty(C)) { // Check if done
        break;
      }

      if ((stack_peek(A) < stack_peek(C) && !stack_empty(A))
          || stack_empty(C)) { // AC
        // A to C
        printf("Move disk %d from peg A to peg C\n", stack_peek(A));
        stack_push(C, stack_pop(A));
      } else {
        // C to A
        printf("Move disk %d from peg C to peg A\n", stack_peek(C));
        stack_push(A, stack_pop(C));
      }
      moves++;
      if (stack_empty(A) && stack_empty(C)) { // Check if done
        break;
      }

      if ((stack_peek(B) < stack_peek(C) && !stack_empty(B))
          || stack_empty(C)) { // BC
        // B to C
        printf("Move disk %d from peg B to peg C\n", stack_peek(B));
        stack_push(C, stack_pop(B));
      } else {
        // C to B
        printf("Move disk %d from peg C to peg B\n", stack_peek(C));
        stack_push(B, stack_pop(C));
      }
      moves++;
      if (stack_empty(A) && stack_empty(C)) { // Check if done
        break;
      }
    }
  } else { // If number of disks is even, move AC, AB, BC
    while (1) { // Game loop
      if ((stack_peek(A) < stack_peek(C) && !stack_empty(A))
          || stack_empty(C)) { // AC
        // A to C
        printf("Move disk %d from peg A to peg C\n", stack_peek(A));
        stack_push(C, stack_pop(A));
      } else {
        // C to A
        printf("Move disk %d from peg C to peg A\n", stack_peek(C));
        stack_push(A, stack_pop(C));
      }
      moves++;
      if (stack_empty(A) && stack_empty(C)) { // Check if done
        break;
      }

      if ((stack_peek(A) < stack_peek(B) && !stack_empty(A))
          || stack_empty(B)) { // AB
        // A to B
        printf("Move disk %d from peg A to peg B\n", stack_peek(A));
        stack_push(B, stack_pop(A));
      } else {
        // B to A
        printf("Move disk %d from peg B to peg A\n", stack_peek(B));
        stack_push(A, stack_pop(B));
      }
      moves++;
      if (stack_empty(A) && stack_empty(C)) { // Check if done
        break;
      }

      if ((stack_peek(B) < stack_peek(C) && !stack_empty(B))
          || stack_empty(C)) { // BC
        // B to C
        printf("Move disk %d from peg B to peg C\n", stack_peek(B));
        stack_push(C, stack_pop(B));
      } else {
        // C to B
        printf("Move disk %d from peg C to peg B\n", stack_peek(C));
        stack_push(B, stack_pop(C));
      }
      moves++;
      if (stack_empty(A) && stack_empty(C)) { // Check if done
        break;
      }
    }
  }

  stack_delete(A);
  stack_delete(B);
  stack_delete(C);

  return moves;
}

int recursive_way(int disks, char start, char end, char spare) {
  if (disks == 1) {
    printf("Move disk %d from peg %c to peg %c\n", disks, start, end);
    moves++;
    return 0;
  }
  recursive_way(disks - 1, start, spare, end);
  printf("Move disk %d from peg %c to peg %c\n", disks, start, end);
  moves++;
  recursive_way(disks - 1, spare, end, start);
  return moves;
}
