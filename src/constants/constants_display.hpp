#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

#pragma once

using namespace std;
using namespace sf;

#define WIDTH	256
#define HEIGHT	240

#define PIXELS	WIDTH * HEIGHT * 4

#define TILE_X	32
#define TILE_Y	30

#define TILES	TILE_X * TILE_Y

#define BYTE_TO_PIXL(b, p) \
(((b) & (3 << ((p) << 1))) >> ((p) << 1))

#define GET_COLOR_R(c)\
(((c) & 0xFF000000) >> 0x18);
#define GET_COLOR_G(c)\
(((c) & 0x00FF0000) >> 0x10);
#define GET_COLOR_B(c)\
(((c) & 0x0000FF00) >> 0x08);
#define GET_COLOR_A(c)\
(((c) & 0x000000FF) >> 0x00);

uint8_t		scaleRate;
uint16_t	scaleWidth, scaleHeight;
uint16_t	screenWidth, screenHeight;

bool hasFocus, fullscreen;

RenderWindow appWindow;
Event appWindowEvent;

Sprite viewSprite;
Texture viewTexture;

uint8_t pixelBuffer[PIXELS];

typedef enum VRAMS{
		BKG_VRAM,
		SPR_VRAM,
		WIN_VRAM,
		ALL_VRAM
}VRAMS;

typedef enum PALS{
		BKG_PALS,
		SPR_PALS,
		WIN_PALS,
		ALL_PALS
}PALS;

//________________STRUCTS_FOR_DISPLAY________________//

typedef struct defineTileVRAM{
	uint16_t	tileVRAM[1024][8];
}defineTileVRAM;


typedef struct defineBKGTiles{
	uint16_t	tileIDNum;
	uint8_t		tilePaletteNum;
}defineBKGTiles;


typedef struct defineSPRTiles{
	uint16_t	tileIDNum;
	uint8_t		tilePaletteNum;
	uint8_t		tilePositionX;
	uint8_t		tilePositionY;
	uint8_t		tileProperties;
}defineSPRTiles;


typedef struct defineWINObject{
	uint8_t		winPositionX;
	uint8_t		winPositionY;
	uint8_t		winTileWidth;
	uint8_t		winTileHeight;
}defineWINObject;


typedef struct definePalettes{
	uint8_t		paletteSets[16][4];
}definePalettes;


