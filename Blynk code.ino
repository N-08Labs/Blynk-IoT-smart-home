#define BLYNK_TEMPLATE_ID "TMPwq4g5weyr6svs"
#define BLYNK_TEMPLATE_NAME "Smart home"
#define BLYNK_AUTH_TOKEN "Jk5uWu9basdfbawetr8tgryqy"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

// WiFi credentials
char ssid[] = "N-08 Labs";
char pass[] = "n08labs";

// GPIO pins for relays
const int relay1Pin = 5; // Relay 1 connected to GPIO 5
const int relay2Pin = 4; // Relay 2 connected to GPIO 4
const int wifiStatusLedPin = 14;

// Variables for WiFi LED blinking
bool wifiConnected = false;
unsigned long previousMillis = 0;
const long interval = 350;  // LED blink interval in milliseconds

void setup() {
  // Set up GPIO pins for relays
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  digitalWrite(relay1Pin, LOW); // Relays off initially
  digitalWrite(relay2Pin, LOW);

  pinMode(wifiStatusLedPin, OUTPUT);
  digitalWrite(wifiStatusLedPin, LOW); // LED off initially

  // Begin Blynk and WiFi connection
  Blynk.begin(auth, ssid, pass);
}
void loop() {
  Blynk.run();

  // WiFi LED blinking when connected to WiFi
  if (Blynk.connected()) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      wifiConnected = !wifiConnected;
      digitalWrite(wifiStatusLedPin, wifiConnected ? HIGH : LOW);
    }
  } else {
    digitalWrite(wifiStatusLedPin, LOW);  // LED off when not connected
  }
}

// Blynk function to control Relay 1 through virtual pin V1
BLYNK_WRITE(V1) {
  int relay1State = param.asInt();
  digitalWrite(relay1Pin, relay1State ? HIGH : LOW); // HIGH to turn on relay
}

// Blynk function to control Relay 2 through virtual pin V2
BLYNK_WRITE(V2) {
  int relay2State = param.asInt();
  digitalWrite(relay2Pin, relay2State ? HIGH : LOW); // HIGH to turn on relay
}

