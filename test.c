#include <stdio.h>
#include <stdlib.h>
#include "data_structures.c"

void swap(int *x, int *y){
    //Swaps values of two  numbers x and y. 
    //Function is complete
    int temp = *x;
    *x = *y;
    *y = temp;
}

int* minimum_cost(short int arena_map[16][16], short int bot_pos[2], int *sortedArray){
    /*
        returns array with [0,1,2,3] as [l,s,r,b] in ascending order of their weights
        Function 90% verified
    */

   //Getting values of neighbors
   int top, left, bottom, right;
   
   //if condition is to check for array out of bound condition
    if (bot_pos[0] == 0){ //if bot is at top row
        top = 1000;
    }
    else{
        top = arena_map[bot_pos[0] - 1][bot_pos[1]];
    }

    if (bot_pos[0] == 15){ //if bot is at bottom row
        bottom = 1000;
    }
    else{
        bottom = arena_map[bot_pos[0] + 1][bot_pos[1]];
    }

    if (bot_pos[1] == 0){ //if bot is at leftmost column
        left = 1000;
    }
    else{
        left = arena_map[bot_pos[0]][bot_pos[1] - 1];
    }

    if (bot_pos[1] == 15){ //if bot is at rightmost column
        right = 1000;
    }
    else{
        right = arena_map[bot_pos[0]][bot_pos[1] + 1];
    }

    int *return_value = calloc (4, sizeof(int)); //array to be returned
    int temp_arr[4] = {left, top, right, bottom}; //array to be sorted
    int smallest =0;
    
    for (int i = 0; i<4; i++){
        return_value[i] =i; //initializing return array to [0,1,2,3]
    }

    //Sorting array (selection sort)
    for (int i  =0 ; i<4; i++){
        smallest = i;
        for (int j = i +1;j<4; j++){
            if (temp_arr[smallest]>temp_arr[j]){ // 9 8 5 5
                smallest = j;
            }
        }

        swap(&temp_arr[i], &temp_arr[smallest]);
        swap(&return_value[i], &return_value[smallest]);
    }

    for (int i =0 ; i<4; i++){ //copying sorted array to sortedArray
        sortedArray[i] = temp_arr[i];
    }

    return return_value;
}

int minimum_value_accessible_neighbors(short int arena_map[16][16], short int pos[2], int wall_array[4], int *smallest_accessible_regardless){
    /*returns 0 for left, 1 for forward, 2 for right, 3 for back, -1 if no minimum accessible neighbors
    Function unverified
    */

    int sortedArray[4]; 
    int *min_cost = minimum_cost(arena_map, pos, sortedArray);

    for (int i =0; i< 4; i++){

        if (arena_map[pos[0]][pos[1]]>sortedArray[i]){ //Checking if current node is greater than minimum accessible neighbors.
            if (wall_array[min_cost[i]] == 0){ //Checking if node is accessible
                return min_cost[i];
            }   
            else{
                continue;
            }
        }

        else{
            if (wall_array[min_cost[i]] == 0){ //Checking if node is accessible
                switch(min_cost[i]){ //assigning smallest_accessible_regardless to the smallest non-accessible neighbor
                    case 0:
                        *smallest_accessible_regardless = arena_map[pos[0]][pos[1] - 1];
                        break;
                    case 1:
                        *smallest_accessible_regardless = arena_map[pos[0] - 1][pos[1]];
                        break;
                    case 2:
                        *smallest_accessible_regardless = arena_map[pos[0]][pos[1] + 1];
                        break;
                    case 3:
                        *smallest_accessible_regardless = arena_map[pos[0] + 1][pos[1]];
                        break;
                    default:
                        break;
                }
                return -1;
            }
        }
    }
}

int init =0;

void rearrange_map(short int arena_map[16][16], short int base_pos[2]){
    //Changes value of map node cost in case the current node has a strictly lower cost than all of its accessible neighbors. Function unverified
    queue_push(base_pos[0], base_pos[1]); //pushing base node to queue
    short int *poped;
    int min_access;
    int *wall_array = calloc (4, sizeof(int));
    int small;

    while (!queue_empty()){
        poped = queue_pop();
        if(init == 0){
            init = 1;
            wall_array[0] = 0;
            wall_array[1] = 0;
            wall_array[2] = 0;
            wall_array[3] = 1;
        }
        else{
            wall_array[0] = 0;
            wall_array[1] = 0;
            wall_array[2] = 0;
            wall_array[3] = 0;
        }
        min_access = minimum_value_accessible_neighbors(arena_map, poped, wall_array, &small); //returns index of minimum value accessible neighbor
        if (min_access == -1){ //if all accessible neighbors have higher cost than current node

            arena_map[poped[0]][poped[1]] = small + 1;

            for (int i = 0; i<4; i++){ //pushing accessible neighbors to queue
                if (wall_array[i] == 0){
                    switch (i){
                        case (0):
                            queue_push(poped[0], poped[1] - 1);
                            break;

                        case (1):
                            queue_push(poped[0] - 1, poped[1]);
                            break;

                        case (2):
                            queue_push(poped[0], poped[1] + 1);
                            break;

                        case (3):
                            queue_push(poped[0] + 1, poped[1]);
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    }
}


int main(){
short int arena_map[16][16] = {
    {14, 14, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
    {5, 12, 13, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
    {12, 14, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},
    {11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},
    {10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},
    { 9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8, 9 },
    { 8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7, 8 },
    { 7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6, 7 },
    { 7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6, 7 },
    { 8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7, 8 },
    { 9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8, 9 },
    {10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},
    {11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},
    {12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},
    {13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
    {14, 10, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
}; //arena node weight map
    short int position[2] = {1, 0};
    initialize_queue();

    rearrange_map(arena_map, position);

    for (int i = 0; i<16; i++){
        for (int j = 0; j<16; j++){
            printf("%d ", arena_map[i][j]);
        }
        printf("\n");
    }
    return 0;
}