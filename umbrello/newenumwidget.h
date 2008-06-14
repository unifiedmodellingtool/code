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

#ifndef NEWENUMWIDGET_H
#define NEWENUMWIDGET_H


#include "newumlrectwidget.h"

#define ENUM_MARGIN 5

/**
 * @short A uml widget to visualize enum.
 * @author Gopala Krishna A
 * @see NewUMLRectWidget
 *
 * Bugs and comments to uml-devel@lists.sf.net or http://bugs.kde.org
 */
class NewEnumWidget : public NewUMLRectWidget
{
public:

    /**
     * Constructs an instance of NewEnumWidget.
     * @param o The NewUMLObject this will be representing.
     */
    explicit NewEnumWidget(UMLObject* o);

    /**
     * Do some initialization which cannot be done inside constructor
     * as it involves calling virtual methods.
     */
    void init();

    QSizeF sizeHint(Qt::SizeHint which);

    /**
     * Reimplemented to draw as needed.
     * Draws the enum as a rectangle with a box underneith with a list of literals
     */
    void paint(QPainter *p, const QStyleOptionGraphicsItem *item, QWidget *widget);

    /**
     * Loads from an "enumwidget" XMI element.
     */
    bool loadFromXMI(QDomElement& qElement);

    /**
     * Saves to the "enumwidget" XMI element.
     */
    void saveToXMI(QDomDocument& qDoc, QDomElement& qElement);

protected:
    /**
     * Overrides method from NewUMLRectWidget.
     */
    void updateGeometry();

private:
    QSizeF m_minimumSize;
    void calculateMinimumSize();
};

#endif // NEWENUMWIDGET_H
