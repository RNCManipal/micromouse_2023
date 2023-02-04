#include<stdio.h>
#include <stdlib.h>
#define SIZE 50

/*Still working on it, almost done*/

int ** queue;
int first, last;

int queue_empty(){
    if (first == last){
        return 1;
    }
    return 0;
}

int queue_full(){
    if ((first +1)%SIZE == last){
        return 1;
    }
    return 0;
}

void queue_push (int x, int y){
    if (queue_full()){
        return;
    }

    last = (last+1)%SIZE;
    queue[last] = calloc (2, sizeof(int));
    queue[last][0] = x;
    queue[last][1] = y;
    printf("Done");
}

int* queue_pop (){

    if (queue_empty()){
        return NULL;
    }

    first = (first + 1)%SIZE;
    int * temp = queue[first];
    free (queue[first]);
    return temp;
}

void display(){
    for (int i = first; (i<SIZE)||(i <= last); i++){
        printf (" i =%d %d ", queue[i][0], queue[i][1]);
    }

    if (first > last){
        for (int i = 0; i <= last; i++){
            printf (" i =%d %d ", queue[i][0], queue[i][1]);
        }
    }
}

int main(){
    queue = calloc (SIZE, sizeof(int*));
    first =0;
    last = 0;
    int ch=0;
    int x, y;
    int *pop = calloc (2, sizeof(int));

    while (ch!=3){
        printf("\n Push pop display \n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            scanf("%d %d", &x, &y);
            queue_push(x,y);
            break;
        
        case 1:
            pop = queue_pop();
            break;

        case 2:
            display();
            break;

        default:
            break;
        }
    }

    return 0;
}