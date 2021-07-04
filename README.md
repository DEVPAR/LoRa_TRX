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
- Before flashing the firmware set the right frequency config in line 23 and the right borad config in line 26 - 29.
  - Currently supported boads: TTGO T-Beam V1, TTGO LoRa32 V1, TTGO LoRa32 V2.1 
- After installing the libraries copy and paste the LoRa_TRX.ino file into your Adurino IDE


## Usage

