# ST7735_Simple_Menu

A minimal Arduino library for displaying and navigating a simple text-based menu on ST7735 TFT displays using the Adafruit ST7735 and GFX libraries.
Features

* Text-based vertical menu display
* Navigate using UP, DOWN, NEXT, and PREVIOUS controls
* Simple callback system for menu item selection
* Optional header display
* Customisable foreground and background colours

## Requirements

* Adafruit GFX Library
* Adafruit ST7735 Library
* SPI

## Usage

```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "ST7735_Simple_Menu.h"

// Example callback
void onSelect() {
  Serial.println("Item selected!");
}

// Setup menu items
MenuItem menuItems[] = {
  MenuItem("Item 1").addCallback(onSelect),
  MenuItem("Item 2").addCallback(onSelect)
};

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
ST7735_Simple_Menu menu(&tft);

void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK);

  menu
    .setHeader("Main Menu")
    .setItems(menuItems, 2)
    .setPreviousPressedCallback([](){
      Serial.println("Back pressed!");
    })
    .init();
}

void loop() {
  // Call menu.buttonPressed(Control::DOWN / UP / NEXT / PREVIOUS) based on input
  menu.draw();
}
```

## License: MIT

> Disclaimer: This README, including the example code, was generated using ChatGPT. It may or may not be accurate as the library was written a long time ago. Please refer to the actual source code for the most reliable information.
