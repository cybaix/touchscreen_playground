#include <Arduino.h>
#include <SPI.h>
//#include <MFRC522.h>
#include <TFT_eSPI.h> 
#include <TJpg_Decoder.h>
#include <hacktar.hpp>
#include <Wire.h>
#include "RAK14014_FT6336U.h"

//#define RST_PIN         44          // Configurable, see typical pin layout above
//#define SS_PIN          37         // Configurable, see typical pin layout above

//MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

#define INT_PIN GPIO_NUM_9

FT6336U ft6336u; 
TFT_eSPI tft = TFT_eSPI();
static uint8_t intSattus = false; // TP interrupt generation flag.

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
   // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  tft.pushImage(x, y, w, h, bitmap);

  return 1;
}

void tpIntHandle(void)
{
  intSattus = true;
}

void setup() {
	Serial.begin(115200);
	//SPI.begin();
	//mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	//mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
	pinMode(GPIO_NUM_10, OUTPUT);
	digitalWrite(GPIO_NUM_10, HIGH);
	digitalWrite(GPIO_NUM_10, LOW);

	//TwoWire wire = TwoWire(0);
	//wire.begin(GPIO_NUM_37, GPIO_NUM_36);

	/*
	while(ft6336u.begin() == false) 
  	{
		Serial.println("ft6336u is not connected.");
		delay(1000);
  	}
	pinMode(INT_PIN, INPUT_PULLUP);
  	attachInterrupt(digitalPinToInterrupt(INT_PIN), tpIntHandle, FALLING);

	Serial.print("FT6336U Firmware Version: "); 
  	Serial.println(ft6336u.read_firmware_id());  
  	Serial.print("FT6336U Device Mode: "); 
  	Serial.println(ft6336u.read_device_mode());  */

	tft.init();
    //tft.initDMA();
    tft.setSwapBytes(true);
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);


    TJpgDec.setJpgScale(1);
    TJpgDec.setCallback(tft_output);

	tft.startWrite();
    TJpgDec.drawJpg(0, 0, BIG_HACKTAR, sizeof(BIG_HACKTAR));
    tft.endWrite();
}

void loop() {
	/*
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
	*/

	/*
	if(intSattus)
	{
		intSattus = false;
		Serial.print("FT6336U TD Status: "); 
		Serial.println(ft6336u.read_td_status());  
		Serial.print("FT6336U Touch Event/ID 1: ("); 
		Serial.print(ft6336u.read_touch1_event()); 
		Serial.print(" / "); 
		Serial.print(ft6336u.read_touch1_id()); 
		Serial.println(")"); 
		Serial.print("FT6336U Touch Position 1: ("); 
		Serial.print(ft6336u.read_touch1_x()); 
		Serial.print(" , "); 
		Serial.print(ft6336u.read_touch1_y()); 
		Serial.println(")"); 
		Serial.print("FT6336U Touch Weight/MISC 1: ("); 
		Serial.print(ft6336u.read_touch1_weight()); 
		Serial.print(" / "); 
		Serial.print(ft6336u.read_touch1_misc()); 
		Serial.println(")"); 
		Serial.print("FT6336U Touch Event/ID 2: ("); 
		Serial.print(ft6336u.read_touch2_event()); 
		Serial.print(" / "); 
		Serial.print(ft6336u.read_touch2_id()); 
		Serial.println(")"); 
		Serial.print("FT6336U Touch Position 2: ("); 
		Serial.print(ft6336u.read_touch2_x()); 
		Serial.print(" , "); 
		Serial.print(ft6336u.read_touch2_y()); 
		Serial.println(")"); 
		Serial.print("FT6336U Touch Weight/MISC 2: ("); 
		Serial.print(ft6336u.read_touch2_weight()); 
		Serial.print(" / "); 
		Serial.print(ft6336u.read_touch2_misc()); 
		Serial.println(")"); 
	}*/
	delay(200);
}