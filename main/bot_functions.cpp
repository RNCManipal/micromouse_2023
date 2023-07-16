#include <stdio.h>
#include <stdlib.h>
#include "bot_functions.h"

/*This project uses flood fill algorithm. Pseudocode is as follows - 
    1. Move mouse to lowest cost node
    2. If all neighbors are higher than or equal to current node, push node to queue.
    3. Pop node from queue
    4. If all neighbors are higher than or equal to current node, change current node's value by minimum value + 1 and push accessible neighbors to queue
    5. Repeat step 3 until queue is empty
    6. Repeat step 1 until current node has 0 cost (end of the maze)

    Code uses a lsrb naming scheme when returning values.
*/

void swap(int *x, int *y){
    //Swaps values of two  numbers x and y. 
    //Function is complete
    int temp = *x;
    *x = *y;
    *y = temp;
}

int* minimum_cost(short int arena_map[6][6], short int bot_pos[2], int *sortedArray){
    /*
        returns array with [0,1,2,3] as [l,s,r,b] in ascending order of their weights
        Function verified
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

    if (bot_pos[0] == 5){ //if bot is at bottom row
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

    if (bot_pos[1] == 5){ //if bot is at rightmost column
        right = 1000;
    }
    else{
        right = arena_map[bot_pos[0]][bot_pos[1] + 1];
    }

    int *return_value = (int *)calloc (4, sizeof(int)); //array to be returned
    int temp_arr[4] = {left, top, right, bottom}; //array to be sorted
    int smallest =0;
    
    for (int i = 0; i<4; i++){
        return_value[i] =i; //initializing return array to [0,1,2,3]
    }

    //Sorting array (selection sort)
    for (int i  =0 ; i<4; i++){
        smallest = i;
        for (int j = i +1;j<4; j++){
            if (temp_arr[smallest]>temp_arr[j]){
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

void trigger(int pinNo){
  digitalWrite (pinNo, LOW);
  delayMicroseconds(2);
  digitalWrite (pinNo, HIGH);
  delayMicroseconds(10);
  digitalWrite (pinNo, LOW);
}

int distance (int pinNo){
  int readv, dis;
  readv = pulseIn(pinNo, HIGH);
  dis = (readv * 0.034) / 2;
  return dis;
}


bool thresHold(int distance){
    if (distance > threshold){
        return 0;
    }
    else{
        return 1;
    }
}

void detect_wall(int face, short int pos[2],bool wall_data[][6][4]){
    /*returns an array [l, s, r, b] with 1 if wall is detected and 0 if not
                       [0,1,2,3]
    ____ s1____    
    |          |    
   s 0        s 2   
    |____s3____|

    // define a data structue map
    /*{
        left: sensor no point towords left,
        top: sensor pointing towards top,
        right: sensor pointing towards right,
        bottom: sensor towards bottom
    }*/
    
    // Head sensor 1
    Map *map = map_init();
    
    trigger(sens_trig2);
    int dis1= distance(sens_echo2);
    trigger(sens_trig1);
    int dis2= distance(sens_echo1);
    trigger(sens_trig0);
    int dis3= distance(sens_echo0);
    trigger(sens_trig3);
    int dis4= distance(sens_echo3);

    int  detection_s0 = thresHold(dis1);
    int  detection_s1 = thresHold(dis2);
    int  detection_s2 = thresHold(dis3);
    int  detection_s3 = thresHold(dis4);

    map_put(map, 0, 0);
    map_put(map, 1, 0);
    map_put(map, 2, 0);
    map_put(map, 3, 0);

    switch(face){
        case 0:
            //  Assuming the the head sensor pointing to left
            //update the map
            /*{
                0: s1,
                1: s2,
                2: s3,
                3: s0
            }*/
            map_update(map, 0, detection_s1);
            map_update(map, 1, detection_s2);
            map_update(map, 2, detection_s3);
            map_update(map, 3, detection_s0);
        break;
        case 1:
            //  Assuming the the head sensor pointing to top
            //update the map
            /*{
                0: s0,
                1: s1,
                2: s2,
                3: s3
            }*/ 
            map_update(map, 0, detection_s0);
            map_update(map, 1, detection_s1);
            map_update(map, 2, detection_s2);
            map_update(map, 3, detection_s3);
        break;
        case 2:
            //  Assuming the the head sensor pointing to right
            //update the map
            /*{
                0: s3,
                1: s0,
                2: s1,
                3: s2
            }*/ 
            map_update(map, 0, detection_s3);
            map_update(map, 1, detection_s0);
            map_update(map, 2, detection_s1);
            map_update(map, 3, detection_s2);
        break;
        case 3:
            //  Assuming the the head sensor pointing to bottom
            //update the map
            /*{
                0: s2,
                1: s3,
                2: s0,
                3: s1
            }*/ 
            map_update(map, 0, detection_s2);
            map_update(map, 1, detection_s3);
            map_update(map, 2, detection_s0);
            map_update(map, 3, detection_s1);
        break;
    }

      // fill the return array with keys values of the map accordingly in the return array
      Serial.print("Wall data: ");
      for(int i =0;i<4;i++){
        wall_data[pos[0]][pos[1]][i] = map_get(map,i);
        Serial.print(wall_data[pos[0]][pos[1]][i]);
    Serial.print(" ");
      }
      Serial.println();
}

