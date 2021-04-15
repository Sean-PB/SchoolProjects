#include <stdint.h> // for enum stuff
#include <stdio.h> // input output library (scanf and printf)
#include <stdlib.h> // for the random number generator

// Prototypes
uint32_t left(uint32_t pos, uint32_t players);
uint32_t right(uint32_t pos, uint32_t players);

// Main
int main(void) {
  // Die
  typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
  faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };
  // Names
  const char *names[] = { "Happy", "Sleepy", "Sneezy", "Dopey", "Bashful",
    "Grumpy", "Doc", "Mirror Mirror", "Snow White", "Wicked Queen" };
  // Input variables
  int num_of_players = 0;
  int seed;

  // Other variables
  int players_out; // Counts how many players have $0
  int num_of_rolls; // Number of rolls for a players turn
  int pot = 0; // Tracks $ in pot
  uint32_t pos = 0; // tracks whose turn it is
  int playing = 1; // Boolean tracks if game is still going

  // ask for random seed
  printf("Random seed: ");
  scanf("%d", &seed);

  // Ask for how many players
  printf("How many players? ");
  scanf("%d", &num_of_players);

  // num_of_players check
  if (num_of_players < 2 || num_of_players > 10) {
    printf("Input error.\nPlease try again\n");
    return 0;
  }

  // Make bank array and deposit 3 dollars into each account
  int bank[num_of_players];
  for (int i = 0; i < num_of_players; i++) {
    bank[i] = 3;
  }

  // set rand seed
  srand(seed);

  // Loop unil game over break
  while (playing) {
    // While player whose turn it is has no money, move right
    while (bank[pos] < 1) {
      pos = right(pos, num_of_players);
    }

    // Print who's rolling
    printf("%s rolls...", names[pos]);

    // For however much money a player has, roll the dice that many times
    num_of_rolls = bank[pos];
    if (num_of_rolls > 3) {
      num_of_rolls = 3; // Limits number of rolls to 3
    }
    for (int i = 0; i < num_of_rolls; i++) {
      // Roll the die
      faces roll = die[rand() % 6];

      // Use a switch to decide what action to take depending on dice roll
      switch (roll) {
      case 0:
        printf(" gives $1 to %s", names[left(pos, num_of_players)]);
        bank[pos] -= 1;
        bank[left(pos, num_of_players)] += 1;
        break;
      case 1:
        printf(" gives $1 to %s", names[right(pos, num_of_players)]);
        bank[pos] -= 1;
        bank[right(pos, num_of_players)] += 1;
        break;
      case 2:
        printf(" puts $1 in the pot");
        bank[pos] -= 1;
        pot += 1;
        break;
      case 3:
        printf(" gets a pass");
        break;
      default:
        printf("error\n");
        break;
      }
      // If players last roll, print new line for next players line of rolls
      if (i == (num_of_rolls - 1)) {
        printf("\n");
      }
    }

    // Move pos right a player for next turn
    pos = right(pos, num_of_players);

    /* check all players to see if game is over 
     * if it is over, then end the game and also break the loop*/
    players_out = 0;
    for (int i = 0; i < num_of_players; i++) {
      if (bank[i] < 1) {
        players_out++;
      }
      if (players_out == (num_of_players - 1)) {
        playing = 0;
      }
    }
  }

  // Print winner info
  const char *winner;
  int money;
  for (int i = 0; i < num_of_players; i++) {
    if (bank[i] > 0) {
      winner = names[i];
      money = bank[i];
    }
  }
  printf(
      "%s wins the $%d pot with $%d left in the bank!\n", winner, pot, money);
  return 0;
}

uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
}

uint32_t right(uint32_t pos, uint32_t players) {
  return ((pos + 1) % players);
}
