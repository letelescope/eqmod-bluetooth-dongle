# Put HC-05 Bluetooth Module into AT Command Mode

This simple platformio project helps you put the HC-05 Bluetooth module into AT command mode. Once in AT command mode, you can configure various settings of the HC-05 module.


## Wiring

Connect the HC-05 module to your Arduino as follows:

- HC-05 VCC to Arduino 5V
- HC-05 GND to Arduino GND
- HC-05 TXD to Arduino RX (Pin 10). Optionally through logic level converter (to step up 3.3V to 5V)
- HC-05 RXD to Arduino TX (Pin 11) through logic level converter (to step down 5V to 3.3V)
- HC-05 KEY/EN to Arduino +3V3 to enter AT command mode

## Code

The following Arduino sketch sets up the HC-05 module in AT command mode and allows you to send AT commands via the Serial Monitor.

```cpp
#include <Arduino.h>
#include <SoftwareSerial.h>

const byte RX_PIN = 10; // RX arduino pin, connected (via logic level converter) to TX pin of the HC-05 bluetooth module
const byte TX_PIN = 11; // TX arduino pin, connected (via logic level converter) to RX pin of the HC-05 bluetooth module
const byte EN_PIN = 9;  // Directly connected to the enable pin of the HC-05 bluetooth module

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
```

This platformio project already includes the [main.cpp](./src/main.cpp) file as well as a [platformio.ini](./platformio.ini) file. Hence, you can directly upload it to your Arduino board and start palying with it.

## Usage

1. Upload the firmware to your Arduino board using platformio.
2. Open the Serial Monitor 
3. send AT commands to the HC-05 module. For example, you can type `AT` and press Enter. The module should respond with `OK`.

## Available AT Commands

Here are some common AT commands you can use with the HC-05 module:
- `AT`: Test command, should return `OK`
- `AT+VERSION?`: Query the firmware version of the module
- `AT+NAME?`: Query the current name of the module
- `AT+NAME=new_name`: Set a new name for the module
- `AT+PSWD?`: Query the current password
- `AT+PSWD=new_password`: Set a new password
- `AT+UART?`: Query the current baud rate
- `AT+UART=new_baud,0,0`: Set a new baud rate (e.g., `AT+UART=9600,0,0`)
- `AT+ROLE?`: Query the current role (master/slave)
- `AT+ROLE=0`: Set the module to slave mode
- `AT+ROLE=1`: Set the module to master mode
- `AT+ADDR?`: Query the MAC address of the module
- `AT+RESET`: Reset the module


## Notes

- Make sure the baud rate in the Serial Monitor is set to 9600.
- Ensure that the HC-05 module is powered correctly and the KEY/EN pin is set to HIGH before powering on the module to enter AT command mode.
- You may need to adjust the baud rate in the `Bluetooth.begin()` function if your HC-05 module is configured differently.
- Use a logic level converter to connect the RX and TX pins of the HC-05 module to the Arduino to avoid damaging the module.
- Refer to the HC-05 datasheet for a list of AT commands and their functions.
  
## License

This project is licensed under the MIT License - see the [LICENSE](../LICENSE) file for details.

## Bibliography

- [HC-05 Bluetooth Module Datasheet](https://components101.com/sites/default/files/component_datasheet/HC-05%20Datasheet.pdf
- PlatformIO Documentation: [https://platformio.org/](https://platformio.org/)
- Arduino SoftwareSerial Library: [https://www.arduino.cc/en/Reference/SoftwareSerial](https://docs.arduino.cc/learn/built-in-libraries/software-serial/)
- Chumbaka wiki entry: [Rename-the-HC05-Bluetooth-Module-Using-AT-Command](https://chumbaka.notion.site/HC05-Rename-the-HC05-Bluetooth-Module-Using-AT-Command-410d21d4d5864df1935bf5c9a5a42582)
- Hackster.io tutorial: [HC-05-bluetooth-module-with-arduino](https://www.hackster.io/Uniostar/hc-05-bluetooth-module-with-arduino-via-at-command-mode-b3595d)