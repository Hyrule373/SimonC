#define SDL_MAIN_HANDLED

#include <iostream>
#include <string>

#include "raylib.h"
#include "header.h"

int main() {
	 //INIT 

	Window* win = new WindowRaylib();
	win->init();
	win->create("Window", 800, 450); //Create window

	sprite richter(10, 10, "images/richter_walk/richter_walk1.gif");

	richter.loadTextureImage();
	richter.unloadImage();

	//Update loop
	while (win->isOpen()) {
		win->detectQuit();

		//Draw
		win->beginDraw();
		win->clear(50, 0, 100);

		richter.drawTexture();

		win->endDraw();
	}

	win->quit();

	return 0;
}