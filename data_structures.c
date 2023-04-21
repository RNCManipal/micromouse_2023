#include <stdio.h>
#include <stdlib.h>
// #include "bot_functions.h"
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

// int main(){
//     initialize_queue();
//     int ch = 0;
//     int *temp;

//     while (ch!=3){
//         printf ("\n1. Push 2. Pop 3. Exit\n");

//         scanf (" %d", &ch);

//         if (ch == 1){
//             int x, y;
//             scanf ("%d %d", &x, &y);
//             queue_push (x, y);
//         }

//         if (ch == 2){
//             temp = queue_pop();
//             if (temp == NULL){
//                 printf ("\nQueue is empty\n");
//             }
//             else{
//                 printf ("\nPopped %d %d\n", temp[0], temp[1]);
//             }
//         }

//         display(); 
//     }
// }