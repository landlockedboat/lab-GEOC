#ifndef _GEOC_DESIGNER_H
#define _GEOC_DESIGNER_H


#include <QtDesigner/QDesignerCustomWidgetInterface>


namespace geoc {


/** \ingroup App */
//! Exposes GeocWidget to Qt Designer.
class GeocWidgetInterface : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
    
    GeocWidgetInterface(QObject* parent = 0) : QObject(parent) {}
    
    QWidget* createWidget(QWidget* parent);
    
    QString domXml() const;
    
    QString group() const { return "Geoc"; }
    
    QIcon icon() const { return QIcon(); }
    
    QString includeFile() const { return "geoc/app/GeocWidget.h"; }
    
    bool isContainer() const { return false; }
    
    bool isInitialized() const { return true; }
    
    QString name() const { return "geoc::GeocWidget"; }
    
    QString toolTip() const { return "Geoc viewer widget"; }
    
    QString whatsThis() const { return "Geoc viewer widget"; }
};


} // namespace geoc end


#endif //_GEOC_DESIGNER_H
