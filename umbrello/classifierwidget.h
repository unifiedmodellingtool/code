 /*
  *  copyright (C) 2004
  *  Umbrello UML Modeller Authors <uml-devel@ uml.sf.net>
  */

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CLASSIFIERWIDGET_H
#define CLASSIFIERWIDGET_H

#include "umlwidget.h"

class UMLClassifier;

/**
 * Intermediate class that serves as the base class for ClassWidget
 * and InterfaceWidget.  Does not itself appear on diagrams.
 *
 * @short Common base class for ClassWidget and InterfaceWidget
 * @author Oliver Kellogg
 * @see	UMLWidget
 * Bugs and comments to uml-devel@lists.sf.net or http://bugs.kde.org
 */
class ClassifierWidget : public UMLWidget {
public:

	/**
	 * Constructs a ClassifierWidget.
	 *
	 * @param view	The parent of this ClassifierWidget.
	 * @param o	The UMLObject to represent.
	 */
	ClassifierWidget(UMLView * view, UMLClassifier * o, Uml::Widget_Type wt);

	/**
	 * Destructor.
	 */
	virtual ~ClassifierWidget();

	/**
	 * Return the status of showing operations.
	 *
	 * @return	Return the status of showing operations.
	 */
	virtual bool getShowOps() const;

	/**
	 *  Set the status of whether to show Operations
	 *
	 * @param _show		True if operations shall be shown.
	 */
	virtual void setShowOps(bool _show);

	/**
	 * Toggles the status of showing operations.
	 */
	virtual void toggleShowOps();

	/**
	 * Return true if public operations/attributes are shown only.
	 */
	virtual bool getShowPublicOnly() const;

	/**
	 * Set whether to show public operations/attributes only.
	 */
	virtual void setShowPublicOnly(bool _status);

	/**
	 * Toggle whether to show public operations/attributes only.
	 */
	virtual void toggleShowPublicOnly();

	/**
	 * Returns the status of whether to show scope.
	 *
	 * @return	True if scope is shown.
	 */
	virtual bool getShowScope() const;

	/**
	 * Set the status of whether to show scope
	 *
	 * @param _scope	True if scope shall be shown.
	 */
	virtual void setShowScope(bool _scope);

	/**
	 * Toggles the status of whether to show scope
	 */
	virtual void toggleShowScope();

	/**
	 * Return the status of showing operation signatures.
	 *
	 * @return	Status of showing operation signatures.
	 */
	virtual Uml::Signature_Type getShowOpSigs() const;

	/**
	 * Set the status of whether to show Operation signature
	 *
	 * @param _show		True if operation signatures shall be shown.
	 */
	virtual void setShowOpSigs(bool _show);

	/**
	 * Toggles the status of showing operation signatures.
	 */
	virtual void toggleShowOpSigs();

	/**
	 * Returns the status of whether to show Package.
	 *
	 * @return	True if package is shown.
	 */
	virtual bool getShowPackage() const;

	/**
	 * Set the status of whether to show Package.
	 *
	 * @param _show		True if package shall be shown.
	 */
	virtual void setShowPackage(bool _status);

	/**
	 * Toggles the status of whether to show package.
	 */
	virtual void toggleShowPackage();

	/**
	 * Set the type of signature to display for an Operation
	 *
	 * @param sig	Type of signature to display for an operation.
	 */
	virtual void setOpSignature(Uml::Signature_Type sig);

	/**
	 * Activate the object after serializing it from a QDataStream.
	 */
	virtual bool activate(IDChangeLog* ChangeLog  = 0 );

protected:

	/**
	 * Initializes key variables of the class.
	 */
	virtual void init(Uml::Widget_Type wt);

	/**
	 * Abstract method for automatically computing the size of the object.
	 */
	virtual void calculateSize() = 0;

	/**
	 * Updates m_ShowOpSigs to match m_bShowScope.
	 */
	virtual void updateSigs();

	bool m_bShowOperations;            ///< Loaded/saved item.
	bool m_bShowPublicOnly;            ///< Loaded/saved item.
	bool m_bShowScope;                 ///< Loaded/saved item.
	bool m_bShowPackage;               ///< Loaded/saved item.
	Uml::Signature_Type m_ShowOpSigs;  ///< Loaded/saved item.

};

#endif
