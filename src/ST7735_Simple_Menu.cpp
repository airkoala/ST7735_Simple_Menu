#include "ST7735_Simple_Menu.h"

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>             // Dependency

#include <Arduino.h>

MenuItem::MenuItem(char text[]) : text(text) {}

MenuItem &MenuItem::addCallback(voidFuncPtr callback)
{
    this->callback = callback;
    return *this;
}

ST7735_Simple_Menu::ST7735_Simple_Menu(Adafruit_ST7735 *tft) : tft(tft) {}

ST7735_Simple_Menu &ST7735_Simple_Menu::setItems(MenuItem menu[])
{
    this->menu = menu;
    // this->menuSize = sizeof(menu) / sizeof(menu[0]);
    this->menuSize = 3;
    return *this;
}

ST7735_Simple_Menu &ST7735_Simple_Menu::setHeader(char *header)
{
    this->header = header;
    return *this;
}

ST7735_Simple_Menu &ST7735_Simple_Menu::init()
{
    if (header != nullptr)
    {
        tft->setCursor(0, 0);
        tft->setTextSize(2);
        tft->setTextColor(fgColor);
        tft->println(header);
    }

    hovered = 0;

    return *this;
}

void ST7735_Simple_Menu::draw()
{
    if (header == NULL)
    {
        tft->setCursor(0, 0);
    }
    else
    {
        int16_t _;
        uint16_t w, h;
        tft->setTextSize(2);
        tft->getTextBounds(header, 0, 0, &_, &_, &w, &h);
        tft->setCursor(0, h + 5);
    }

    tft->setTextSize(1);

    for (int i = 0; i < menuSize; i++)
    {
        if (i == hovered)
        {
            tft->setTextColor(bgColor, fgColor);
        }
        else
        {
            tft->setTextColor(fgColor, bgColor);
        }

        tft->println(menu[i].text);
    }
}

void ST7735_Simple_Menu::buttonPressed(Control btn)
{
    switch (btn)
    {
    case UP:
        hovered = max(0, hovered - 1);
        break;
    case DOWN:
        hovered = min(menuSize - 1, hovered + 1);
        break;
    case NEXT:
        if (menu[hovered].callback != nullptr)
        {
            menu[hovered].callback();
        }
        break;
    case PREVIOUS:
        if (onPreviousPressed != nullptr)
        {
            onPreviousPressed();
        }
        break;
    }
}

ST7735_Simple_Menu &ST7735_Simple_Menu::setPreviousPressedCallback(voidFuncPtr callback)
{
    onPreviousPressed = callback;
    return *this;
}