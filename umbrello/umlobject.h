/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef UMLOBJECT_H
#define UMLOBJECT_H

#include "basictypes.h"
#include "umlpackagelist.h"

//qt includes
#include <QDomDocument>
#include <QDomElement>
#include <QObject>
#include <QPointer>
#include <QString>

class UMLStereotype;

/**
 * This class is the non-graphical version of @ref UMLWidget.  These are
 * created and maintained in the class @ref UMLDoc.  This class holds all
 * the generic information needed for all UML objects.
 *
 * @ref clone needs to be implemented by each child class.
 *
 * @ref saveToXMI saves the XMI attributes of each specific model class.
 * It needs to be implemented by each child class.
 * For creating the QDomElement and saving the common XMI parts,
 * it can use the save() method.
 *
 * @short The base class for UML objects.
 * @author Paul Hensgen <phensgen@techie.com>
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class UMLObject : public QObject
{
    Q_OBJECT
    Q_ENUMS(ObjectType)

public:
    enum ObjectType
    {
        ot_Unknown = -1,
        ot_UMLObject  = 100,
        ot_Actor,
        ot_UseCase,
        ot_Package,
        ot_Interface,
        ot_Datatype,
        ot_Enum,
        ot_Class,
        ot_Association,
        ot_Attribute,
        ot_Operation,
        ot_EnumLiteral,
        ot_Template,
        ot_Component,
        ot_Artifact,
        ot_Node,
        ot_Stereotype,
        ot_Role,
        ot_Entity,
        ot_EntityAttribute,
        ot_Folder,
        ot_EntityConstraint,
        ot_UniqueConstraint,
        ot_ForeignKeyConstraint,
        ot_CheckConstraint,
        ot_Category,
        ot_Port
    };

    static QString toString(ObjectType ot);
    static QString toI18nString(ObjectType t);

    explicit UMLObject(UMLObject* parent, const QString& name, Uml::ID::Type id = Uml::ID::None);
    explicit UMLObject(UMLObject* parent);
    explicit UMLObject(const QString& name = QString(), Uml::ID::Type id = Uml::ID::None);
    virtual ~UMLObject();

    bool operator==(const UMLObject & rhs) const;

    virtual void copyInto(UMLObject *lhs) const;

    virtual UMLObject* clone() const = 0;

    virtual void setBaseType(ObjectType ot);
    ObjectType baseType() const;
    QLatin1String baseTypeStr() const;

    virtual void setID(Uml::ID::Type NewID);
    virtual Uml::ID::Type id() const;

    QString doc() const;
    bool hasDoc() const;
    void setDoc(const QString &d);

    void setVisibility(Uml::Visibility::Enum visibility);
    void setVisibilityCmd(Uml::Visibility::Enum visibility);
    Uml::Visibility::Enum visibility() const;

    void setStereotype(const QString &_name);
    void setStereotypeCmd(const QString &_name);
    QString stereotype(bool includeAdornments = false) const;

    void setUMLStereotype(UMLStereotype *stereo);
    UMLStereotype *umlStereotype();

    void setPackage(const QString &_name);
    QString package(const QString& separator = QString(),
                    bool includeRoot = false);

    bool setUMLPackage(UMLPackage* pPkg);
    UMLPackage* umlPackage();

    UMLPackageList packages(bool includeRoot = false) const;

    virtual void setName(const QString &strName);
    void setNameCmd(const QString &strName) ;
    QString name() const;

    virtual QString fullyQualifiedName(const QString& separator = QString(),
                                       bool includeRoot = false) const;

    void setAbstract(bool bAbstract);
    bool isAbstract() const;

    virtual bool showPropertiesDialog(QWidget* parent = 0);

    virtual bool resolveRef();

    virtual void saveToXMI(QDomDocument & qDoc, QDomElement & qElement) = 0;
    virtual bool loadFromXMI(QDomElement & element);

    bool loadStereotype(QDomElement & element);

    void setStatic(bool bStatic);
    bool isStatic() const;

    virtual bool acceptAssociationType(Uml::AssociationType::Enum);  //:TODO: check if this is really needed here

    void setSecondaryId(const QString& id);
    QString secondaryId() const;

    void setSecondaryFallback(const QString& id);
    QString secondaryFallback() const;

    QDomElement save(const QString &tag, QDomDocument & qDoc);

    friend QDebug operator<< (QDebug out, const UMLObject& obj);

public slots:
    void emitModified();

signals:
    void modified();

protected:
    void init();

    void maybeSignalObjectCreated();

    virtual bool load(QDomElement& element);

    Uml::ID::Type          m_nId;          ///< object's id
    QString                m_Doc;          ///< object's documentation
    UMLPackage*            m_pUMLPackage;  ///< package the object belongs to if applicable
    QPointer<UMLStereotype> m_pStereotype;  ///< stereotype of the object if applicable
    QString                m_name;         ///< objects name
    ObjectType             m_BaseType;     ///< objects type
    Uml::Visibility::Enum  m_visibility;   ///< objects visibility
    bool                   m_bAbstract;    ///< state of whether the object is abstract or not
    bool                   m_bStatic;      ///< flag for instance scope
    bool                   m_bInPaste;     ///< caller sets this true when in paste operation
    bool        m_bCreationWasSignalled;   ///< auxiliary to maybeSignalObjectCreated()
    QPointer<UMLObject>    m_pSecondary;   ///< pointer to an associated object
                                           ///< Only a few of the classes inheriting from UMLObject use this.
                                           ///< However, it needs to be here because of inheritance graph
                                           ///< disjunctness.
    QString                m_SecondaryId;  ///< xmi.id of the secondary object for intermediate use during
                                           ///< loading. The secondary ID is resolved to the m_pSecondary
                                           ///< in the course of resolveRef() at the end of loading.
    QString           m_SecondaryFallback; ///< Last-chance backup for when m_SecondaryId is not found.
                                           ///< Used by Rose import: MDL files specify both a "quidu"
                                           ///< (which corresponds to m_SecondaryId) and the human readable
                                           ///< fully qualified target name of a reference.
                                           ///< In case the quidu is not found, the human readable name is
                                           ///< used which we store in m_SecondaryFallback.
};

#endif
