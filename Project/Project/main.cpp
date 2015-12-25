// Project.cpp : 定義主控台應用程式的進入點。
//


//==========================設計===================================
//程式大部分重疊的塔與敵人大多設計為reference (&)  而非pointer



//=================================================================




/**************************問題***********************************/


/*****************************************************************/

#include "stdafx.h"
#include <iostream>
#include "SDL.h"
using namespace std;
int main()
{

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 255 };

	//Current time start time
	Uint32 startTime = 0;

	//In memory text stream
	//std::stringstream timeText;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			//Reset start time on return keypress
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
			{
				startTime = SDL_GetTicks();
			}
		}

		//Set text to be rendered
		timeText.str("");
		timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime;

		//Render text
		if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
		{
			printf("Unable to render time texture!\n");
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render textures
		gPromptTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 2, 0);
		gTimeTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gPromptTextTexture.getHeight()) / 2);

		//Update screen
		SDL_RenderPresent(gRenderer);
	}
















    return 0;
}

