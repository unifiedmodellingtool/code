
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*  This code generated by:
 *      Author : thomas
 *      Date   : Fri Aug 07 2003
 */

#ifndef OWNEDHIERARCHICALCODEBLOCK_H
#define OWNEDHIERARCHICALCODEBLOCK_H

#include "hierarchicalcodeblock.h"

class UMLObject;
class CodeDocument;

/**
  * class OwnedHierarchicalCodeBlock
  * A "chunk" of code within the code document that is "owned" by some
  * umlobject. This is an abstract class that should be inherited.
  */

class OwnedHierarchicalCodeBlock : public HierarchicalCodeBlock, public OwnedCodeBlock
{
    Q_OBJECT
public:

    /**
     * constructor with QString so we can create & populate it in
     * one step.
     */
    OwnedHierarchicalCodeBlock ( UMLObject * parent, CodeDocument * parentDoc, const QString &start="", const QString &end="", const QString &comment="" );

    /**
     * Empty Destructor
     */
    virtual ~OwnedHierarchicalCodeBlock ( );

    /**
     * Return the parent code document
     */
    CodeDocument * getParentDocument();

    virtual void updateContent ( ) = 0;

    // these next 2 methods should be supplied by inheriting classes
    /**
     * Save the XMI representation of this object
     */
    virtual void saveToXMI ( QDomDocument & doc, QDomElement & root ) = 0;

    /**
     * load params from the appropriate XMI element node.
     */
    virtual void loadFromXMI ( QDomElement & root ) = 0;

protected:

    /**
     * causes the text block to release all of its connections
     * and any other text blocks that it 'owns'.
     * needed to be called prior to deletion of the textblock.
     */
    virtual void release ();

    /**
     * set attributes of the node that represents this class
     * in the XMI document.
     */
    virtual void setAttributesOnNode ( QDomDocument & doc, QDomElement & blockElement);

    /**
     * set the class attributes of this object from
     * the passed element node.
     */
    virtual void setAttributesFromNode ( QDomElement & element);

    /**
     * set the class attributes from a passed object
     */
    virtual void setAttributesFromObject (TextBlock * obj);

private:

public slots:

    void syncToParent ( );

};

#endif // OWNEDHIERARCHICALCODEBLOCK_H