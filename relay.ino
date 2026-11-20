#include <ESP8266WiFi.h>
#include <KiwisIoT.h>

// WiFi credentials
const char* ssid = "YOUR WIFI NAME";
const char* pass = "YOUR PASSWORD";

// KiwisIoT Topic ID
const char* topic = "DASHBOARD TOPIC ID";

// Relay pin
#define MOTOR_RELAY D1

// KiwisIoT object
KiwisIoT kiwisiot(ssid, pass, topic);

// Motor control function
void onControl(String ch, String val) {

  Serial.print("Channel: ");
  Serial.println(ch);

  Serial.print("Received: ");
  Serial.println(val);

  // Motor control channel
  if (ch == "1") {

    // Turn motor ON
    if (val == "1" || val == "turn on motor") {

      digitalWrite(MOTOR_RELAY, LOW);
      Serial.println("MOTOR ON");
    }

    // Turn motor OFF
    else if (val == "0" || val == "turn off motor") {

      digitalWrite(MOTOR_RELAY, HIGH);
      Serial.println("MOTOR OFF");
    }
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(MOTOR_RELAY, OUTPUT);

  // Motor OFF initially
  digitalWrite(MOTOR_RELAY, HIGH);

  // Start KiwisIoT
  kiwisiot.begin();

  // Receive commands
  kiwisiot.onReceive(onControl);

  Serial.println("IoT Water Pump Control Started");
}

void loop() {

  kiwisiot.run();
}
