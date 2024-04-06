#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

#pragma once

using namespace std;
using namespace sf;

#include "../constants/constants_inputs.hpp"

uint8_t keyboardPressed[12];

#define KEY_NONE	0
#define KEY_PRES	1
#define KEY_HELD	2

void updateKeyboard(){
	for(uint8_t loopK = 0; loopK != KEY_ALL; loopK++){
		if(Keyboard::isKeyPressed(inputKeys[loopK])){
			//________________KEY_IS_INPUT________________//
			if(keyboardPressed[loopK] != KEY_NONE){
				keyboardPressed[loopK] = KEY_HELD;
			}
			else{
				keyboardPressed[loopK] = KEY_PRES;
			}
		}
		else{
			//________________KEY_IS_NOT_INPUT________________//
			keyboardPressed[loopK] = KEY_NONE;
		}
	}
}

bool getKeyboardInputs(uint8_t button, uint8_t inputType){
	if(keyboardPressed[button] == inputType){
		return true;
	}
	return false;
}