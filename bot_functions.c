#include <stdio.h>
#include <stdlib.h>

int queue_size;
int queue[]; //queue for storing the path

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int* minimum_cost(int **arena_map, int bot_pos[2]){
    /*
        returns arnray with [0,1,2,3] as [l,s,r,b] in ascending order
        to do: check for array out of bound
    */

    int top    = arena_map[bot_pos[0] - 1][bot_pos[1]];
    int bottom = arena_map[bot_pos[0] + 1][bot_pos[1]];
    int left   = arena_map[bot_pos[0]][bot_pos[1] - 1];
    int right  = arena_map[bot_pos[0]][bot_pos[1] + 1];
    int *return_value = calloc (4, sizeof(int));
    int temp_arr[4] = {left, top, right, bottom};
    int smallest =0, temp = 0;
    
    for (int i = 0; i<4; i++){
        return_value[i] =i;
    }

    //Sorting array
    for (int i  =0 ; i<4; i++){
        smallest = i;
        for (int j = i +1;j<4; j++){
            if (temp_arr[i]>temp_arr[j]){
                smallest = j;
            }
        }
        swap(temp_arr[i], temp_arr[smallest]);
        swap(return_value[i], return_value[smallest]);
    }

    return return_value;
}

int* detect_wall(){
    /*Siya needs to update
    returns an array [l, s, r, b] with 1 if wall is detected and 0 if not*/
}

void rearrange_map(int ** arena_map, int base_pos[2]){
    /*Not Complete*/
    queue_push(base_pos[0], base_pos[1]);
    int *poped;
    int min_access;
    while (!queue_empty()){
        poped = queue_pop();
        min_access = minimum_value_accessible_neighbors(arena_map, base_pos);
    }
    // for (int i = 0; i<4; i++){
    //     if (wall_array[i] == 0){
    //         switch(i){
    //             case 0:
    //                 queue_push(base_pos[0], base_pos[1] -1);
    //                 break;
    //             case 1:
    //                 queue_push(base_pos[0]-1, base_pos[1]);
    //                 break;
    //             case 2: 
    //                 queue_push(base_pos[0], base_pos[1] -1);
    //                 break;
    //             case 3: 
    //                 queue_push(base_pos[0]+1, base_pos[1]);
    //                 break;
    //         }
    //     }
    // }
}


void final_action(int **arena_map, int bot_pos[2]){
    int *smallest_value;
    int min_access = minimum_value_accessible_neighbors(arena_map, bot_pos);

    switch (min_access){
        case 0://move left
            break;
        case 1: //move forward
            break;
        case 2: //move right
            break;
        case 3: // turn around
            break;
        case -1:
            rearrange_map(arena_map, bot_pos);
    }
}

int minimum_value_accessible_neighbors(int ** arena_map, int pos[2]){
    int *wall_array = detect_wall();
    int *min_cost = minimum_cost(arena_map, pos);
    for (int i =0; i< 4; i++){
        if (arena_map[pos[0]][pos[1]]>min_cost[i]){
            //check for obstacles in path, if obstacle continue;
            return i;
        }
        else{
            return -1;
        }
    }
}