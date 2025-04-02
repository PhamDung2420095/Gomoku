#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

const int SCREEN_HEIGHT = 700;
const int SCREEN_WIDTH = 600;
const int GRID_SIZE = 15;
const int TILE_SIZE = SCREEN_WIDTH / GRID_SIZE;
const int MAP_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;
const int MAP_WIDTH = SCREEN_WIDTH / TILE_SIZE;
const int dx[4] = {1, 0, 1, -1};
const int dy[4] = {0, 1, 1, 1};
int CurrentPlayer = 1;
int startX = (SCREEN_WIDTH - GRID_SIZE * TILE_SIZE) / 2;
int startY = (SCREEN_HEIGHT - GRID_SIZE * TILE_SIZE) / 2;

#endif // CONSTANTS_H_INCLUDED
