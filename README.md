# DIY EQMOD Bluetooth Dongle

This project demonstrates how to set a wireless Bluetooth connection for an EQMOD-compatible telescope mount using an HC-05 Bluetooth module. Optionally, the HC-05 module can be configured using AT command mode, allowing you to customize its settings such as name, password, and baud rate.

## Project Structure


```markdown
eqmod-bluetooth-dongle/
├── utils/
│   └── flash-HC-05/              # PlatformIO project to configure HC-05 via AT commands using an Arduino board
│       ├── src/
│       │   └── main.cpp          # Arduino firmware code for HC-05 configuration
│       ├── platformio.ini        # PlatformIO configuration file
│       └── README.md             # Usage of the HC-05 configuration utility
│ 
├── LICENSE                       # Project license
└── README.md                     # You are here!
```

For the time being, this project only includes the utility to configure the HC-05 module. The main EQMOD Bluetooth dongle firmware will be added in the future.

## Configuring HC-05 Module via AT Commands

For configuring the HC-05 module, you can use the provided PlatformIO project located in the [utils/flash-HC-05/](utils/flash-HC-05/) directory. This project allows you to send AT commands to the HC-05 module using an Arduino board as a bridge. Please see the [readme](utils/flash-HC-05/README.md) file in that directory for detailed instructions. 

But basically, to configure the HC-05 module, you can follow these steps:

1. Connect and wire the HC-05 module to your Arduino board
2. Upload the provided firmware to your Arduino board using PlatformIO.
3. Open the Serial Monitor and send AT commands to the HC-05 module.
4. The module will respond to the commands, allowing you to configure its settings.

## Bibliography

- HC-05 Bluetooth Module Datasheet: [https://components101.com/sites/default/files/component_datasheet/HC-05%20Datasheet.pdf)](https://components101.com/sites/default/files/component_datasheet/HC-05%20Datasheet.pdf)
- EQMod EQDirect-BT documentation: [https://eq-mod.sourceforge.net/eqdirectindex.html](https://eq-mod.sourceforge.net/eqdirectindex.html)

