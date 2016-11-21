#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../pkg/wiringEmuPi/wiringPi/wiringPi.h"

int main (void){

	int i,j;
	struct timespec start, end;
	int times[1000];
	double totaltime;


	for (j=0;j<1000;j++){

		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

		i = 1;


		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
		double t_ns = (double)(end.tv_sec - start.tv_sec) * 1.0e9 +
			(double)(end.tv_nsec - start.tv_nsec);
		times[j] = t_ns;
		totaltime += t_ns; 		
	}

	for (i=0; i<1000; i++){
		printf("%i\n",times[i]);
	}

	printf("%f\n",(totaltime/1000));

}

