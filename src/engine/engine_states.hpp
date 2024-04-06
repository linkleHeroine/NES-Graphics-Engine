#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

#pragma once

using namespace std;
using namespace sf;

#include "../constants/constants_states.hpp"

#include "../data/data_globals.hpp"

#include "../states/states_title.hpp"

void runTitleState(){
	titleSubStateList[titleState.subState]();
}



const stateHandler primaryStatesList[STATES_ALL] = {
	runTitleState
};