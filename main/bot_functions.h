#ifndef BOT_FUNC_H
#define BOT_FUNC_H

#include <Arduino.h>
#include <stdbool.h>

//Frequent Varibles
#define MAX_SIZE 4 
#define OPTIMUM_SPEED 150
#define WHEEL_DIAMETER 10.681415

int kp1, ki1, kd1;
int kp2, ki2, kd2;
int kp3, ki3, kd3;
int threshold;
int counts_per_rotation = 170;

/* Input pins */
int mtrpin1_1 ;
int mtrpin1_2 ;
int mtrpin2_1 ;
int mtrpin2_2 ;

int mtrspd1 ;
int mtrspd2 ;

int sens_trig0, sens_echo0;
int sens_trig1, sens_echo1;
int sens_trig2, sens_echo2;
int sens_trig3, sens_echo3;

int ENCA, ENCB, ENCC, ENCD;

int buttonpin ;

//Constants
int count;
bool wall_data[16][16][4];


// Data Types
typedef struct {
    int key;
    int value;
} KeyValuePair;

// Struct for the map
typedef struct {
    KeyValuePair *pairs[MAX_SIZE];
    int size;
} Map;


//bot_functions.c
//Flood-fill Code
void swap(int *x, int *y);
int* minimum_cost(short int arena_map[16][16], short int bot_pos[2], int *sortedArray);
void detect_wall(int face, int pos[2],bool wall_data[][16][4]);
int minimum_value_accessible_neighbors(short int arena_map[16][16], short int pos[2], int *smallest_accessible_regardless,bool wall_data[][16][4]);
void rearrange_map(short int arena_map[16][16], short int base_pos[2],bool wall_data[][16][4]);
bool thresHold(int distance);
int direction_wrt_compass(short int arena_map[16][16], short int bot_pos[2],bool wall_data[][16][4]);
int direction_wrt_bot(short int arena_map[16][16], short int bot_pos[2], int facing,bool wall_data[][16][4]);

//movement.c
//Bot Movement functions
void forward();
void brake();
void backward();
void right();
void left();
void turn_around();
void Motor_SetSpeed(int spdL, int spdR);

//data_structures.c
//Queue
void initialize_queue();
int queue_empty();
int queue_full();
void queue_push (short int x, short int y);
short int* queue_pop ();

// Map
Map *map_init();
void map_put(Map *map, int key, int value);
int map_get(Map *map, int key);
void map_update(Map *map, int key, int value);

//PID Codes
//pid.c
void p2p_pid(int dist);
void sens_pid();
void turn(int angle);
void composite_pid(int dist);

#endif
