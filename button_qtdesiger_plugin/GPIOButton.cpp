#include <QApplication>
#include <string>
#include <QTimer>
#include <QDebug>
#include <sys/shm.h>
#include "GPIOButton.h"

GPIOButton::GPIOButton(QWidget *parent) : QPushButton(parent),
    gpio_pin_(0),
    click_duration_(100)
{

    //Connect to GPIO shared memory
    key_t key = ftok("/proc/cpuinfo",0x84);
    int shmid = shmget(key, sizeof(shared_gpio_state), 0666);
    gpio_state = (shared_gpio_state*)shmat(shmid, (void *)0, 0);

    set_gpio_pin(gpio_pin_);
    set_click_duration(click_duration_);

}


GPIOButton::~GPIOButton(){}


int GPIOButton::gpio_pin(){
    return gpio_pin_;
}

int GPIOButton::click_duration(){
    return click_duration_;
}

void GPIOButton::set_gpio_pin(int pin){
    gpio_pin_=pin;
}

void GPIOButton::set_click_duration(int duration){
    click_duration_=duration;
}


void GPIOButton::set_gpio(bool state){


   if (get_gpio_pin_function() == 0){
       qDebug() << "Set pin " << gpio_pin_ << " to " << (state?"1":"0");
        if (state)
            gpio_state->GPLEV0 |= (1 << gpio_to_bcm2835_map[gpio_pin_]);
        else
            gpio_state->GPLEV0 &= (~(1 << gpio_to_bcm2835_map[gpio_pin_]));
    }

    update();
}


void GPIOButton::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::LeftButton) {
        set_gpio(true);
        QTimer::singleShot(click_duration_, this, SLOT(click_timeout()));
    }
}

void GPIOButton::click_timeout(){

    set_gpio(false);

}

int GPIOButton::
get_gpio_pin_function(){

  int pin = gpio_to_bcm2835_map[gpio_pin_];

  if (pin<10)            return ((gpio_state->GPFSEL0 >> (3*pin))      & 0x7);
  if (pin>=10 && pin<20) return ((gpio_state->GPFSEL1 >> (3*(pin-10))) & 0x7);
  if (pin>=20 && pin<30) return ((gpio_state->GPFSEL2 >> (3*(pin-20))) & 0x7);
  if (pin>=30 && pin<40) return ((gpio_state->GPFSEL3 >> (3*(pin-30))) & 0x7);
  if (pin>=40 && pin<50) return ((gpio_state->GPFSEL4 >> (3*(pin-40))) & 0x7);
  return ((gpio_state->GPFSEL5 >> (3*(pin-50))) & 0x7);

}


