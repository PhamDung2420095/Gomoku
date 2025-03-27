#include <bits/stdc++.h>
#include <SDL.h>
#include "constants.h"
#include "board.h"
#include "DrawPieces.h"
#include "CheckWin.h"
#include <SDL_ttf.h>

using namespace std;

class Game{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    SDL_Event event;
    TTF_Font* font;

    Game() {
        running = true;
        if(SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1){
            cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
            running = false;
        }
        window = SDL_CreateWindow("Gomoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(!window){
            cerr << "SDL could not be created! SDL_Error: " << SDL_GetError() << endl;
            running = false;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer){
            cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
            running = false;
        }
        font = TTF_OpenFont("./Downloads/Pixelify_Sans/PixelifySans-VariableFont_wght.ttf", 24);
        if(!font){
            cerr << "Font could not be created! SDL_Error: " << SDL_GetError() << endl;
        }
    }

    void renderText(const string &text, int x, int y, SDL_Color color){
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect dest = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &dest);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void RenderMenu(){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Rect playButton = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 50};
        SDL_Rect quitButton = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 200, 50};

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &playButton);
        renderText("Play", playButton.x + 70, playButton.y + 10, {0, 0, 0});

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &quitButton);
        renderText("Quit", quitButton.x + 70, quitButton.y + 10, {0, 0, 0});


        SDL_RenderPresent(renderer);

        bool inMenu = true;
        while(inMenu){
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    running = false;
                    return;
                }
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    int x = event.button.x;
                    int y = event.button.y;

                    if(x >= playButton.x && x <= playButton.x + playButton.w && y >= playButton.y && y <= playButton.y + playButton.h){
                        inMenu = false;
                    }
                    if(x >= quitButton.x && x <= quitButton.x + playButton.w && y >= quitButton.y && y <= quitButton.y + quitButton.h){
                        running = false;
                        return;
                    }
                }
            }
            SDL_Delay(16);
        }
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for(int i = 1; i < MAP_HEIGHT - 1; ++i){
            for(int j = 1; j < MAP_WIDTH - 1; ++j){
                SDL_Rect tile = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(renderer, &tile);
            }
        }

        DrawBoard(renderer);
        DrawPieces(renderer);
        SDL_RenderPresent(renderer);
    }

    bool isFull(){
        for(int i = 0; i < MAP_WIDTH; ++i){
            for(int j = 0; j < MAP_HEIGHT; ++j){
                if(board[i][j] == 0){
                    return false;
                }
            }
        }
        return true;
    }

    void run() {
        RenderMenu();

        while(running){
            render();
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    running = false;
                }
                if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                    int x = event.button.x / TILE_SIZE;
                    int y = event.button.y / TILE_SIZE;
                    if(board[x][y] == 0){
                        board[x][y] = CurrentPlayer;
                        if(CheckWin(CurrentPlayer)){
                            cout << "Player " << CurrentPlayer << " Win!" << endl;
                            running = false;
                        }
                        else if(isFull()){
                            cout << "Draw!" << endl;
                            running = false;
                        }
                        CurrentPlayer = (CurrentPlayer == 1) ? 2 : 1;
                    }
                }
            }
            SDL_Delay(16);
        }
    }

    ~Game() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

int main(int argc, char* argv[])
{
    Game game;
    if(game.running){
        game.run();
    }
    return 0;
}
