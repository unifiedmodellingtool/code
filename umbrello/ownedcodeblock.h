

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
 *      Date   : Tue Aug 19 2003
 */

#ifndef OWNEDCODEBLOCK_H
#define OWNEDCODEBLOCK_H

#include <qdom.h>
#include <qstring.h>
#include <qobject.h>

class TextBlock;
class CodeDocument;
class UMLObject;

/**
  * class OwnedCodeBlock
  * Describes any codeblock which is 'owned' by a UMLobject of some sort and should
  * be in sync with that parent.
  */

class OwnedCodeBlock : virtual public QObject 
{
	Q_OBJECT
public:

	// Constructors/Destructors
	//  

	/**
	 * Constructor
	 */
	OwnedCodeBlock ( UMLObject * parent );

	/**
	 * Empty Destructor
	 */
	virtual ~OwnedCodeBlock ( );

	/**
	 * @return	UMLObject
	 */
	virtual UMLObject * getParentObject ( ) = 0;

	// get the parent code document of this code block
	virtual CodeDocument * getParentDocument ( ) = 0;

protected:

        /** set attributes of the node that represents this class
         * in the XMI document.
         */
        virtual void setAttributesOnNode ( QDomDocument & doc, QDomElement & blockElement);

        /** set the class attributes of this object from
         * the passed element node.
         */
        virtual void setAttributesFromNode ( QDomElement & element);

	/** set the class attributes from a passed object
         */
        virtual void setAttributesFromObject (TextBlock * obj) = 0;

	/**
         * This is the method called from within syncToParent
	 */
	virtual void updateContent ( ) = 0;

private:

	void initFields( UMLObject * parent );

public slots:

	virtual void syncToParent ( );

};

#endif // OWNEDCODEBLOCK_H
