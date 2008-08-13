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

// own header
#include "cppcodegenerationpolicy.h"

// app includes
#include "cppcodegenerationpolicypage.h"
#include "uml.h"
#include "umbrellosettings.h"
#include "optionstate.h"

// kde includes
#include <kdebug.h>
#include <kconfig.h>

// qt includes
#include <QtCore/QRegExp>

const char * CPPCodeGenerationPolicy::DEFAULT_VECTOR_METHOD_APPEND = "%VARNAME%.push_back(value);";
const char * CPPCodeGenerationPolicy::DEFAULT_VECTOR_METHOD_REMOVE = "int size = %VARNAME%.size();\nfor ( int i = 0; i < size; ++i) {\n\t%ITEMCLASS% item = %VARNAME%.at(i);\n\tif(item == value) {\n\t\tvector<%ITEMCLASS%>::iterator it = %VARNAME%.begin() + i;\n\t\t%VARNAME%.erase(it);\n\t\treturn;\n\t}\n }";
const char * CPPCodeGenerationPolicy::DEFAULT_VECTOR_METHOD_INIT = ""; // nothing to do in std::vector
const char * CPPCodeGenerationPolicy::DEFAULT_OBJECT_METHOD_INIT = "%VARNAME% = new %ITEMCLASS%( );";

CPPCodeGenerationPolicy::CPPCodeGenerationPolicy()
{
    init();
}

CPPCodeGenerationPolicy::~CPPCodeGenerationPolicy ( ) { }

/**
 * Set the value of publicAccessors
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setAccessorsArePublic ( bool var )
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.publicAccessors = var;
    // @todo we should probably use an own signal for this
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

/**
 * Get the value of publicAccessors
 * @return value the boolean value of m_publicAccessors
 */
bool CPPCodeGenerationPolicy::getAccessorsArePublic( )
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.publicAccessors;
}

/**
 * Set the value of inlineAccessors
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setAccessorsAreInline ( bool var )
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.inlineAccessors = var;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

/**
 * Get the value of inlineAccessors
 * @return value the boolean value of m_inlineAccessors
 */
bool CPPCodeGenerationPolicy::getAccessorsAreInline( )
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.inlineAccessors;
}

/**
 * Set the value of inlineOperations
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setOperationsAreInline ( bool var )
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.inlineOps = var;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

/**
 * Get the value of inlineOperations
 * @return value the boolean value of m_inlineOperations
 */
bool CPPCodeGenerationPolicy::getOperationsAreInline( )
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.inlineOps;
}

/**
 * Set the value of virtualDestructors
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setDestructorsAreVirtual ( bool var )
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.virtualDestructors = var;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

/**
 * Get the value of virtualDestructors
 * @return value the boolean value of m_virtualDestructors
 */
bool CPPCodeGenerationPolicy::getDestructorsAreVirtual( )
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.virtualDestructors;
}

/**
 * Set the value of packageIsNamespace
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setPackageIsNamespace ( bool var )
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.packageIsNamespace = var;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

/**
 * Get the value of packageIsNamespace
 * @return value the boolean value of m_packageIsNamespace
 */
bool CPPCodeGenerationPolicy::getPackageIsNamespace( )
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.packageIsNamespace;
}

/**
 * Set the value of autoGenerateAccessors
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setAutoGenerateAccessors( bool var )
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.autoGenAccessors = var;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

bool CPPCodeGenerationPolicy::getAutoGenerateAccessors( )
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.autoGenAccessors;
}

QString CPPCodeGenerationPolicy::getStringClassName()
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.stringClassName;
}

QString CPPCodeGenerationPolicy::getStringClassNameInclude()
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.stringClassNameInclude;
}

QString CPPCodeGenerationPolicy::getVectorClassName()
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.vectorClassName;
}

QString CPPCodeGenerationPolicy::getVectorClassNameInclude()
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.vectorClassNameInclude;
}

void CPPCodeGenerationPolicy::setStringClassName(const QString &value)
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.stringClassName = value;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

void CPPCodeGenerationPolicy::setStringClassNameInclude(const QString &value)
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.stringClassNameInclude = value;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

void CPPCodeGenerationPolicy::setVectorClassName(const QString &value)
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.vectorClassName = value;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

void CPPCodeGenerationPolicy::setVectorClassNameInclude(const QString &value)
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.vectorClassNameInclude = value;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

/** determine if the string include is global one */
bool CPPCodeGenerationPolicy::stringIncludeIsGlobal ()
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.stringIncludeIsGlobal;
}

