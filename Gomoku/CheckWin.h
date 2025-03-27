#ifndef CHECKWIN_H_INCLUDED
#define CHECKWIN_H_INCLUDED

bool CheckWin(int player){
    for (int x = 0; x < GRID_SIZE; ++x){
        for (int y = 0; y < GRID_SIZE; ++y){
            if (board[y][x] == player){
                // Kiểm tra hướng ngang
                if (x + 4 < GRID_SIZE && board[y][x + 1] == player && board[y][x + 2] == player && board[y][x + 3] == player && board[y][x + 4] == player)
                    return true;
                // Kiểm tra hướng dọc
                if (y + 4 < GRID_SIZE && board[y + 1][x] == player && board[y + 2][x] == player && board[y + 3][x] == player && board[y + 4][x] == player)
                    return true;
                // Kiểm tra hướng chéo xuống
                if (x + 4 < GRID_SIZE && y + 4 < GRID_SIZE && board[y + 1][x + 1] == player && board[y + 2][x + 2] == player && board[y + 3][x + 3] == player && board[y + 4][x + 4] == player)
                    return true;
                // Kiểm tra hướng chéo lên
                if (x - 4 >= 0 && y + 4 < GRID_SIZE && board[y + 1][x - 1] == player && board[y + 2][x - 2] == player && board[y + 3][x - 3] == player && board[y + 4][x - 4] == player)
                    return true;
            }
        }
    }
    return false;
}

#endif // CHECKWIN_H_INCLUDED
