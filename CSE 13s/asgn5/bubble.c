#include "bubble.h"
#include <stdlib.h>

static int info[2] = { 0, 0 };

int *bubble_sort(int arr[], int len) {
  int temp;
  // Loop through array
  for (int i = 0; i < len - 1; i++) {
    // j = length of the array that needs to be looped through still
    int j = len - 1;
    while (j > i) {
      // compare neighboring elements
      if (arr[j] < arr[j - 1]) {
        // Swaps the two numbers
        temp = arr[j];
        arr[j] = arr[j - 1];
        arr[j - 1] = temp;
        // Adds 3 to move count
        info[1] += 3;
      }
      // Add to comparison count
      info[0]++;

      // Don't need to look at the largest sorted elements again.
      // So decriment j.
      j -= 1;
    }
  }
  // Return move and comparison counts
  return info;
}
