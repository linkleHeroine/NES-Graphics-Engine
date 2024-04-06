#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

#pragma once

using namespace std;
using namespace sf;

typedef enum stateNames{
	STATES_TITLE,
	STATES_ALL
}stateNames;

typedef struct defineFullStates{
	uint8_t		subState;
	uint8_t		animTick;
	uint8_t		tempTick;
	uint8_t		miscVars[16];
}defineFullStates;

typedef struct defineMiniStates{
	uint8_t		subState;
	uint8_t		animTick;
	uint8_t		tempTick;
}defineMiniStates;

typedef void (*stateHandler)();