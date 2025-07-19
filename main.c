#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159

int main(int argc, char *argv[])
{
  int close = 0;  //for closing program

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
  {
    printf("error initializing SDL: %s\n", SDL_GetError());
  }

  int screen_width = 1920;
  int screen_height = 1080;

  SDL_Window* win = SDL_CreateWindow("HSLodz Stroboscope",
                                     0, 0, screen_width, screen_height, 
                                     SDL_WINDOW_FULLSCREEN);

  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

  //HSŁ logo texture preparation
  SDL_Texture* hslLogoTexture = IMG_LoadTexture(rend, "hsl_logo.png");
  SDL_Texture* cioranTexture = IMG_LoadTexture(rend, "djcioran.png");
  SDL_Texture* dyingTexture = IMG_LoadTexture(rend, "zakaz_umierania.png");
  SDL_Texture* papajTexture = IMG_LoadTexture(rend, "rzultamordunia_1.png");
  SDL_Texture* dziwnyTexture = IMG_LoadTexture(rend, "dziwnypapaj.png");


  SDL_Rect image;
  image.x = 0;
  image.y = 0;
  image.w = screen_width;
  image.h = screen_height;

  int image_id = 0;
  bool key_pressed = false;

  bool red = true;
  bool blue = true;
  bool green = true;
    
  int rzultosc = 256;

  int frame = 0;
  int fps = 144;
  int flicker_rate = 5;
  float time_for_rotation = 1.0;

  while (!close) 
  {
    frame++;

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
          //printf("%d\n",event.key.keysym.sym); 
          switch(event.key.keysym.sym)
          {
            case 49:  // 1
              image.x = 0;
              image.y = 0;
              image_id = 0;
            break;

            case 50:  // 2
              image.x = 0;
              image.y = 0;
              image_id = 1;
            break;

            case 51:  // 3
              image.x = 0;
              image.y = 0;
              image_id = 2;
            break;
            
	          case 52:  // 4
              image_id = 3;
            break;
	          
            case 53:  // 5
              image.x = 0;
              image.y = 0;
              image_id = 4;
            break;

            case 114: // R
              if(!key_pressed)
              {
                red = !red;

                key_pressed = true;
              }
            break;

            case 98:  // G
              if(!key_pressed)
              {
                green = !green;

                key_pressed = true;
              }
            break;
            
            case 103: // B
              if(!key_pressed)
              {
                blue = !blue;

                key_pressed = true;
              }
            break;

            case 32:  // Space
              if(!key_pressed)
              {
                image_id++;

                if(image_id == 4) image_id = 0;

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
 

    if(frame % (fps / flicker_rate) == 0)
    {
      //sets random color to texture
      SDL_SetTextureColorMod(hslLogoTexture, 
                             rand() * red % 256, 
                             rand() * green % 256,
                             rand() * blue % 256);
      SDL_SetTextureColorMod(cioranTexture , 
                             rand() * red % 256, 
                             rand() * green % 256,
                             rand() * blue % 256);
      SDL_SetTextureColorMod(dyingTexture, 
                             rand() * red % 256, 
                             rand() * green % 256,
                             rand() * blue % 256);
      
      //set something between black and rzulty for papaj
      rzultosc = rand() % 256;
      SDL_SetTextureColorMod(papajTexture, 
                             rzultosc, 
                             rzultosc,
                             0);				//blue lol 
      SDL_SetTextureColorMod(dziwnyTexture, 
                             rzultosc, 
                             rzultosc,
                             0);				//blue lol 
    }
    	
    

    //hehe papiesz tanczy
    if(image_id == 3)
    {
      image.y = sin(frame * 2 * PI / (time_for_rotation * fps)) * 100;
      image.x = cos(frame * 2 * PI / (time_for_rotation * fps)) * 100;
    }

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
      
      case 3:
        SDL_RenderCopy(rend, papajTexture, NULL, &image);
      break;
      
      case 4:
        SDL_RenderCopy(rend, dziwnyTexture, NULL, &image);
      break;
    }
    

    //render
    SDL_RenderPresent(rend);
 
    /*while (fps == 0)
    {
      fps = 15;
    }*/

    //limits fps to set value
    SDL_Delay(1000 / fps);
  }
 
 
  return 0;
}
