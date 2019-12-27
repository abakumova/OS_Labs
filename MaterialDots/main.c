#include <stdio.h>
#include <stdlib.h>
#include "dot.h"

#define NumberOfDots 5

int main() {

    Dot *pointerArrayOfDots;
    Dot *pointerArrayOfDots1;
    double *pointerArrayOfDistance;
    double minValue;
    int minIndex;

    pointerArrayOfDots = (Dot*)malloc(NumberOfDots * sizeof(Dot));

    pointerArrayOfDots[0].weight=8;
    pointerArrayOfDots[0].Xcoordinate=0;
    pointerArrayOfDots[0].Ycoordinate=0;

    pointerArrayOfDots[1].weight=5;
    pointerArrayOfDots[1].Xcoordinate=0;
    pointerArrayOfDots[1].Ycoordinate=5;

    pointerArrayOfDots[2].weight=7;
    pointerArrayOfDots[2].Xcoordinate=3;
    pointerArrayOfDots[2].Ycoordinate=4;

    pointerArrayOfDots[3].weight=4;
    pointerArrayOfDots[3].Xcoordinate=2;
    pointerArrayOfDots[3].Ycoordinate=2;

    pointerArrayOfDots[4].weight=6;
    pointerArrayOfDots[4].Xcoordinate=5;
    pointerArrayOfDots[4].Ycoordinate=1;

    for (int i = 0; i < (NumberOfDots - 1); i++) {

        printf("Step -  %d \n", i+1);


        printArrayOfDots(pointerArrayOfDots, NumberOfDots-i);
        qsort(pointerArrayOfDots, NumberOfDots-i, sizeof(Dot), comp);


        //distance
        pointerArrayOfDistance = (double*)malloc((NumberOfDots - (i+1)) * sizeof(double));

        for (int j = 1; j < NumberOfDots - i ; ++j) {
            pointerArrayOfDistance[j - 1] = distance(pointerArrayOfDots[0], pointerArrayOfDots[j]);
        }

        printArrayOfDistance(pointerArrayOfDistance, (NumberOfDots-(i+1)));

        //index of min distance
        minValue = pointerArrayOfDistance[0];
        minIndex = 0;

        for (int u = 1; u < NumberOfDots - (i+1); u++) {
            if (minValue > pointerArrayOfDistance[u]){
                minValue = pointerArrayOfDistance[u];
                minIndex = u;
            }
        }

        //operation
        pointerArrayOfDots[minIndex+1].weight += pointerArrayOfDots[0].weight;
        pointerArrayOfDots[0].weight=-222222;
        pointerArrayOfDots[0].Xcoordinate=-222222;
        pointerArrayOfDots[0].Ycoordinate=-222222;

        pointerArrayOfDots1 = (Dot*)malloc((NumberOfDots - (i+1))* sizeof(Dot));
        for (int u = 0; u < (NumberOfDots - (i+1)); u++) {
            pointerArrayOfDots1[u]=pointerArrayOfDots[u+1];
        }

        printArrayOfDots(pointerArrayOfDots1, (NumberOfDots - (i+1)));
        free(pointerArrayOfDots);
        pointerArrayOfDots = pointerArrayOfDots1;
        free(pointerArrayOfDistance);
    }
    return EXIT_SUCCESS;
}

