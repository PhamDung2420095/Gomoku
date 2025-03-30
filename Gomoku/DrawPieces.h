#ifndef DRAWPIECES_H_INCLUDED
#define DRAWPIECES_H_INCLUDED
#include "constants.h"
void DrawPieces(SDL_Renderer* renderer){
    for(int x = 0; x < GRID_SIZE; ++x){
        for(int y = 0; y < GRID_SIZE; ++y){
            if(board[x][y] == 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_Rect piece = {startX + x * TILE_SIZE + 10, startY + y * TILE_SIZE + 10, TILE_SIZE - 20, TILE_SIZE - 20};
                SDL_RenderFillRect(renderer, &piece);
            }
            else if(board[x][y] == 2){
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_Rect piece = {startX + x * TILE_SIZE + 10, startY + y * TILE_SIZE + 10, TILE_SIZE - 20, TILE_SIZE - 20};
                SDL_RenderFillRect(renderer, &piece);
            }
        }
    }
}

#endif // DRAWPIECES_H_INCLUDED
