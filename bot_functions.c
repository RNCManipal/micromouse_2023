#include <stdio.h>
#include <stdlib.h>

int queue_size;
int queue[]; //queue for storing the path

int* minimum_cost(int **arena_map, int bot_pos[2], int *smallest_value){
    /*
        returns array with 1 if the direction is the smallest cost in [l, s, r, b] format
        to do: check for array out of bound
    */

    int top    = arena_map[bot_pos[0] - 1][bot_pos[1]];
    int bottom = arena_map[bot_pos[0] + 1][bot_pos[1]];
    int left   = arena_map[bot_pos[0]][bot_pos[1] - 1];
    int right  = arena_map[bot_pos[0]][bot_pos[1] + 1];
    int *return_value = calloc (4, sizeof(int));

    if ((left <= top) && (left <= bottom) && (left <= right)){
        *smallest_value = left;
        return_value[0] = 1;
    }
    else{
        return_value[0] = 0;
    }

    if ((top <= bottom) && (top <= left) && (top <= right)){
        *smallest_value = top;
        return_value[1] = 1;
    }
    else{
        return_value[1] = 0;
    }

    if ((right <= top) && (right <= bottom) && (right <= left)){
        *smallest_value = right;
        return_value[2] = 1;
    }
    else{
        return_value[2] = 0;
    }

    if ((bottom <= top) && (bottom <= left) && (bottom <= right)){
        *smallest_value = bottom;
        return_value[3] = 1;
    }
    else{
        return_value[3] = 0;
    }

    return return_value;
}

int* detect_wall(){
    /*Siya needs to update
    returns an array [l, s, r, b] with 1 if wall is detected and 0 if not*/
}

void check_surroundings(int **arena_map, int curr_row, int curr_col, int* wall_array, int smallest_value){
    int row = curr_row;
    int col = curr_col;
    int bot_pos[2] = {row, col};
    
    int smallest_value;
    int min_cost;
    
    add_queue(&queue, queue_size, row, col);

    while (!queue_empty(queue, queue_size)){
        remove_queue(queue, queue_size, &row, &col);

        min_cost = minimum_cost(arena_map, bot_pos, &smallest_value);

        if (arena_map[row][col] <= smallest_value){
            arena_map[row][col] += 1;
            for (int i = 0; i<4; i++){
                if (wall_array[i] == 0){
                    add_queue(&queue, queue_size, row, col);
                }
            }
        }   

    }
}


void final_action(int **arena_map, int bot_pos[2]){
    int *wall_array = detect_wall();
    int smallest_value;
    int min_cost = minimum_cost(arena_map, bot_pos, &smallest_value);

    if (min_cost == 0){
        if (wall_array[0] == 1){

        }
        else{
            left();
        }
    }
    else if (min_cost == 1){
        if (wall_array[1] == 1){

        }
        else{
            forward();
        }
    }
    if (min_cost == 2){
        if (wall_array[2] == 1){

        }
        else{
            right();
        }
    }
    if (min_cost == 3){
        if (wall_array[3] == 1){

        }
        else{
            turn_around();
        }
    }
}