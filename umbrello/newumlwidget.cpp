/***************************************************************************
 * Copyright (C) 2008 by Gopala Krishna A <krishna.ggk@gmail.com>          *
 *                                                                         *
 * This is free software; you can redistribute it and/or modify            *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2, or (at your option)     *
 * any later version.                                                      *
 *                                                                         *
 * This software is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this package; see the file COPYING.  If not, write to        *
 * the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,   *
 * Boston, MA 02110-1301, USA.                                             *
 ***************************************************************************/

#include "newumlwidget.h"

#include "uml.h"
#include "umlobject.h"
#include "umlscene.h"
#include "uniqueid.h"
#include "widget_utils.h"

#include <QtCore/QTimer>
#include <kdebug.h>

// Documentation for some inline and other entities.

/**
 * @class NewUMLWidget
 *
 * @short The base class for UML widgets that appear on UML diagrams.
 *
 * This class provides the common interface required for all the UML
 * widgets including rectangular and non rectangular widgets.
 * Rectangular widgets should use NewUmlRectWidget as its base.
 */

/**
 * @fn NewUMLWidget::umlObject
 *
 * @return The UMLObject represented by this widget or null if this
 *         widget has no UMLObject representation.
 */

/**
 * @fn NewUMLWidget::baseType
 *
 * @return The base type rtti info for this widget.
 */

/**
 * @fn NewUMLWidget::lineColor
 *
 * @return The color used to draw lines of the widget.
 */

/**
 * @fn NewUMLWidget::lineWidth
 *
 * @return The width of the line, drawn in the widget.
 */

/**
 * @fn NewUMLWidget::fontColor
 *
 * @return Font color used to draw font.
 */

/**
 * @fn NewUMLWidget::brush
 *
 * @return The QBrush object used to fill this widget.
 */

/**
 * @fn NewUMLWidget::font
 *
 * @return The font used for displaying any text inside this
 * widget.
 */

/**
 * @fn NewUMLWidget:: boundingRect
 *
 * @return The bounding rectangle for this widget.
 * @see setBoundingRectAndShape
 */

/**
  *@fn NewUMLWidget::shape
  *
  * @return The shape of this widget.
  * @see setBoundingRectAndShape
  */

// Inline and other entity documentation ends.


/**
 * @short A class to encapsulate some properties to be stored as a
 * part of Lazy initialization.
 *
 * The properties encapsulated here are used only if the widget does
 * not have UMLObject representation.
 */
struct WidgetInterfaceData
{
    WidgetInterfaceData() : id(Uml::id_None)
    {
    }

    Uml::IDType id;
    QString documentation;
    QString name;
};

/**
 * Constructs a NewUMLWidget object with the associated UMLObject to
 * \a object and the parent item of the widget being null.  Also sets
 * the ItemIsMovable and ItemIsSelectable flag.
 *
 * @param object UMLObject that is represented by this widget. Pass
 *               null if this widget does not have UMLObject
 *               representation.
 *
 * @note The widget's visual properties are best to be set by the
 *       Widget_Factory::createWidget method.
 */
NewUMLWidget::NewUMLWidget(UMLObject *object) :
    m_umlObject(object),
    m_lineWidth(0),
    m_widgetInterfaceData(0),
    firstTime(true)
{
    if(!object) {
        m_widgetInterfaceData = new WidgetInterfaceData;
    }
    setFlags(ItemIsSelectable | ItemIsMovable);
    // Call init this way so that virtual methods may be called.
    QTimer::singleShot(0, this, SLOT(slotInit()));

    // DEPRECATED INITIALIZATION
    {
        for(int i= FT_NORMAL; i < FT_INVALID; ++i) {
            m_pFontMetrics[i] = new QFontMetrics(font());
        }

        m_pMenu = 0;
    }
}

/**
 * Destructor
 */
NewUMLWidget::~NewUMLWidget()
{
    delete m_widgetInterfaceData;
}

/**
 * Set the UMLObject for this widget to represent.
 *
 * @todo Either remove this method, or allow it to only allow specific
 *       users as making this method public violates encapsulation.
 */
void NewUMLWidget::setUMLObject(UMLObject *obj)
{
    UMLObject *oldObj = m_umlObject;
    m_umlObject = obj;

    if(oldObj) {
        oldObj->disconnect(this);
    }

    if(m_umlObject) {
        delete m_widgetInterfaceData;
        connect(umlObject(), SIGNAL(modified()), this,
                SLOT(slotUMLObjectDataChanged()));
    }
    else if(!m_widgetInterfaceData) {
        m_widgetInterfaceData = new WidgetInterfaceData;
    }

    umlObjectChanged(oldObj);
}

