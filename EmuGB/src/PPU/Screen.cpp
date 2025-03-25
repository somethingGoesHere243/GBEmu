#include <SDL3/SDL.h>
#include<iostream>

#include "Screen.h"

Screen::Screen(int scale) {

	// Attempt to initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL failed to initialise. SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Create window (of given dimensions) and renderer
	if (!SDL_CreateWindowAndRenderer("GBEmu", mWidth * scale, mHeight * scale, 0, &mWindow, &mRenderer)) {
		std::cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Set render scale
	SDL_SetRenderScale(mRenderer, scale, scale);

	// Get pixel format of window
	SDL_PixelFormat pixelFormat = SDL_GetWindowPixelFormat(mWindow);

	// Create blank surface of the given width and height
	mSurface = SDL_CreateSurface(mWidth, mHeight, pixelFormat);

	// Set all pixels to lightest color
	Uint32 lightPixel = SDL_MapSurfaceRGBA(mSurface, 155, 188, 15, 255);
	constexpr int bytesPerPixel = 4;
	for (int x = 0; x < mWidth; ++x) {
		for (int y = 0; y < mHeight; ++y) {
			SDL_LockSurface(mSurface);
			Uint8* targetPixel = (Uint8*)mSurface->pixels + y * mSurface->pitch + x * bytesPerPixel;

			*(Uint32*)targetPixel = lightPixel;

			SDL_UnlockSurface(mSurface);
		}
	}

	loadFromSurface();
	render();
}

Screen::~Screen() {
	// Free Texture if it exists
	if (mTexture) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
	// Destroy Surface
	SDL_DestroySurface(mSurface);
	mSurface = nullptr;

	// Destroy Renderer
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;

	// Destroy Window
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}

void Screen::loadFromSurface() {
	// Free old texture if it exists
	if (mTexture) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}

	// Create texture from surface pixels
	mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);

	// Check texture was created
	if (!mTexture) {
		std::cout << "Unable to create texture from surface. SDL Error: " << SDL_GetError() << std::endl;
	}

	// Set scaling mode to maintain pixelated look
	SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);
}

void Screen::render() {
	// Clear window
	SDL_RenderClear(mRenderer);

	// Set rendering space
	SDL_FRect renderQuad{ 0, 0, mWidth, mHeight };

	// Render to screen
	SDL_RenderTexture(mRenderer, mTexture, nullptr, &renderQuad);

	// Show new frame
	SDL_RenderPresent(mRenderer);
}

void Screen::editPixel(int pixelIndex, Uint8 r, Uint8 g, Uint8 b) {
	// Get x,y coordinates of pixel to be edited
	int x = pixelIndex % mWidth;
	int y = pixelIndex / mWidth;

	// Generate data to overwrite old pixel data
	Uint32 newPixel = SDL_MapSurfaceRGBA(mSurface, r, g, b, 255);

	constexpr int bytesPerPixel = 4;

	// Replace old pixel data
	SDL_LockSurface(mSurface);
	Uint8* targetPixel = (Uint8*)mSurface->pixels + y * mSurface->pitch + x * bytesPerPixel;

	*(Uint32*)targetPixel = newPixel;

	SDL_UnlockSurface(mSurface);
}
