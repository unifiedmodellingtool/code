
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
 *      Date   : Mon Aug 04 2003
 */

/**
  We carve the XMLSchema document up into sections as follows:

  * header
  * XML schema body
*/

#include <iostream.h>
#include <kdebug.h>
// #include <qregexp.h>

#include "xmlschemaclassifiercodedocument.h"
#include "xmlschemacodegenerator.h"

// Constructors/Destructors
//  

XMLSchemaClassifierCodeDocument::XMLSchemaClassifierCodeDocument ( UMLClassifier * concept , XMLSchemaCodeGenerator *parent) 
   : ClassifierCodeDocument (concept, (CodeGenerator *) parent) { 
	init();
};

XMLSchemaClassifierCodeDocument::~XMLSchemaClassifierCodeDocument ( ) { };

//  
// Methods
//  

// Accessor methods
//

/**
 * Save the XMI representation of this object
 * @return      bool    status of save
 */
bool XMLSchemaClassifierCodeDocument::saveToXMI ( QDomDocument & doc, QDomElement & root ) {
        bool status = true;

        QDomElement docElement = doc.createElement( "javaclassifiercodedocument" );

        setAttributesOnNode(doc, docElement);

        root.appendChild( docElement );

        return status;
}

/**
 * load params from the appropriate XMI element node.
 */
void XMLSchemaClassifierCodeDocument::loadFromXMI ( QDomElement & root ) {
        setAttributesFromNode(root);
}

/** set attributes of the node that represents this class
 * in the XMI document.
 */
void XMLSchemaClassifierCodeDocument::setAttributesOnNode ( QDomDocument & doc, QDomElement & docElement)
{

        // superclass call
        ClassifierCodeDocument::setAttributesOnNode(doc,docElement);

        // now set local attributes/fields
// FIX
}

/** set the class attributes of this object from
 * the passed element node.
 */
void XMLSchemaClassifierCodeDocument::setAttributesFromNode ( QDomElement & root)
{

        // superclass save
        ClassifierCodeDocument::setAttributesFromNode(root);

        // now set local attributes
// FIX

}

/**
 * create a new CodeAccesorMethod object belonging to this CodeDocument.
 * @return      CodeAccessorMethod
 */
CodeAccessorMethod * XMLSchemaClassifierCodeDocument::newCodeAccessorMethod( CodeClassField *cf, CodeAccessorMethod::AccessorType type ) {
        return getParentGenerator()->newCodeAccessorMethod(cf, type);
}

/**
 * create a new CodeOperation object belonging to this CodeDocument.
 * @return      CodeOperation
 */
CodeOperation * XMLSchemaClassifierCodeDocument::newCodeOperation( UMLOperation * op) {
        return getParentGenerator()->newCodeOperation(this, op);
}


// Make it easier on ourselves 
/*
XMLSchemaCodeGenerationPolicy * XMLSchemaClassifierCodeDocument::getXMLSchemaPolicy() {
	CodeGenerator *g = getParentGenerator();
        XMLSchemaCodeGenerationPolicy * policy = dynamic_cast<XMLSchemaCodeGenerationPolicy*>(g->getPolicy());
        return policy;
}
*/

/**
 * Get the dialog widget which allows user interaction with the object parameters.
 * @return      CodeDocumentDialog
 */
/*
CodeDocumentDialog XMLSchemaClassifierCodeDocument::getDialog ( ) {
}
*/

bool XMLSchemaClassifierCodeDocument::forceDoc () {
        return getParentGenerator()->forceDoc();
}

// We overwritten by XMLSchema language implementation to get lowercase path
/*
QString XMLSchemaClassifierCodeDocument::getPath ( )
{

        QString path = getPackage();

        // Replace all white spaces with blanks
        path.simplifyWhiteSpace();

        // Replace all blanks with underscore
        path.replace(QRegExp(" "), "_");

        path.replace(QRegExp("\\."),"/");

        path.lower();

        return path;
}
*/


// Other methods
//  

/**
 * @param       op
 */
// in the vannilla version, we just tack all operations on the end
// of the document
bool XMLSchemaClassifierCodeDocument::addCodeOperation (CodeOperation * op ) {
        return addTextBlock(op);
}

// Initialize this xmlschema classifier code document
void XMLSchemaClassifierCodeDocument::init ( ) {

	setFileExtension(".xsd");

	// this makes the initial initialization of the textblocks 
	// within the document
        syncronize();

}

/*
QString XMLSchemaClassifierCodeDocument::scopeToXMLSchemaDecl(Uml::Scope scope)
{
        QString scopeString;
        switch(scope)
        {
                case Uml::Public:
                        scopeString = "public";
                        break;
                case Uml::Protected:
                        scopeString = "protected";
                        break;
                case Uml::Private:
                default:
                        scopeString = "private";
                        break;
        }
        return scopeString;
}
*/

// This method will cause the class to rebuild its text representation.
// based on the parent classifier object.
// For any situation in which this is called, we are either building the code
// document up, or replacing the existing auto-generated parts. As
// such, we will want to insert everything we resonablely will want
// during creation. We can set various parts of the document (esp. the
// comments) to appear or not, as needed.
void XMLSchemaClassifierCodeDocument::updateContent( ) 
{

cerr<<"XML schema ClassifierCodeDoc "<<this<<" SyncToParent Called"<<endl;

      	// Gather info on the various fields and parent objects of this class...
	// UMLClassifier * c = getParentClassifier();
	CodeGenerator * g = getParentGenerator();

      	// attribute-based ClassFields
      	// we do it this way to have the static fields sorted out from regular ones
/*
        QPtrList<CodeClassField> staticAttribClassFields = getSpecificClassFields (CodeClassField::Attribute, true);
        QPtrList<CodeClassField> attribClassFields = getSpecificClassFields (CodeClassField::Attribute, false);
      	// association-based ClassFields 
      	// dont care if they are static or not..all are lumped together
        QPtrList<CodeClassField> plainAssocClassFields = getSpecificClassFields ( CodeClassField::PlainAssociation );
        QPtrList<CodeClassField> aggregationClassFields = getSpecificClassFields ( CodeClassField::Aggregation );
        QPtrList<CodeClassField> compositionClassFields = getSpecificClassFields ( CodeClassField::Composition );
*/

//        bool hasOperationMethods = c->getFilteredOperationsList()->last() ? true : false;
        QString endLine = g->getNewLineEndingChars(); // a shortcut..so we dont have to call this all the time

	//
	// START GENERATING CODE/TEXT BLOCKS and COMMENTS FOR THE DOCUMENT
	//

	// ROOT Document BLOCK
	//

	// get the declaration block. If its not already present, add it too
        HierarchicalCodeBlock * rootBlock = getHierarchicalCodeBlock("rootBlock", "Schema", 1);

        // Update the comment: we only set comment to appear under the following conditions
        CodeComment * fcomment = rootBlock->getComment();
        if (!forceDoc() && !hasClassFields() )
		fcomment->setWriteOutText(false);
	else
		fcomment->setWriteOutText(true);

cerr<<"XMLschema ClassifierCodeDoc SyncToParent END "<<endl;

}