/**
 * If this widget represents a UMLObject, the id of that object is
 * returned. Else the id stored in this widget is returned.
 *
 * @return The identifier of this widget.
 */
Uml::IDType NewUMLWidget::id() const
{
    if(m_umlObject) {
        return m_umlObject->getID();
    }
    return m_widgetInterfaceData->id;
}

/**
 * If this widget represents a UMLObject, the id of that object is set
 * to \a id. Else the id is stored in this widget.
 */
void NewUMLWidget::setId(Uml::IDType id)
{
    if(m_umlObject) {

        if(m_umlObject->getID() != Uml::id_None) {
            uWarning() << "changing old UMLObject " << ID2STR(m_umlObject->getID())
                       << " to " << ID2STR(id) << endl;
        }

        m_umlObject->setID(id);
    }
    else {
        m_widgetInterfaceData->id = id;
    }
}

/**
 * @return The UMLScene for this widget is returned, or 0 if the
 *         widget is not stored in a scene.
 *
 * @note To add or remove widgets to scene, use UMLScene::addItem
 */
UMLScene* NewUMLWidget::umlScene() const
{
    return qobject_cast<UMLScene*>(this->scene());
}

/**
 * This is shortcut method for UMLApp::app()->getDocument()
 *
 * @return Pointer to the UMLDoc object.
 */
UMLDoc* NewUMLWidget::umlDoc() const
{
    return UMLApp::app()->getDocument();
}

/**
 * If this widget represents a UMLObject, the documentation string
 * stored in the object is returned. Else the documentation string
 * stored in the widget is returned.
 *
 * @return A string representing the documentation for this widget
 *         which is usually set by the user.
 */
QString NewUMLWidget::documentation() const
{
    if(m_umlObject) {
        return m_umlObject->getDoc();
    }
    return m_widgetInterfaceData->documentation;
}

/**
 * If this widget represents a UMLObject, the documentation string
 * of that object is set to \a doc. Else the documentation string
 * stored in the widget is set to \a doc.
 */
void NewUMLWidget::setDocumentation(const QString& doc)
{
    if(m_umlObject) {
        m_umlObject->setDoc(doc);
    }
    else {
        m_widgetInterfaceData->documentation = doc;
    }
}

/**
 * If this widget represents a UMLObject, the name string stored
 * in the object is returned. Else the name string stored in the
 * widget is returned.
 *
 * @return A string representing the name for this widget
 *         which is usually set by the user.
 */
QString NewUMLWidget::name() const
{
    if(m_umlObject) {
        return m_umlObject->getName();
    }
    return m_widgetInterfaceData->name;
}

/**
 * If this widget represents a UMLObject, the name string of that
 * object is set to \a name. Else the name string stored in the
 * widget is set to \a name.
 */
void NewUMLWidget::setName(const QString& name)
{
    if(m_umlObject) {
        m_umlObject->setName(name);
    }
    else {
        m_widgetInterfaceData->name = name;
    }
    updateGeometry();
}

/**
 * Set the linecolor to \a color and updates the widget.
 *
 * @param color The color to be set
 */
void NewUMLWidget::setLineColor(const QColor& color)
{
    m_lineColor = color;
    if(!m_lineColor.isValid()) {
        uDebug() << "Invalid color";
        m_lineColor = Qt::black;
    }
    update();
}

/**
 * Sets the line width of widget lines to \a lw and calls
 * updateGeometry() method to let object calculate new bound rect
 * based on the new line width.
 *
 * @param lw  The width of line to be set.
 */
void NewUMLWidget::setLineWidth(uint lw)
{
    m_lineWidth = lw;
    updateGeometry();
}

/**
 * Sets the color of the font to \a color.
 * If \a color is invalid, line color is used for font color.
 */
void NewUMLWidget::setFontColor(const QColor& color)
{
    m_fontColor = color;
    if(!m_fontColor.isValid()) {
        m_fontColor = m_lineColor;
    }
}

/**
 * Sets the QBrush object of this widget to \a brush which is used to
 * fill this widget.
 *
 * This method implicitly calls update on this widget.
 */
void NewUMLWidget::setBrush(const QBrush& brush)
{
    m_brush = brush;
    update();
}

