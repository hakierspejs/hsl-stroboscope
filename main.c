#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_timer.h>
#include <stdbool.h>

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
  SDL_Texture* cioranTexture = IMG_LoadTexture(rend, "djcioran.png");
  SDL_Texture* dyingTexture = IMG_LoadTexture(rend, "zakaz_umierania.png");
  
  SDL_Rect image;
  image.x = 0;
  image.y = 0;
  image.w = 1920;
  image.h = 1080;



  int image_id = 0;
  bool key_pressed = false;

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

        case SDL_KEYDOWN:
          switch(event.key.keysym.sym)
          {
            case 32:  //Space
              if(!key_pressed)
              {
                image_id++;

                if(image_id == 3) image_id = 0;

                key_pressed = true;
              }
            break;

            case 27:  //Escape
              close = 1;
            break;
          }
        break;
        
        case SDL_KEYUP:
          key_pressed = false;
        break;


      }
    }
 


    //sets random color to texture
    SDL_SetTextureColorMod(hslLogoTexture, 
                           rand() % 256, rand() % 256, rand() % 256);
    SDL_SetTextureColorMod(cioranTexture , 
                           rand() % 256, rand() % 256, rand() % 256);
    SDL_SetTextureColorMod(dyingTexture, 
                           rand() % 256, rand() % 256, rand() % 256);

 
    // clears the screen with black color
    SDL_SetRenderDrawColor( rend, 0, 0, 0, 255 );
    SDL_RenderClear(rend);
   
    //draw stuff
    switch(image_id)
    {
      case 0:
        SDL_RenderCopy(rend, hslLogoTexture, NULL, &image);
      break;
      
      case 1:
        SDL_RenderCopy(rend, cioranTexture, NULL, &image);
      break;
      
      case 2:
        SDL_RenderCopy(rend, dyingTexture, NULL, &image);
      break;
    }
    

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
