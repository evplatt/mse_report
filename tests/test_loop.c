#include <stdlib.h>
#include <stdio.h>
#include "../pkg/wiringEmuPi/wiringPi/wiringPi.h"

int main (void){

	wiringPiSetup();
	int i;

	for (i=0; i<4; i++) pinMode(i,OUTPUT);
	for (i=4; i<8; i++) pinMode(i,INPUT);

	while(1){
		for (i=4; i<8; i++){
			digitalWrite(i-4,digitalRead(i));
		}		
	}
}

