#include <SDL.h>
#include "InputManager.h"
#include "ImguiRenderer.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...

		ImguiRenderer::GetInstance().ProcessEvents(e);
	}

	return true;
}
