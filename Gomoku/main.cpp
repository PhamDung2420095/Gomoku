#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "constants.h"
#include "board.h"
#include "DrawPieces.h"
#include "CheckWin.h"

using namespace std;

class Game{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    TTF_Font* font;
    SDL_Surface* bgSurface;
    SDL_Texture* bgTexture;
    bool running = true;
    bool FirstMove = false;
    string player1 = "Player 1";
    string player2 = "Player 2";

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
        if(TTF_Init() == -1) {
            cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
            running = false;
        }

        bgSurface = IMG_Load("background.jpg");
        bgTexture = nullptr;
        if(!bgSurface){
            cerr << "Failed to load background image: " << IMG_GetError() << endl;
            running = false;
        }

        font = TTF_OpenFont("VeraMoBd.ttf", 24);
        if (!font) {
            cerr << "Failed to load font! SDL_Error: " << TTF_GetError() << endl;
            running = false;
        }
    }

    void RenderText(const string& text, int x, int y, SDL_Color color){
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect dest = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &dest);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void RenderMenu(){ // hiện menu game
        bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Color titleColor = {0, 0, 0, 255};
        TTF_Font* largeFont = TTF_OpenFont("VeraMoBd.ttf", 64); // tên game

        SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr); // hiện background

        if(largeFont){
            SDL_Surface* titleSurface = TTF_RenderText_Solid(largeFont, "Gomoku", titleColor);
            SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
            SDL_Rect titleRect = {SCREEN_WIDTH / 2 - titleSurface->w / 2, 100, titleSurface->w, titleSurface->h};
            SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);

            SDL_FreeSurface(titleSurface);
            SDL_DestroyTexture(titleTexture);
            TTF_CloseFont(largeFont);
        }

        SDL_Rect playButton = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 50};
        SDL_Rect quitButton = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 80, 200, 50};

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &playButton);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &quitButton);

        SDL_Color textColor = {0, 0, 0, 255};
        RenderText("Play", playButton.x + 75, playButton.y + 10, textColor);
        RenderText("Quit", quitButton.x + 75, quitButton.y + 10, textColor);

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

    void renderPlayerNames(){ // hiện tên người chơi
        SDL_Color activeColor = {0, 0, 0, 255};
        SDL_Color inactiveColor = {211, 211, 211, 255};
        if(CurrentPlayer == 1){
            RenderText(player1, 50, 20, activeColor);
            RenderText(player2, SCREEN_WIDTH - 150, 20, inactiveColor);
        }
        else{
            RenderText(player1, 50, 20, inactiveColor);
            RenderText(player2, SCREEN_WIDTH - 150, 20, activeColor);
        }
    }

    void renderEndMenu(const string& announce){ // thông báo kết quả
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr); // End Menu background

        SDL_Color textColor = {0, 0, 0, 255};
        RenderText(announce, SCREEN_WIDTH / 2 - 100, 150, textColor);

        SDL_Rect replayButton = {SCREEN_WIDTH / 2 - 100, 300, 200, 50};
        SDL_Rect quitButton = {SCREEN_WIDTH / 2 - 100, 400, 200, 50};

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &replayButton);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &quitButton);

        RenderText("Play Again", replayButton.x + 40, replayButton.y + 10, textColor);
        RenderText("Quit", quitButton.x + 75, quitButton.y + 10, textColor);

        SDL_RenderPresent(renderer);

        bool inEndMenu = true;
        while(inEndMenu){
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    running = false;
                    return;
                }
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    int x = event.button.x;
                    int y = event.button.y;

                    if(x >= replayButton.x && x <= replayButton.x + replayButton.w && y >= replayButton.y && y <= replayButton.y + replayButton.h){
                        ResetGame();
                        return;
                    }

                    if (x >= quitButton.x && x <= quitButton.x + quitButton.w && y >= quitButton.y && y <= quitButton.y + quitButton.h) {
                        running = false;
                        return;
                    }
                }
            }
            SDL_Delay(16);
        }
    }

    void ResetGame(){
        for(auto& row : board){
            fill(row.begin(), row.end(), 0);
        }
        CurrentPlayer = 1;
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
        renderPlayerNames();
        DrawBoard(renderer);
        DrawPieces(renderer);
        SDL_RenderPresent(renderer);
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
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    if(mouseX >= startX && mouseX < startX + GRID_SIZE * TILE_SIZE && mouseY >= startY && mouseY < startY + GRID_SIZE * TILE_SIZE){
                        int x = (mouseX - startX) / TILE_SIZE;
                        int y = (mouseY - startY) / TILE_SIZE;

                        if(board[x][y] == 0){
                            board[x][y] = CurrentPlayer;
                            int result = CheckWin(CurrentPlayer);
                            if(result == 1){
                                renderEndMenu("Player " + to_string(CurrentPlayer) + " win!");
                                FirstMove = true;
                            }
                            else if(result == -1){
                                renderEndMenu("Draw!");
                                FirstMove = true;
                            }
                            else{
                                CurrentPlayer = (CurrentPlayer == 1) ? 2 : 1;
                            }
                        }
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
