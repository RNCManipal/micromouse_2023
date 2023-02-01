#include <stdio.h>


int minimum_cost(int arena_map[16][16], int bot_pos[2]){
    /*
        returns 0 for left, 1 for straight, 2 for right, and 3 for back
    */

    int top    = bot_pos[0] + 1;
    int bottom = bot_pos[0] - 1;
    int left   = bot_pos[1] - 1;
    int right  = bot_pos[1] + 1;

    if ((left <= top) && (left <= bottom) && (left <= right)){
        return 0;
    }

    else if ((top <= bottom) && (top <= left) && (top <= right)){
        return 1;
    }

    else if ((right <= top) && (right <= bottom) && (right <= left)){
        return 2;
    }

    else if ((bottom <= top) && (bottom <= left) && (bottom <= right)){
        return 3;
    }
}