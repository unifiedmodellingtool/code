/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2001      Gustavo Madrigal gmadrigal@nextphere.com      *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef UMLOBJECTLIST_H
#define UMLOBJECTLIST_H

#include <QList>

// forward declarations
class UMLObject;

typedef QListIterator<UMLObject*> UMLObjectListIt;

/**
 * This sub-class adds copyInto and clone to the QList<UMLObject*>
 * base class.
 */
class UMLObjectList : public QList<UMLObject*>
{
public:

    UMLObjectList();
    virtual ~UMLObjectList();

    virtual void copyInto(UMLObjectList *rhs) const;

    virtual UMLObjectList* clone() const;
};

#endif
