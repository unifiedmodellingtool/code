/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DATATYPE_H
#define DATATYPE_H

#include "classifier.h"

/**
 * This class contains the non-graphical information required for a UML
 * Datatype.
 * This class inherits from @ref UMLClassifier which contains most of the
 * information.
 *
 * The @ref UMLDoc class creates instances of this type.  All Datatypes
 * will need a unique id.  This will be given by the @ref UMLDoc class.
 * If you don't leave it up to the @ref UMLDoc class then call the method
 * @ref UMLDoc::getUniqueID to get a unique id.
 *
 * @short Information for a non-graphical Datatype.
 * @author Jonathan Riddell
 * Bugs and comments to uml-devel@lists.sf.net or http://bugs.kde.org
 */
class UMLDatatype : public UMLClassifier {
public:
	/**
	 * Sets up an datatype.
	 *
	 * @param name		The name of the Concept.
	 * @param id		The unique id of the Concept.
	 */
	UMLDatatype(const QString & name = "", int id = -1);

	/**
	 * Standard deconstructor.
	 */
	virtual ~UMLDatatype();

	/**
	 * Overloaded '==' operator.
	 */
  	bool operator==(UMLDatatype& rhs);
  
	/**
	 * Empty, just calls parent method
	 */
	virtual QString uniqChildName(const UMLObject_Type type);

	/**
	 * Creates the <UML:Datatype> element including its operations,
	 * attributes and templates.
	 */
	virtual bool saveToXMI(QDomDocument& qDoc, QDomElement& qElement);

	/**
	 * Loads the <UML:Datatype> element including its operations,
	 * attributes and templates.
	 */
	virtual bool loadFromXMI(QDomElement& element);

	/**
	 * returns false
	 */
	virtual bool isInterface();

protected:

	/**
	 * Initializes key variables of the class.
	 */
	virtual void init(); // doesnt seem to be any reason for this to be public 
};

#endif // DATATYPE_H 
