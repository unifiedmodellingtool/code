/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003      Brian Thomas <thomas@mail630.gsfc.nasa.gov>   *
 *   copyright (C) 2004-2008                                               *
 *   Umbrello UML Modeller Authors <uml-devel@uml.sf.net>                  *
 ***************************************************************************/

#ifndef HIERARCHICALCODEBLOCK_H
#define HIERARCHICALCODEBLOCK_H

#include "codegenobjectwithtextblocks.h"
#include "codeblockwithcomments.h"
#include "codeclassfieldlist.h"

#include <QtCore/QMap>
#include <QtCore/QString>

class HierarchicalCodeBlock : public CodeBlockWithComments, public CodeGenObjectWithTextBlocks
{
    friend class CodeGenObjectWithTextBlocks;
public:

    /**
     * Constructor
     */
    explicit HierarchicalCodeBlock ( CodeDocument * doc , const QString &startString = "", const QString &endString = "", const QString &comment = "");

    /**
     * Empty Destructor
     */
    virtual ~HierarchicalCodeBlock ( );

    /**
     * Set the value of m_endText
     * @param new_var the new value of m_endText
     */
    void setEndText ( const QString &new_var );

    /**
     * Get the value of m_endText
     * @return the value of m_endText
     */
    QString getEndText ( ) const;

    /**
     * Add a TextBlock object to the m_textblockVector List
     */
    bool addTextBlock ( TextBlock * add_object );

    /**
     * Insert a new text block before/after the existing text block. Returns
     * false if it cannot insert the textblock.
     */
    bool insertTextBlock (TextBlock * newBlock, TextBlock * existingBlock, bool after = true);

    /**
     * Remove a TextBlock object from m_textblockVector List
     * returns boolean - true if successful
     */
    bool removeTextBlock ( TextBlock * remove_object );

    /**
     * @param   text
     */
    void setStartText ( const QString &text );

    /**
     * @return  QString
     */
    QString getStartText ( ) const;

    /**
     * Save the XMI representation of this object
     */
    virtual void saveToXMI ( QDomDocument & doc, QDomElement & root );

    /**
     * load params from the appropriate XMI element node.
     */
    virtual void loadFromXMI ( QDomElement & root );

    /**
     * @return  QString
     */
    virtual QString toString ( ) const;

    /**
     * return a unique, and currently unallocated, text block tag for this hblock
     */
    QString getUniqueTag();
    QString getUniqueTag( const QString& prefix );

    /**
     * Utility method to add accessormethods in this object
     */
    void addCodeClassFieldMethods ( CodeClassFieldList &list );

    virtual CodeBlock * newCodeBlock();
    virtual CodeBlockWithComments * newCodeBlockWithComments();
    virtual HierarchicalCodeBlock * newHierarchicalCodeBlock();

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
    virtual void setAttributesOnNode (QDomDocument & doc, QDomElement & elem );

    /**
     * set the class attributes of this object from
     * the passed element node.
     */
    virtual void setAttributesFromNode ( QDomElement & element);

    /**
     * set the class attributes from a passed object
     */
    virtual void setAttributesFromObject (TextBlock * obj);

    /**
     * look for specific text blocks which belong to code classfields
     */
    TextBlock * findCodeClassFieldTextBlockByTag ( const QString &tag );

private:

    QString m_startText;
    QString m_endText;

    QString childTextBlocksToString() const;
    void initAttributes ( ) ;

};

#endif // HIERARCHICALCODEBLOCK_H