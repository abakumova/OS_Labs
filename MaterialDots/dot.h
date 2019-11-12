//
// Created by Asus on 22.09.2019.
//

#ifndef LABA1TASK0_DOT_H
#define LABA1TASK0_DOT_H

struct materialDot
{
    int weight;
    int Xcoordinate;
    int Ycoordinate;
} ;

typedef struct materialDot Dot;

int comp(const void *elem1, const void *elem2);
void printArrayOfDots(Dot  arrayOfDots[], int length);
double distance(Dot A, Dot B);
void printArrayOfDistance(double arrayOfDistance[], int length);

#endif //LABA1TASK0_DOT_H
