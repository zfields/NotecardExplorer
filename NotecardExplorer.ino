#include <Notecard.h>

#include "OLED_FeatherWing.hpp"

#define SERIAL_TIMEOUT_MS 2500

Notecard notecard;

  /**********/
 /* SKETCH */
/**********/

void setup() {
  // Await debug output
  notecard.setDebugOutputStream(Serial);
  Serial.begin(9600);
  const size_t serial_timeout_millis = (::millis() + SERIAL_TIMEOUT_MS);
  while (!Serial && (::millis() < serial_timeout_millis));
  Serial.println("Debug output connected!");

  // Initialize Peripherals
  notecard.begin();
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  // Display Blues Splash Screen
  display.setTextColor(SSD1306_WHITE);
  displayBluesSplash(1500);
  resetDisplay();
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);

  // Configure OLED Buttons
  ::pinMode(OFW_BUTTON_A, INPUT_PULLUP);
  ::pinMode(OFW_BUTTON_B, INPUT_PULLUP);
  ::pinMode(OFW_BUTTON_C, INPUT_PULLUP);
  Serial.println("OLED Buttons Configured");
}

void loop() {
  if (!::digitalRead(OFW_BUTTON_A)) {
    Serial.println("\"A\" Button Pressed");
    resetDisplay();
    if (J* req = notecard.newRequest("hub.get")) {
      displayJsonObject(req);
      if (J* rsp = notecard.requestAndResponse(req)) {
        displayJsonObject(rsp);
        notecard.deleteResponse(rsp);
      } else {
        // Null response returned
        notecard.deleteResponse(req);
      }
    }
    ::delay(500);  // debounce
  }
  if (!::digitalRead(OFW_BUTTON_B)) {
    Serial.println("\"B\" Button Pressed");
    display.print("B");
    display.display();
    ::delay(500);  // debounce
  }
  if(!::digitalRead(OFW_BUTTON_C)) {
    Serial.println("\"C\" Button Pressed");
    display.print("C");
    display.display();
    ::delay(500);  // debounce
  }
  ::delay(10);
  ::yield();
}
