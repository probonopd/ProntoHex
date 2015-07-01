/*
  ProntoHex by Simon Peter
*/

#ifndef ProntoHex_h
#define ProntoHex_h

#include "Arduino.h"

class ProntoHex
{
  public:
    String convert(String hexcode);
    int frequency;
    unsigned int hexToInt(const char *hex);
    String join(unsigned int strs[], int len);
    unsigned int *raw; // Should be a "pointer to an array" - "you can return a pointer to an array by specifying the array's name without an index."
};

#endif
