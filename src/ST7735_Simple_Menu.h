#ifndef ST7735_SIMPLE_MENU_H
#define ST7735_SIMPLE_MENU_H

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>             // Dependency

enum Control
{
    NEXT,
    PREVIOUS,
    DOWN,
    UP,
};

class MenuItem
{
public:
    char *text;
    voidFuncPtr callback;
    MenuItem(char text[]);
    MenuItem &addCallback(voidFuncPtr callback);
};

class ST7735_Simple_Menu
{
private:
    Adafruit_ST7735 *tft;
    MenuItem *menu;
    uint8_t hovered;
    uint8_t menuSize;
    voidFuncPtr onPreviousPressed;
    char *header;

public:
    uint16_t bgColor = ST7735_BLACK;
    uint16_t fgColor = ST7735_WHITE;

    ST7735_Simple_Menu(Adafruit_ST7735 *tft);
    ST7735_Simple_Menu &setItems(MenuItem menu[], uint8_t menuSize);
    ST7735_Simple_Menu &setPreviousPressedCallback(voidFuncPtr callback);
    ST7735_Simple_Menu &setHeader(char *header);
    ST7735_Simple_Menu &init();
    void draw();
    void buttonPressed(Control btn);
};

#endif