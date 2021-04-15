#include "binary.h"
#include <stdlib.h>

static int info[2] = { 0, 0 };

int *binary_insertion_sort(int arr[], int length) {
  // Temp for swaps
  int temp;
  // Initializing values before loops
  int value;
  int left;
  int right;
  int mid;
  // Loop through each element in the array starting after the first
  // Through each loop the sorted sub-array grows and the unsorted sub-array
  // shrinks
  for (int i = 1; i < length; i++) {
    value = arr[i]; // Element to be compared
    left = 0;
    right = i;
    // Binary search
    // While left index hasn't passed right index
    while (left < right) {
      // Find middle of left and right
      mid = left + ((right - left) / 2);
      // if value to be compared is greater than or equal to middle value,
      if (value >= arr[mid]) {
        // Move left index past middle index
        left = mid + 1;
      }
      // else (if value to be compared is less than middle value),
      else {
        // Move right index to middle index
        right = mid;
      }
      info[0]++;
    }
    // While the amount of elements compared is greater than the amount of
    // values greater than the middle index, decrementing the amount of elements
    // compared, we...
    for (int j = i; j > left; j--) {
      // Swap
      temp = arr[j - 1];
      arr[j - 1] = arr[j];
      arr[j] = temp;
      info[1] += 3;
    }
  }
  return info;
}
