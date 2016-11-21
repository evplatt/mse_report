#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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

static char *functions[] = {"In","Out","Alt1","Alt2","Alt3","Alt4","Alt5"};

void print_state(shared_gpio_state *state);
void copy_state(shared_gpio_state* from, shared_gpio_state* to);

void main(void){

  key_t key;
  int shmid=-1;
  int init=1;
  shared_gpio_state *state;
  shared_gpio_state *last_state;

  last_state = (shared_gpio_state *)malloc(sizeof(shared_gpio_state));

  key = ftok("/proc/cpuinfo",0x84);
  shmid = shmget(key, sizeof(shared_gpio_state), 0666);
  state = shmat(shmid, (void *)0, 0);

  while (1){

    if (init==1 || (init==0 &&
      ((state->GPFSEL0 != last_state->GPFSEL0) ||
      (state->GPFSEL1 != last_state->GPFSEL1) ||
      (state->GPFSEL2 != last_state->GPFSEL2) ||
      (state->GPFSEL3 != last_state->GPFSEL3) ||
      (state->GPFSEL4 != last_state->GPFSEL4) ||
      (state->GPFSEL5 != last_state->GPFSEL5) ||
      (state->outstate0 != last_state->outstate0) ||
      (state->outstate1 != last_state->outstate1)))
    ){
        print_state(state);
    }
    copy_state(state,last_state);
    init=0;

    sleep(1);
  }

}

void print_state(shared_gpio_state *state){

  printf("\tFunc\tLVL\tOutput\n");
  printf("GPIO0\t%s\t%i\t%i\n",functions[(int)((state->GPFSEL1 >> 21) & 0x7)],(state->GPLEV0 &   0x20000 ? 1 : 0),(state->outstate0 &   0x20000 ? 1 : 0));  // GPIO0 <=> BCM2385 GPIO17
  printf("GPIO1\t%s\t%i\t%i\n",functions[(int)((state->GPFSEL1 >> 24) & 0x7)],(state->GPLEV0 &   0x40000 ? 1 : 0),(state->outstate0 &   0x40000 ? 1 : 0));  // GPIO1 <=> BCM2385 GPIO18
  printf("GPIO2\t%s\t%i\t%i\n",functions[(int)((state->GPFSEL2 >>  3) & 0x7)],(state->GPLEV0 &  0x200000 ? 1 : 0),(state->outstate0 &  0x200000 ? 1 : 0));  // GPIO2 <=> BCM2385 GPIO21
  printf("GPIO3\t%s\t%i\t%i\n",functions[(int)((state->GPFSEL2 >>  6) & 0x7)],(state->GPLEV0 &  0x400000 ? 1 : 0),(state->outstate0 &  0x400000 ? 1 : 0));  // GPIO3 <=> BCM2385 GPIO22
  printf("GPIO4\t%s\t%i\t%i\n",functions[(int)((state->GPFSEL2 >>  9) & 0x7)],(state->GPLEV0 &  0x800000 ? 1 : 0),(state->outstate0 &  0x800000 ? 1 : 0));  // GPIO4 <=> BCM2385 GPIO23
  printf("GPIO5\t%s\t%i\t%i\n",functions[(int)((state->GPFSEL2 >> 12) & 0x7)],(state->GPLEV0 & 0x1000000 ? 1 : 0),(state->outstate0 & 0x1000000 ? 1 : 0));  // GPIO5 <=> BCM2385 GPIO24
  printf("GPIO6\t%s\t%i\t%i\n",functions[(int)((state->GPFSEL2 >> 15) & 0x7)],(state->GPLEV0 & 0x2000000 ? 1 : 0),(state->outstate0 & 0x2000000 ? 1 : 0));  // GPIO6 <=> BCM2385 GPIO25
  printf("GPIO7\t%s\t%i\t%i\n",functions[(int)((state->GPFSEL0 >> 12) & 0x7)],(state->GPLEV0 &      0x10 ? 1 : 0),(state->outstate0 &      0x10 ? 1 : 0));  // GPIO7 <=> BCM2385 GPIO4
  printf("\n");

}

void copy_state(shared_gpio_state* from, shared_gpio_state* to){

  to->GPFSEL0=from->GPFSEL0;
  to->GPFSEL1=from->GPFSEL1;
  to->GPFSEL2=from->GPFSEL2;
  to->GPFSEL3=from->GPFSEL3;
  to->GPFSEL4=from->GPFSEL4;
  to->GPFSEL5=from->GPFSEL5;
  to->GPLEV0=from->GPLEV0;
  to->GPLEV1=from->GPLEV1;
  to->outstate0=from->outstate0;
  to->outstate1=from->outstate1;


}
