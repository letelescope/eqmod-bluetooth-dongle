/*
 * main.cpp
 * Copyright (C) 2025 - Present, Le Télescope - Ivry sur Seine - All Rights Reserved
 * Licensed under the MIT License. See the accompanying LICENSE file for terms.
 *
 * Description: Arduino firmware to configure the HC-05 module.
 *
 * Authors:
 * - Florian Gautier
 *
 */
#include <Arduino.h>
#include <SoftwareSerial.h>

const byte RX_PIN = 10; // RX arduino pin, connected (via logic level converter) to TX pin of the HC-05 bluetooth module
const byte TX_PIN = 11; // TX arduino pin, connected (via logic level converter) to RX pin of the HC-05 bluetooth module

SoftwareSerial Bluetooth(RX_PIN, TX_PIN); // RX, TX

void setup() {

  Serial.begin(9600);        // Arduino UNO default serial speed 

  Serial.println("Choose Bluetooth HC-05 module mode:");
  Serial.println(" - 1: To enter AT command mode, ensure KEY/EN pin is HIGH before powering the module.");
  Serial.println(" - 2: To enter Data mode, ensure KEY/EN pin is LOW before powering the module.");

  int choice = 0;
  while (!(choice == 1 || choice == 2)){
    if (Serial.available()) {
      String response = Serial.readStringUntil('\n');
      response.trim();
      choice = response.toInt();
    }
  }
  if (choice == 1) {
    Serial.println("HC-05 module in AT command mode. Enter AT commands:");
    Bluetooth.begin(38400);    // HC-05 default speed in AT command mode
  } else {
    Serial.println("HC-05 set to Data mode.");
    Bluetooth.begin(9600);    // HC-05 default speed in Data mode
  }

}

void loop() {

  if (Bluetooth.available()) {
    String command = Bluetooth.readStringUntil('\n');
    command.trim(); // Remove any trailing newline or spaces
    Serial.println(command); // Forward data from Bluetooth to Serial Monitor
  }

  if (Serial.available()) {
    String response = Serial.readStringUntil('\n');
    response.trim(); // Remove any trailing newline or spaces
    Bluetooth.println(response); // Forward data from Serial Monitor to Bluetooth
  }
}
