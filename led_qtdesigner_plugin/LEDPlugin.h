#ifndef _LED_PLUGIN_H_
#define _LED_PLUGIN_H_

#include <QDesignerCustomWidgetInterface>

class LEDPlugin : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    Q_PLUGIN_METADATA(IID "com.EvanPlatt")
#endif

public:
	LEDPlugin(QObject* parent=0);

    QString name() const;
    QString group() const;
    QString toolTip() const;
    QString whatsThis() const;
    QString includeFile() const;
    QIcon icon() const;

    bool isContainer() const;

    QWidget *createWidget(QWidget *parent);

private:
    bool initialized;
};

#endif
