#ifndef GPIOBUTTON_H
#define GPIOBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class GPIOButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(int gpio_pin READ gpio_pin WRITE set_gpio_pin)
    Q_PROPERTY(int click_duration READ click_duration WRITE set_click_duration)

public:
    GPIOButton(QWidget *parent = 0);
    ~GPIOButton();

    int gpio_pin();
    int click_duration();
    void set_gpio_pin(int pin);
    void set_click_duration(int duration);
    void set_gpio(bool state);
    int get_gpio_pin_function();

public slots:
  void click_timeout();

protected:
    void mousePressEvent(QMouseEvent *e);


private:

    int gpio_pin_;
    int click_duration_;

    struct shared_gpio_state {

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

    };
    shared_gpio_state *gpio_state;

    const int gpio_to_bcm2835_map[8] = {17,18,21,22,23,24,25,4};


};

#endif // SQUARE_H
