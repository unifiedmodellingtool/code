
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
 *      Date   : Thu Jun 19 2003
 */

#include <iostream.h>

#include <kdebug.h>
#include <kconfig.h>
#include <qregexp.h>

#include "javacodegenerator.h"
#include "javacodecomment.h"
#include "javacodeclassfield.h"
#include "javacodeclassfielddeclarationblock.h"
#include "javagetaccessormethod.h"
#include "javasetaccessormethod.h"
#include "javaaddaccessormethod.h"
#include "javaremoveaccessormethod.h"
#include "javalistaccessormethod.h"

// Constructors/Destructors
//  

JavaCodeGenerator::JavaCodeGenerator ( UMLDoc * parentDoc , const char * name, QDomElement & elem )
    : CodeGenerator ( parentDoc , name) 
{
	initFields();
	loadFromXMI(elem);
}

JavaCodeGenerator::JavaCodeGenerator ( UMLDoc * parentDoc, const char * name )
    : CodeGenerator ( parentDoc , name) 
{

	initFields();
};

JavaCodeGenerator::~JavaCodeGenerator ( ) { 
 	cerr<<"JavaCodeGenerator "<<this<<" destroyed"<<endl;
};

//  
// Methods
//  

// return our language
QString JavaCodeGenerator::getLanguage() {
	return "Java";
}

/**
 * Set the value of m_createANTBuildFile
 * @param new_var the new value of m_createANTBuildFile
 */
void JavaCodeGenerator::setCreateANTBuildFile ( bool buildIt) {
        m_createANTBuildFile = buildIt;
        CodeDocument * antDoc = findCodeDocumentByID("ANTDOC");
	if (antDoc)
		antDoc->setWriteOutCode(buildIt);
}

/**
 * Get the value of m_createANTBuildFile
 * @return the value of m_createANTBuildFile
 */
bool JavaCodeGenerator::getCreateANTBuildFile ( ) {
        return m_createANTBuildFile;
}

// Accessor methods
//  


// Public attribute accessor methods
//  


// Other methods
//  

QString JavaCodeGenerator::capitalizeFirstLetter(QString string)
{
        // we could lowercase everything tostart and then capitalize? Nah, it would
        // screw up formatting like getMyRadicalVariable() to getMyradicalvariable(). Bah.
        QChar firstChar = string.at(0);
        string.replace( 0, 1, firstChar.upper());
        return string;
}

void JavaCodeGenerator::setPolicy ( CodeGenerationPolicy* policy ) 
{
	JavaCodeGenerationPolicy * jpolicy = dynamic_cast<JavaCodeGenerationPolicy*>(policy);
	CodeGenerator::setPolicy(policy);
	setJavaPolicy(jpolicy);
}

void JavaCodeGenerator::setJavaPolicy( JavaCodeGenerationPolicy * policy) {
        m_javacodegenerationpolicy = policy;
}

JavaCodeGenerationPolicy * JavaCodeGenerator::getJavaPolicy() {
        return m_javacodegenerationpolicy;
}

JavaCodeGenerationPolicy::JavaCommentStyle JavaCodeGenerator::getCommentStyle ( ) 
{
	return getJavaPolicy()->getCommentStyle();
}

bool JavaCodeGenerator::getAutoGenerateConstructors ( ) 
{
	return getJavaPolicy()->getAutoGenerateConstructors();
} 

bool JavaCodeGenerator::getAutoGenerateAccessors ( )
{
        return getJavaPolicy()->getAutoGenerateAccessors ();
}

/**
 * @return      JavaANTCodeDocument
 */
JavaANTCodeDocument * JavaCodeGenerator::newANTCodeDocument ( ) {
	return new JavaANTCodeDocument(this);
}

CodeGenerationPolicy * JavaCodeGenerator::newCodeGenerationPolicy( KConfig * config)
{
	CodeGenerationPolicy * myPolicy = new JavaCodeGenerationPolicy(this,config);
	return myPolicy;
}

CodeOperation * JavaCodeGenerator::newCodeOperation (ClassifierCodeDocument * doc, UMLOperation * op)
{
	return new JavaCodeOperation((JavaClassifierCodeDocument*)doc,op);
}

CodeAccessorMethod * JavaCodeGenerator::newCodeAccessorMethod(CodeClassField *cf, CodeAccessorMethod::AccessorType type) {
	CodeAccessorMethod * method = (CodeAccessorMethod*) NULL;
	switch (type) {
		case CodeAccessorMethod::GET:  
			method = new JavaGetAccessorMethod((JavaCodeClassField*)cf);
			method->setOverallIndentationLevel(1);
			break;
		case CodeAccessorMethod::SET:  
			method = new JavaSetAccessorMethod((JavaCodeClassField*)cf);
			method->setOverallIndentationLevel(1);
			break;
		case CodeAccessorMethod::LIST: 
			method = new JavaListAccessorMethod((JavaCodeClassField*)cf);
			method->setOverallIndentationLevel(1);
			break;
		case CodeAccessorMethod::REMOVE:  
			method = new JavaRemoveAccessorMethod((JavaCodeClassField*)cf);
			method->setOverallIndentationLevel(1);
			break;
		case CodeAccessorMethod::ADD:
			method = new JavaAddAccessorMethod((JavaCodeClassField*)cf);
			method->setOverallIndentationLevel(1);
			break;
		default:
			// perhaps this is a fatal condition??
			kdWarning()<<"Error: cannot make accessor method with type:"<<type<<endl;
			break;
	}
	return method;
}

