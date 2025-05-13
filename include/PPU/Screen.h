#pragma once
#include <SDL3/SDL.h>

class Screen {
private:
	// Window to act as the screen
	SDL_Window* mWindow{ nullptr };

	// Renderer to draw texture to window
	SDL_Renderer* mRenderer{ nullptr };

	// Texture to be rendered
	SDL_Texture* mTexture{ nullptr };

	// Surface to be copied onto texture
	SDL_Surface* mSurface{ nullptr };

	// Screen Dimensions (Gameboy is 160 x 144 pixels)
	int mWidth;
	int mHeight;

	// Store time at which last frame was drawn
	int lastFrameTime = 0;

public:
	// Constructor to set up all member variables and initialise SDL
	Screen(int width, int height, int scale, const char* windowName, bool isMainWindow = false);

	// Deallocate memory
	~Screen();

	// Resets screen to all white (AKA colour 0)
	void reset();

	// Create texture from surface pixels
	void loadFromSurface();

	// Render texture to window
	void render();

	// Set pixel at given index in pixel array (ordered top-left to bottom-right) to a given color
	void editPixel(int pixelIndex, Uint8 r, Uint8 g, Uint8 b);

	void setRenderScale(int scale);

	SDL_Window* getWindow() { return mWindow; }
};
