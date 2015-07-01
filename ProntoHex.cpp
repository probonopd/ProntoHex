/*
  ProntoHex by Simon Peter

  Based on information from
  http://stackoverflow.com/questions/25771333/ir-hex-to-raw-ir-code-conversion
  and https://www.remotecentral.com/features/irdisp2.htm

*/

#include "Arduino.h"
#include "ProntoHex.h"

int frequency;
int length;
unsigned int convertedRaw[256];

void ProntoHex::convert(String prontoDataStr)
{
  int i = 0;
  uint16_t array[128];
  uint16_t j = 0;

  while (  i < strlen(prontoDataStr.c_str()) ) // .c_str() makes a char[] out of an Arduino String
  {
    char hexchararray[5]; // Length is 5 because 5th is null termination, one reason why I dislike C
    strncpy(hexchararray, prontoDataStr.c_str() + i, 4);
    hexchararray[4] = '\0'; // Null terminate

    // string, String, char* and char[] - four ways to do essentially the same. Very confusing, one reason why I prefer Python over C
    // Need to convert "char array" to "char *"
    // "A char[] can be cast to a const char *, but not vice versa." http://stackoverflow.com/questions/14785442/typcasting-a-character-array-to-a-const-char
    char *charstar = &hexchararray[0];  // get the address of (=pointer to) the start of the array
    unsigned int hexNumber = this->hexToInt(charstar);
    array[j] = hexNumber;
    j++;
    i = i + 5; // TODO: Better would be to find the position of the next blank and use that
  }

  float carrierFrequency = 1000000 / (array[1] * 0.241246);

  int codeLength = array[2];
  if (codeLength == 0) codeLength = array[3]; // If Sequence #1 is missing (array[2]=0000), then Burst Sequence #2 starts at array[4]

  int repeatCodeLength = array[3];
  length = codeLength*2;

  // TODO: Handle repeat sequences
  // sequence1EndPoint = 2 * codeLength
  // sequence2EndPoint = sequence1EndPoint + 2 * repeatCodeLength
  // firstSequence = fullSequenceConverted from index 0 to sequence1EndPoint
  // secondSequence = fullSequenceConverted from sequence1EndPoint to sequence2EndPoint

  int index = 0;
  
  for (int i = 4; i < j; i++ )
  {
    int convertedToMicrosec = (1000000 * (array[i] / carrierFrequency) + 0.5);
    convertedRaw[index++] = convertedToMicrosec;
  }

  frequency = (int)(carrierFrequency / 1000);

}

// http://stackoverflow.com/questions/4951714/c-code-to-convert-hex-to-int
// Something like that should come with the Arduino libraries
// strtol is too complicated and did not work for me
unsigned int ProntoHex::hexToInt(const char *hex)
{
  unsigned int result = 0;
  while (*hex)
  {
    if (*hex > 47 && *hex < 58)
      result += (*hex - 48);
    else if (*hex > 64 && *hex < 71)
      result += (*hex - 55);
    else if (*hex > 96 && *hex < 103)
      result += (*hex - 87);
    if (*++hex)
      result <<= 4;
  }
  return result;
}

// Take an array of ints and return a string, containing + and - prefixes for displaying raw timings
String ProntoHex::join(unsigned int strs[], int len) {
  String result = "";
  String prefix = "";
  for (int i = 0; i < len; i++) {
    if (i % 2 == 0) // Check if number is even or uneven
    {
      prefix = "+";
    }
    else
    {
      prefix = "-";
    }
    result += prefix + String(strs[i]) + " ";
  }
  return result.substring(0, result.length() - 1);
}