/**
 * Set the font used to display text inside this widget.
 *
 * This method implicitly updateGeometry() virtual method to let the
 * subclasses calculate its new bound rect based on the new font.
 */
void NewUMLWidget::setFont(const QFont& font)
{
    m_font = font;
    updateGeometry();
}

/**
 * A virtual method for the widget to display a property dialog box.
 * Subclasses should reimplment this appropriately.
 */
void NewUMLWidget::showPropertiesDialog()
{
}

/**
 * A virtual method to setup a context menu actions. Subclasses can
 * call this method and add other actions as desired.
 *
 * @param menu The ListPopupMenu into which the menu actions should be
 *             added.
 *
 * @note The menu is not a pointer to avoid destruction problems.
 */
void NewUMLWidget::setupContextMenuActions(ListPopupMenu &menu)
{
	Q_UNUSED(menu);
}

/**
 * A virtual method to load the properties of this widget from a
 * QDomElement into this widget.
 *
 * Subclasses should reimplement this to load addtional properties
 * required, calling this base method to load the basic properties of
 * the widget.
 *
 * @param qElement A QDomElement which contains xml info for this
 *                 widget.
 *
 * @todo Add support to load older version.
 */
bool NewUMLWidget::loadFromXMI(QDomElement &qElement)
{
    // NOTE:
    // The "none" is used by kde3 version of umbrello. The current
    // technique to determine whether a property is being used from
    // the diagram or not is just to compare the same, rather than
    // having flags for them.
    //
    // This way, there is no burden to update the flags and the code
    // is more robust.
    const QLatin1String none("none");

    // Load the line color first

    // Workaround for old "linecolour" usage.
    QString lineColor = qElement.attribute("linecolour");
    lineColor = qElement.attribute("linecolor", lineColor);
    if(!lineColor.isEmpty() && lineColor != none) {
        setLineColor(QColor(lineColor));
    }
    else if(umlScene()) {
        setLineColor(umlScene()->getLineColor());
    }

    // Load the line width.
    QString lineWidth = qElement.attribute("linewidth");
    if(!lineWidth.isEmpty() && lineWidth != none) {
        setLineWidth(lineWidth.toInt());
    }
    else if(umlScene()) {
        setLineWidth(umlScene()->getLineWidth());
    }

    // Load the font color, if invalid line color is automatically used.
    QString fontColor = qElement.attribute("fontcolor");
    setFontColor(QColor(fontColor));

    // Load the brush.
    QBrush newBrush;
    bool brushSet = Widget_Utils::loadBrushFromXMI(qElement, newBrush);

    // If this fails, we try to load fillColor attribute which is used in kde3 version of umbrello.
    if(!brushSet) {
        // Workaround for old "fillcolour" usage.
        QString fillColor = qElement.attribute("fillcolour");
        fillColor = qElement.attribute("fillcolor");

        if(!fillColor.isEmpty() && fillColor != none) {
            setBrush(QColor(fillColor));
            brushSet = true;
        }
    }
    else {
        setBrush(newBrush);
    }
    // Set the diagram's brush if it is not yet set.
    if(!brushSet && umlScene()) {
        setBrush(umlScene()->brush());
    }

    // Load the font.
    QString font = qElement.attribute(QLatin1String("font"));
    bool fontSet = false;
    if(!font.isEmpty()) {
        fontSet = m_font.fromString(font);
        if(fontSet) {
            setFont(m_font);
        }
        else {
            uWarning() << "Loading font attribute->" << font << " failed";
        }
    }
    // Set diagram's default font if font is not yet set.
    if(!fontSet && umlScene()) {
        setFont(umlScene()->font());
    }

    QString id = qElement.attribute("xmi.id", "-1");
    // Assert for the correctness of id loaded and the created object.
    if(m_umlObject) {
        if(id != ID2STR(this->id())) {
            uWarning() << "ID mismatch between NewUMLRectWidget and its UMLObject"
                       << "So the id read will be ignored.";
        }
    }
    else {
        setId(STR2ID(id));
    }

    qreal x = qElement.attribute("x", "0").toDouble();
    qreal y = qElement.attribute("y", "0").toDouble();
    setPos(x, y);

    return true;
}

/**
 * A virtual method to save the properties of this widget into a
 * QDomElement i.e xml.
 *
 * Subclasses should first create a new dedicated element as the child
 * of \a qElement parameter passed.  Then this base method should be
 * called to save basic widget properties.
 *
 * @param qDoc A QDomDocument object representing the xml document.
 * @oaram qElement A QDomElement representing xml element data.
 */
