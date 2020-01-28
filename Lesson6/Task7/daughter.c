#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define A 0
#define B 10
#define C 10
#define D 20
#define R 5

int main(int argc, char const *argv[])
{
	int count_shots=atoi(argv[1]);
	// printf("count_shots %i",count_shots);
	int count_good_shots=0;
	// int x=0,y=0;
	double x=0,y=0;
	double x0=((double)(B-A)/2.0)+(double)A;
	double y0=((double)(D-C)/2.0)+(double)C;
	srand(time(NULL)-count_shots);
	for(int i=0;i<count_shots;i++){
		// x=A+rand()%(B-A);
		// y=C+rand()%(D-B);
		x=((double)(A+rand()%(B-A)))+(((double)rand())/(double)RAND_MAX);
		y=((double)(C+rand()%(D-B)))+(((double)rand())/(double)RAND_MAX);
		// printf("x = %f\ty= %f\tRes = %f\n",x,y,(pow(((double)x)-x0,2.0)+pow(((double)y)-y0,2.0)));
		if((pow(x-x0,2.0)+pow(y-y0,2.0))<=pow(R,2))
			count_good_shots++;
	}
	// printf("count_good_shots %i\n", count_good_shots);
	// printf("res %f\n",((double)count_good_shots*100.0)/((double)count_shots));
	return count_good_shots;
}
