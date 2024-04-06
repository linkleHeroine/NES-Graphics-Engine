#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <stdint.h>

#pragma once

using namespace std;
using namespace sf;

typedef enum inputKeyNames{
	KEY_F11,
	KEY_A,
	KEY_W,
	KEY_S,
	KEY_D,
	KEY_ENTER,
	KEY_ALL
}inputKeyNames;

typedef enum inputMouseNames{
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_ALL
}inputMouseNames;

const Keyboard::Key inputKeys[KEY_ALL] = {
	Keyboard::F11,
	Keyboard::A,
	Keyboard::W,
	Keyboard::S,
	Keyboard::D,
	Keyboard::Enter
};

const Mouse::Button inputMouse[MOUSE_ALL] = {
	Mouse::Left,
	Mouse::Right,
	Mouse::Middle
};