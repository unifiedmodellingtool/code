
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
 
#ifndef JAVASETACCESSORMETHOD_H
#define JAVASETACCESSORMETHOD_H

#include <qstring.h>

#include "../codeaccessormethod.h"
#include "javacodeclassfield.h"

class JavaSetAccessorMethod : public CodeAccessorMethod
{
	Q_OBJECT
public:

	// Constructors/Destructors
	//  


	/**
	 * Constructor
	 */
	JavaSetAccessorMethod ( JavaCodeClassField * field );

	/**
	 * Empty Destructor
	 */
	virtual ~JavaSetAccessorMethod ( );

       /**
         * Save the XMI representation of this object
         * @return      bool    status of save
         */
        virtual bool saveToXMI ( QDomDocument & doc, QDomElement & root );

        /**
         * load params from the appropriate XMI element node.
         */
        virtual void loadFromXMI ( QDomElement & root );

protected:

        /** set attributes of the node that represents this class
         * in the XMI document.
         */
        virtual void setAttributesOnNode ( QDomDocument & doc, QDomElement & blockElement);

        /** set the class attributes of this object from
         * the passed element node.
         */
        virtual void setAttributesFromNode ( QDomElement & element);


	void updateMethodDeclaration();
	void updateContent();

private:

};

#endif // JAVASETACCESSORMETHOD_H
