#include "GPIOButton.h"
#include "GPIOButtonPlugin.h"

#include <QtPlugin>

GPIOButtonPlugin::
GPIOButtonPlugin(QObject* parent) :
	QObject(parent),
	initialized(false)
{
}

QString GPIOButtonPlugin::
name() const
{
    return "GPIOButton";
}

QString GPIOButtonPlugin::
group() const
{
    return tr("Evan Platt");
}

QString GPIOButtonPlugin::
toolTip() const
{
    return tr("PiGPIO Button");
}

QString GPIOButtonPlugin::
whatsThis() const
{
    return tr("PiGPIO Button");
}

QString GPIOButtonPlugin::
includeFile() const
{
    return "GPIOButton.h";
}

QIcon GPIOButtonPlugin::
icon() const
{
	return QIcon();
}

bool GPIOButtonPlugin::
isContainer() const
{
	return false;
}

QWidget * GPIOButtonPlugin::
createWidget(QWidget *parent)
{
    return new GPIOButton(parent);
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
Q_EXPORT_PLUGIN2(gpiobuttonplugin, GPIOButtonPlugin)
#endif
