
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
 *      Date   : Aug Jun 30 2003
 */

#ifndef XMLSCHEMACODECLASSFIELD_H
#define XMLSCHEMACODECLASSFIELD_H

#include <qstring.h>

#include "../codeclassfield.h"
 
class XMLSchemaClassifierCodeDocument;

class XMLSchemaCodeClassField : public CodeClassField
{
	Q_OBJECT
public:

	// Constructors/Destructors
	//  

	/**
	 * Constructors 
	 */
	XMLSchemaCodeClassField (XMLSchemaClassifierCodeDocument * parentDoc, UMLRole * role);
	XMLSchemaCodeClassField (XMLSchemaClassifierCodeDocument * parentDoc, UMLAttribute * attrib);

	/**
	 * Empty Destructor
	 */
	virtual ~XMLSchemaCodeClassField ( );

	/**
	 * @return	QString
	 */
	QString toXML ( );

protected:

	QString fixTypeName(QString string); 
//	QString getFieldType();
//	QString getFieldName();
//	QString getInitialValue();

private:

};

#endif // XMLSCHEMACODECLASSFIELD_H
