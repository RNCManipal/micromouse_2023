#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include "data_structures.c"
using namespace std;

 bool wall_data[6][6][4];
bool dup_arr[6][6][4]={
    {{1,1,0,1},{0,1,0,0},{0,1,0,0},{0,1,1,1},{1,1,0,0},{0,1,1,1}},
    {{1,1,0,0},{0,0,1,1},{1,0,0,1},{0,1,0,1},{0,0,0,1},{0,1,1,0}},
    {{1,0,0,0},{1,1,1,0},{1,1,0,0},{0,1,1,0},{1,1,1,0},{1,0,1,0}},
    {{1,0,1,0},{1,0,1,0},{1,0,0,1},{0,0,1,0},{1,0,0,0},{0,0,1,1}},
    {{1,0,1,0},{1,0,0,0},{0,1,0,0},{0,0,0,1},{0,0,0,1},{0,1,1,1}},
    {{1,0,1,1},{1,0,1,1},{1,0,0,1},{0,1,0,1},{0,1,0,1},{0,1,1,1}}
};

bool visited[6][6]={
    
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
};



void swap(int *x, int *y){
    //Swaps values of two  numbers x and y. 
    //Function is complete
    int temp = *x;
    *x = *y;
    *y = temp;
}

int* minimum_cost2(short int arena_map[6][6], short int bot_pos[2], int *sortedArray_fast_run){
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

    int *return_value_fast_run = (int *)calloc (4, sizeof(int)); //array to be returned
    int temp_arr[4] = {left, top, right, bottom}; //array to be sorted
    int smallest =0;
    
    for (int i = 0; i<4; i++){
        return_value_fast_run[i] =i; //initializing return array to [0,1,2,3]
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
        swap(&return_value_fast_run[i], &return_value_fast_run[smallest]);
    }

    for (int i =0 ; i<4; i++){ //copying sorted array to sortedArray
        sortedArray_fast_run[i] = temp_arr[i];
    }

    return return_value_fast_run;
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


int minimum_value_accessible_neighbors2(short int arena_map[6][6], short int pos[2], int *smallest_accessible_regardless_fast_run,bool wall_data[][6][4]){
    /*returns 0 for left, 1 for forward, 2 for right, 3 for back, -1 if no minimum accessible neighbors
    Function verified
    */

    int sortedArray_fast_run[4]; 
    int *min_cost = minimum_cost2(arena_map, pos, sortedArray_fast_run);

//        Serial.print(sortedArray[0]);
//    Serial.print(" ");
//    Serial.print(sortedArray[1]);
//    Serial.print(" ");
//    Serial.print(sortedArray[2]);
//    Serial.print(" ");
//    Serial.println(sortedArray[3]);
    
    for (int i =0; i< 4; i++){
    //   Serial.print("min: ");
    //   Serial.println(sortedArray[i]);
    //   Serial.print(" pos:");
    //   Serial.println(min_cost[i]);

        if (arena_map[pos[0]][pos[1]]>sortedArray_fast_run[i]){ //Checking if current node is greater than minimum accessible neighbors.
            if (wall_data[pos[0]][pos[1]][min_cost[i]] == 0){ //Checking if node is accessible
                return min_cost[i];
            }   
            else{
                continue;
            }
        }

        else{
            if (wall_data[pos[0]][pos[1]][min_cost[i]] == 0){ //Checking if node is accessible
              
                return -1;
            }
        }
    }
}



// minimum_value_accessible_neighbors(arena_map, poped, &small, wall_data)
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
    //   Serial.print("min: ");
    //   Serial.println(sortedArray[i]);
    //   Serial.print(" pos:");
    //   Serial.println(min_cost[i]);

        if (arena_map[pos[0]][pos[1]]>sortedArray[i]){ //Checking if current node is greater than minimum accessible neighbors.
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



//  rearrange_map(arena_map, bot_pos, wall_data);
void rearrange_map(short int arena_map[6][6], short int base_pos[2],bool wall_data[][6][4]){
    //Changes value of map node cost in case the current node has a strictly lower cost than all of its accessible neighbors. Function verified

    queue_push(base_pos[0], base_pos[1]); //pushing base node to queue
    short int *poped;
    int min_access;
    int small;

    while (!queue_empty()){
        poped = queue_pop();
        min_access = minimum_value_accessible_neighbors(arena_map, poped, &small, wall_data); //returns index of minimum value accessible neighbor
        if (poped[0]<0 || poped[0]>5 || poped[1]<0 || poped[1]>5){
            continue;
        }
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


int direction_wrt_compass2(short int arena_map[6][6], short int bot_pos[2], bool wall_data[][6][4]){
    // Checks which direction to move in wrt to a compass. i.e 0=>East, 1=>North, 2=>West, 3=>South. Function unverified

    int *smallest_value;
    int small_fast_run;
    int min_access;

    

   min_access = minimum_value_accessible_neighbors2(arena_map, bot_pos, &small_fast_run, wall_data);

   
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
            return -1;
            break;
    }
   
}


int direction_wrt_compass(short int arena_map[6][6], short int bot_pos[2], bool wall_data[][6][4]){
    // Checks which direction to move in wrt to a compass. i.e 0=>East, 1=>North, 2=>West, 3=>South. Function unverified

    int *smallest_value;
    int small;
    int min_access;

    do{
        min_access = minimum_value_accessible_neighbors(arena_map, bot_pos, &small, wall_data);

    // Serial.print("Direction: ");
    // Serial.println(min_access);
        
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


int direction_wrt_bot2(short int arena_map[6][6], short int bot_pos[2], int facing, bool wall_data[][6][4]){
    //Decide which direction the both should move in from its perspective
    int direction1 = direction_wrt_compass2(arena_map, bot_pos, wall_data);
    if(direction1==-1){
      return-1;
    }
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



int direction_wrt_bot(short int arena_map[6][6], short int bot_pos[2], int fast_run_facing, bool wall_data[][6][4]){
    //Decide which direction the both should move in from its perspective
    int direction1 = direction_wrt_compass(arena_map, bot_pos, wall_data);

    if (fast_run_facing == direction1){
        //move forward
        return 1;
    }

    else if (((fast_run_facing+1)%4 == direction1)){
        //turn right
        return 2;
    }

    else if (fast_run_facing == (direction1+1)%4){
        //turn left 
        return 0;
    }

    return 3;
}


int find_req_facing(int turn_direction, int facing){
    switch (turn_direction){
        case 0:
            // printf("Turn left\n");
            facing = facing - 1;
            if (facing == -1){
                facing = 3;
            }        
            break;

        case 1:
            // printf("Move forward\n");        
            break; //Facing the correct node

        case 2:
            facing = (facing + 1)%4;
            // printf("Turn right\n");       
            break;

        case 3:
            facing = (facing + 2)%4;       
            // printf("Turn back\n");
            break;

        default:
            // Serial.println("Not possible");
            break;
    }

   return facing;
}

void known_path_travel( short int fast_run_position[2],short int arena_map[6][6],int fast_run_facing){
   int starting_val=arena_map[fast_run_position[0]][fast_run_position[1]];
   int curr_facing=fast_run_facing;
   int i=0;
   int row=starting_val;
   int col=2;
   int** fast_run_arr=new int* [row];  //put this part to data_structures.c
    for(int k=0; k<row; k++){
      fast_run_arr[k]=new int[col];
    }                               //till here
    int count_s=0;
   while(starting_val!=-1 && visited[fast_run_position[0]][fast_run_position[1]]){
        cout<<endl;
        cout<<"{"<<fast_run_position[0]<<" , "<<fast_run_position[1]<<" } " <<endl;
        int req_facing;
        //number of box to travel straight
        int turn_direction = direction_wrt_bot2(arena_map, fast_run_position, fast_run_facing, wall_data);
        if(turn_direction==-1){   //means there is no smaller number in arena-map around current position
            break;
        }
        req_facing=find_req_facing(turn_direction,fast_run_facing);

        if(curr_facing==req_facing){
            switch(req_facing){   //Update current position
                case 0:
                    fast_run_position[1] -= 1;
                    break;

                case 1:
                    fast_run_position[0] -= 1;
                    break;

                case 2:
                    fast_run_position[1] += 1;
                    break;

                case 3:
                    fast_run_position[0] += 1;
                    break;
            }   
        }

        cout<<"box to go"<<"{"<<fast_run_position[0]<<" , "<<fast_run_position[1]<<" } " <<endl;
        cout<<"curr_facing"<<curr_facing<<endl;
        cout<<"req_facing"<<req_facing<<endl;
        if(curr_facing==req_facing){
            count_s++;
            fast_run_arr[i][0]=count_s;
            fast_run_arr[i][1]=-1;
            
            curr_facing=req_facing;
        }else if(curr_facing!=req_facing){
            int req_count_90_turns=0;
            
            
            req_count_90_turns=req_facing - curr_facing;
            if(req_count_90_turns<0){
                req_count_90_turns=4+req_count_90_turns;
            }
            curr_facing=req_facing;
            fast_run_arr[i][1]=req_count_90_turns;
            // cout<<"Number of boxes to move straight: "<<fast_run_arr[i][0]<<endl;
            // cout<<"Number of 90* turns req: "<<fast_run_arr[i][1]<<endl;
            count_s=0;
            i++;
            // cout<<endl;
            // cout<<endl;
        }
    }
    for(int j=0; j<starting_val; j++){
       cout<<"box to travel "<<fast_run_arr[j][0]<< "  "<<"box to turn "<<fast_run_arr[j][1]<<endl;
       cout<<endl;
       
    }
    // cout<<"box to travel "<<fast_run_arr[i][0]<<endl;
    // cout<<"box to turn "<<fast_run_arr[i][1]<<endl;
    // cout<<"exited the while loop"<<endl;
}

int main(){
 
    short int arena_map[6][6] = {
    
        {4,3,2,2,3,4},
        {3,2,1,1,2,3},
        {2,1,0,0,1,2},
        {2,1,0,0,1,2},
        {3,2,1,1,2,3},
        {4,3,2,2,3,4},
    
    };

    
    short int position[2] = {5,0};
    // short int fast_run_position[2];
    // for(int i=0; i<2; i++){
    //     fast_run_position[i]=position[i];
    // }  //or we can hardcode the value above without using for loop;

    visited[position[0]][position[1]]=1;
    initialize_queue();
    int facing = 1;
    int fast_run_facing;

    while (true){
        
        // printf("Wall data for current node: \n");
        for (int i =0 ; i<4; i++){
            int temp;
            wall_data[position[0]][position[1]][i] = dup_arr[position[0]][position[1]][i];
            
        
            if(!(position[1]-1<0)){
                wall_data[position[0]][position[1]-1][2]=wall_data[position[0]][position[1]][0];
            }
            if(!(position[0]-1<0)){
                wall_data[position[0]-1][position[1]][3]=wall_data[position[0]][position[1]][1];
            }    
            if(!(position[1]+1>5)){
                wall_data[position[0]][position[1]+1][0]=wall_data[position[0]][position[1]][2];
            }     
            if(!(position[0]+1>5)){
                wall_data[position[0]+1][position[1]][1]=wall_data[position[0]][position[1]][3];
            }
            
            
            // printf("%d ", wall_data[position[0]][position[1]][i]);
        }
        // printf("\n");

        if (arena_map[position[0]][position[1]] == 0){
            printf("Reached center!\n");
            printf("visited  data\n");
                for (int i =0 ; i<6; i++){
                  for (int j =0; j<6; j++){
                        printf("%d ", visited[i][j]);
                    }
                printf("\n");
                } 
               
            printf("\n");
            printf("Map data\n");
            for (int i =0 ; i<6; i++){
                for (int j =0; j<6; j++){
                    printf("%d ", arena_map[i][j]);
                }
                printf("\n");
            } 
            short int fast_run_position[2]={5,0};
            fast_run_facing=1;
            known_path_travel(fast_run_position,arena_map,fast_run_facing);

            int a;
            scanf("%d",&a);
            if(a==1){
                  
                position[0] = 5;
                position[1] =0;
                initialize_queue();
                int facing = 1;
                continue;
            }else{
               return 0;
               break;
            }
            
        }

        int turn_direction = direction_wrt_bot(arena_map, position, facing, wall_data); //Decide direction to turn to so as to face the correct node
        // printf("Turn direction: %d\n", turn_direction);

        switch (turn_direction){
            case 0:
                // printf("Turn left\n");
                facing = facing - 1;
                if (facing == -1){
                    facing = 3;
                }
                break;

            case 1:
                // printf("Move forward\n");
                break; //Facing the correct node

            case 2:
                facing = (facing + 1)%4;
                // printf("Turn right\n");
                break;

            case 3:
                facing = (facing + 2)%4;
                // printf("Turn back\n");
                break;

            default:
                // Serial.println("Not possible");
                break;
        }

        switch(facing){ //Update current position
            case 0:
                position[1] -= 1;
                break;

            case 1:
                position[0] -= 1;
                break;

            case 2:
                position[1] += 1;
                break;

            case 3:
                position[0] += 1;
                break;
        }
        visited[position[0]][position[1]]=1;

        printf("Current position: %d %d\n", position[0], position[1]);
        printf("Current facing: %d\n", facing);
                
    }
    
    
    return 0;
}