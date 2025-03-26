#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

void GamePlay(SDL_Renderer* renderer){
    for(int x = 0; x < GRID_SIZE; ++x){
        for(int y = 0; y < GRID_SIZE; ++y){
            if(board[x][y] == 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_Rect piece = {x * TILE_SIZE + 10, y * TILE_SIZE + 10, TILE_SIZE - 20, TILE_SIZE - 20};
                SDL_RenderFillRect(renderer, &piece);
            }
            else if(board[x][y] == 2){
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_Rect piece = {x * TILE_SIZE + 10, y * TILE_SIZE + 10, TILE_SIZE - 20, TILE_SIZE - 20};
                SDL_RenderFillRect(renderer, &piece);
            }
        }
    }
}



#endif // GAMEPLAY_H_INCLUDED
