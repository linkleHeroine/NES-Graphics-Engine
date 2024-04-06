#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

#pragma once

using namespace std;
using namespace sf;

#include "../constants/constants_display.hpp"

#include "../data/data_globals.hpp"

defineViewDisplay viewDisplay;

void initDisplay(){
	scaleRate = (VideoMode::getDesktopMode().height) / HEIGHT;
	scaleHeight = HEIGHT * scaleRate;
	scaleWidth = WIDTH * scaleRate;
	screenHeight = VideoMode::getDesktopMode().height;
	screenWidth = VideoMode::getDesktopMode().width;

	appWindow.create(VideoMode(scaleWidth, scaleHeight), "SFML", Style::Resize && Style::Close);
	appWindow.setFramerateLimit(60);
	hasFocus = true;
	fullscreen = false;

	viewTexture.create(WIDTH, HEIGHT);
	viewSprite.setTexture(viewTexture);
	viewSprite.scale(scaleRate, scaleRate);

	viewDisplay.updatePalette(BKG_PALS, 0, &holdPalette[0]);
	viewDisplay.updatePalette(BKG_PALS, 1, &holdPalette[4]);
	viewDisplay.updatePalette(BKG_PALS, 2, &holdPalette[8]);
	viewDisplay.updateVRAM(BKG_VRAM, 0, 2, &tempTile[0]);
	viewDisplay.updateBKGTile(1, 1, 1, 3, 4);
	viewDisplay.updateBKGPalette(1, 1, 1, 1, 2);
	viewDisplay.updateBKGPalette(2, 2, 1, 1, 2);
}

void drawPixel(uint8_t positionX, uint8_t positionY, uint8_t colorNum){
	uint32_t pulledColor = colorPalette[colorNum];
	uint32_t tempZ = ((positionY * WIDTH) + positionX) * 4;
	if(positionY < HEIGHT){
		pixelBuffer[tempZ + 0] = GET_COLOR_R(pulledColor);
		pixelBuffer[tempZ + 1] = GET_COLOR_G(pulledColor);
		pixelBuffer[tempZ + 2] = GET_COLOR_B(pulledColor);
		pixelBuffer[tempZ + 3] = 255;
	}
}

void updateTexture(){
	const uint32_t pixelTotal = PIXELS >> 2;
	int16_t tempX, tempY;
	uint8_t tempC, tempP, tempA;
	uint16_t tempT, tempZ;
	uint32_t tempXXX = 0;

	//________________DRAW_BACKGROUND_TILES________________//
	for(uint32_t loopP = 0; loopP != pixelTotal; loopP++){
		tempX = viewDisplay.backgroundBufferX + (loopP & 255);
		if(tempX >= 512) tempX -= 512; if(tempX < 0) tempX += 512;
		tempY = viewDisplay.backgroundBufferY + (loopP / 256);
		if(tempY >= 512) tempY -= 512; if(tempY < 0) tempY += 512;
		//printf("\n%u, %u", tempX, tempY);

		tempZ = ((tempY / 8) * 64) + (tempX / 8);

		tempT = viewDisplay.backgroundBuffer[tempZ].tileIDNum;
		tempP = viewDisplay.backgroundBuffer[tempZ].tilePaletteNum;

		tempA = BYTE_TO_PIXL(viewDisplay.listVRAM[BKG_VRAM].tileVRAM[tempT][(tempY & 7)], (7 - (tempX & 7)));
		tempC = viewDisplay.listPalettes[BKG_PALS].paletteSets[tempP][tempA];

		drawPixel((loopP & 255), (loopP / 256), tempC);
	}
	viewTexture.update(pixelBuffer, WIDTH, HEIGHT, 0, 0);
}