/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

// own header
#include "stereotype.h"

// local includes
#include "debug_utils.h"
#include "umldoc.h"
#include "uml.h"
#include "stereotypesmodel.h"

// kde includes
#include <klocale.h>
#include <kinputdialog.h>


/**
 * Sets up a stereotype.
 *
 * @param name   The name of this UMLStereotype.
 * @param id     The unique id given to this UMLStereotype.
 */
UMLStereotype::UMLStereotype(const QString &name, Uml::ID::Type id /* = Uml::id_None */)
  : UMLObject(name, id)
{
    m_BaseType = UMLObject::ot_Stereotype;
    UMLStereotype * existing = UMLApp::app()->document()->findStereotype(name);
    if (existing) {
        uError() << "UMLStereotype constructor: " << name << " already exists"
                  << kBacktrace(25);
    }
    m_refCount = 0;
}

/**
 * Sets up a stereotype.
 */
UMLStereotype::UMLStereotype()
  : UMLObject()
{
    m_BaseType = UMLObject::ot_Stereotype;
    m_refCount = 0;
}

/**
 * Destructor.
 */
UMLStereotype::~UMLStereotype()
{
    Q_ASSERT(m_refCount == 0);
}

/**
 * Overloaded '==' operator.
 */
bool UMLStereotype::operator==(const UMLStereotype &rhs) const
{
    if (this == &rhs) {
        return true;
    }

    if (!UMLObject::operator==(rhs)) {
        return false;
    }

    return true;
}

/**
 * Copy the internal presentation of this object into the new
 * object.
 */
void UMLStereotype::copyInto(UMLObject *lhs) const
{
    UMLObject::copyInto(lhs);
}

/**
 * Make a clone of this object.
 */
UMLObject* UMLStereotype::clone() const
{
    UMLStereotype *clone = new UMLStereotype();
    copyInto(clone);

    return clone;
}

/**
 * Saves to the <UML:StereoType> XMI element.
 */
void UMLStereotype::saveToXMI(QDomDocument& qDoc, QDomElement& qElement)
{
    //FIXME: uml13.dtd compliance
    QDomElement stereotypeElement = UMLObject::save(QLatin1String("UML:Stereotype"), qDoc);
    qElement.appendChild(stereotypeElement);
}

/**
 * Display the properties configuration dialog for the stereotype
 * (just a line edit).
 */
bool UMLStereotype::showPropertiesDialog(QWidget* parent)
{
    bool ok;
    QString stereoTypeName = KInputDialog::getText(i18n("Stereotype"), i18n("Enter name:"), name(), &ok, parent);
    if (ok) {
        setName(stereoTypeName);
    }
    return ok;
}

/**
 * Increments the reference count for this stereotype.
 */
void UMLStereotype::incrRefCount()
{
    m_refCount++;
    UMLApp::app()->document()->stereotypesModel()->emitDataChanged(this);
}

/**
 * Decrements the reference count for this stereotype.
 */
void UMLStereotype::decrRefCount()
{
    m_refCount--;
    UMLApp::app()->document()->stereotypesModel()->emitDataChanged(this);
}

/**
 * Returns the reference count for this stereotype.
 */
int UMLStereotype::refCount() const
{
    return m_refCount;
}

/**
 * Returns the name as string
 */
QString UMLStereotype::name(bool includeAdornments) const
{
    if (includeAdornments)
        return QString::fromUtf8("«") + UMLObject::name() + QString::fromUtf8("»");
    else
        return UMLObject::name();
}
