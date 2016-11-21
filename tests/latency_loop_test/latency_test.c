#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define NUM_TRIALS 1000

typedef struct shared_gpio_state {

  unsigned int GPFSEL0;
  unsigned int GPFSEL1;
  unsigned int GPFSEL2;
  unsigned int GPFSEL3;
  unsigned int GPFSEL4;
  unsigned int GPFSEL5;
  unsigned int GPLEV0;
  unsigned int GPLEV1;
  unsigned int outstate0;
  unsigned int outstate1;

} shared_gpio_state;

void main(void){

  shared_gpio_state *state;
  struct timespec start, end;
  int i;
  int times[NUM_TRIALS];
  double totaltime;

  key_t key = ftok("/proc/cpuinfo",0x84);
  int shmid = shmget(key, sizeof(shared_gpio_state), 0666);
  state = shmat(shmid, (void *)0, 0);

  for (i=0; i<NUM_TRIALS; i++){

    state->GPLEV0 &= ~(1 << 23); //Clear GPIO 4 input

    usleep(10);

    state->GPLEV0 |= (1 << 23); //Set GPIO 4 input

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); // get initial time-stamp

    while((state->outstate0 & (1 << 17)) == 0){}  //Wait for GPIO 0 output

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);   // get final time-stamp

    double t_ns = (double)(end.tv_sec - start.tv_sec) * 1.0e9 +
              (double)(end.tv_nsec - start.tv_nsec);

    times[i]=t_ns;
    totaltime += t_ns;

  }

  for (i=0; i<NUM_TRIALS; i++){
    printf("%i\n",times[i]);
  }
	
  printf("%f\n",(totaltime/NUM_TRIALS));

}
