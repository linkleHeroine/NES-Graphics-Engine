#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

#pragma once

using namespace std;
using namespace sf;

#include "../constants/constants_inputs.hpp"
#include "../constants/constants_display.hpp"

#define MOUSE_NONE	0
#define MOUSE_PRES	1
#define MOUSE_HELD	2

uint8_t mousePressed[3];

void updateMouse(){
	for(uint8_t loopM = 0; loopM != MOUSE_ALL; loopM++){
		if(Mouse::isButtonPressed(inputMouse[loopM])){
			//________________MOUSE_IS_INPUT________________//
			if(mousePressed[loopM] != MOUSE_NONE){
				mousePressed[loopM] = MOUSE_HELD;
			}
			else{
				mousePressed[loopM] = MOUSE_PRES;
			}
		}
		else{
			//________________MOUSE_IS_NOT_INPUT________________//
			mousePressed[loopM] = MOUSE_NONE;
		}
	}
}

bool getMouseInputs(uint8_t button, uint8_t inputType){
	if(mousePressed[button] == inputType){
		return true;
	}
	return false;
}

bool isMouseInside(Vector2i tempPos){
	uint16_t positionX = (screenWidth / 2) - (scaleWidth / 2);
	uint16_t positionY = (screenHeight / 2) - (scaleHeight / 2);
	if(!((tempPos.x > positionX) && (tempPos.x < (positionX + scaleWidth)))){
		return false;
	}
	if(!((tempPos.y > positionY) && (tempPos.y < (positionY + scaleHeight)))){
		return false;
	}
	return true;
}

void getMousePositionInside(Vector2i* posPointer){
	uint16_t positionX = (screenWidth / 2) - (scaleWidth / 2);
	uint16_t positionY = (screenHeight / 2) - (scaleHeight / 2);
	posPointer->x -= positionX;
	posPointer->x /= scaleRate;
	posPointer->y -= positionY;
	posPointer->y /= scaleRate;
}

void getScaledMousePosition(Vector2i* posPointer){
	posPointer->x /= scaleRate;
	posPointer->y /= scaleRate;
}