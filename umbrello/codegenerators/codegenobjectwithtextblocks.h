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

#ifndef CODEGENOBJECTWITHTEXTBLOCKS_H
#define CODEGENOBJECTWITHTEXTBLOCKS_H

#include "codeaccessormethod.h"
#include "textblocklist.h"

#include <QtCore/QMap>

class CodeBlock;
class CodeBlockWithComments;
class CodeClassField;
class CodeComment;
class CodeDocument;
class HierarchicalCodeBlock;
class TextBlock;

/**
 * This abstract class is for code generator objects which 'own' text blocks.
 */
class CodeGenObjectWithTextBlocks
{
public:

    /**
     * Constructor
     */
    CodeGenObjectWithTextBlocks ( CodeDocument *parent );

    /**
     * Empty Destructor
     */
    virtual ~CodeGenObjectWithTextBlocks ( );

    /**
     * Add a TextBlock object to the m_textblockVector List
     * @return boolean value where false means not added because an TextBlock
     *                 object with that tag already exists in this document.
     */
    virtual bool addTextBlock ( TextBlock * add_object );

    /**
     * Remove a TextBlock object from m_textblockVector List
     */
    virtual bool removeTextBlock ( TextBlock * remove_object );

    /**
     * Insert a new text block before/after the existing text block. Returns
     * false if it cannot insert the textblock.
     */
    virtual bool insertTextBlock (TextBlock * newBlock, TextBlock * existingBlock, bool after) = 0;

    /**
     * Get the list of TextBlock objects held by m_textblockVector
     * @return TextBlockList list of TextBlock objects held by m_textblockVector
     */
    TextBlockList * getTextBlockList ( ) const;

    /**
     * Will get a hierarchicalcodeblock from the document with given tag. IF the codeblock
     * doesn't exist, then it will create it at the end of the document textBlock
     * list and pass back a reference.
     * @return  HierarchicalCodeBlock
     * @param   tag
     * @param   comment
     * @param   indentLevel
     */
    virtual HierarchicalCodeBlock * getHierarchicalCodeBlock ( const QString &tag, const QString &comment, int indentLevel );

    /**
     * Will get a codeblockwithcomments from the document with given tag. IF the codeblock
     * doesn't exist, then it will create it at the end of the document textBlock
     * list and pass back a reference.
     * @return  CodeBlockWithComments
     * @param   tag
     * @param   comment
     * @param   indentLevel
     */
    virtual CodeBlockWithComments * getCodeBlockWithComments ( const QString &tag, const QString &comment, int indentLevel );

    /**
     * Allows the user to add a code comment to the end of the list
     * of text blocks in this document OR, if a text block already exists
     * with that tag, it will update it with the passed text as appropriate.
     * @return codeblock/comment pointer to the object which was created/updated.
     * @return   CodeComment
     * @param    tag
     * @param    text
     * @param    indentationLevel
     */
    CodeComment * addOrUpdateTaggedCodeComment (const QString &tag = "", const QString &text = "", int indentationLevel = 0 );

    /**
     * Allows the user to either add a code block with comments to the end of the list
     * of text blocks in this document OR, if a text block already exists
     * with that tag, it will update it with the passed text as appropriate.
     * @return codeblock/comment pointer to the object which was created/updated.
     * @return   CodeBlockWithComments
     * @param    tag
     * @param    text
     * @param    comment
     * @param    indentLevel
     * @param    forceUserBlockUpdate
     */
    CodeBlockWithComments * addOrUpdateTaggedCodeBlockWithComments (const QString &tag, const QString &text, const QString &comment, int indentLevel, bool forceUserBlockUpdate );

    /**
     * @return  TextBlock
     * @param   tag
     */
    TextBlock * findTextBlockByTag ( const QString &tag );

    /**
     * @return  QString
     * @param   prefix
     */
    virtual QString getUniqueTag (const QString& prefix = "" ) = 0;

    /**
     * Virtual methods that return a new code document objects.
     */
    virtual CodeBlock * newCodeBlock() = 0;
    virtual CodeBlockWithComments * newCodeBlockWithComments() = 0;
    virtual HierarchicalCodeBlock * newHierarchicalCodeBlock() = 0;

    /**
     * Find the direct parent for a given textblock. This
     * may be any object which holds text blocks, e.g. a CodeGenObjectWithTextBlocks.
     * @return parent object. Could return null if the textblock is missing from the
     * branch of the document tree being examined.
     */
    CodeGenObjectWithTextBlocks * findParentObjectForTaggedTextBlock (const QString & tag);

protected:

    /**
     * Set attributes of the node that represents this class
     * in the XMI document.
     */
    virtual void setAttributesOnNode (QDomDocument & doc, QDomElement & elem );

    /**
     * Set the class attributes of this object from
     * the passed element node.
     */
    virtual void setAttributesFromNode ( QDomElement & element);

    /*virtual*/ void setAttributesFromObject (CodeGenObjectWithTextBlocks * obj);

    /**
     * In this vanilla version, we only load comments and codeblocks
     * as they are the only instanciatable (vanilla) things
     * this method should be overridden if this class is inherited
     * by some other class that is concrete and takes children
     * derived from codeblock/codecomment/hierarchicalcb/ownedhiercodeblock
     */
    virtual void loadChildTextBlocksFromNode ( QDomElement & root);

    /**
     * Reset/clear the inventory text blocks held by this object.
     */
    virtual void resetTextBlocks();

    /**
     * Find specific text block belonging to code classfields.
     * Block may not presently be alocated t othe textblock list.
     */
    virtual TextBlock * findCodeClassFieldTextBlockByTag( const QString &tag) = 0;

    QMap<QString, TextBlock *> m_textBlockTagMap;
    TextBlockList m_textblockVector;

private:

    // needed in order to use findTextBlocksByTag
    CodeDocument *m_pCodeDoc;

};

#endif // CODEGENOBJECTWITHTEXTBLOCKS_H