int minimum_value_accessible_neighbors(short int arena_map[6][6], short int pos[2], int *smallest_accessible_regardless,bool wall_data[][6][4]){
    /*returns 0 for left, 1 for forward, 2 for right, 3 for back, -1 if no minimum accessible neighbors
    Function verified
    */

    int sortedArray[4]; 
    int *min_cost = minimum_cost(arena_map, pos, sortedArray);

//        Serial.print(sortedArray[0]);
//    Serial.print(" ");
//    Serial.print(sortedArray[1]);
//    Serial.print(" ");
//    Serial.print(sortedArray[2]);
//    Serial.print(" ");
//    Serial.println(sortedArray[3]);
    
    for (int i =0; i< 4; i++){
      Serial.print("min: ");
      Serial.println(sortedArray[i]);
      Serial.print(" pos:");
      Serial.println(min_cost[i]);
        if (arena_map[pos[0]][pos[1]]>sortedArray[i]){ //Checking if current node is greater than minimum accessible neighbors.
            // if (wall_array[min_cost[i]] == 0){ //Checking if node is accessible
            if (wall_data[pos[0]][pos[1]][min_cost[i]] == 0){ //Checking if node is accessible
                return min_cost[i];
            }   
            else{
                continue;
            }
        }

        else{
            if (wall_data[pos[0]][pos[1]][min_cost[i]] == 0){ //Checking if node is accessible
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

void rearrange_map(short int arena_map[6][6], short int base_pos[2],bool wall_data[][6][4]){
    //Changes value of map node cost in case the current node has a strictly lower cost than all of its accessible neighbors. Function verified

    queue_push(base_pos[0], base_pos[1]); //pushing base node to queue
    short int *poped;
    int min_access;
    int small;

    while (!queue_empty()){
        poped = queue_pop();
        if (poped[0]<0 || poped[0]>5 || poped[1]<0 || poped[1]>5){
            continue;
        }
        min_access = minimum_value_accessible_neighbors(arena_map, poped, &small, wall_data); //returns index of minimum value accessible neighbor

        if (min_access == -1){ //if all accessible neighbors have higher cost than current node

            arena_map[poped[0]][poped[1]] = small + 1;

            for (int i = 0; i<4; i++){ //pushing accessible neighbors to queue
                if (wall_data[poped[0]][poped[1]][i] == 0){
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

int direction_wrt_compass(short int arena_map[6][6], short int bot_pos[2], bool wall_data[][6][4]){
    // Checks which direction to move in wrt to a compass. i.e 0=>East, 1=>North, 2=>West, 3=>South. Function unverified

    int *smallest_value;
    int small;
    int min_access;

    do{
        min_access = minimum_value_accessible_neighbors(arena_map, bot_pos, &small, wall_data);

    Serial.print("Direction: ");
    Serial.println(min_access);
        
        switch (min_access){  //lsrb if nodes are equal
            case 0://move east
                return 0;
                break;
            case 1: //move north
                return 1;
                break;
            case 2: //move west
                return 2;
                break;
            case 3: // move south
                return 3;
                break;
            case -1:
                rearrange_map(arena_map, bot_pos, wall_data);
        }

    }while (min_access == -1);
}


int direction_wrt_bot(short int arena_map[6][6], short int bot_pos[2], int facing, bool wall_data[][6][4]){
    /*Decide which direction the both should move in from its perspective*/
    int direction1 = direction_wrt_compass(arena_map, bot_pos, wall_data);

    if (facing == direction1){
        //move forward
        return 1;
    }

    else if (((facing+1)%4 == direction1)){
        //turn right
        return 2;
    }

    else if (facing == (direction1+1)%4){
        //turn left 
        return 0;
    }

    return 3;
}

void position_init(){
    //Initializes the bot so that  it is at the center of the cell.
    //Sensor values of left, right, back should be equal
    //May not be possible if we are not using a back sensor. 
    //In that case, we can use the front sensor to check if the bot is at the center of the cell, but pid should be enough to stabilize itself so shouldnt be a problem.
}
