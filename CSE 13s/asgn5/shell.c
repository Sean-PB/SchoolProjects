#include "shell.h"
#include <stdlib.h>

// Number to be tracked in lou of yield
static int n;
// Information to be returned
static int info[2] = { 0, 0 };

// Gap function, returns gap size
int gap(int num) {
  // The number being tracked, n, becomes the input
  n = num;
  // Modify n
  while (n > 1) {
    if (n <= 2) {
      n = 1;
    } else {
      n = 5 * n / 11;
    }
    return n;
  }
  return n;
}

// Actual shell sort function
int *shell_sort(int arr[], int length) {
  int temp;
  int step;
  n = length;
  do { // Loop until step = 1, and end after that.
    step = gap(n);
    for (int i = step; i < length; i++) { // Loop from step until end of array
      for (int j = i; j > step - 1;
           j -= step) { // Loop while j > step -1, decrementing by step
        // Compare values
        if (arr[j] < arr[j - step]) {
          // Swap values
          temp = arr[j];
          arr[j] = arr[j - step];
          arr[j - step] = temp;
          // Add to move count
          info[1] += 3;
        }
        // Add to compare count
        info[0]++;
      }
    }
  } while (step > 1);
  // Return move and comparision counts
  return info;
}
