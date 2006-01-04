/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *  copyright (C) 2006                                                     *
 *  Umbrello UML Modeller Authors <uml-devel@ uml.sf.net>                  *
 ***************************************************************************/

// own header
#include "object_factory.h"

// qt/kde includes
#include <qregexp.h>
#include <qstringlist.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kdebug.h>

// app includes
#include "inputdialog.h"
#include "umlobject.h"
#include "umlpackagelist.h"
#include "package.h"
#include "classifier.h"
#include "datatype.h"
#include "enum.h"
#include "entity.h"
#include "actor.h"
#include "usecase.h"
#include "component.h"
#include "node.h"
#include "artifact.h"
#include "stereotype.h"
#include "association.h"
#include "umldoc.h"
#include "uml.h"
#include "codegenerator.h"
#include "model_utils.h"

namespace Object_Factory {

UMLObject* createUMLObject(Uml::Object_Type type, const QString &n,
                           UMLPackage *parentPkg /* = NULL */,
                           bool prepend /* = false */) {
    UMLDoc *doc = UMLApp::app()->getDocument();
    bool ok = false;
    QString name;
    if( !n.isEmpty() && doc->isUnique(n, parentPkg) )
    {
        name = n;
    }
    else
    {
        name = Model_Utils::uniqObjectName(type, n, parentPkg);
        bool bValidNameEntered = false;
        do {
            name = KInputDialog::getText(i18n("Name"), i18n("Enter name:"), name, &ok, (QWidget*)UMLApp::app());
            if (!ok) {
                return 0;
            }
            if (name.length() == 0) {
                KMessageBox::error(0, i18n("That is an invalid name."),
                                   i18n("Invalid Name"));
                continue;
            }
            if (doc->getCurrentCodeGenerator() != NULL &&
                    doc->getCurrentCodeGenerator()->isReservedKeyword(name)) {
                KMessageBox::error(0, i18n("This is a reserved keyword for the language of the configured code generator."),
                                   i18n("Reserved Keyword"));
                continue;
            }
            if (! doc->isUnique(name, parentPkg)) {
                KMessageBox::error(0, i18n("That name is already being used."),
                                   i18n("Not a Unique Name"));
                continue;
            }
            bValidNameEntered = true;
        } while (bValidNameEntered == false);
    }
    UMLObject *o = NULL;
    if(type == Uml::ot_Actor) {
        o = new UMLActor(name);
    } else if(type == Uml::ot_UseCase) {
        o = new UMLUseCase(name);
    } else if(type == Uml::ot_Class ) {
        o = new UMLClassifier(name);
    } else if(type == Uml::ot_Package) {
        o = new UMLPackage(name);
    } else if(type == Uml::ot_Component) {
        o = new UMLComponent(name);
    } else if(type == Uml::ot_Node) {
        o = new UMLNode(name);
    } else if(type == Uml::ot_Artifact) {
        o = new UMLArtifact(name);
    } else if(type == Uml::ot_Interface) {
        UMLClassifier *c = new UMLClassifier(name);
        c->setInterface();
        o = c;
    } else if(type == Uml::ot_Datatype) {
        o = new UMLDatatype(name);
    } else if(type == Uml::ot_Enum) {
        o = new UMLEnum(name);
    } else if(type == Uml::ot_Entity) {
        o = new UMLEntity(name);
    } else {
        kdWarning() << "CreateUMLObject(int) error unknown type: " << type << endl;
        return (UMLObject*)0L;
    }
    o->setUMLPackage(parentPkg);
    doc->addUMLObject(o, prepend);
    doc->signalUMLObjectCreated(o);
    return o;
}

UMLObject* makeObjectFromXMI(const QString &xmiTag) {
    UMLObject* pObject = 0;
    if (Uml::tagEq(xmiTag, "UseCase")) {
        pObject = new UMLUseCase();
    } else if (Uml::tagEq(xmiTag, "Actor")) {
        pObject = new UMLActor();
    } else if (Uml::tagEq(xmiTag, "Class")) {
        pObject = new UMLClassifier();
    } else if (Uml::tagEq(xmiTag, "Package")) {
        pObject = new UMLPackage();
    } else if (Uml::tagEq(xmiTag, "Component")) {
        pObject = new UMLComponent();
    } else if (Uml::tagEq(xmiTag, "Node")) {
        pObject = new UMLNode();
    } else if (Uml::tagEq(xmiTag, "Artifact")) {
        pObject = new UMLArtifact();
    } else if (Uml::tagEq(xmiTag, "Interface")) {
        UMLClassifier *c = new UMLClassifier();
        c->setInterface();
        pObject = c;
    } else if (Uml::tagEq(xmiTag, "DataType") || Uml::tagEq(xmiTag, "Primitive")
               || Uml::tagEq(xmiTag, "Datatype")) {   // for bkwd compat.
        pObject = new UMLDatatype();
    } else if (Uml::tagEq(xmiTag, "Enumeration") ||
               Uml::tagEq(xmiTag, "Enum")) {   // for bkwd compat.
        pObject = new UMLEnum();
    } else if (Uml::tagEq(xmiTag, "Entity")) {
        pObject = new UMLEntity();
    } else if (Uml::tagEq(xmiTag, "Stereotype")) {
        pObject = new UMLStereotype();
    } else if (Uml::tagEq(xmiTag, "Association") ||
               Uml::tagEq(xmiTag, "AssociationClass")) {
        pObject = new UMLAssociation();
    } else if (Uml::tagEq(xmiTag, "Generalization")) {
        pObject = new UMLAssociation(Uml::at_Generalization);
    } else if (Uml::tagEq(xmiTag, "Realization") ||
               Uml::tagEq(xmiTag, "Abstraction")) {
        pObject = new UMLAssociation(Uml::at_Realization);
    } else if (Uml::tagEq(xmiTag, "Dependency")) {
        pObject = new UMLAssociation(Uml::at_Dependency);
    }
    return pObject;
}

}  // end namespace Object_Factory

