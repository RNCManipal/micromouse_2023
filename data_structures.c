#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bot_functions.h"
#define MAX_SIZE 4 
#define SIZE 260

short int ** queue;
int first, last;

void initialize_queue(){
    queue = calloc (SIZE, sizeof(short int*));
    first = 0;
    last = 0;
}

int queue_empty(){
    if (first == last){
        return 1;
    }
    return 0;
}

int queue_full(){
    if ((last +1)%SIZE == first){
        return 1;
    }
    return 0;
}

void queue_push (short int x, short int y){
    if (queue_full()){
        return;
    }

    queue[last] = calloc (2, sizeof(short int));
    queue[last][0] = x;
    queue[last][1] = y;
    last = (last+1)%SIZE;
    // printf("Done");
}

short int* queue_pop (){

    if (queue_empty()){
        return NULL;
    }

    // printf("\n%d %d", queue[first][0], queue[first][1]);

    short int *temp = queue[first];

    // printf("\n%d %d", temp[0], temp[1]);

    first = (first + 1)%SIZE;

    return temp;
}

void display(){
    if (queue_empty()){
        // printf ("\nQueue is empty\n");
        return;
    }
    
    if(last>first){
        for(int i=first;i<last;i++)
            printf("\n%d %d\n",queue[i][0], queue[i][1]);
    }
    else
    {
        int i=first;
        while(i<SIZE)
        {
            printf("\n%d %d\n",queue[i][0], queue[i][1]);;
            i++;
        }
        i=0;
        while(i<last)
        {
            printf("\n%d %d\n",queue[i][0], queue[i][1]);
            i++;
        }
    }                     
}

// Map

typedef struct {
    int key;
    int value;
} KeyValuePair;

// Struct for the map
typedef struct {
    KeyValuePair *pairs[MAX_SIZE];
    int size;
} Map;

// Initialize the map
Map *map_init() {
    Map *map = malloc(sizeof(Map));
    map->size = 0;
    return map;
}

// Add a key-value pair to the map
void map_put(Map *map, int key, int value) {
    if (map->size == MAX_SIZE) {
        printf("Map is full!\n");
        return;
    }
    KeyValuePair *pair = malloc(sizeof(KeyValuePair));
    pair->key = key;
    pair->value = value;
    map->pairs[map->size] = pair;
    map->size++;
}

// Get the value associated with a given key
int map_get(Map *map, int key) {
    int i;
    for (i = 0; i < map->size; i++) {
        if (map->pairs[i]->key == key) {
            return map->pairs[i]->value;
        }
    }
    printf("Key not found in map!\n");
    return -1;
}

// Update the value associated with a given key
void map_update(Map *map, int key, int value) {
    int i;
    for (i = 0; i < map->size; i++) {
        if (map->pairs[i]->key == key) {
            map->pairs[i]->value = value;
            return;
        }
    }
    printf("Key not found in map!\n");
}

int main(){
    initialize_queue();
    int ch = 0;
    int *temp;

    while (ch!=3){
        printf ("\n1. Push 2. Pop 3. Exit\n");

        scanf (" %d", &ch);

        if (ch == 1){
            int x, y;
            scanf ("%d %d", &x, &y);
            queue_push (x, y);
        }

        if (ch == 2){
            temp = queue_pop();
            if (temp == NULL){
                printf ("\nQueue is empty\n");
            }
            else{
                printf ("\nPopped %d %d\n", temp[0], temp[1]);
            }
        }

        display(); 
    }
    
    // Map *map = map_init();
    // map_put(map, 1, 10);
    // map_put(map, 2, 20);
    // printf("%d\n", map_get(map, 1));
    // printf("%d\n", map_get(map, 2));
    // map_update(map, 1, 100);
    // printf("%d\n", map_get(map, 1));
    // printf("%d\n", map_get(map, 3));

    return 0;
}
