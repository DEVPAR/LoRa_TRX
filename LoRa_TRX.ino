#include "BluetoothSerial.h"
#include <stdio.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


/*Frequency setup*/
// 433E6 for Asia
// 866E6 for Europe
// 915E6 for North America
// 433775000 for Ham Radio
#define BAND 433775000


/*Board setup for LoRa and OLED Pins, comment out the boards you dont use*/
//#define LORA32-V1
//#define LORA32-V2.1
  #define LORA32-T-BAEM

#ifdef LORA32-V1
//Board: LoRa32-V1
//LoRa and OLED Pins
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#endif


#ifdef LORA32-V2.1
//Board: LoRa32-V2.1
//LoRa and OLED Pins
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26
#define DIO1 33  // GPIO 33
#define DIO2 32  // GPIO 32
//OLED pins
#define OLED_SDA 21
#define OLED_SCL 22 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#endif


#ifdef LORA32-T-BEAM
//Board: LoRa32-T-Beam
//LoRa and OLED Pins
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
#define DIO1 33  // GPIO 33
#define DIO2 32  // GPIO 32
//OLED pins
#define OLED_SDA 21
#define OLED_SCL 22 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#endif


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

BluetoothSerial SerialBT;
String LoRaData;
String message;
//String LoRaData;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_LoRa_TRX"); //Bluetooth device name
  Serial.println("Started, pair it with bluetooth!");

  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
  
  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("LoRa_TRX by DM5LG");
  display.display();

  Serial.println("LoRa Receiver Test");
  
  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {         //433775000 or BAND
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0,10);
  display.setTextSize(1);
  display.println("Version 0.1 Beta");
  display.display(); 
  //LoRa settings
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(125000);
  LoRa.setCodingRate4(5);
  LoRa.enableCrc();
  LoRa.setTxPower(20);
  delay(2000);
  
  display.clearDisplay();
  display.setCursor(0,10);
  display.setTextSize(1);
  display.println("LORA RX");
  display.display(); 
}


void loop() {
 
  while (SerialBT.available()) {
    //Serial.write(SerialBT.read());
    char incomingChar = SerialBT.read();
    message += String(incomingChar);

    // sending a packet
    if (incomingChar == '\n'){

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("LORA TX");
  display.display();
  
  LoRa.beginPacket();
  //LoRa.write('<');
  //LoRa.write(0xFF);
  //LoRa.write(0x01);
  LoRa.print(message); 
  //LoRa.print(counter);
  LoRa.endPacket();
  
  display.clearDisplay();
  display.setCursor(0,10);
  display.println("LORA RX");
  display.display();
  }
  }


//try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    //received a packet
    Serial.print("Received packet ");

    //read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    //print RSSI of packet
    int rssi = LoRa.packetRssi();
    float snr = LoRa.packetSnr();
    Serial.print(" with RSSI ");    
    Serial.println(rssi);
   
   //send LoRaData and RSSI via SerialBT
 
    SerialBT.println(LoRaData + "RSSI:" + rssi + " dBm");
    
  
    
   // Dsiplay information
   display.clearDisplay();
   display.setCursor(0,0);
   display.print("Received packet:");
   display.setCursor(0,10);
   display.print("RSSI:");
   display.setCursor(30,10);
   display.print(rssi);
   display.setCursor(0,30);
   display.print(LoRaData);
   display.display();
    
  }
  message = "";
}
