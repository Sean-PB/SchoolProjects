#include "bf.h"
#include "speck.h"
#include <stdlib.h>

// Constructor for a BloomFilter
//
// size: The number of entries in the BloomFilter.
//
BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) { // If malloc was sucessful
    // Set salt values (numbers given in lab pdf)
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    // bf->filter is the actual bloom filter (bitvector)
    bf->filter = bv_create(size);
    return bf;
  } // If malloc failed return NIL
  return (BloomFilter *)NIL;
}

// Destructor for a BloomFilter.
//
// bf:   The BloomFilter.
//
void bf_delete(BloomFilter *bf) {
  if (bf == NULL) { // Check that BloomFilter isn't null
    return;
  }
  // Free everything in BloomFilter including BitVector
  bv_delete(bf->filter);
  free(bf);
  return;
}

// Inserts a new key into the BloomFilter.
// Indices to set bits are given by the hash functions.
//
// bf:    The BloomFilter.
// key:   The key to insert into the BloomFilter.
//
void bf_insert(BloomFilter *bf, char *key) {
  if (bf == NULL) { // Check that BloomFilter isn't NULL
    return;
  }
  // Set 3 disticnt bits for every one key in BloomFilter
  //  to reduce number of collisions.
  //  The point of salts is to make the hash give a different index
  //  value for each.
  //  Make sure to modulo hash by bit vector length to avoid setting beyond
  //  bit vector bounds
  bv_set_bit(bf->filter, (hash(bf->primary, key) % bv_get_len(bf->filter)));
  bv_set_bit(bf->filter, (hash(bf->secondary, key) % bv_get_len(bf->filter)));
  bv_set_bit(bf->filter, (hash(bf->tertiary, key) % bv_get_len(bf->filter)));
  return;
}

// Probes a BloomFilter to check if a key has been inserted.
//
// bf:    The BloomFilter.
// key:   The key in whcih to check membership.
//
bool bf_probe(BloomFilter *bf, char *key) {
  if (bf == NULL) { // Check that bloom filter isn't null
    return NULL;
  }
  // Check all three indexes the key would be set at
  bool x = bv_get_bit(
      bf->filter, (hash(bf->primary, key) % bv_get_len(bf->filter)));
  bool y = bv_get_bit(
      bf->filter, (hash(bf->secondary, key) % bv_get_len(bf->filter)));
  bool z = bv_get_bit(
      bf->filter, (hash(bf->tertiary, key) % bv_get_len(bf->filter)));
  // If ALL three are true, then it may be true (flase positives still possible)
  // but if any are false then it DEFINITLEY is false.
  if (x && y && z) {
    return true;
  } else {
    return false;
  }
}

// My function, is not in the lab pdf
// Counts the number of set bits in bloom filter
//
// bf:   Bloom filter
//
int bf_set_count(BloomFilter *bf) {
  int count = 0;
  // For every bit in BitVector
  for (uint32_t i = 0; i < bv_get_len(bf->filter); i++) {
    // If that bit is true (AKA 1)
    if (bv_get_bit(bf->filter, i)) {
      // Increment count
      count++;
    }
  }
  return count;
}
