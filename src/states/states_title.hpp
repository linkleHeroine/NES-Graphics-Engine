#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

#pragma once

using namespace std;
using namespace sf;

#include "../constants/constants_states.hpp"

#include "../data/data_globals.hpp"

#include "../engine/engine_display.hpp"
#include "../engine/engine_keyboard.hpp"

defineFullStates titleState;

void initTitleState(){
	titleState.subState = 1;
}

void mainTitleState(){
	if(getKeyboardInputs(KEY_A, KEY_HELD)){
		viewDisplay.moveBackground(-2, 0);
	}
	if(getKeyboardInputs(KEY_S, KEY_HELD)){
		viewDisplay.moveBackground(0, 2);
	}
	if(getKeyboardInputs(KEY_D, KEY_HELD)){
		viewDisplay.moveBackground(2, 0);
	}
	if(getKeyboardInputs(KEY_W, KEY_HELD)){
		viewDisplay.moveBackground(0, -2);
	}
	if(getKeyboardInputs(KEY_ENTER, KEY_PRES)){
		for(uint8_t loopX = 0; loopX != 64; loopX++){
			for(uint8_t loopY = 0; loopY != 8; loopY++){
				printf("%u, ", viewDisplay.listVRAM[BKG_VRAM].tileVRAM[loopX][loopY]);
				printf("%u, ", viewDisplay.listPalettes[BKG_PALS].paletteSets[loopX][(loopY >> 1)]);
			}
			printf("\n\n");
		}
	}
}


const stateHandler titleSubStateList[] = {
	initTitleState,
	mainTitleState
};