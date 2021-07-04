# LoRa_TRX

## Its a proof of concept to realize half-duplex comunication on ESP32 LoRa Boards.


## Installation

**Using Arduino IDE:**
- Install ESP32 Boards on Arduino IDE 
  - [Install instructions for the ESP32 Board](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
- Install OLED Libraries
  - Sketch -> Include Library -> Manage Libraries
  - Search for "SSD1306" from Adafruit in Library Manager -> Install
  - Search for "GFX Library" from Adafruit in Library Manager -> Install
- Install LoRa Library for Semtech SX1276/77/78/79
  - Sketch -> Include Library -> Manage Libraries
  - Search for "LoRa" (LoRa by Sandeep Mistry) -> Install
- After installing the libraries copy and paste the LoRa_TRX.ino file into your Adurino IDE
- Before flashing the firmware set the right frequency config in line 23 and the right borad config in line 26 - 29.
  - Currently supported boads: TTGO T-Beam V1, TTGO LoRa32 V1, TTGO LoRa32 V2.1 
- Compile it and upload to the board


## Usage

- Sending and receiving messages is done via  serial communication over Bluetooth. 
- Pair your Smartphone with the ESP32 LoRa-Board.
- Download The [Serial Bluetooth Terminal APP](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en) APP and chose your previously paired device for serial communication.
- Once you are connected you can start sending and receiving messages over LoRa direct on your cellphone.


## Screenshots


![TRX](https://github.com/DEVPAR/LoRa_TRX/blob/main/photo_2021-07-04_21-34-18.jpg)


![TRX](https://github.com/DEVPAR/LoRa_TRX/blob/main/photo_2021-07-04_21-34-25.jpg)


![TRX](https://github.com/DEVPAR/LoRa_TRX/blob/main/photo_2021-07-04_21-34-29.jpg)


![TRX](https://github.com/DEVPAR/LoRa_TRX/blob/main/photo_2021-07-04_21-34-33.jpg)


