
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
 *      Date   : Fri Jul 25 2003
 */

#ifndef CODECLASSFIELDDECLARATIONBLOCK_H
#define CODECLASSFIELDDECLARATIONBLOCK_H

#include <qstring.h>
#include <qptrlist.h>

class UMLObject;
class CodeClassField; 

#include "codeblockwithcomments.h"
#include "ownedcodeblock.h"

/**
  * class CodeClassFieldDeclarationBlock
  * Used to declare classifier fields (e.g. either class attributes or classifier
  * associations) in the code document for any given code classfield. This is a
  * special CodeBlockWithComments which is "sync'd" to the parent CodeClassField.
  */

class CodeClassFieldDeclarationBlock : public CodeBlockWithComments, public OwnedCodeBlock 
{
	friend class CodeClassField;
	Q_OBJECT
public:

	// Constructors/Destructors
	//  

	/**
	 * Constructor
	 */
	CodeClassFieldDeclarationBlock (CodeClassField * parent);

	/**
	 * Empty Destructor
	 */
	virtual ~CodeClassFieldDeclarationBlock ( );

	/**
	 * Get the value of m_parentclassfield
	 * @return the value of m_parentclassfield
	 */
	CodeClassField * getParentClassField ( );

	/** A Utility method to get the parent object of the parentCodeClassfield
 	 */
	UMLObject * getParentObject ( );

	// get the parent document
	CodeDocument * getParentDocument ( );

	/**
	 * Save the XMI representation of this object
	 */
	virtual void saveToXMI ( QDomDocument & doc, QDomElement & root );

	/**
	 * load params from the appropriate XMI element node.
	 */
	virtual void loadFromXMI ( QDomElement & root );

	/** set the class attributes from a passed object
	 */
	virtual void setAttributesFromObject (TextBlock * obj);

protected:

	virtual void release ();

	/** set attributes of the node that represents this class
	 * in the XMI document.
	 */
	virtual void setAttributesOnNode ( QDomDocument & doc, QDomElement & blockElement);

	/** set the class attributes of this object from
	 * the passed element node.
	 */
	virtual void setAttributesFromNode ( QDomElement & element);

	/** this is called by syncToParent
	 */
	virtual void updateContent() = 0;

	// so parent can actually release this block
	void forceRelease ();

private:

	CodeClassField * m_parentclassfield;
	void init(CodeClassField * parent);

public slots:

	virtual void syncToParent();

};

#endif // CODECLASSFIELDDECLARATIONBLOCK_H
