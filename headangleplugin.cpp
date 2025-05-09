#include "headangle.h"
#include "headangleplugin.h"

#include <QtPlugin>

HeadAnglePlugin::HeadAnglePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void HeadAnglePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool HeadAnglePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *HeadAnglePlugin::createWidget(QWidget *parent)
{
    return new HeadAngle(parent);
}

QString HeadAnglePlugin::name() const
{
    return QLatin1String("HeadAngle");
}

QString HeadAnglePlugin::group() const
{
    return QLatin1String("");
}

QIcon HeadAnglePlugin::icon() const
{
    return QIcon(QLatin1String(":/plane.png"));
}

QString HeadAnglePlugin::toolTip() const
{
    return QLatin1String("");
}

QString HeadAnglePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool HeadAnglePlugin::isContainer() const
{
    return false;
}

QString HeadAnglePlugin::domXml() const
{
    return QLatin1String("<widget class=\"HeadAngle\" name=\"headAngle\">\n"
                         " <property name=\"geometry\">\n"
                         "  <rect>\n"
                         "   <x>0</x>\n"
                         "   <y>0</y>\n"
                         "   <width>100</width>\n"
                         "   <height>100</height>\n"
                         "  </rect>\n"
                         " </property>\n"
                         "</widget>\n");
}

QString HeadAnglePlugin::includeFile() const
{
    return QLatin1String("headangle.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(headangleplugin, HeadAnglePlugin)
#endif // QT_VERSION < 0x050000
