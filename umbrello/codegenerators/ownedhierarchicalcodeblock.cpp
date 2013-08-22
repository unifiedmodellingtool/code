/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003      Brian Thomas <thomas@mail630.gsfc.nasa.gov>   *
 *   copyright (C) 2004-2013                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

// own header
#include "ownedhierarchicalcodeblock.h"

// local includes
#include "association.h"
#include "umldoc.h"
#include "umlobject.h"
#include "umlrole.h"
#include "codedocument.h"
#include "codegenerator.h"

OwnedHierarchicalCodeBlock::OwnedHierarchicalCodeBlock(UMLObject *parent, CodeDocument * doc, const QString &start, const QString &end, const QString &comment)
  : OwnedCodeBlock(parent),
    HierarchicalCodeBlock(doc, start, end, comment)
{
}

OwnedHierarchicalCodeBlock::~OwnedHierarchicalCodeBlock()
{
}

/**
 * causes the text block to release all of its connections
 * and any other text blocks that it 'owns'.
 * needed to be called prior to deletion of the textblock.
 */
void OwnedHierarchicalCodeBlock::release()
{
    OwnedCodeBlock::release();
    HierarchicalCodeBlock::release();
}

/**
 * set the class attributes from a passed object
 */
void OwnedHierarchicalCodeBlock::setAttributesFromObject(TextBlock * obj)
{
    HierarchicalCodeBlock::setAttributesFromObject(obj);
    OwnedCodeBlock::setAttributesFromObject(obj);
}

/**
 * set attributes of the node that represents this class
 * in the XMI document.
 */
void OwnedHierarchicalCodeBlock::setAttributesOnNode(QDomDocument & doc, QDomElement & elem)
{
    // set super-class attributes
    HierarchicalCodeBlock::setAttributesOnNode(doc, elem);
    OwnedCodeBlock::setAttributesOnNode(doc, elem);

    // set local class attributes
    elem.setAttribute("parent_id",Uml::ID::toString(getParentObject()->id()));

    // setting ID's takes special treatment
    // as UMLRoles arent properly stored in the XMI right now.
    // (change would break the XMI format..save for big version change)
    UMLRole * role = dynamic_cast<UMLRole*>(getParentObject());
    if(role) {
        // see comment on role_id at OwnedCodeBlock::setAttributesOnNode()
        elem.setAttribute("role_id", (role->role() == Uml::RoleType::A));
    }
    /* else
            elem.setAttribute("role_id","-1");
    */
}

/**
 * set the class attributes of this object from
 * the passed element node.
 */
void OwnedHierarchicalCodeBlock::setAttributesFromNode(QDomElement & root)
{
    // set attributes from the XMI
    HierarchicalCodeBlock::setAttributesFromNode(root); // superclass load
    OwnedCodeBlock::setAttributesFromNode(root); // superclass load
}

/**
 * Return the parent code document
 */
CodeDocument * OwnedHierarchicalCodeBlock::getParentDocument()
{
    return TextBlock::getParentDocument();
}

void OwnedHierarchicalCodeBlock::syncToParent()
{
    if (contentType() != CodeBlock::AutoGenerated)
        return;

    updateContent();
}

#include "ownedhierarchicalcodeblock.moc"
