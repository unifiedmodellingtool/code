
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
 *      Date   : Mon Jun 30 2003
 */

#include "javacodeoperation.h"

#include "javaclassifiercodedocument.h"
#include "javacodedocumentation.h"

// Constructors/Destructors
//  

JavaCodeOperation::JavaCodeOperation ( JavaClassifierCodeDocument * doc, UMLOperation *parent, QString body, QString comment )
    : CodeOperation ((ClassifierCodeDocument*)doc, parent, body, comment) 
{
	init(doc, parent);
};

JavaCodeOperation::JavaCodeOperation ( JavaClassifierCodeDocument * doc, UMLOperation *parent )
    : CodeOperation ((ClassifierCodeDocument*)doc, parent) 
{
	init(doc, parent);
};

JavaCodeOperation::~JavaCodeOperation ( ) { };

// Other methods
//  

/** Save the XMI representation of this object
 * @return      bool    status of save
 */
bool JavaCodeOperation::saveToXMI ( QDomDocument & doc, QDomElement & root ) {
        bool status = true;

        QDomElement blockElement = doc.createElement( "codeoperation" );

        // set attributes
        setAttributesOnNode(doc, blockElement);

        root.appendChild( blockElement );

        return status;
}

void JavaCodeOperation::setAttributesOnNode ( QDomDocument & doc, QDomElement & blockElement)
{

        // set super-class attributes
        CodeOperation::setAttributesOnNode(doc, blockElement);

        // set local attributes now

}

/**
 * load params from the appropriate XMI element node.
 */
void JavaCodeOperation::loadFromXMI ( QDomElement & root )
{
        setAttributesFromNode(root);
}

void JavaCodeOperation::setAttributesFromNode( QDomElement & root)
{

        // set attributes from superclass method the XMI
        CodeOperation::setAttributesFromNode(root);

        // load local stuff

}

// we set the body of the operation here
void JavaCodeOperation::updateContent() {
	// empty. Dont auto-generate content for operations
}

// we basically want to update the doc and start text of this method
void JavaCodeOperation::updateMethodDeclaration()
{

        CodeDocument * doc = getParentDocument();
        JavaClassifierCodeDocument * javadoc = dynamic_cast<JavaClassifierCodeDocument*>(doc);
	UMLOperation * o = getParentOperation();

	// first, the comment on the operation
	QString comment = o->getDoc();
	getComment()->setText(comment);

	// now, the starting text.
	QString strVis = javadoc->scopeToJavaDecl(o->getScope());
	// no return type for constructors
	QString returnType = o->isConstructorOperation() ? QString("") : (o->getReturnType() + QString(" "));
	QString methodName = o->getName();
	QString paramStr = QString("");

	// assemble parameters
        QPtrList<UMLAttribute> * list = getParentOperation()->getParmList();
	int nrofParam = list->count();
	int paramNum = 0;
	for(UMLAttribute* parm = list->first(); parm; parm=list->next())
	{
		QString rType = parm->getTypeName();
		QString paramName = parm->getName();
		paramStr += rType + " " + paramName;
		paramNum++;

		if (paramNum != nrofParam )
			paramStr  += ", ";
	}

	QString startText = strVis + " "+ returnType + methodName + " ( "+paramStr+") {";
	setStartMethodText(startText);

}

void JavaCodeOperation::init (JavaClassifierCodeDocument * doc, UMLOperation * parent ) 
{

	// lets not go with the default comment and instead use
	// full-blown java documentation object instead 
        setComment(new JavaCodeDocumentation(doc));

	// these things never change..
        setOverallIndentationLevel(1);
	setEndMethodText("}"); 

        updateMethodDeclaration();
        updateContent();

}
