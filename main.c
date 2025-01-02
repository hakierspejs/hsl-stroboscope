#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_timer.h>

int main(int argc, char *argv[])
{
  int close = 0;  //for closing program

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
  {
    printf("error initializing SDL: %s\n", SDL_GetError());
  }

  SDL_Window* win = SDL_CreateWindow("HSLodz Stroboscope",
                                     0, 0, 1920, 1080, 
                                     SDL_WINDOW_FULLSCREEN);

  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

  //HSŁ logo texture preparation
  SDL_Texture* hslLogoTexture = IMG_LoadTexture(rend, "hsl_logo.png");
  SDL_Rect hslLogo;
  hslLogo.x = 0;
  hslLogo.y = 0;
  hslLogo.w = 1920;
  hslLogo.h = 1080;

  while (!close) 
  {
    SDL_Event event;
 
    // Events management
    while (SDL_PollEvent(&event)) 
    {
      switch (event.type) 
      {
        case SDL_QUIT:
        // handling of close button
          close = 1;
        break;
      }
    }
  
    //sets random color to texture
    SDL_SetTextureColorMod(hslLogoTexture, 
                           rand() % 256, rand() % 256, rand() % 256);

 
    // clears the screen with black color
    SDL_SetRenderDrawColor( rend, 0, 0, 0, 255 );
    SDL_RenderClear(rend);
   
    //draw stuff
    SDL_RenderCopy(rend, hslLogoTexture, NULL, &hslLogo);

    //render
    SDL_RenderPresent(rend);
 
    //limits fps to set value
    int fps = 0;
    while (fps == 0)
    {
      fps = rand() % 50 + 15; //random fps from 15 to 65
    }

    SDL_Delay(1000 / fps);
  }
 
 
  return 0;
}
