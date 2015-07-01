/*
  ProntoHex by Simon Peter

  Convert Pronto Hex infrared remote control codes to raw timings that can be sent with usual IR sending libraries
*/

#include "ProntoHex.h"

void setup()
{
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

  // Convert the Pronto Hex string to raw timings. In reality, we would not just print these but send them using an infrared sending library
  ph.convert(pronto);
  String converted = ph.join(ph.convertedRaw, ph.length);
  Serial.println("Converted to raw timings:");
  Serial.println(converted);
  Serial.println("");

  Serial.println("Contents of the convertedRaw array:");
  for (int i = 0; i < ph.length; i++)
  {
    Serial.print(ph.convertedRaw[i]);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.println("");
  
  Serial.println("Frequency:");
  Serial.println(ph.frequency); // Works
}

void loop() {
}
