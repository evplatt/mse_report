#include <math.h>

#include <QPainter>
#include <QGradient>
#include <QPaintDevice>
#include <QTimer>
#include <QDebug>
#include <sys/shm.h>
#include "LED.h"

LED::
LED(QWidget* parent) :
	QWidget(parent),
	diameter_(5),
	color_(QColor("red")),
	alignment_(Qt::AlignCenter),
	initialState_(true),
	state_(true),
  gpio_pin_(0),
  refresh_rate_(10)
{

    setDiameter(diameter_);
    set_gpio_pin(gpio_pin_);
    set_refresh_rate(refresh_rate_);

    connect_gpio();

    gpio_timer_ = new QTimer(this);
    connect(gpio_timer_, SIGNAL(timeout()), this, SLOT(gpio_refresh()));

    //start gpio readings
    gpio_timer_->start(refresh_rate_);

}

LED::
~LED()
{
}

void LED::
connect_gpio()
{

    key_t key = ftok("/proc/cpuinfo",0x84);
    int shmid = shmget(key, sizeof(shared_gpio_state), 0666);
    if (shmid == -1) qDebug() << "Error connecting to shared memory";
    gpio_state = (shared_gpio_state*)shmat(shmid, (void *)0, 0);

    update();

}

double LED::
diameter() const
{
	return diameter_;
}

void LED::
setDiameter(double diameter)
{
	diameter_ = diameter;

	pixX_ = round(double(height())/heightMM());
	pixY_ = round(double(width())/widthMM());

	diamX_ = diameter_*pixX_;
	diamY_ = diameter_*pixY_;

	update();
}


QColor LED::
color() const
{
	return color_;
}

void LED::
setColor(const QColor& color)
{
	color_ = color;
	update();
}

Qt::Alignment LED::
alignment() const
{
	return alignment_;
}

void LED::
setAlignment(Qt::Alignment alignment)
{
	alignment_ = alignment;

	update();
}

void LED::
set_gpio_pin(int gpio_pin)
{
    gpio_pin_ = gpio_pin;

    update();
}

void LED::
set_refresh_rate(int refresh_rate)
{
    refresh_rate_ = refresh_rate;

    update();
}

void LED::
setState(bool state)
{
	state_ = state;
	update();
}


void LED::
gpio_refresh()
{

    //make sure it's an output then set the LED state
    if (get_gpio_pin_function() == 1) state_ = ((gpio_state->outstate0 & (1 << gpio_to_bcm2835_map[gpio_pin_])) > 0);
    else state_ = false;

    update();
}

int LED::
heightForWidth(int width) const
{
	return width;
}

QSize LED::
sizeHint() const
{
	return QSize(diamX_, diamY_);
}

QSize LED::
minimumSizeHint() const
{
	return QSize(diamX_, diamY_);
}

void LED::
paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

	QPainter p(this);

	QRect geo = geometry();
	int width = geo.width();
	int height = geo.height();

	int x=0, y=0;
	if ( alignment_ & Qt::AlignLeft )
		x = 0;
	else if ( alignment_ & Qt::AlignRight )
		x = width-diamX_;
	else if ( alignment_ & Qt::AlignHCenter )
		x = (width-diamX_)/2;
	else if ( alignment_ & Qt::AlignJustify )
		x = 0;

	if ( alignment_ & Qt::AlignTop )
		y = 0;
	else if ( alignment_ & Qt::AlignBottom )
		y = height-diamY_;
	else if ( alignment_ & Qt::AlignVCenter )
		y = (height-diamY_)/2;

	QRadialGradient g(x+diamX_/2, y+diamY_/2, diamX_*0.4,
		diamX_*0.4, diamY_*0.4);

	g.setColorAt(0, Qt::white);
	if ( state_ )
		g.setColorAt(1, color_);
	else
		g.setColorAt(1, Qt::black);
	QBrush brush(g);

	p.setPen(color_);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setBrush(brush);
	p.drawEllipse(x, y, diamX_-1, diamY_-1);

}

bool LED::
state() const
{
    return state_;
}

int LED::
gpio_pin() const
{
    return gpio_pin_;
}

int LED::
refresh_rate() const
{
    return refresh_rate_;
}

int LED::
get_gpio_pin_function(){

  int pin = gpio_to_bcm2835_map[gpio_pin_];

  if (pin<10)            return ((gpio_state->GPFSEL0 >> (3*pin))      & 0x7);
  if (pin>=10 && pin<20) return ((gpio_state->GPFSEL1 >> (3*(pin-10))) & 0x7);
  if (pin>=20 && pin<30) return ((gpio_state->GPFSEL2 >> (3*(pin-20))) & 0x7);
  if (pin>=30 && pin<40) return ((gpio_state->GPFSEL3 >> (3*(pin-30))) & 0x7);
  if (pin>=40 && pin<50) return ((gpio_state->GPFSEL4 >> (3*(pin-40))) & 0x7);
  return ((gpio_state->GPFSEL5 >> (3*(pin-50))) & 0x7);

}
