#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

void ablak_renderer(int szeles, int magas, SDL_Window **window, SDL_Renderer **renderer) {
    SDL_Window *window_seged = SDL_CreateWindow("Aknakereso", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window_seged == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer_seged = SDL_CreateRenderer(window_seged, -1, SDL_RENDERER_SOFTWARE);
    if (renderer_seged == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer_seged);
 
    *window = window_seged;
    *renderer = renderer_seged;
}

int SDL_main(int argc, char*argv[]){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    //scanf("%d %d",&szelesseg, &magassag);
    SDL_Window *ablak;
    SDL_Renderer *renderer;
    int szelesseg = 290;
    int magassag = 330;
    ablak_renderer(szelesseg, magassag, &ablak, &renderer);
    
    SDL_Rect button = {0, 0, 60, 40};
    SDL_Event event;
    bool fut = true;
    int kattintas = 0;

    Uint32 start_ticks = SDL_GetTicks();
    int elapsed_seconds = 0;
    char szoveg[32];

    while (fut) {
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        if (kattintas == 0){
            SDL_SetRenderDrawColor(renderer, 0,255, 0, 255);
            SDL_RenderFillRect(renderer, &button);
            stringRGBA(renderer, 11, 15, "kezdo", 0, 0, 0, 255);
        }
        else if (kattintas == 1){
            SDL_SetRenderDrawColor(renderer,255,140,0, 255);
            SDL_RenderFillRect(renderer, &button);
            stringRGBA(renderer, 8, 15, "halado", 0, 0, 0, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer,255,0,0, 255);
            SDL_RenderFillRect(renderer, &button);
            stringRGBA(renderer, 8, 15, "mester", 0, 0, 0, 255);
        }
        
        for (int i = 10; i <= szelesseg-10; i += 30){
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderDrawLine(renderer, i, 50, i, magassag-10);
        }
        for (int i = 50; i <= magassag-10; i += 30){
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderDrawLine(renderer, 10, i, szelesseg-10, i);
        }

        Uint32 current_ticks = SDL_GetTicks();
        elapsed_seconds = (current_ticks - start_ticks) / 1000;
        sprintf(szoveg, "Ido: %d mp", elapsed_seconds);
        stringRGBA(renderer, 70, 20, szoveg, 255, 255, 255, 255);
        
        if(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                fut = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                int x = event.button.x;
                int y = event.button.y;
                if (x >= button.x && x <= button.x + button.w && y >= button.y && y <= button.y + button.h) {
                    kattintas = (kattintas + 1) %3;
                    if (kattintas == 0){
                        szelesseg = 290;
                        magassag = 330;
                    }
                    else if (kattintas == 1){
                        szelesseg = 500;
                        magassag = 540;
                    }
                    else{
                        szelesseg = 920;
                        magassag = 540;
                    }
                    SDL_SetWindowSize(ablak, szelesseg, magassag);
                    start_ticks = SDL_GetTicks();
                }
                break;
    }
}
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    return 0;
}