/**
 * Send IR codes sent as Pronto Hex commands in a HTTP POST request or CORS http://enable-cors.org/server.html
 * This sketch is for the ESP8266 platform
 **/
 
#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <ProntoHex.h>

#include "/secrets.h" // Delete this line and populate the following
//const char* ssid = "********";
//const char* password = "********";

IRsend irsend(2);
ProntoHex ph = ProntoHex();

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  irsend.begin();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) return;

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) delay(1);

  String line;
  // Read the first line of the request
  bool found = false;
  while (client.available()) {
    line = client.readStringUntil('\r');
    if (found == true)
      break;
    if (line == "")
      found = true;
  }
  line.trim(); // Remove extraneous whitespace; this is important
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Type: text/javascript\r\n\r\n";

  if (line.startsWith("0000 ")) // Then we assume it is Pronto Hex
  {
    ph.convert(line);
    irsend.sendRaw(ph.convertedRaw, ph.length, ph.frequency);
    s += ph.join(ph.convertedRaw, ph.length);
  }
  client.print(s);
  delay(1);
}
