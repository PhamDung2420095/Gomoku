#include <bits/stdc++.h>
#include <SDL.h>
#include "constants.h"
#include "board.h"
#include "DrawPieces.h"
#include "CheckWin.h"

using namespace std;

class Game{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    SDL_Event event;

    Game() {
        running = true;
        if(SDL_Init(SDL_INIT_VIDEO) < 0){
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
