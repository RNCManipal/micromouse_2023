#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 4 

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
    Map *map = map_init();
    map_put(map, 1, 10);
    map_put(map, 2, 20);
    printf("%d\n", map_get(map, 1));
    printf("%d\n", map_get(map, 2));
    map_update(map, 1, 100);
    printf("%d\n", map_get(map, 1));
    printf("%d\n", map_get(map, 3));
    return 0;

}