typedef struct defineViewDisplay{
	defineTileVRAM		listVRAM[ALL_VRAM];

	defineBKGTiles		backgroundBuffer[4096];
	defineSPRTiles		spriteBuffer[1024];
	defineBKGTiles		windowBuffer[960];
	defineWINObject		windowObject;

	definePalettes		listPalettes[ALL_PALS];

	int16_t backgroundBufferX;
	int16_t backgroundBufferY;

	//________________FUNCTIONS_FOR_VRAM________________//

	void updateVRAM(uint8_t VRAM, uint16_t tileNum, uint16_t tileCount, const uint16_t* dataPointer){
		for(uint16_t loopX = 0; loopX != tileCount; loopX++){
			for(uint8_t loopY = 0; loopY != 8; loopY++){
				listVRAM[VRAM].tileVRAM[tileNum + loopX][loopY] = dataPointer[(loopX << 3) + loopY];
			}
		}
	}


	//________________FUNCTIONS_FOR_BACKGROUNDS_TILES________________//

	void updateBKGTile(uint16_t tileID, uint8_t positionX, uint8_t positionY){
		uint16_t tempZ = ((positionY * 64) + positionX);
		backgroundBuffer[tempZ].tileIDNum = tileID;
	}
	void updateBKGTile(uint16_t tileID, uint8_t positionX, uint8_t positionY, uint8_t width, uint8_t height){
		uint16_t tempZ;
		for(uint8_t loopX = 0; loopX != width; loopX++){
			for(uint8_t loopY = 0; loopY != height; loopY++){
				tempZ = (((positionY + loopY) * 64) + (positionX + loopX));
				backgroundBuffer[tempZ].tileIDNum = tileID;
				printf("\n%u", backgroundBuffer[tempZ].tileIDNum);
			}
		}
	}
	void updateBKGTile(const uint16_t* areaMap, uint8_t positionX, uint8_t positionY, uint8_t width, uint8_t height){
		uint16_t tempZ;
		for(uint8_t loopX = 0; loopX != width; loopX++){
			for(uint8_t loopY = 0; loopY != height; loopY++){
				tempZ = (((positionY + loopY) * 64) + (positionX + loopX));
				backgroundBuffer[tempZ].tileIDNum = areaMap[(loopY * width) + loopX];
			}
		}
	}


	//________________FUNCTIONS_FOR_BACKGROUNDS_PALETTES________________//

	void updateBKGPalette(uint8_t paletteNum, uint8_t positionX, uint8_t positionY){
		uint16_t tempZ = ((positionY * 64) + positionX);
		backgroundBuffer[tempZ].tilePaletteNum = paletteNum;
	}
	void updateBKGPalette(uint16_t palette, uint8_t positionX, uint8_t positionY, uint8_t width, uint8_t height){
		uint16_t tempZ;
		for(uint8_t loopX = 0; loopX != width; loopX++){
			for(uint8_t loopY = 0; loopY != height; loopY++){
				tempZ = (((positionY + loopY) * 64) + (positionX + loopX));
				backgroundBuffer[tempZ].tilePaletteNum = palette;
			}
		}
	}
	void updateBKGPalette(const uint16_t* areaMap, uint8_t positionX, uint8_t positionY, uint8_t width, uint8_t height){
		uint16_t tempZ;
		for(uint8_t loopX = 0; loopX != width; loopX++){
			for(uint8_t loopY = 0; loopY != height; loopY++){
				tempZ = (((positionY + loopY) * 64) + (positionX + loopX));
				backgroundBuffer[tempZ].tilePaletteNum = areaMap[(loopY * width) + loopX];
			}
		}
	}


	//________________FUNCTIONS_FOR_SPRITES________________//

	void updateSPRTile(uint16_t tileID, uint16_t tileNum){
		spriteBuffer[tileNum].tileIDNum = tileID;
	}

	void updateSPRPal(uint16_t palette, uint16_t tileNum){
		spriteBuffer[tileNum].tilePaletteNum = palette;
	}

	void updateSPRProperties(uint8_t properties, uint16_t tileNum){
		spriteBuffer[tileNum].tileProperties = properties;
	}


	//________________FUNCTIONS_FOR_THE_WINDOW_TILES________________//

	void updateWINTile(uint16_t tileID, uint8_t positionX, uint8_t positionY){
		uint16_t tempZ = ((positionY * 64) + positionX);
		windowBuffer[tempZ].tileIDNum = tileID;
	}
	void updateWINTile(uint16_t tileID, uint8_t positionX, uint8_t positionY, uint8_t width, uint8_t height){
		uint16_t tempZ;
		for(uint8_t loopX = 0; loopX != width; loopX++){
			for(uint8_t loopY = 0; loopY != height; loopY++){
				tempZ = (((positionY + loopY) * 64) + (positionX + loopX));
				windowBuffer[tempZ].tileIDNum = tileID;
			}
		}
	}
	void updateWINTile(const uint16_t* areaMap, uint8_t positionX, uint8_t positionY, uint8_t width, uint8_t height){
		uint16_t tempZ;
		for(uint8_t loopX = 0; loopX != width; loopX++){
			for(uint8_t loopY = 0; loopY != height; loopY++){
				tempZ = (((positionY + loopY) * 64) + (positionX + loopX));
				windowBuffer[tempZ].tileIDNum = areaMap[(loopY * width) + loopX];
			}
		}
	}


	//________________FUNCTIONS_FOR_THE_WINDOW_PALETTES________________//

	void updateWINPalette(uint16_t palette, uint8_t positionX, uint8_t positionY){
		uint16_t tempZ = ((positionY * 64) + positionX);
		windowBuffer[tempZ].tilePaletteNum = palette;
	}
	void updateWINPalette(uint16_t palette, uint8_t positionX, uint8_t positionY, uint8_t width, uint8_t height){
		uint16_t tempZ;
		for(uint8_t loopX = 0; loopX != width; loopX++){
			for(uint8_t loopY = 0; loopY != height; loopY++){
				tempZ = (((positionY + loopY) * 64) + (positionX + loopX));
				windowBuffer[tempZ].tilePaletteNum = palette;
			}
		}
	}
	void updateWINPalette(const uint16_t* areaMap, uint8_t positionX, uint8_t positionY, uint8_t width, uint8_t height){
		uint16_t tempZ;
		for(uint8_t loopX = 0; loopX != width; loopX++){
			for(uint8_t loopY = 0; loopY != height; loopY++){
				tempZ = (((positionY + loopY) * 64) + (positionX + loopX));
				windowBuffer[tempZ].tilePaletteNum = areaMap[(loopY * width) + loopX];
			}
		}
	}


	//________________FUNCTIONS_FOR_THE_WINDOW_POSITION_AND_SIZE________________//

	void updateWinPosition(uint8_t posX, uint8_t posY){
		windowObject.winPositionX = posX;
		windowObject.winPositionY = posY;
	}

	void updateWinDimensions(uint8_t width, uint8_t height){
		windowObject.winTileWidth = width;
		windowObject.winTileHeight = height;
	}

	//________________FUNCTIONS_FOR_THE_PALETTES________________//

	void updatePalette(uint8_t paletteList, uint8_t palette, uint8_t colorSlot, uint8_t colorNum){
		listPalettes[paletteList].paletteSets[palette][colorSlot] = colorNum;
	}

	void updatePalette(uint8_t paletteList, uint8_t palette, const uint8_t* prePalette){
		for(uint8_t loopX = 0; loopX != 4; loopX++){
			listPalettes[paletteList].paletteSets[palette][loopX] = prePalette[loopX];
		}
	}


	//________________FUNCTIONS_FOR_MOVING_BACKGROUND________________//
	void setBackground(uint16_t positionX, uint16_t positionY){
		backgroundBufferX = positionX;
		backgroundBufferY = positionY;
		backgroundBufferX &= 511;
		backgroundBufferY &= 511;
	}

	void moveBackground(int8_t scrollX, int8_t scrollY){
		backgroundBufferX += scrollX;
		backgroundBufferY += scrollY;
		backgroundBufferX &= 511;
		backgroundBufferY &= 511;
	}

}defineViewDisplay;


