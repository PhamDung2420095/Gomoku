#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <vector>
using namespace std;
vector<vector<int>> board(GRID_SIZE, vector<int>(GRID_SIZE, 0));

void DrawBoard(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for(int i = 0; i <= GRID_SIZE; ++i){
        SDL_RenderDrawLine(renderer, 0, i * TILE_SIZE, SCREEN_WIDTH, i * TILE_SIZE);
        SDL_RenderDrawLine(renderer, i * TILE_SIZE, 0, i * TILE_SIZE, SCREEN_HEIGHT);
    }
}

#endif // BOARD_H_INCLUDED
