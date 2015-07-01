/*
  ProntoHex by Simon Peter

  Convert Pronto Hex infrared remote control codes to raw timings that can be sent with usual IR sending libraries
*/

#include "ProntoHex.h"

void setup() {
  ProntoHex ph = ProntoHex();

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // A string containing Pronto Hex. In reality, this would most likely not be hardcoded in the sketch but received at runtime via Serial, Ethernet, or WiFi
  String pronto = F("0000 006C 0022 0002 015B 00AD 0016 0016 0016 0016 0016 0041 0016 0041 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0041 0016 0016 0016 0016 0016 0016 0016 0041 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0041 0016 0041 0016 0041 0016 0016 0016 0016 0016 0041 0016 0041 0016 0041 0016 0016 0016 0016 0016 0016 0016 0041 0016 0041 0016 06A4 015B 0057 0016 0E6C");
  Serial.println("Pronto Hex:");
  Serial.println(pronto);
  Serial.println("");

  // Convert the Pronto Hex string to raw timings.
  String converted = ph.convert(pronto);
  Serial.println("Converted to raw timings:");
  Serial.println(converted);
  Serial.println("");

  // FIXME:
  // In reality, this would most likely not be printed but sent with an infrared remote control sending library.
  // For that it would be better if we could access convertedRaw (an array of ints for the timings) rather than the String above.
  // But C++ makes it really hard to return an array of variable length from a method, something that is trivial in Python.
  // It insists on pointers, which I still don't like. Feel free to help.
  unsigned int *array = ph.raw;
  Serial.println("Int of the first timing (does not work; FIXME):");
  Serial.println((int)&array); // Does not work
  Serial.println("");

  Serial.println("Frequency:");
  Serial.println(ph.frequency); // Works
}

void loop() {
}
