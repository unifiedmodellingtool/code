
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

/** basicially a class to allow for syncronization of the contents based on the
 *  values of the parentClassField's parentObject 
 */
#include "codeclassfielddeclarationblock.h"

#include "codeclassfield.h"
#include "umlrole.h"

// Constructors/Destructors
//  

CodeClassFieldDeclarationBlock::CodeClassFieldDeclarationBlock ( CodeClassField * parentCF )  
    : CodeBlockWithComments ( (CodeDocument*) parentCF->getParentDocument() ),
	OwnedCodeBlock ((UMLObject*) parentCF->getParentObject()) 
{
	init(parentCF);
}

CodeClassFieldDeclarationBlock::~CodeClassFieldDeclarationBlock ( ) { 
// Q: is this needed??
//      m_parentclassfield->getParentObject()->disconnect(this);
}

//  
// Methods
//  

// Accessor methods
//  

/**
 * Get the value of m_parentclassfield
 * @return the value of m_parentclassfield
 */
CodeClassField * CodeClassFieldDeclarationBlock::getParentClassField ( ) {
	return m_parentclassfield;
}

/** Get the parent object of the parentCodeClassfield 
 */
UMLObject * CodeClassFieldDeclarationBlock::getParentObject ( ) {
	return m_parentclassfield->getParentObject();
}

CodeDocument * CodeClassFieldDeclarationBlock::getParentDocument ( ) {
	return TextBlock::getParentDocument();
}

// Other methods
//

// this type of textblock is special
// we DONT release it when resetTextBlocks is
// called because we re-use it over and over
// until the codeclassfield is released.
void CodeClassFieldDeclarationBlock::release () {
	// do nothing
}

void CodeClassFieldDeclarationBlock::forceRelease () {
	if(m_parentclassfield)
	{
//		m_parentclassfield->getParentObject()->disconnect(this);
		m_parentclassfield->disconnect(this);
	}
	m_parentclassfield = 0;
	OwnedCodeBlock::release();
	TextBlock::release();
}

/**
 * Save the XMI representation of this object
 */
void CodeClassFieldDeclarationBlock::saveToXMI ( QDomDocument & doc, QDomElement & elem) 
{
	QDomElement docElement = doc.createElement( "ccfdeclarationcodeblock" );

	setAttributesOnNode(doc, docElement);

	elem.appendChild( docElement );
}

void CodeClassFieldDeclarationBlock::loadFromXMI ( QDomElement & root ) 
{
	setAttributesFromNode(root);
}

void CodeClassFieldDeclarationBlock::setAttributesOnNode (QDomDocument & doc, QDomElement & elem ) {

	// set super-class attributes
	CodeBlockWithComments::setAttributesOnNode(doc, elem);
	OwnedCodeBlock::setAttributesOnNode(doc, elem);

}

/**
 * load params from the appropriate XMI element node.
 */
void CodeClassFieldDeclarationBlock::setAttributesFromNode( QDomElement & root ) {

	// set attributes from the XMI
	CodeBlockWithComments::setAttributesFromNode(root); // superclass load
	OwnedCodeBlock::setAttributesFromNode(root); // superclass load
	
	syncToParent();
}

/** set the class attributes from a passed object
 */
void CodeClassFieldDeclarationBlock::setAttributesFromObject (TextBlock * obj) {

	CodeBlockWithComments::setAttributesFromObject(obj);

	CodeClassFieldDeclarationBlock * ccb = dynamic_cast<CodeClassFieldDeclarationBlock*>(obj);
	if(ccb)
	{
		m_parentclassfield->disconnect(this);
		init(ccb->getParentClassField());

		syncToParent();
	}

}

void CodeClassFieldDeclarationBlock::syncToParent () {

	// for role-based accessors, we DONT write ourselves out when
	// the name of the role is not defined.
	if(!(getParentClassField()->parentIsAttribute()))
	{
		UMLRole * parent = (UMLRole*)getParentObject();
		if(parent->getName().isEmpty())
		{
			getComment()->setWriteOutText(false);
			setWriteOutText(false);
		} else {
			getComment()->setWriteOutText(true);
			setWriteOutText(true);
		}
	}

	// only update IF we are NOT AutoGenerated
	if(getContentType() != AutoGenerated)
		return;

	updateContent();

}

void CodeClassFieldDeclarationBlock::init (CodeClassField * parentCF) 
{
	m_parentclassfield = parentCF;
	m_canDelete = false;
	connect(m_parentclassfield,SIGNAL(modified()),this,SLOT(syncToParent()));
}

#include "codeclassfielddeclarationblock.moc"
