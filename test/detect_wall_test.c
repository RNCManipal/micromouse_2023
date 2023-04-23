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

int *detect_wall(int face){
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
    
    int  detection_s0 =1;//sensor_output();
    int  detection_s1 = 0;//sensor_output();
    int  detection_s2 = 1;//sensor_output();
    int  detection_s3 = 0;//sensor_output();
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
      int *return_value = calloc (4, sizeof(int));
      for(int i =0;i<4;i++){
        return_value[i]= map_get(map,i);
      }

    return return_value;
}

int main(){
    for (int i=0;i<4;i++)
    printf("%d",*(detect_wall(3)+i));

    return 0;
}