#include "LED.h"
#include "LEDPlugin.h"

#include <QtPlugin>

LEDPlugin::
LEDPlugin(QObject* parent) :
	QObject(parent),
	initialized(false)
{
}

QString LEDPlugin::
name() const
{
	return "LED";
}

QString LEDPlugin::
group() const
{
    return tr("Evan Platt");
}

QString LEDPlugin::
toolTip() const
{
    return tr("PiGPIO LED");
}

QString LEDPlugin::
whatsThis() const
{
    return tr("PiGPIO LED");
}

QString LEDPlugin::
includeFile() const
{
	return "LED.h";
}

QIcon LEDPlugin::
icon() const
{
	return QIcon();
}

bool LEDPlugin::
isContainer() const
{
	return false;
}

QWidget * LEDPlugin::
createWidget(QWidget *parent)
{
	return new LED(parent);
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
Q_EXPORT_PLUGIN2(ledplugin, LEDPlugin)
#endif
