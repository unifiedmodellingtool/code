
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
 *      Date   : Wed Jun 18 2003
 */

#include <kdebug.h>
#include "codeblockwithcomments.h"
#include "codedocument.h"
#include "hierarchicalcodeblock.h"

// Constructors/Destructors
//  

CodeBlockWithComments::CodeBlockWithComments ( HierarchicalCodeBlock * hb, const QString & body, const QString & comment)
	: CodeBlock (hb, body)
{
	initFields();
	CodeDocument * parent = hb->getParentDocument();
	CodeComment * codecomment = parent->newCodeComment();
	codecomment->setText(comment);
	setComment(codecomment);
}

CodeBlockWithComments::CodeBlockWithComments ( CodeDocument * parent , const QString & body, const QString & comment) 
	: CodeBlock (parent, body)
{
	initFields();
	CodeComment * codecomment = parent->newCodeComment();
	codecomment->setText(comment);
	setComment(codecomment);
}

CodeBlockWithComments::~CodeBlockWithComments ( ) { }

//  
// Methods
//  


// Accessor methods
//  


/**
 * Set the comment on this code block.
 */
void CodeBlockWithComments::setComment ( CodeComment * object ) {
	m_comment = object;
}

/**
 * Remove a Comment object from m_commentVector List
 */
CodeComment * CodeBlockWithComments::getComment ( ) {
	return m_comment;
}

// Other methods
//  

/**
 * Save the XMI representation of this object
 * @return      bool    status of save
 */
bool CodeBlockWithComments::saveToXMI ( QDomDocument & doc, QDomElement & root ) {
        bool status = true;

        QDomElement blockElement = doc.createElement( "codeblockwithcomments" );

        // set attributes
        setAttributesOnNode(doc, blockElement);

        root.appendChild( blockElement );

        return status;
}

void CodeBlockWithComments::setAttributesOnNode ( QDomDocument & doc, QDomElement & blockElement) 
{

        // set super-class attributes
        CodeBlock::setAttributesOnNode(doc, blockElement);

	// set local attributes now..e.g. a comment 
	// which we will store in its own separate child node block
        QDomElement commElement = doc.createElement( "header" );
        getComment()->saveToXMI(doc, commElement); // comment
        blockElement.appendChild( commElement);

}

void CodeBlockWithComments::setAttributesFromObject(TextBlock * obj)
{

        CodeBlock::setAttributesFromObject(obj);

        CodeBlockWithComments * cb = dynamic_cast<CodeBlockWithComments*>(obj);
        if(cb)
		getComment()->setAttributesFromObject((TextBlock*)cb->getComment());

}

/**
 * load params from the appropriate XMI element node.
 */
void CodeBlockWithComments::loadFromXMI ( QDomElement & root ) 
{
        setAttributesFromNode(root);
}

void CodeBlockWithComments::setAttributesFromNode( QDomElement & root) 
{

        // set attributes from superclass method the XMI
	CodeBlock::setAttributesFromNode(root);

	// load comment now
	// by looking for our particular child element
        QDomNode node = root.firstChild();
        QDomElement element = node.toElement();
	bool gotComment = false;
        while( !element.isNull() ) {
                QString tag = element.tagName();
                if( tag == "header" ) {
        		QDomNode cnode = element.firstChild();
        		QDomElement celem = cnode.toElement();
			getComment()->loadFromXMI(celem);
			gotComment = true;
			break;
		} 
		node = element.nextSibling();
		element = node.toElement();
	}

	if(!gotComment)
		kdWarning()<<" loadFromXMI : Warning: unable to initialize CodeComment in block:"<<getTag()<<endl;

}

/**
 * @return	QString
 */
QString CodeBlockWithComments::toString ( ) {

	QString string = QString();

	if(getWriteOutText()) {
		QString indent = getIndentationString();
		QString endLine = getNewLineEndingChars();
		QString body = formatMultiLineText (getText(), indent, endLine);
		QString comment = getComment()->toString();

		if(!comment.isEmpty() && getComment()->getWriteOutText())
			string.append(comment);
		if(!body.isEmpty())
			string.append(body);
	}

	return string;
}

// slave indentation level for both the header and text body
void CodeBlockWithComments::setOverallIndentationLevel ( int level ) 
{
	setIndentationLevel(level);
	m_comment->setIndentationLevel(level);
}

void CodeBlockWithComments::initFields ( ) {
	m_comment = getParentDocument()->newCodeComment();
}

#include "codeblockwithcomments.moc"
