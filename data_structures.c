#include<stdio.h>
#include <stdlib.h>

/*Not done at all, needs to be attempted again from scratch with a circular queue*/


typedef struct queue{
    int row;
    int col;
    int data;
};


int first = -1;
int last = -1;

void add_queue(int *queue, int size, int value){
    if (last == size -1){
        printf("Unsuccessful queue allocation");
    }
    else{
        queue[++last] = value;
        return 1;
    }
}

int remove_queue(int *queue, int size){
    if (first == last){
        return -1;
    }
    else{
        return queue[++first];
    }
}