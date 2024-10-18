#pragma once

#define SDL_MAIN_HANDLED

#include "iostream"
#include "string"

#include <SDL2/SDL.h>
#include "raylib.h"

class Window {
public:
	virtual void init() = 0;
	virtual void create(std::string _name, int _w, int _h) = 0;
	virtual int detectQuit() = 0;
	virtual bool isOpen() = 0;
	virtual void beginDraw() = 0;
	virtual void clear(int r, int g, int b) = 0;
	virtual void endDraw() = 0;
	virtual void quit() = 0;
};

class WindowSDL : public Window {
	SDL_Surface* winSurface = NULL;
	SDL_Window* window = NULL;
	SDL_Event eve;
public:
	virtual void init() override {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
			system("pause");
			// End the program
			exit(1);
		}
	}
	virtual void create(std::string _name, int _w, int _h) override {
		window = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _w, _h, SDL_WINDOW_SHOWN);
		if (!window) {
			std::cout << "Error creating window: " << SDL_GetError() << std::endl;
			system("pause");
			// End the program
			exit(1);
		}

		winSurface = SDL_GetWindowSurface(window);
		if (!winSurface) {
			std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
			system("pause");
			// End the program
			exit(1);
		}
	}
	virtual bool isOpen() override {
		return (window != nullptr);
	}
	virtual void beginDraw() override {

	}
	virtual void clear(int r, int g, int b) override {
		SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, r, g, b));
	}
	virtual void endDraw() {
		SDL_UpdateWindowSurface(window);
	}
	virtual int detectQuit() override {
		while (SDL_PollEvent(&eve) != 0)
		{
			if (eve.type == SDL_QUIT)
			{
				quit();

				return 0;
			}
		}
	}
	virtual void quit() override {
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};

class WindowRaylib : public Window {
public:
	virtual void init() override {
		SetTargetFPS(60);
	}
	virtual void create(std::string _name, int _w, int _h) override {
		InitWindow(_w, _h, _name.c_str());
	}
	virtual bool isOpen() override {
		return !WindowShouldClose();
	}
	virtual void beginDraw() override {
		BeginDrawing();
	}
	virtual void clear(int r, int g, int b) {
		Color _color;
		_color.r = r;
		_color.g = g;
		_color.b = b;
		_color.a = 255;
		ClearBackground(_color);
	}
	virtual void endDraw() override {
		EndDrawing();
	}
	virtual int detectQuit()override {
		return 0;
	}

	virtual void quit() override {
		CloseWindow();
	}
};



//////////SPRITE/////////////

class sprite {
protected:
	int x, y;
	Image image;
	Texture2D texture;

public:
	sprite(int _x, int _y, const char* path): x(_x), y(_y){
		image = LoadImage(path);
	}
	virtual void loadTextureImage() {
		texture = LoadTextureFromImage(image);
	}
	virtual void unloadImage() {
		UnloadImage(image);
	}

	virtual void drawTexture() {
		DrawTexture(texture, x, y, WHITE);
	}

	virtual int getX() {
		return x;
	}
	virtual int getY() {
		return y;
	}
};

////class spriteSDL : public sprite {
////
////	virtual void drawImage()
////	sprite.image = IMG_LoadTexture(renderer, IMG_PATH);
////
////};
//
//class spriteRaylib : public sprite {
//public:
//	virtual void loadImage() override {
//		LoadImage(path);
//	}
//
//	virtual void loadTextureFromImage() override {
//		LoadTextureFromImage(image);
//	}
//
//	virtual void drawTexture() {
//		DrawTexture(texture, x, y, WHITE);
//	}
//};