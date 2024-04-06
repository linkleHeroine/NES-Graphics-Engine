#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

#pragma once

using namespace std;
using namespace sf;

uint8_t		frameTicker = 0;

uint8_t		primaryState = 0;

const uint8_t holdPalette[] = {
	0x04, 0x05, 0x06, 0x07,
	0x10, 0x11, 0x12, 0x13,
	0x20, 0x21, 0x22, 0x23,
	0x04, 0x05, 0x06, 0x07
};

const uint16_t tempTile[] = {
	0xFFFF, 0x2222, 0x1111, 0x0000,
	0x0000, 0x1111, 0x2222, 0xFFFF,
	0xFFFF, 0xFF00, 0x0000, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};