
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



#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include <qdom.h>
#include <qobject.h>
#include <qstring.h>

class CodeDocument;

/**
  * class TextBlock
  * The fundemental unit of text within an output file containing code.
  */

class TextBlock : virtual public QObject {
	Q_OBJECT
public:

	// Constructors/Destructors
	//  

	/**
	 * Constructors 
	 */
	TextBlock ( CodeDocument * parent, const QString & text = "");

	// destructor 
	~TextBlock ( );

	// Public attributes
	//  

	// Public attribute accessor methods
	//  

	/**
	 * Set the value of m_text
	 * The actual text of this code block.
	 * @param new_var the new value of m_text
	 */
	void setText ( QString new_var );

	/**
	 * Add text to this object.
  	 *
 	 */
	void appendText ( QString new_text );

	/**
	 * Get the value of m_text
	 * The actual text of this code block.
	 * @return the value of m_text
	 */
	QString getText ( ) const;

    	/**
         * Get the tag of this text block. This tag
         * may be used to find this text block in the code document
         * to which it belongs.
         */
        QString getTag( ) const;

        /**
         * Set the tag of this text block. This tag
         * may be used to find this text block in the code document
         * to which it belongs.
         */
        void setTag( QString value );
 
	/**
	 * Get the value of m_parentDoc
	 * @return the value of m_parentDoc
 	 */
	CodeDocument * getParentDocument ( );

	/**
	 * Set the value of m_writeOutText
	 * Whether or not to include the text of this TextBlock into a file.
	 * @param new_var the new value of m_writeOutText
	 */
	void setWriteOutText ( bool new_var );

	/**
	 * Get the value of m_writeOutText
	 * Whether or not to include the text of this TextBlock into a file.
	 * @return the value of m_writeOutText
	 */
	bool getWriteOutText ( );

	/** Set how many times to indent this text block. 
	 * The amount of each indenatation is determined from the parent
	 * codedocument codegeneration policy.
	 */
	void setIndentationLevel ( int level );

	/** Get how many times to indent this text block. 
	 * The amount of each indenatation is determined from the parent
	 * codedocument codegeneration policy.
	 */
	int getIndentationLevel ( );

	/** Get the actual amount of indentation for a given level of indentation.
         */
	QString getIndentationString ( int level = 0);

	/** Get how much a single "level" of indentation will actually indent.
	 */
	QString getIndentation();

	QString getNewLineEndingChars ( );

	/** Format a long text string to be more readable.
	 */
	// should be static 
	QString formatMultiLineText ( const QString &text, const QString &linePrefix, QString breakStr, 
                                      bool alwaysAddBreak = true, bool lastLineHasBreak = true);

	/**
	 * @return	QString
	 */
	virtual QString toString ( );

	/** encode text for XML storage
	 * we simply convert all types of newLines to the "\n" or &#010;
	 * entity.
	 */
	static QString encodeText( QString text , QString endChars);


        /** decode text from XML storage
         * We simply convert all newLine entity &#010; to chosen line ending.
         */
	static QString decodeText( QString text ,QString endChars);

	/**
         * Save the XMI representation of this object
         * @return      bool    status of save
         */
        virtual bool saveToXMI ( QDomDocument & doc, QDomElement & root ) = 0;

        /**
         * load params from the appropriate XMI element node.
         */
        virtual void loadFromXMI ( QDomElement & root ) = 0;

	/** Determine if its OK to delete this textblock from the document.
	 * Used by the text editor to know if deletion could cause a crash of
	 * the program.
	 */
	bool canDelete ();

        /** set the class attributes from a passed object
         */
        virtual void setAttributesFromObject (TextBlock * obj);

protected:

        /**
         * Set the value of m_parentDocument
         * @param new_var the new value of m_parentDoc
         */
        void setParentDocument ( CodeDocument * new_var );

	/** set attributes of the node that represents this class
	 * in the XMI document.
	 */
	virtual void setAttributesOnNode ( QDomDocument & doc, QDomElement & blockElement);

	/** set the class attributes of this object from
	 * the passed element node.
	 */ 
	virtual void setAttributesFromNode ( QDomElement & element);

	bool m_canDelete;

private:

        // The actual text of this code block.
        QString m_text;
        QString m_tag;

        // Whether or not to include the text of this TextBlock into a file.
        bool m_writeOutText;

	int m_indentationLevel;
	CodeDocument * m_parentDocument;

	void initFields ( CodeDocument * doc);

};

#endif // TEXTBLOCK_H
