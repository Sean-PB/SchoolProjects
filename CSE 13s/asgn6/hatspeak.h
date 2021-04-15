#ifndef __HATSPEAK_H__
#define __HATSPEAK_H__

// Struct definition for a Hatterspeak.
//
// oldspeak:     Old word that may or may not be forbiden. Always present.
// hatterspeak:  Translated version of oldspeak. Might be NULL
typedef struct HatterSpeak {
  char *oldspeak;
  char *hatterspeak;
} HatterSpeak;

// Constructor for a Hatterspeak struct
//
// oldspeak:     Old word that may or may not be forbiden. Always present.
// hatterspeak:  Translated version of oldspeak. Might be null.
//
HatterSpeak *hs_create(char *oldspeak, char *hatterspeak);

// Destructor for a Hatterspeak struct.
//
// g:   the Hatterspeak struct
//
void hs_delete(HatterSpeak *g);

#endif
