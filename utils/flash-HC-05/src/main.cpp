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
const byte EN_PIN = 9;  // Directly connected to the enable pin of the HC-05 bluetooth module

SoftwareSerial Bluetooth(RX_PIN, TX_PIN); // RX, TX

void setup() {

  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH); // Enable the HC-05 module

  Serial.begin(9600);        // Arduino UNO default serial speed 
  Bluetooth.begin(38400);    // HC-05 default speed in AT command mode
  
  Serial.println("HC-05 module in AT command mode. Enter AT commands:");
}

void loop() {

  if (Bluetooth.available()) {
    char c = Bluetooth.read();
    Serial.write(c); // Forward data from Bluetooth to Serial Monitor
  }

  if (Serial.available()) {
    char c = Serial.read();
    Bluetooth.write(c); // Forward data from Serial Monitor to Bluetooth
  }
}