CodeClassFieldDeclarationBlock * JavaCodeGenerator::newDeclarationCodeBlock (CodeClassField * cf ) {
	return new JavaCodeClassFieldDeclarationBlock(cf);
}

QString JavaCodeGenerator::getListFieldClassName () {
	return QString("Vector");
}

/**
 * @return      ClassifierCodeDocument
 * @param       classifier 
 */
CodeDocument * JavaCodeGenerator::newClassifierCodeDocument ( UMLClassifier * c)
{
        JavaClassifierCodeDocument * doc = new JavaClassifierCodeDocument(c,this);
        return doc;
}

CodeClassField * JavaCodeGenerator::newCodeClassField (ClassifierCodeDocument * doc, UMLAttribute * at) {
	//JavaClassifierCodeDocument*jdoc = dynamic_cast<JavaClassifierCodeDocument*>(doc);
	JavaClassifierCodeDocument *jdoc = (JavaClassifierCodeDocument*) doc;
	return new JavaCodeClassField(jdoc,at);
}

CodeClassField * JavaCodeGenerator::newCodeClassField (ClassifierCodeDocument * doc, UMLRole * role) {
	// JavaClassifierCodeDocument *jdoc = dynamic_cast<JavaClassifierCodeDocument*>(doc);
	JavaClassifierCodeDocument *jdoc = (JavaClassifierCodeDocument*)doc;
        return new JavaCodeClassField(jdoc,role);
}

CodeComment * JavaCodeGenerator::newCodeComment ( CodeDocument * doc) {
        return new JavaCodeComment(doc);
}

void JavaCodeGenerator::loadFromXMI(QDomElement & qElement ) {

cerr<<" **** LOAD FROM XMI CALLED FOR JAVA CODE GENERATOR **** "<<endl;

        //now look for our particular child element
        QDomNode node = qElement.firstChild();
        QDomElement element = node.toElement();
	QString langType = getLanguage();
        while( !element.isNull() ) {
                QString tag = element.tagName();
                if( tag == "codegenerator" && element.attribute( "language", "UNKNOWN" ) == langType ) {
			// got our code generator element, now load 
			// codedocuments
        		QDomNode codeDocNode = element.firstChild();
        		QDomElement codeDocElement = codeDocNode.toElement();
        		while( !codeDocElement.isNull() ) {

                		QString docTag = codeDocElement.tagName();
                		if( docTag == "codedocument" ) {
					QString id = codeDocElement.attribute( "tag", "-1" );
cerr<<" XMI LOAD: GOT CODE DOCUMENT W/ ID:"<<id.latin1()<<endl;
					CodeDocument * codeDoc = findCodeDocumentByID(id);
					if(codeDoc)
						codeDoc->loadFromXMI(element);
					else { 
						kdWarning()<<" LOAD FROM XMI: MISSING CODE DOCUMENT, create a new one or ignore and throw a warning?"<<endl;
						// FIX: have switch based on a 'type' attribute
					}
				} else {
					kdWarning()<<" XMI WARNING: got unknown codegenerator child node:"<<docTag<<", ignoring."<<endl;
				}

				codeDocNode = codeDocElement.nextSibling();
                		codeDocElement = codeDocNode.toElement();
			}
			break; // no more to do 
		}
		node = element.nextSibling();
                element = node.toElement();
	}
}

bool JavaCodeGenerator::saveToXMI ( QDomDocument & doc, QDomElement & root ) {
	QString langType = getLanguage();
	QDomElement docElement = doc.createElement( "codegenerator" );
	docElement.setAttribute("language",langType);
	bool status = true;

	QPtrList<CodeDocument> * docList = getCodeDocumentList();
	for (CodeDocument * codeDoc = docList->first(); codeDoc; codeDoc= docList->next())
	{
		ClassifierCodeDocument * classDoc = dynamic_cast<ClassifierCodeDocument*>(codeDoc);
/*
		if(classDoc)
{
cerr<<" saveToXMI got a classifier code document"<<endl;
			status = classDoc->saveToXMI(doc, docElement) ? status : false;
}
		else
*/
			status = codeDoc->saveToXMI(doc, docElement) ? status : false;
	}

	root.appendChild( docElement );

	return status;
}

void JavaCodeGenerator::initFields ( ) {

cerr<<"JAVA CODE GENERTOR INIT"<<endl;

	setPolicy ( new JavaCodeGenerationPolicy(this, getPolicy()) );

	// load Classifier documents from parent document
	initFromParentDocument();

	// add in an ANT document
        JavaANTCodeDocument * buildDoc = newANTCodeDocument( );
        addCodeDocument(buildDoc);

	// set our 'writeout' policy for that code document
        setCreateANTBuildFile(DEFAULT_BUILD_ANT_DOC);

cerr<<"JAVA CODE GENERTOR INIT - END"<<endl;
}