void NewUMLWidget::saveToXMI(QDomDocument &qDoc, QDomElement &qElement)
{
    qElement.setAttribute("linecolor", m_lineColor.name());
    qElement.setAttribute("linewidth", m_lineWidth);
    qElement.setAttribute("fontcolor", m_fontColor.name());
    qElement.setAttribute("font", m_font.toString());

    Widget_Utils::saveBrushToXMI(qDoc, qElement, m_brush);

    qElement.setAttribute("xmi.id", ID2STR(id()));
    qElement.setAttribute("x", pos().x());
    qElement.setAttribute("y", pos().y());
}

/**
 * @return Whether the widget type has an associated UMLObject
 */
bool NewUMLWidget::widgetHasUMLObject(Uml::Widget_Type type)
{
	switch(type)
	{
	case Uml::wt_Actor:
	case Uml::wt_UseCase:
	case Uml::wt_Class:
	case Uml::wt_Interface:
	case Uml::wt_Enum:
	case Uml::wt_Datatype:
	case Uml::wt_Package:
	case Uml::wt_Component:
	case Uml::wt_Node:
	case Uml::wt_Artifact:
	case Uml::wt_Object:
		return true;
	default:
		return false;
	}
}

/**
 * This slot is connected to UMLObject::modified() signal to sync the
 * required changes as well as to update visual aspects corresponding
 * to the change.
 *
 * @note Subclasses can *reimplement* this slot to fine tune its own
 *       updations.
 */
void NewUMLWidget::slotUMLObjectDataChanged()
{
    updateGeometry();
}

/**
 * This slot is used to intialize the widget, also allowing virtual
 * methods to be called.
 */
void NewUMLWidget::slotInit()
{
    setUMLObject(m_umlObject);
    updateGeometry();
}

/**
 * This virtual method is called by this NewUMLWidget base class to
 * notify subclasses about the need to change its boundingRect
 * Example. When a new pen is set on a widget which paints
 *
 * The default implementation just calls update()
 */
void NewUMLWidget::updateGeometry()
{
    update();
}

/**
 * This virtual method is called when the underlying uml object of
 * this widget changes. Disconnections to signals wrt to old object,
 * connections to new signals of new object are to be made and any
 * other book keeping work can also be done.
 *
 * @param obj The old UMLObject. The new one is accessible through
 *            umlObject()
 *
 * @note obj can be null!
 *
 * @note The reimplemented method should call this base method to
 *       connect/disconnect signals done at UMLObject level.
 */
void NewUMLWidget::umlObjectChanged(UMLObject *oldObj)
{
    Q_UNUSED(oldObj);
}

/**
 * This method sets the bounding rectangle of this widget to \a
 * rect. The bounding rect being set is cached locally for performance
 * reasons.
 *
 * Also the prepareGeometryChange() method is implicitly called to
 * update QGraphicsScene indexes.
 *
 * @param rect The bounding rectangle for this widget.
 *
 * @note The bounding rect being set should also be compensated with
 *       half pen width if the widget is painting an outline/stroke.
 *
 * @note Also note that, subclasses reimplementing @ref boundingRect()
 *       virtual method will not be affected by this method unless the
 *       subclassed widget explicitly uses it.
 *
 * @see Widget_Utils::adjustedBoundingRect
 */
void NewUMLWidget::setBoundingRect(const QRectF &rect)
{
    prepareGeometryChange();
    m_boundingRect = rect;
}

/**
 * This method sets the shape of the widget to \a path. The shape of
 * the widget is cached for performance reasons.
 *
 * @param path The shape of this widget. If empty, boundingRect will
 *             be used as widget shape.
 *
 * @see NewUMLWidget::setBoundingRect
 *
 * @todo Check the accuracy of this method for non rectangular widgets
 *       as this doesn't call prepareGeometryChange.
 *
 * @note Also note that, subclasses reimplementing @ref shape()
 *       virtual method will not be affected by this method unless the
 *       subclassed widget explicitly uses it.
 */
void NewUMLWidget::setShape(const QPainterPath& path)
{
    m_shape = path;
    if(m_shape.isEmpty()) {
        m_shape.addRect(boundingRect());
    }
    update();
}



///////////////////////////////SOME DEPRECATED STUFF///////////////