bool CPPCodeGenerationPolicy::vectorIncludeIsGlobal ()
{
    return Settings::getOptionState().codeGenerationState.cppCodeGenerationState.vectorIncludeIsGlobal;
}

void CPPCodeGenerationPolicy::setStringIncludeIsGlobal(bool value)
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.stringIncludeIsGlobal = value;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

void CPPCodeGenerationPolicy::setVectorIncludeIsGlobal(bool value)
{
    Settings::getOptionState().codeGenerationState.cppCodeGenerationState.vectorIncludeIsGlobal = value;
    UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}

QString CPPCodeGenerationPolicy::getVectorMethodAppend(const QString & variableName, const QString & itemClassName)
{
    QString value = m_vectorMethodAppendBase;
    if(!variableName.isEmpty())
        value.replace(QRegExp("%VARNAME%"),variableName);
    value.replace(QRegExp("%VECTORTYPENAME%"), Settings::getOptionState().codeGenerationState.cppCodeGenerationState.vectorClassName);
    if(!itemClassName.isEmpty())
        value.replace(QRegExp("%ITEMCLASS%"),itemClassName);
    return value;
}

QString CPPCodeGenerationPolicy::getVectorMethodRemove(const QString & variableName, const QString & itemClassName)
{
    QString value = m_vectorMethodRemoveBase;
    if(!variableName.isEmpty())
        value.replace(QRegExp("%VARNAME%"),variableName);
    value.replace(QRegExp("%VECTORTYPENAME%"), Settings::getOptionState().codeGenerationState.cppCodeGenerationState.vectorClassName);
    if(!itemClassName.isEmpty())
        value.replace(QRegExp("%ITEMCLASS%"),itemClassName);
    return value;
}

QString CPPCodeGenerationPolicy::getVectorMethodInit(const QString & variableName, const QString & itemClassName)
{
    QString value = m_vectorMethodInitBase;
    if(!variableName.isEmpty())
        value.replace(QRegExp("%VARNAME%"),variableName);
    value.replace(QRegExp("%VECTORTYPENAME%"), Settings::getOptionState().codeGenerationState.cppCodeGenerationState.vectorClassName);
    if(!itemClassName.isEmpty())
        value.replace(QRegExp("%ITEMCLASS%"),itemClassName);
    return value;
}

QString CPPCodeGenerationPolicy::getObjectMethodInit(const QString & variableName, const QString & itemClassName)
{
    QString value = m_objectMethodInitBase;
    if(!variableName.isEmpty())
        value.replace(QRegExp("%VARNAME%"),variableName);
    value.replace(QRegExp("%VECTORTYPENAME%"), Settings::getOptionState().codeGenerationState.cppCodeGenerationState.vectorClassName);
    if(!itemClassName.isEmpty())
        value.replace(QRegExp("%ITEMCLASS%"),itemClassName);
    return value;
}

void CPPCodeGenerationPolicy::setDefaults ( CPPCodeGenerationPolicy * cppclone, bool emitUpdateSignal )
{
    blockSignals(true); // we need to do this because otherwise most of these
    // settors below will each send the modifiedCodeContent() signal
    // needlessly (we can just make one call at the end).

    {
        setAutoGenerateAccessors(cppclone->getAutoGenerateAccessors());

        setAccessorsAreInline(cppclone->getAccessorsAreInline());
        setOperationsAreInline(cppclone->getOperationsAreInline());
        setDestructorsAreVirtual(cppclone->getDestructorsAreVirtual());
        setPackageIsNamespace(cppclone->getPackageIsNamespace());

        setStringClassName(cppclone->getStringClassName() );
        setStringClassNameInclude(cppclone->getStringClassNameInclude());
        setStringIncludeIsGlobal(cppclone->stringIncludeIsGlobal());

        setVectorClassName(cppclone->getVectorClassName());
        setVectorClassNameInclude(cppclone->getVectorClassNameInclude());
        setVectorIncludeIsGlobal(cppclone->vectorIncludeIsGlobal());
    }

    blockSignals(false); // "as you were citizen"

    if(emitUpdateSignal)
        UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();

}

