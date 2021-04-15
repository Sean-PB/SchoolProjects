#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "Absqip:r:n:"

void print_sorted(
    int *arr, int arr_len, int compares, int moves, int print_len);
void reset(int *workable, int *base, int length);

int main(int argc, char **argv) {
  // User input variables
  bool All = false, bubble = false, shell = false, quick = false,
       insertion = false;
  int print_len = 100, seed = 8222022, length = 100;
  char choice;
  // Getopt loop
  while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
    switch (choice) {
    case 'A':
      All = true;
      break;
    case 'b':
      bubble = true;
      break;
    case 's':
      shell = true;
      break;
    case 'q':
      quick = true;
      break;
    case 'i':
      insertion = true;
      break;
    case 'p':
      print_len = atoi(optarg);
      break;
    case 'r':
      seed = atoi(optarg);
      break;
    case 'n':
      length = atoi(optarg);
      break;
    default:
      // Error message
      printf("Only these arguments are allowed:\n-A : All sorting method.\n-b "
             ": Bubble sort.\n-s : Shell sort.\n-q : Quick sort.\n-i : Binary "
             "insertion sort.\n-p : (followed by a number value) specifies the "
             "how many\n     of the values to print from the array. Default is "
             "100.\n-r : (followed by a number value) specifies the random\n   "
             "  seed for the unsorted array.\n-n : (followed by a number "
             "value) specifies the size\n     of the array to be sorted.\n");
      return 0;
    }
  }

  // If no sorts are specified...
  if (All == false && bubble == false && shell == false && quick == false
      && insertion == false) {
    All = true; // Default to all
  }

  // If user tries to print more elements than are in the array
  if (print_len > length) {
    printf("Number of values to be printed must be less than the length\n "
           "of the array\n");
    return 0;
  }

  // Make the unsorted array based on the input variables or defaults
  int *workable = calloc(length, sizeof(int)); // Array to be sorted
  if (workable == NULL) { // End program if theres a calloc error
    printf("base calloc error");
    return 0;
  }
  int *base = calloc(
      length, sizeof(int)); // Array to reset the workable array once its sorted
  if (base == NULL) { // Free memory and end program if theres a calloc error
    printf("base calloc error");
    free(workable);
    return 0;
  }
  // Fill arrays with random numbers
  srand(seed);
  int num;
  for (int i = 0; i < length; i++) {
    num = (rand() & 0x3FFFFFFF);
    workable[i] = num;
    base[i] = num;
  }

  // All sorts
  if (All) {
    int *info; // Initializing info once
    // Bubble sort
    // No need to reset because this will be the first time a sort is beig run
    printf("Bubble Sort\n");
    info = bubble_sort(workable, length);
    print_sorted(workable, length, info[0], info[1], print_len);

    // Shell sort
    reset(workable, base, length); // Make sure array is unsorted
    printf("Shell Sort\n");
    info = shell_sort(workable, length);
    print_sorted(workable, length, info[0], info[1], print_len);

    // Quick Sort
    reset(workable, base, length);
    printf("Quick Sort\n");
    info = quick_sort(workable, 0,
        length - 1); // Length - 1 here because its the for the
        // last value, not a loop
    print_sorted(workable, length, info[0], info[1], print_len);

    // Binary insertion sort
    reset(workable, base, length); // Make sure array is unsorted
    printf("Binary Insertion Sort\n");
    info = binary_insertion_sort(workable, length);
    print_sorted(workable, length, info[0], info[1], print_len);

    // End program here to avaoid repeating outputs
    // Free arrays calloc'd earlier
    free(workable);
    free(base);
    return 0;
  }

  // Bubble sort
  if (bubble) {
    // No need to reset because this will be the first time a sort is being run
    printf("Bubble Sort\n");
    int *info = bubble_sort(workable, length);
    print_sorted(workable, length, info[0], info[1], print_len);
  }

  // Shell sort
  if (shell) {
    reset(workable, base, length); // Make sure array is unsorted
    printf("Shell Sort\n");
    int *info = shell_sort(workable, length);
    print_sorted(workable, length, info[0], info[1], print_len);
  }

  // Quick Sort
  if (quick) {
    reset(workable, base, length); // Make sure array is unsorted
    printf("Quick Sort\n");
    int *info = quick_sort(workable, 0,
        length - 1); // Length - 1 here because its the for
        // the last value, not a loop
    print_sorted(workable, length, info[0], info[1], print_len);
  }

  // Binary insertion sort
  if (insertion) {
    reset(workable, base, length); // Make sure array is unsorted
    printf("Binary Insertion Sort\n");
    int *info = binary_insertion_sort(workable, length);
    print_sorted(workable, length, info[0], info[1], print_len);
  }

  // Free arrays calloc'd earlier
  free(workable);
  free(base);
  return 0;
}

// Prints desired output for any soritng function
void print_sorted(
    int *arr, int arr_len, int compares, int moves, int print_len) {
  printf("%d elements, %d moves, %d compares\n", arr_len, moves, compares);
  for (int i = 0; i < print_len; i++) {
    if (i % 7 == 0 && i != 0) { // 7 columns of numbers
      printf("\n");
    }
    // Prints number in correct format
    printf("%13" PRIu32, arr[i]);
  }
  printf("\n");
  return;
}

// Resets workable array to its original state
void reset(int *workable, int *base, int length) {
  for (int i = 0; i < length; i++) {
    workable[i] = base[i];
  }
  return;
}
