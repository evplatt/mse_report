#ifndef _LED_H_
#define _LED_H_

#include <QtDesigner/QtDesigner>
#include <QWidget>

class QTimer;

class QDESIGNER_WIDGET_EXPORT LED : public QWidget
{
	Q_OBJECT

	Q_PROPERTY(double diameter READ diameter WRITE setDiameter) // mm
	Q_PROPERTY(QColor color READ color WRITE setColor)
	Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
	Q_PROPERTY(bool state READ state WRITE setState)
  Q_PROPERTY(int gpio_pin READ gpio_pin WRITE set_gpio_pin)
  Q_PROPERTY(int refresh_rate READ refresh_rate WRITE set_refresh_rate)

public:
	explicit LED(QWidget* parent=0);
	~LED();

	double diameter() const;
	void setDiameter(double diameter);

	QColor color() const;
	void setColor(const QColor& color);

	Qt::Alignment alignment() const;
	void setAlignment(Qt::Alignment alignment);

  bool state() const;

	void set_gpio_pin(int gpio_pin);
	void set_refresh_rate(int refresh_rate);
	int gpio_pin() const;
	int refresh_rate() const;
	void connect_gpio();
    int get_gpio_pin_function();

public slots:
	void setState(bool state);
	void gpio_refresh();

public:
	int heightForWidth(int width) const;
	QSize sizeHint() const;
	QSize minimumSizeHint() const;

protected:
	void paintEvent(QPaintEvent* event);

private:
	double diameter_;
	QColor color_;
	Qt::Alignment alignment_;
	bool initialState_;
	bool state_;

	int gpio_pin_;
	int refresh_rate_;

	//
	// Pixels per mm for x and y...
	//
	int pixX_, pixY_;

	//
	// Scaled values for x and y diameter.
	//
	int diamX_, diamY_;

	QRadialGradient gradient_;
	QTimer* timer_;
  QTimer* gpio_timer_;

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

  const int gpio_to_bcm2835_map[8] = {17,18,21,22,23,24,25,4};

  shared_gpio_state *gpio_state;

};

#endif
