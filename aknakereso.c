#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

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

void akna_eldontes(char *input,int *aknaszam, int kattintas){
    int seged_aknaszam;
    sscanf(input, "%d", &seged_aknaszam);
    if (seged_aknaszam > 0 && seged_aknaszam < 92 && kattintas % 3 == 0)
        *aknaszam = seged_aknaszam;
    else if (seged_aknaszam > 0 && seged_aknaszam < 257 && kattintas % 3 == 1)
        *aknaszam = seged_aknaszam;
    else if (seged_aknaszam > 0 && seged_aknaszam < 481 && kattintas % 3 == 2)
        *aknaszam = seged_aknaszam;
}

int SDL_main(int argc, char*argv[]){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    srand(time(NULL));

    //ablak
    SDL_Window *ablak;
    SDL_Renderer *renderer;
    int szelesseg = 290;
    int magassag = 330;
    ablak_renderer(szelesseg, magassag, &ablak, &renderer);

    //nehezsegigomb
    SDL_Rect button = {0, 0, 60, 40};
    SDL_Event event;
    bool fut = true;
    int kattintas = 0;

    //idozito
    Uint32 start_ticks = SDL_GetTicks();
    int elapsed_seconds = 0;
    char ido_kiier[64];
    
    //aknak
    int aknaszam = 10;
    char akna_kiir[64];
    char input[16] = "";
    bool input_bool = false;
    bool aknabool = true;
    SDL_StartTextInput();

    bool kirajzol = true;
    
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    while (fut) {

        //kockak
        if (kirajzol){
            for (int i = 12; i < szelesseg - 12; i += 30) {
                for (int j = 52; j < magassag - 12; j += 30) {
                    SDL_Rect kockak = {i, j, 26, 26};
                    SDL_SetRenderDrawColor(renderer, 55, 63, 67, 255);
                    SDL_RenderFillRect(renderer, &kockak);
                }
            }
        }

        //nehezsegigomb
        if (kattintas == 0){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &button);
            stringRGBA(renderer, 11, 15, "kezdo", 0, 0, 0, 255);
        }
        else if (kattintas == 1){
            SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
            SDL_RenderFillRect(renderer, &button);
            stringRGBA(renderer, 8, 15, "halado", 0, 0, 0, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &button);
            stringRGBA(renderer, 8, 15, "mester", 0, 0, 0, 255);
        }

        //racsok
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 10; i <= szelesseg - 10; i += 30)
            SDL_RenderDrawLine(renderer, i, 50, i, magassag - 10);
        for (int i = 50; i <= magassag - 10; i += 30)
            SDL_RenderDrawLine(renderer, 10, i, szelesseg - 10, i);
            
            //idozito
        SDL_Rect takaro1 = {100, 10, 100, 20};
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderFillRect(renderer, &takaro1);
        Uint32 current_ticks = SDL_GetTicks();
        elapsed_seconds = (current_ticks - start_ticks) / 1000;
        sprintf(ido_kiier, "Ido: %d mp", elapsed_seconds);
        stringRGBA(renderer, 70, 20, ido_kiier, 255, 255, 255, 255);
            
        //aknaszam
        SDL_Rect takaro2 = {236, 20, 40, 20};
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderFillRect(renderer, &takaro2);
        if (aknabool){
            sprintf(akna_kiir, "Aknak: %d", aknaszam);
            stringRGBA(renderer, 180, 20, akna_kiir, 255, 255, 255, 255);
        }
        if (input_bool) {
            stringRGBA(renderer, 180, 20, "Aknak: ", 200, 200, 255, 255);
            stringRGBA(renderer, 236, 20, input, 255, 255, 255, 255);
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                fut = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (x >= button.x && x <= button.x + button.w && y >= button.y && y <= button.y + button.h) {
                    kattintas = (kattintas + 1) % 3;
                    if (kattintas == 0) {
                        szelesseg = 290;
                        magassag = 330;
                        aknaszam = 10;
                    }
                    else if (kattintas == 1) {
                        szelesseg = 500;
                        magassag = 540;
                        aknaszam = 40;
                    }
                    else {
                        szelesseg = 920;
                        magassag = 540;
                        aknaszam = 99;
                    }
                    SDL_SetWindowSize(ablak, szelesseg, magassag);
                    start_ticks = SDL_GetTicks();
                    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
                    SDL_RenderClear(renderer);
                    kirajzol = true;
                }
                if (event.button.button == SDL_BUTTON_LEFT && x >=12 && x < szelesseg - 12 && y >= 52 && y <= magassag - 12){
                    SDL_Rect eltunik = {((x-12)/30)*30+12, ((y-52)/30)*30+52, 26, 26};
                    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
                    SDL_RenderFillRect(renderer, &eltunik);
                    kirajzol = false;
                }

                if (x > 175 && x < 255 && y > 10 && y < 35) {
                    input_bool = true;
                    aknabool = false;
                    strcpy(input, "");
                }
            }
            else if (event.type == SDL_TEXTINPUT && input_bool) {
                if (isdigit(event.text.text[0]) && strlen(input) < 3) {
                    strcat(input, event.text.text);
                }
            }
            else if (event.type == SDL_KEYDOWN && input_bool) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(input) > 0) {
                    input[strlen(input) - 1] = '\0';
                }
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    akna_eldontes(input, &aknaszam, kattintas);
                    
                    input_bool = false;
                    aknabool = true;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    input_bool = false;
                    aknabool = true;
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    SDL_Quit();
    return 0;
}
