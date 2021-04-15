#include "bv.h"
#include <stdio.h>
#include <stdlib.h>

// Creates a new BitVector of specified length
BitVector *bv_create(uint32_t bit_len) { /////////////////////
  BitVector *new_bv = (BitVector *)malloc(sizeof(BitVector));
  if (new_bv == NULL) {
    printf("Error in bv_create\n");
    return 0;
  } else {
    uint8_t *vector = (uint8_t *)calloc(((bit_len / 8) + 1), sizeof(uint8_t));
    new_bv->vector = vector;
    new_bv->length = bit_len;
    return new_bv;
  }
}

// Frees memory allocated for a BitVector
void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
  return;
}

// Returns the length in bits of the BitVector
uint32_t bv_get_len(BitVector *v) {
  if (v == NULL) {
    printf("Error finding length\n");
    return -1;
  }
  return v->length;
}

// Sets the bit at index i in the BitVector
void bv_set_bit(BitVector *v, uint32_t i) {
  v->vector[i / 8] |= (1 << (i % 8));
  return;
}

// Clears the bit at index i in the BitVector to 0
void bv_clr_bit(BitVector *v, uint32_t i) {
  if (v == NULL) {
    printf("Error clearing bit\n");
    return;
  }
  v->vector[i / 8] &= (~(1 << (i % 8)));
  return;
}

// Gets a bit from a BitVector
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  if (v == NULL) {
    printf("Error getting bit\n");
    return -1;
  }
  return (v->vector[i / 8] & (1 << (i % 8))) >> (i % 8);
}

// Sets all bits in a BitVector to 1
void bv_set_all_bits(BitVector *v) {
  if (v == NULL) {
    printf("Error setting all bits\n");
    return;
  }
  for (uint8_t i = 0; i < ((v->length / 8) + 1); i++) {
    v->vector[i] |= 0xff;
  }
  return;
}
