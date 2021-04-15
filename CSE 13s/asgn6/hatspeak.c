#include "hatspeak.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constructor for a HatterSpeak struct
//
// oldspeak:     Old word that may or may not be forbiden. Always present.
// hatterspeak:  Translated version of oldspeak. Might be null.
//
HatterSpeak *hs_create(char *oldspeak, char *hatterspeak) {
  HatterSpeak *g = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  if (g == NULL) { // Check that malloc worked
    printf("HatterSpeak failed to allocate\n");
    return NULL;
  }
  // Coppies input oldspeak to g->speak
  g->oldspeak = (char *)(malloc(strlen(oldspeak) + 1));
  if (g->oldspeak == NULL) { // Check that malloc worked
    printf("Malloc error in hs_create");
    free(g);
    return NULL;
  }
  // Copy input into recently malloced HatterSpeak->oldspeak
  strcpy(g->oldspeak, oldspeak);

  // Check if hatterspeak tanslation is available
  if (hatterspeak != NULL) {
    g->hatterspeak = (char *)(malloc(strlen(hatterspeak) + 1));
    if (g->hatterspeak == NULL) { // Make sure malloc worked
      printf("Malloc error in hs_create");
      free(g->oldspeak);
      free(g);
      return NULL;
    }
    // Copy input into recently malloced HatterSpeak->hatterspeak
    strcpy(g->hatterspeak, hatterspeak);
  } else { // If no translation is avaliable its NULL
    g->hatterspeak = NULL;
  }

  return g;
}

// Destructor for a HatterSpeak struct.
//
// g:   the Hatterspeak struct
//
void hs_delete(HatterSpeak *g) {
  if (g == NULL) { // Check that HatterSpeak isn't null
    printf("Hatterspeak is Null");
    return;
  }
  // Free everything in HatterSpeak struct
  free(g->oldspeak);
  // hatterspeak translation may be null so check before freeing
  if (g->hatterspeak != NULL) {
    free(g->hatterspeak);
  }
  return;
}
