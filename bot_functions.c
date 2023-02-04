#include <stdio.h>
#include <stdlib.h>

/*This project uses flood fill algorithm. Pseudocode is as follows - 
    1. Move mouse to lowest cost node
    2. If all neighbors are higher than or equal to current node, push node to queue.
    3. increment current node by 1 and push acessible neighbors to queue
    4. repeat step 3 until queue is empty
*/

void swap(int *x, int *y){
    //Swaps values of two  numbers x and y. 
    //Fucntion is complete
    int temp = *x;
    *x = *y;
    *y = temp;
}

int* minimum_cost(int **arena_map, int bot_pos[2]){
    /*
        returns array with [0,1,2,3] as [l,s,r,b] in ascending order
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
            if (temp_arr[i]>temp_arr[j]){
                smallest = j;
            }
            else if (temp_arr[i] == temp_arr[j]){ //if two values are equal, l, s, r, b order is maintained
                if (return_value[i] > return_value[j]){
                    swap(&return_value[i], &return_value[j]);
                }
            }
        }

        swap(&temp_arr[i], &temp_arr[smallest]);
        swap(&return_value[i], &return_value[smallest]);
    }
    return return_value;
}

int* detect_wall(){
    /*Siya needs to update
    returns an array [l, s, r, b] with 1 if wall is detected and 0 if not
    Function unverified*/
}

void rearrange_map(int ** arena_map, int base_pos[2]){
    //Changes value of map node cost in case the current node has a strictly lower cost than all of its accessible neighbors. Function unverified

    queue_push(base_pos[0], base_pos[1]); //pushing base node to queue
    int *poped;
    int min_access;
    int *wall_array;
    int small;

    while (!queue_empty()){
        poped = queue_pop();
        wall_array = detect_wall();
        min_access = minimum_value_accessible_neighbors(arena_map, poped, wall_array, small); //returns index of minimum value accessible neighbor

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

int minimum_value_accessible_neighbors(int ** arena_map, int *pos, int *wall_array, int *smallest_accessible_regardless){
    /*returns 0 for left, 1 for forward, 2 for right, 3 for back, -1 if no minimum accessible neighbors
    Function unverified
    */

    int *min_cost = minimum_cost(arena_map, pos);

    for (int i =0; i< 4; i++){

        if (arena_map[pos[0]][pos[1]]>min_cost[i]){ //Checking if current node is greater than minimum accessible neighbors.
            if (wall_array[min_cost[i]] == 0){ //Checking if node is accessible
                return i;
            }   
            else{
                continue;
            }
        }

        else{
            if (wall_array[min_cost[i]] == 0){ //Checking if node is accessible
                switch(i){ //assigning smallest_accessible_regardless to the smallest non-accessible neighbor
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

int final_action(int **arena_map, int bot_pos[2]){
    // Main function that decided the action to be taken. Function unverified

    int *smallest_value;
    int *wall_array = detect_wall();
    int small;
    int min_access;

    do{
        min_access = minimum_value_accessible_neighbors(arena_map, bot_pos, wall_array, &small);
        switch (min_access){
            case 0://move left
                return 0;
                break;
            case 1: //move forward
                return 1;
                break;
            case 2: //move right
                return 2;
                break;
            case 3: // turn around
                return 3;
                break;
            case -1:
                rearrange_map(arena_map, bot_pos);
        }
    }while (min_access != -1);
}