const uint32_t colorPalette[] = {
	0xFCFCFCFF, 0xF8F8F8FF, 0xBCBCBCFF, 0x7C7C7CFF,
	0xA4E4FCFF, 0x3CBCFCFF, 0x0078F8FF, 0x0000FCFF,
	0xB8B8F8FF, 0x6888FCFF, 0x0058F8FF, 0x0000BCFF,
	0xD8B8F8FF, 0x9878F8FF, 0x6844FCFF, 0x4428BCFF,

	0xF8B8F8FF, 0xF878F8FF, 0xD800CCFF, 0x940084FF,
	0xF8A4C0FF, 0xF85898FF, 0xE40058FF, 0xA80020FF,
	0xF0D0B0FF, 0xF87858FF, 0xF83800FF, 0xA81000FF,
	0xFCE0A8FF, 0xFCA044FF, 0xE45C10FF, 0x881400FF,

	0xF8D878FF, 0xF8B800FF, 0xAC7C00FF, 0x503000FF,
	0xD8F878FF, 0xB8F818FF, 0x00B800FF, 0x007800FF,
	0xB8F8B8FF, 0x58D854FF, 0x00A800FF, 0x006800FF,
	0xB8F8D8FF, 0x58F898FF, 0x00A844FF, 0x005800FF,

	0x00FCFCFF, 0x00E8D8FF, 0x008888FF, 0x004058FF,
	0xF8D8F8FF, 0x787878FF, 0x000000FF, 0x000000FF
};