#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "spn:"

void fib(int i);
void luc(int i);
void mer(int i);
void palindrome(BitVector *bv, int base);
bool is_palindrome(char *str);
char *base_change(uint32_t num, int base);

// Global variables to track the fib, lucas, and mersenne numbers
int current_f = 1, last_f = 0, current_l = 1, last_l = 2, last_m = 2;

int main(int argc, char **argv) {
  char choice;
  int end_num = 1000;
  bool special = false;
  bool pal = false;
  // Getopt loop
  while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
    switch (choice) {
    case 's':
      special = true;
      break;
    case 'p':
      pal = true;
      break;
    case 'n':
      end_num = atoi(optarg);
      break;
    default:
      printf("Only these arguments are allowed:\n-s : Special Primes\n"
             "-p : Palindromic Primes\n"
             "-n : (Optional) Specifies the largest value to consider."
             " Requires a number after.\n");
      return 0;
    }
  }

  // If the user put -s find the special primes
  if (special) {
    // Create and sieve bitvector
    BitVector *bv = bv_create(end_num);
    sieve(bv);
    // For i in bv
    for (uint32_t i = 0; i < bv_get_len(bv); i++) {
      if (bv_get_bit(bv, i)) { // if number is prime
        printf("%d: prime",
            i); // prints the current number WITHOUT a newline... yet
        mer(i); // prints mersenne if number is a mersenne prime
        luc(i); // prints lucas if number is a lucas prime
        fib(i); // prints fibonacci if number is a fibonacci prime
        printf(
            "\n"); // newline once all specials have been checked for given number
      }
    }
    bv_delete(bv); // free memory
  }
  // If the user put -p find the palindromic primes
  if (pal) {
    // Create and sieve bitvector
    BitVector *bv = bv_create(end_num);
    sieve(bv);
    // Check if the number is a palindrome in each required base
    palindrome(bv, 2);
    printf("\n");
    palindrome(bv, 9);
    printf("\n");
    palindrome(bv, 10);
    printf("\n");
    palindrome(bv, 12);
    bv_delete(bv); // Free memory
  }
  return 0;
}

// Function prints fiboacci if number is in the fibonacci sequence
void fib(int prime) {
  // Continue fib sequence until we reach our prime
  while (current_f < prime) {
    int temp = current_f;
    current_f += last_f;
    last_f = temp;
  }
  // If the fibonacci number were at == the given prime, print fibonacci
  if (current_f == prime) {
    printf(", fibonacci");
    return;
  } else { // Otherwise just return
    return;
  }
}

// Function prints lucas if the number is in the lucas sequence
void luc(int prime) {
  // Continue lucas sequence until we reach our prime
  while (current_l < prime) {
    int temp = current_l;
    current_l += last_l;
    last_l = temp;
  }
  /// If the lucas number were at == the given prime, print lucas
  if (current_l == prime) {
    printf(", lucas");
    return;
  } else { // Otherwise just return
    return;
  }
}

// Function prints mersenne if the number is in the mersenne sequence
void mer(int prime) {
  // Continue mersenne sequence until we reach our prime
  while (last_m < prime + 1) {
    last_m *= 2;
  }
  // If the mersenne number were at == the given prime, print mersenne
  if (last_m == (prime + 1)) {
    printf(", mersenne");
    return;
  } else { // Otherwise just return
    return;
  }
}

// Function prints all the numbers in a given base and range that are palindromic primes
void palindrome(BitVector *bv, int base) {
  char *str;
  printf("Base %2d\n---- --\n", base); // Header that shows the base
  for (uint32_t i = 0; i < bv_get_len(bv); i++) { // for i in bv
    if (bv_get_bit(bv, i)) { // if i is prime
      str = base_change(i,
          base); // Takes current number i and converts it to the given base and a string
      if (is_palindrome(
              str)) { // Checks if the string is a palindrom, if it is then print it
        printf("%d = %s\n", i, str);
      }
    }
  }
  return;
}

// Function takes a number and converts it to a given base and into a string
char *base_change(uint32_t num, int base) {
  char str1[32] = "";
  char str2[32] = "";
  char letter;
  uint32_t remain;
  char *temp;
  // Loop unitl the quotient is 0
  do {
    remain = num % base; // Find the next least significat digit
    num = num / base; // Find the quotient
    // If the next least significant digit should be a letter, make it a letter
    // and add the previous least significant digits to the end of it
    if (remain > 9) {
      letter = (char)(87 + remain);
      strcat(&letter, str2);
      strcpy(str2, &letter);
    } else { // If the next least significant digit should be a number, make it a string and add the previous least significant digits to the end of it
      sprintf(str1, "%d", remain);
      strcat(str1, str2);
      strcpy(str2, str1);
    }
  } while (num != 0);
  // Return the finished converted string of the number
  return strcat(str2, "");
}

// Function checks if a given string is a palindrome
bool is_palindrome(char *str) {
  int length;
  for (length = 0; str[length] != '\0'; ++length)
    ; // Length of string
  length -= 1;
  // For the first half of the string...
  for (int i = 0; i <= (length / 2); i++) {
    // Check if the current char is the same on the opposite side, if not return false
    if (str[i] != str[length - i]) {
      return false;
    }
  }
  // If the str makes it through the for loop without returning false then its a palindrom so return true
  return true;
}
