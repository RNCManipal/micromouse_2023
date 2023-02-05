#include<stdio.h>
#include <stdlib.h>
#define SIZE 3

int ** queue;
int first, last;

void initialize_queue(){
    queue = calloc (SIZE, sizeof(int*));
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

void queue_push (int x, int y){
    if (queue_full()){
        return;
    }

    queue[last] = calloc (2, sizeof(int));
    queue[last][0] = x;
    queue[last][1] = y;
    last = (last+1)%SIZE;
    printf("Done");
}

int* queue_pop (){

    if (queue_empty()){
        return NULL;
    }

    int * temp = queue[first];
    free (queue[first]);
    first = (first + 1)%SIZE;

    return temp;
}

void display(){
    for (int i = first; (i<SIZE)&&(i < last); i++){
        printf (" i =%d %d ", queue[i][0], queue[i][1]);
    }

    if (first > last){
        for (int i = 0; i < last; i++){
            printf (" i =%d %d ", queue[i][0], queue[i][1]);
        }
    }
}

int main(){
    initialize_queue();
    
}