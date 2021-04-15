#include "quick.h"
#include <stdio.h>
#include <stdlib.h>

// Compare and move count to be returned
static int info[2] = { 0, 0 };

// Partition function to be used in quick_sort
int partition(int arr[], int left, int right) {
  int pivot = arr[left]; // Item to be pivoted around
  int lo = left + 1; // Far left side of array thats being worked with
  int hi = right; // Far right side of array that being worked with
  int temp;
  // Loop indefinitley
  while (1) {
    // While the low and high elements haven't passed by each other and
    // while the high element is larger than or equal to the pivot
    while (lo <= hi && arr[hi] >= pivot) {
      hi -= 1; // move the high element down
      info[0] += 1;
    }
    // While the low and high elements haven't passed by each other and
    // while  the high element is less than or equal to the pivot
    while (lo <= hi && arr[lo] <= pivot) {
      lo += 1; // move the low element up
      info[0] += 1;
    }
    // If the current low element is less than the current high element
    // then swap them
    if (lo <= hi) {
      temp = arr[lo];
      arr[lo] = arr[hi];
      arr[hi] = temp;
      info[0]++;
      info[1] += 3; // add to move count
    }
    // Otherwise the partition has been sorted except for the pivot so...
    else {
      break;
    }
  }
  // Move the pivot into the correct place
  temp = arr[left];
  arr[left] = arr[hi];
  arr[hi] = temp;
  info[1] += 3; // Add to move count
  // Return high index as the partition for the next recursive loop
  return hi;
}

// Quick sort function (recursive)
int *quick_sort(int arr[], int left, int right) {
  // If the array is not yet fully sorted
  // AKA if the partition is not yet fully sorted
  // AKA if the partition is more than 1 element
  if (left < right) {
    info[0]++;
    int index = partition(arr, left, right);
    // Left partition
    quick_sort(arr, left, index - 1);
    // Right partition
    quick_sort(arr, index + 1, right);
  }

  return info;
}
