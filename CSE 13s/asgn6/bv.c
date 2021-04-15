#include "bv.h"
#include <stdio.h>
#include <stdlib.h>

// Creates a new BitVector of specified length
//
// bit_len:   The length of biits of the BitVector
//
BitVector *bv_create(uint32_t bit_len) {
  BitVector *new_bv = (BitVector *)malloc(sizeof(BitVector));
  if (new_bv == NULL) { // Check that malloc didn't fail
    return 0;
  } else {
    // Vector is the actual BitVector so calloc to ensure it starts all 0
    uint8_t *vector = (uint8_t *)calloc(((bit_len / 8) + 1), sizeof(uint8_t));
    if (vector == NULL) { // Check that calloc didn't fail
      free(new_bv);
      return 0;
    }
    // Assign BitVector strcut values
    new_bv->vector = vector;
    new_bv->length = bit_len;
    return new_bv;
  }
}

// Frees memory allocated for a BitVector
//
// v:   The BitVector
//
void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
  return;
}

// Returns the length in bits of the BitVector
//
// v:   The BitVector
//
uint32_t bv_get_len(BitVector *v) {
  if (v == NULL) {
    printf("Error finding length\n");
    return -1;
  }
  return v->length;
}

// Sets the bit at index i in the BitVector
//
// v:   The BitVector.
// i:   Index of the bit to set.
//
void bv_set_bit(BitVector *v, uint32_t i) {
  if (v == NULL) { // Check that the BitVector exists
    printf("Error setting bit\n");
    return;
  }
  // Use a bit mask on a byte to set ONLY the specified bit
  // [i / 8] finds the correct byte
  // (i % 8) finds the correct bit in a byte
  // 1 << (i % 8) makes the mask by shifting 1 to the correcct bit
  // |= sets that bit in the byte with the mask.
  v->vector[i / 8] |= (1 << (i % 8));
  return;
}

// Clears the bit at index i in the BitVector to 0
//
// v:   The BitVector.
// i:   Index of the bit to set.
//
void bv_clr_bit(BitVector *v, uint32_t i) {
  if (v == NULL) { // Check that the BitVecor exists
    printf("Error clearing bit\n");
    return;
  }
  // Use a bit mask on a byte to set ONLY the specified bit
  // [i / 8] finds the correct byte
  // (i % 8) finds the correct bit in a byte
  // (~(1 << (i % 8))) makes the mask by shifting 0 to the correcct bit
  // |= clears that bit in the byte with the mask.
  v->vector[i / 8] &= (~(1 << (i % 8)));
  return;
}

// Gets a bit from a BitVector
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  if (v == NULL) { // Check that BitVector exists
    printf("Error getting bit\n");
    return -1;
  }
  // Use a bit mask on a byte to set ONLY the specified bit
  // [i / 8] finds the correct byte
  // (i % 8) finds the correct bit in a byte
  // 1 << (i % 8) makes the mask by shifting 1 to the correcct bit
  // & returns that bit in the byte with the mask.
  return (v->vector[i / 8] & (1 << (i % 8))) >> (i % 8);
}

// Sets all bits in a BitVector to 1
void bv_set_all_bits(BitVector *v) {
  if (v == NULL) { // Check that BitVector exists
    printf("Error setting all bits\n");
    return;
  }
  // For every byte in the BitVector
  for (uint8_t i = 0; i < ((v->length / 8) + 1); i++) {
    // Set all bits in byte to 1
    v->vector[i] |= 0xff;
  }
  return;
}
