/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2004-2006                                               *
 *   Umbrello UML Modeller Authors <uml-devel@uml.sf.net>                  *
 ***************************************************************************/

/*  This code generated by:
 *      Author : thomas
 *      Date   : Thu Aug 28 2003
 */

#ifndef CPPHEADERCODEDOCUMENT_H
#define CPPHEADERCODEDOCUMENT_H

#include <qstring.h>

#include "../codeclassfieldlist.h"
#include "../classifiercodedocument.h"
#include "../hierarchicalcodeblock.h"
#include "classifierinfo.h"

class CPPHeaderClassDeclarationBlock;

/**
  * class CPPHeaderCodeDocument
  * A CPP UMLClassifier Header Code Document.
  */

class CPPHeaderCodeDocument : public ClassifierCodeDocument
{
    Q_OBJECT
public:

    // Constructors/Destructors
    //

    /**
     * Constructor
     */
    CPPHeaderCodeDocument (UMLClassifier * classifier);

    /**
     * Empty Destructor
     */
    virtual ~CPPHeaderCodeDocument ( );

    /** add a code operation to this cpp classifier code document.
     *  @return bool which is true IF the code operation was added successfully
     */
    bool addCodeOperation (CodeOperation * op );

    /**
     * Save the XMI representation of this object
     */
    //virtual void saveToXMI ( QDomDocument & doc, QDomElement & root );

protected:

    // reset/clear our inventory of textblocks in this document
    void resetTextBlocks();

    /**
    * need to overwrite this for cpp header since we need to pick up the
    * header class declaration block.
    */
    virtual void loadChildTextBlocksFromNode ( QDomElement & root);

    void addOrUpdateCodeClassFieldMethodsInCodeBlock(CodeClassFieldList &list, CPPHeaderClassDeclarationBlock * codeBlock);

    /**
     * create a new code comment. IN this case it is a CPPCodeDocumentation object.
     */
    CodeComment * newCodeComment ( );

    void updateContent();

private:

    CPPHeaderClassDeclarationBlock * classDeclCodeBlock;

    HierarchicalCodeBlock * publicBlock;
    HierarchicalCodeBlock * privateBlock;
    HierarchicalCodeBlock * protectedBlock;

    HierarchicalCodeBlock * namespaceBlock;

    HierarchicalCodeBlock * pubConstructorBlock;
    HierarchicalCodeBlock * protConstructorBlock;
    HierarchicalCodeBlock * privConstructorBlock;

    HierarchicalCodeBlock * pubOperationsBlock;
    HierarchicalCodeBlock * privOperationsBlock;
    HierarchicalCodeBlock * protOperationsBlock;

    QString fileName; // Just for our convience in creating code
    QString endLine; // characters for ending line. Just for our convience in creating code
    QString CPPClassName;

    CPPHeaderClassDeclarationBlock * getClassDecl();

};

#endif // CPPHEADERCODEDOCUMENT_H
