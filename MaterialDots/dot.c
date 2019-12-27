#include <stdio.h>
#include <math.h>
#include "dot.h"

int comp(const void *elem1, const void *elem2) {
    int f = *((int *) elem1);
    int s = *((int *) elem2);
    if (f > s) return 1;
    if (f < s) return -1;
    return 0;
}

void printArrayOfDots(Dot  arrayOfDots[], int length){
    for (int i = 0; i < length; ++i) {
        printf("%d %d %d \n", arrayOfDots[i].weight, arrayOfDots[i].Xcoordinate, arrayOfDots[i].Ycoordinate);
    }
    printf("\n");
}

void printArrayOfDistance(double arrayOfDistance[], int length){
    for (int i = 0; i < length; ++i) {
        printf("Distance %lf \n", arrayOfDistance[i]);
    }
    printf("\n");
}


double distance(Dot A, Dot B) {
    return sqrt((pow((A.Xcoordinate - B.Xcoordinate), 2) + pow((A.Ycoordinate - B.Ycoordinate), 2)));
}