NewUMLWidget::NewUMLWidget(UMLScene *scene, UMLObject *object) :
    QObject(),
    QGraphicsItem(0),

    m_umlObject(object),
    m_lineWidth(0),
    m_widgetInterfaceData(0),
    firstTime(true)
{
    for(int i= FT_NORMAL; i < FT_INVALID; ++i) {
        m_pFontMetrics[i] = new QFontMetrics(font());
    }
    m_pMenu = 0;
    if(!object) {
        m_widgetInterfaceData = new WidgetInterfaceData;
    }
    setFlags(ItemIsSelectable | ItemIsMovable);
    // Call init this way so that virtual methods may be called.
    QTimer::singleShot(0, this, SLOT(slotInit()));
    scene->addItem(this);
}

NewUMLWidget::NewUMLWidget(UMLScene *scene, const Uml::IDType &_id) :
    m_umlObject(0),
    m_lineWidth(0),
    firstTime(true)
{
    for(int i= FT_NORMAL; i < FT_INVALID; ++i) {
        m_pFontMetrics[i] = new QFontMetrics(font());
    }
    m_pMenu = 0;
    m_widgetInterfaceData = new WidgetInterfaceData;
    if(_id == Uml::id_None) {
        m_widgetInterfaceData->id = UniqueID::gen();
    }
    else {
        m_widgetInterfaceData->id = _id;
    }
    scene->addItem(this);
    setFlags(ItemIsSelectable | ItemIsMovable);
    // Call init this way so that virtual methods may be called.
    QTimer::singleShot(0, this, SLOT(slotInit()));
}

void NewUMLWidget::setDefaultFontMetrics(NewUMLWidget::FontType fontType)
{
    setupFontType(m_font, fontType);
    setFontMetrics(fontType, QFontMetrics(m_font));
}

void NewUMLWidget::setupFontType(QFont &font, NewUMLWidget::FontType fontType)
{
    switch (fontType) {
    case FT_NORMAL:
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        break;
    case FT_BOLD:
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        break;
    case FT_ITALIC:
        font.setBold(false);
        font.setItalic(true);
        font.setUnderline(false);
        break;
    case FT_UNDERLINE:
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(true);
        break;
    case FT_BOLD_ITALIC:
        font.setBold(true);
        font.setItalic(true);
        font.setUnderline(false);
        break;
    case FT_BOLD_UNDERLINE:
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(true);
        break;
    case FT_ITALIC_UNDERLINE:
        font.setBold(false);
        font.setItalic(true);
        font.setUnderline(true);
        break;
    case FT_BOLD_ITALIC_UNDERLINE:
        font.setBold(true);
        font.setItalic(true);
        font.setUnderline(true);
        break;
    default: return;
    }
}

void NewUMLWidget::setDefaultFontMetrics(NewUMLWidget::FontType fontType, QPainter &painter)
{
    setupFontType(m_font, fontType);
    painter.setFont(m_font);
    setFontMetrics(fontType, painter.fontMetrics());
}

//FIXME this is probably the source of problems with widgets not being wide enough
QFontMetrics &NewUMLWidget::getFontMetrics(NewUMLWidget::FontType fontType)
{
    if (m_pFontMetrics[fontType] == 0) {
        setDefaultFontMetrics(fontType);
    }
    return *m_pFontMetrics[fontType];
}

void NewUMLWidget::setFontMetrics(NewUMLWidget::FontType fontType, QFontMetrics fm)
{
    delete m_pFontMetrics[fontType];
    m_pFontMetrics[fontType] = new QFontMetrics(fm);
}

void NewUMLWidget::forceUpdateFontMetrics(QPainter *painter)
{
    if (painter == 0) {
        for (int i = 0; i < (int)NewUMLWidget::FT_INVALID; ++i) {
            if (m_pFontMetrics[(NewUMLWidget::FontType)i] != 0)
                setDefaultFontMetrics((NewUMLWidget::FontType)i);
        }
    } else {
        for (int i2 = 0; i2 < (int)NewUMLWidget::FT_INVALID; ++i2) {
            if (m_pFontMetrics[(NewUMLWidget::FontType)i2] != 0)
                setDefaultFontMetrics((NewUMLWidget::FontType)i2, *painter);
        }
    }
    // calculate the size, based on the new font metric
    updateComponentSize();
}

ListPopupMenu* NewUMLWidget::setupPopupMenu()
{
    return 0;
}

#include "newumlwidget.moc"