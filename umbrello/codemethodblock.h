
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
 *      Date   : Fri Jun 20 2003
 */



#ifndef CODEMETHODBLOCK_H
#define CODEMETHODBLOCK_H

#include <qstring.h>
#include <qptrlist.h>

#include "ownedcodeblock.h"
#include "codeblockwithcomments.h"
#include "codeparameter.h"
#include "umlnamespace.h"

class ClassifierCodeDocument;

/**
  * class CodeMethodBlock
  * A  common type of "code block" that occurs in OO code.
  */

class CodeMethodBlock : public CodeBlockWithComments, OwnedCodeBlock 
{
	Q_OBJECT
public:

	// Constructors/Destructors
	//  


	/**
	 * Empty Constructor
	 */
	CodeMethodBlock ( ClassifierCodeDocument * doc );
	CodeMethodBlock ( ClassifierCodeDocument * doc , QString body, QString comment);

	/**
	 * Empty Destructor
	 */
	virtual ~CodeMethodBlock ( );

	// Public attributes
	//  

	/**
	 * @return	QString
	 */
	virtual QString toString ( );

        /**
         * Get the starting text that begins this method before the body is printed.
         */
        QString getStartMethodText () const;

        /**
         * Get the ending text that finishes this method after the body is printed.
         */
        QString getEndMethodText () const;

	// get the parent code document
	CodeDocument * getParentDocument();

protected:

        /**
         * Set the starting text that begins this method before the body is printed.
         */
        void setStartMethodText (QString value);

        /**
         * Set the ending text that finishes this method after the body is printed.
         */
        void setEndMethodText (QString value);

	/** this is the method called from within syncToparent().
	  * to update the start and end Method text. It is called
     	  * whether or not the method is Auto or User generated.
	  */
	virtual void updateMethodDeclaration ( ) = 0;

	/** this is the method called from within syncToparent().
	  * to update the *body* of the method
     	  * It is only called if the method is Auto-generated.
	  */
	virtual void updateContent ( ) = 0;

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
        virtual void setAttributesFromObject (TextBlock * obj);

private:

	QString m_startMethod;
	QString m_endMethod;

	void initFields ( );

public slots:

	virtual void syncToParent();
};

#endif // CODEMETHODBLOCK_H