void CPPCodeGenerationPolicy::setDefaults(bool emitUpdateSignal )
{
    blockSignals(true); // we need to do this because otherwise most of these
    // settors below will each send the modifiedCodeContent() signal
    // needlessly (we can just make one call at the end).

    setAutoGenerateAccessors(UmbrelloSettings::autoGenAccessors());

    setAccessorsAreInline(UmbrelloSettings::inlineAccessors());
    setAccessorsArePublic(UmbrelloSettings::publicAccessors());
    setOperationsAreInline(UmbrelloSettings::inlineOps());
    setDestructorsAreVirtual(UmbrelloSettings::virtualDestructors());
    setPackageIsNamespace(UmbrelloSettings::packageIsNamespace());

    setStringClassName(UmbrelloSettings::stringClassName());
    setStringClassNameInclude(UmbrelloSettings::stringClassNameInclude());
    setStringIncludeIsGlobal(UmbrelloSettings::stringIncludeIsGlobal());

    setVectorClassName(UmbrelloSettings::vectorClassName());
    setVectorClassNameInclude(UmbrelloSettings::vectorClassNameInclude());
    setVectorIncludeIsGlobal(UmbrelloSettings::vectorIncludeIsGlobal());

    blockSignals(false); // "as you were citizen"

    if(emitUpdateSignal)
        UMLApp::app()->getCommonPolicy()->emitModifiedCodeContentSig();
}


/**
 * Create a new dialog interface for this object.
 * @return dialog object
 */
CodeGenerationPolicyPage * CPPCodeGenerationPolicy::createPage ( QWidget *parent, const char *name )
{
    return new CPPCodeGenerationPolicyPage ( parent, name, this );
}

void CPPCodeGenerationPolicy::init()
{
    blockSignals(true);

    m_vectorMethodAppendBase = DEFAULT_VECTOR_METHOD_APPEND;
    m_vectorMethodRemoveBase = DEFAULT_VECTOR_METHOD_REMOVE;
    m_vectorMethodInitBase = DEFAULT_VECTOR_METHOD_INIT;
    m_objectMethodInitBase = DEFAULT_OBJECT_METHOD_INIT;

    Settings::OptionState optionState = Settings::getOptionState();
    setAutoGenerateAccessors( optionState.codeGenerationState.cppCodeGenerationState.autoGenAccessors);

    setAccessorsAreInline(optionState.codeGenerationState.cppCodeGenerationState.inlineAccessors);
    setAccessorsArePublic( optionState.codeGenerationState.cppCodeGenerationState.publicAccessors);
    setOperationsAreInline(optionState.codeGenerationState.cppCodeGenerationState.inlineOps);
    setDestructorsAreVirtual( optionState.codeGenerationState.cppCodeGenerationState.virtualDestructors);
    setPackageIsNamespace(optionState.codeGenerationState.cppCodeGenerationState.packageIsNamespace);

    setStringClassName(optionState.codeGenerationState.cppCodeGenerationState.stringClassName);
    setStringClassNameInclude(optionState.codeGenerationState.cppCodeGenerationState.stringClassNameInclude);
    setStringIncludeIsGlobal(optionState.codeGenerationState.cppCodeGenerationState.stringIncludeIsGlobal);

    setVectorClassName(optionState.codeGenerationState.cppCodeGenerationState.vectorClassName);
    setVectorClassNameInclude(optionState.codeGenerationState.cppCodeGenerationState.vectorClassNameInclude);
    setVectorIncludeIsGlobal(optionState.codeGenerationState.cppCodeGenerationState.vectorIncludeIsGlobal);

    blockSignals(false);
}

#include "cppcodegenerationpolicy.moc"