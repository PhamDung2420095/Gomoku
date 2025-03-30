#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <vector>
#include "constants.h"
using namespace std;
vector<vector<int>> board(GRID_SIZE, vector<int>(GRID_SIZE, 0));

void DrawBoard(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for(int i = 0; i <= GRID_SIZE; ++i){
        SDL_RenderDrawLine(renderer, startX, startY + i * TILE_SIZE, startX + GRID_SIZE * TILE_SIZE, startY + i * TILE_SIZE);
        SDL_RenderDrawLine(renderer, startX + i * TILE_SIZE, startY, startX + i * TILE_SIZE, startY + GRID_SIZE * TILE_SIZE);
    }
}

#endif // BOARD_H_INCLUDED
