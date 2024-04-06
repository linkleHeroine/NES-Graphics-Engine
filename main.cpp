#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

#include "src/data/data_globals.hpp"

#include "src/engine/engine_mouse.hpp"
#include "src/engine/engine_keyboard.hpp"
#include "src/engine/engine_display.hpp"
#include "src/engine/engine_states.hpp"

void initApp(){
	initDisplay();
}

uint8_t color;

int main(){
	initApp();

	RectangleShape outline(Vector2f(scaleWidth, scaleHeight));
	outline.setFillColor(Color::White);

    while (appWindow.isOpen() && !(Keyboard::isKeyPressed(Keyboard::Escape))){
		//________________GAME_LOOP________________//
		while(appWindow.pollEvent(appWindowEvent)){
			switch(appWindowEvent.type){
				case Event::Closed:
					appWindow.close();
					break;
				case Event::LostFocus:
					hasFocus = false;
					appWindow.setActive(false);
					break;
				case Event::GainedFocus:
					hasFocus = true;
					appWindow.setActive(true);
					break;
				case Event::Resized:
					Vector2u tempSizeResize(scaleWidth, scaleHeight);
					appWindow.setSize(tempSizeResize);
					break;
			}
		}

		if(hasFocus){
			//________________UPDATE_VALUES_FOR_GAME________________//
			frameTicker++;
			updateMouse();
			updateKeyboard();

			//________________CHECK_IF_SHOULD_GO_FULLSCREEN________________//
			if(getKeyboardInputs(KEY_F11, KEY_PRES)){
				fullscreen = !fullscreen;
				if(fullscreen){
					appWindow.create(VideoMode::getFullscreenModes()[0], "SFML", Style::Fullscreen);
					viewSprite.setPosition((screenWidth / 2) - (scaleWidth / 2), (screenHeight / 2) - (scaleHeight / 2));
				}
				else{
					appWindow.create(VideoMode(scaleWidth, scaleHeight), "SFML", Style::Resize && Style::Close);
					viewSprite.setPosition(0, 0);
				}
			}

			//________________TEST_CODE________________//

			if(getMouseInputs(MOUSE_LEFT, MOUSE_PRES)){
				color = (color + 1) % 56;
				Vector2i tempPos = Mouse::getPosition(appWindow);
				if(fullscreen){
					if(isMouseInside(tempPos)){
						getMousePositionInside(&tempPos);
						drawPixel(tempPos.x, tempPos.y, color);
					}
				}
				else{
					getScaledMousePosition(&tempPos);
					drawPixel(tempPos.x, tempPos.y, color);
				}
			}

			//________________STATE_HANDLER________________//

			primaryStatesList[primaryState]();

			//________________DRAW_TO_SCREEN________________//
			updateTexture();
	        appWindow.clear();
			appWindow.draw(viewSprite);

    	    appWindow.display();
		}
    }

    return 0;
}
