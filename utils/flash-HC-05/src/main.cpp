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

int selectBluetoothModuleMode();

void setup() {

  Serial.begin(9600);          // Arduino UNO default serial speed 

  selectBluetoothModuleMode(); // Prompt user to select mode AT command mode or Data mode
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

int selectBluetoothModuleMode() {
  Serial.println("Select HC-05 Bluetooth Module Mode:");
  Serial.println("1: AT Command Mode, ensure KEY/EN pin is HIGH before powering the module.");
  Serial.println("2: Data Mode, ensure KEY/EN pin is LOW before powering the module.");

  while (true) {
    if (Serial.available()) {
      switch (Serial.readStringUntil('\n').toInt())
      {
      case 1:
        Serial.println("HC-05 set to AT Command Mode.");
        Bluetooth.begin(38400); // Default baud rate for AT command mode
        return 1;
      case 2:
        Serial.println("HC-05 set to Data Mode.");
        Bluetooth.begin(9600); // Default baud rate for Data mode
        return 2;
      default:
        Serial.println("Invalid choice. Please enter 1 or 2:");
        break;
      }
    }
  }
}