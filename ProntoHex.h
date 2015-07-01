/*
  ProntoHex by Simon Peter
*/

#ifndef ProntoHex_h
#define ProntoHex_h

#include "Arduino.h"

class ProntoHex
{
  public:
    void convert(String hexcode);
    int frequency;
    int length;
    unsigned int hexToInt(const char *hex);
    String join(unsigned int strs[], int len);
    unsigned int convertedRaw[256];
};

#endif
