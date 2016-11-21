#include <stdlib.h>
#include <stdio.h>
#include "../pkg/wiringEmuPi/wiringPi/wiringPi.h"
#include <unistd.h>

int main (void){

	wiringPiSetup();
	int i;

	pinMode(0,OUTPUT);

	for (i=0; i<1000; i++) {
		digitalWrite(0,1);
		digitalWrite(0,0);
	}

}

