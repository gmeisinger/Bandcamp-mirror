
//The headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>

SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget)
{
    SDL_Texture *texture = nullptr;
    SDL_Texture *texture = nullptr;
    if(surface == NULL)
        std::cout << "ERROR" << std::endl;
    else
    {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        SDL_SetTextureColorMod(texture, 128, 255, 255);
        if(texture == NULL)
            std::cout << "ERROR" << std::endl;
    }
    SDL_FreeSurface(surface);

    return texture;    
}// end *LoadTexture


int main(int argc, char *argV[])
{
    SDL_Window *window = nullptr;
    SDL_Texture *currentImage = nullptr;
    SDL_Renderer *renderTarget = nullptr;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("Bandcamp Music Tester", SDL_WINDOWPSO_CENTERED, SDL_WINDOWPSO_CENTERED, 640, 480, 0);

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        std::cout << "ERROR" << Mix_GetErro() << std::endl;

    Mix_Music *bgm = Mix_LoadMUS("CS1666 Game Music 4 110bpm Cm.wav");

    bool isRunning = true;
    SDL_Event ev;

    while(isRunning)
    {
        while(SDL_PollEvent(&ev) != 0)
        {
            if(ev.type == SDL_QUIT)
                isRunning = false;
            else if(ev.type == SDL_KEYDOWN)
            {
                switch(ev.key.keysym.sym)
                {
                    case SDL_m: // play or resume music 
                        if(!Mix_PlayingMusic())
                            Mix_PlayMusic(bgm, -1);
                        else if(Mix_PauseMusic())
                            Mix_ResumeMusic();
                        else
                            Mix_PauseMusic();
                        break;
                    case SDL_n: // pause music
                        Mix_HaltMusic();
                        break;
                }
            }    

        }//end while(SDL_PollEvent(&ev) != 0)    

        SDL_RenderClear(renderTarget);
        SDL_RenderCopy(renderTarget, currentImage, NULL, NULL);
        SDL_RenderPresent(renderTarget);        

    }//end while(isRunning)


    // clean up
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(currentImage);
    SDL_DestroyRenderer(renderTarget);
    Mix_FreeMusic(bgm);


    window = nullptr;
    currentImage = nullptr;
    renderTarget = nullptr;
    bgm = nullptr;

    Mix_Quit();    
    SDL_Quit();

    return 0;
}//end main
