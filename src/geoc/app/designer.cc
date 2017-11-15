#include <geoc/app/GeocWidget.h>
#include <geoc/app/designer.h>
#include <QtPlugin>


using namespace geoc;


const char domxml[] =
        "<ui language=\"c++\">\n"
        " <widget class=\"geoc::GeocWidget\" name=\"geoc::GeocWidget\">\n"
        "  <property name=\"geometry\">\n"
        "   <rect>\n"
        "    <x>0</x>\n"
        "    <y>0</y>\n"
        "    <width>320</width>\n"
        "    <height>280</height>\n"
        "   </rect>\n"
        "  </property>\n"
        "  <property name=\"toolTip\" >\n"
        "   <string>Geoc Viewer</string>\n"
        "  </property>\n"
        "  <property name=\"whatsThis\" >\n"
        "   <string>Geoc viewer widget.</string>\n"
        "  </property>\n"
        " </widget>\n"
        "</ui>\n";


QString GeocWidgetInterface::domXml() const
{
    return domxml;
}


QWidget* GeocWidgetInterface::createWidget(QWidget* parent)
{
    GeocWidget* w = new GeocWidget(parent, true);
    return w;
}


Q_EXPORT_PLUGIN2(geoc, GeocWidgetInterface)
