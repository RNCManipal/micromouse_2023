#ifndef BOT_FUNC_H
#define BOT_FUNC_H
#include <Arduino.h>

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
void detect_wall(int face, int pos[2]);
int minimum_value_accessible_neighbors(short int arena_map[16][16], short int pos[2], int *smallest_accessible_regardless);
void rearrange_map(short int arena_map[16][16], short int base_pos[2]);
int direction_wrt_compass(short int arena_map[16][16], short int bot_pos[2]);
int direction_wrt_bot(short int arena_map[16][16], short int bot_pos[2], int facing);

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
int* queue_pop ();

// Map
void map_put(Map *map, int key, int value);
int map_get(Map *map, int key);
void map_update(Map *map, int key, int value);

#endif
