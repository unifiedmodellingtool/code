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

#ifndef NEWUMLRECTWIDGET_H
#define NEWUMLRECTWIDGET_H

#include "newumlwidget.h"
#include "associationwidgetlist.h"

class AssociationWidget;
class WidgetHandle;
class UMLWidgetController;
class TextItemGroup;

/**
 * @short The base class for rectangular base UML widgets.
 *
 * This class extends the functionality provided by NewUMLWidget with
 * facilities to resize the widget, provide flexible constraints
 * management.
 *
 * Also this class handles connected association widgets whenever
 * required.
 */
class NewUMLRectWidget : public NewUMLWidget
{
	Q_OBJECT
public:
    /**
     * This enum presents options for @ref setMinimumSize and @ref
     * setMaximumSize methods.
     */
    enum SizeHintOption {
        DontAddMargin,
        AddMargin ///< adds 2 * margin() to width and height
    };
    static const QSizeF DefaultMinimumSize;
    static const QSizeF DefaultMaximumSize;

	explicit NewUMLRectWidget(UMLObject *object);
    ~NewUMLRectWidget();

	/// @return The minimum size for this widget.
	QSizeF minimumSize() const {
		return m_minimumSize;
	}
	void setMinimumSize(const QSizeF& newSize, SizeHintOption option = AddMargin);

	/// @return The maximum size for this widget.
	QSizeF maximumSize() const {
		return m_maximumSize;
	}
	void setMaximumSize(const QSizeF& newSize, SizeHintOption option = AddMargin);

	/// @return The current size of this widget.
    QSizeF size() const {
		return m_size;
	}
    void setSize(const QSizeF &size);
    void setSize(qreal width, qreal height) {
        setSize(QSizeF(width, height));
    }

	/// @return Whether widget is resizable or not.
    bool isResizable() const {
        return m_resizable;
    }
	/**
	 * Shorthand for QRectF(QPointF(0, 0), size()); The rect() area is
	 * where all the widget painting should go.
	 *
	 * @note boundingRect() is always larger than or equal to rect().
	 */
    QRectF rect() const {
        return QRectF(QPointF(0, 0), size());
    }

	/**
	 * @return The margin from the rect() left for good visual appeal.
	 */
	qreal margin() const {
		return m_margin;
	}
	void setMargin(qreal margin);

	/// @return The instance name for this widget.
    QString instanceName() const {
		return m_instanceName;
	}
    void setInstanceName(const QString &name);

	/// @return Whether this is an instance or not.
	bool isInstance() const {
		return m_isInstance;
	}
	void setIsInstance(bool b);

	/// @return Whether to show stereotype or not.
    bool showStereotype() const {
		return m_showStereotype;
	}
    void setShowStereotype(bool b);

	/// @return A list representing AssociationWidget connected to
	///         this widget.
    AssociationWidgetList associationWidgetList() const {
		return m_associationWidgetList;
	}
    void addAssociationWidget(AssociationWidget *assoc);
    void removeAssociationWidget(AssociationWidget *assoc);
    virtual void adjustAssociations();

    virtual void showPropertiesDialog();
    virtual void setupContextMenuActions(ListPopupMenu &menu);

    virtual bool loadFromXMI(QDomElement &qElement);
    virtual void saveToXMI(QDomDocument &qDoc, QDomElement &qElement);

protected:
	virtual QVariant attributeChange(WidgetAttributeChange change, const QVariant& oldValue);
    virtual void updateGeometry();
    virtual void setResizable(bool resizable);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);


    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

	TextItemGroup* createTextItemGroup();
	int indexOfTextItemGroup(TextItemGroup *group) const;
	TextItemGroup* textItemGroupAt(int index) const;
	virtual void updateTextItemGroups();

	/**
	 * List of TextItemGroup , which manages various texts for this
	 * widget.
	 */
	QList<TextItemGroup*> m_textItemGroups;

protected Q_SLOTS:
    virtual void slotUMLObjectDataChanged();

private:
	/// Current size of the widget.
    QSizeF m_size;

	QSizeF m_minimumSize;
	QSizeF m_maximumSize;

	/// Margin for this widget.
	qreal m_margin;

	QString m_instanceName;
	bool m_isInstance;
	bool m_showStereotype;

	/// Whether resizable or not.
	bool m_resizable;
    AssociationWidgetList m_associationWidgetList;

	/// Widget handle for this widget (for resizing)
	WidgetHandle *m_widgetHandle;

	QRectF m_geometryBeforeResize;

	// Dispable copy constructor and operator=
    DISABLE_COPY(NewUMLRectWidget);

public:
    //////////////////  DEPRECATED //////////////////////////
    NewUMLRectWidget(UMLScene *scene, const Uml::IDType & _id = Uml::id_None);
    NewUMLRectWidget(UMLScene *scene, UMLObject *obj);

    qreal getWidth() const { return size().width(); }
    void setWidth(qreal w) { setSize(w, getHeight()); }
    qreal getHeight() const { return size().height(); }
    void setHeight(qreal h) { setSize(getWidth(), h); }

    QString getInstanceName() const { return instanceName(); }
    bool getIsInstance() const { return isInstance(); }
    bool getShowStereotype() const { return showStereotype(); }

    void adjustAssocs(qreal, qreal) {}
    QSizeF calculateSize() { return minimumSize(); }
    bool getStartMove() const { return false; }
    bool getIgnoreSnapToGrid() const { return false; }
    void setIgnoreSnapToGrid(bool) {}
    bool getIgnoreSnapComponentSizeToGrid() const { return false; }
    void setIgnoreSnapComponentSizeToGrid(bool) {}
    bool m_bStartMove;
    void adjustUnselectedAssocs(qreal, qreal) {}
    UMLWidgetController* getWidgetController() const { return 0; }
    ListPopupMenu* setupPopupMenu();

    AssociationWidgetList getAssocList() const { return associationWidgetList(); }
    void addAssoc(AssociationWidget *assoc) { addAssociationWidget(assoc); }
    void removeAssoc(AssociationWidget *assoc) { removeAssociationWidget(assoc); }
};

#endif //NEWUMLRECTWIDGET_H