
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
 *      Date   : Mon Jun 23 2003
 */

// own header
#include "cppcodegenerationpolicy.h"
// qt/kde includes
#include <qregexp.h>
#include <kdebug.h>
#include <kconfig.h>
// app includes
#include "cppcodegenerationpolicypage.h"
#include "cppcodegenerator.h"
#include "../uml.h"

const CPPCodeGenerationPolicy::CPPCommentStyle CPPCodeGenerationPolicy::DEFAULT_COMMENT = SlashStar;
const bool CPPCodeGenerationPolicy::DEFAULT_AUTO_GEN_EMPTY_CONSTRUCTORS = false;
const bool CPPCodeGenerationPolicy::DEFAULT_AUTO_GEN_ACCESSORS = true;
const bool CPPCodeGenerationPolicy::DEFAULT_INLINE_ACCESSORS = false;
const bool CPPCodeGenerationPolicy::DEFAULT_INLINE_OPERATIONS = false;
const bool CPPCodeGenerationPolicy::DEFAULT_VIRTUAL_DESTRUCTORS = true;
const bool CPPCodeGenerationPolicy::DEFAULT_PACKAGE_IS_NAMESPACE = false;
const char * CPPCodeGenerationPolicy::DEFAULT_STRING_CLASS_NAME = "string";
const char * CPPCodeGenerationPolicy::DEFAULT_STRING_CLASS_INCLUDE = "string";
const char * CPPCodeGenerationPolicy::DEFAULT_VECTOR_CLASS_NAME = "vector";
const char * CPPCodeGenerationPolicy::DEFAULT_VECTOR_CLASS_INCLUDE = "vector";
const char * CPPCodeGenerationPolicy::DEFAULT_VECTOR_METHOD_APPEND = "%VARNAME%.push_back(value);";
const char * CPPCodeGenerationPolicy::DEFAULT_VECTOR_METHOD_REMOVE = "int size = %VARNAME%.size();\nfor ( int i = 0; i < size; ++i) {\n\t%ITEMCLASS% item = %VARNAME%.at(i);\n\tif(item == value) {\n\t\tvector<%ITEMCLASS%>::iterator it = %VARNAME%.begin() + i;\n\t\t%VARNAME%.erase(it);\n\t\treturn;\n\t}\n }";
const char * CPPCodeGenerationPolicy::DEFAULT_VECTOR_METHOD_INIT = ""; // nothing to do in std::vector
const char * CPPCodeGenerationPolicy::DEFAULT_OBJECT_METHOD_INIT = "%VARNAME% = new %ITEMCLASS%( );";
const bool CPPCodeGenerationPolicy::DEFAULT_STRING_INCLUDE_GLOBAL = true;
const bool CPPCodeGenerationPolicy::DEFAULT_VECTOR_INCLUDE_GLOBAL = true;


// Constructors/Destructors
//

CPPCodeGenerationPolicy::CPPCodeGenerationPolicy(CodeGenerationPolicy *defaults)
    : CodeGenerationPolicy(defaults)
{
	init();
	setDefaults(defaults,false);
}

CPPCodeGenerationPolicy::CPPCodeGenerationPolicy(KConfig *config)
    : CodeGenerationPolicy(config)
{
	init();
	setDefaults(config,false);
}

CPPCodeGenerationPolicy::~CPPCodeGenerationPolicy ( ) { }

//
// Methods
//

// Accessor methods
//

/**
 * Set the value of m_inlineAccessors
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setAccessorsAreInline ( bool var )
{
	m_inlineAccessors = var;
	emit modifiedCodeContent();
}

/**
 * Get the value of m_inlineAccessors
 * @return value the boolean value of m_inlineAccessors
 */
bool CPPCodeGenerationPolicy::getAccessorsAreInline( )
{
	return m_inlineAccessors;
}

/**
 * Set the value of m_inlineOperations
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setOperationsAreInline ( bool var )
{
	m_inlineOperations = var;
	emit modifiedCodeContent();
}

/**
 * Get the value of m_inlineOperations
 * @return value the boolean value of m_inlineOperations
 */
bool CPPCodeGenerationPolicy::getOperationsAreInline( )
{
	return m_inlineOperations;
}

/**
 * Set the value of m_virtualDestructors
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setDestructorsAreVirtual ( bool var )
{
	m_virtualDestructors = var;
	emit modifiedCodeContent();
}

/**
 * Get the value of m_virtualDestructors
 * @return value the boolean value of m_virtualDestructors
 */
bool CPPCodeGenerationPolicy::getDestructorsAreVirtual( )
{
	return m_virtualDestructors;
}

/**
 * Set the value of m_packageIsNamespace
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setPackageIsNamespace ( bool var ) {
	m_packageIsNamespace = var;
	emit modifiedCodeContent();
}

/**
 * Get the value of m_packageIsNamespace
 * @return value the boolean value of m_packageIsNamespace
 */
bool CPPCodeGenerationPolicy::getPackageIsNamespace( ) {
	return m_packageIsNamespace;
}

/**
 * Set the value of m_commentStyle
 * @param new_var the new value of m_commentStyle
 */
void CPPCodeGenerationPolicy::setCommentStyle ( CPPCommentStyle new_var ) {
	m_commentStyle = new_var;
	emit modifiedCodeContent();
}

/**
 * Get the value of m_commentStyle
 * @return the value of m_commentStyle
 */
CPPCodeGenerationPolicy::CPPCommentStyle CPPCodeGenerationPolicy::getCommentStyle ( ) {
	return m_commentStyle;
}

/**
 * Set the value of m_autoGenerateConstructors
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setAutoGenerateConstructors( bool var ) {
        m_autoGenerateConstructors = var;
	emit modifiedCodeContent();
}

/**
 * Get the value of m_autoGenerateConstructors
 * @return the value of m_autoGenerateConstructors
 */
bool CPPCodeGenerationPolicy::getAutoGenerateConstructors( ){
        return m_autoGenerateConstructors;
}

/**
 * Set the value of m_autoGenerateAccessors
 * @param new_var the new value
 */
void CPPCodeGenerationPolicy::setAutoGenerateAccessors( bool var ) {
        m_autoGenerateAccessors = var;
	emit modifiedCodeContent();
}

/**
 * Get the value of m_autoGenerateConstructors
 * @return the value of m_autoGenerateConstructors
 */
bool CPPCodeGenerationPolicy::getAutoGenerateAccessors( ){
        return m_autoGenerateAccessors;
}

QString CPPCodeGenerationPolicy::getStringClassName() {
	return m_stringClassName;
}

QString CPPCodeGenerationPolicy::getStringClassNameInclude() {
	return m_stringClassNameInclude;
}

QString CPPCodeGenerationPolicy::getVectorClassName() {
	return m_vectorClassName;
}

QString CPPCodeGenerationPolicy::getVectorClassNameInclude() {
	return m_vectorClassNameInclude;
}

void CPPCodeGenerationPolicy::setStringClassName(const QString &value) {
	m_stringClassName = value;
	emit modifiedCodeContent();
}

void CPPCodeGenerationPolicy::setStringClassNameInclude(const QString &value) {
	m_stringClassNameInclude = value;
	emit modifiedCodeContent();
}

void CPPCodeGenerationPolicy::setVectorClassName(const QString &value) {
	m_vectorClassName = value;
	emit modifiedCodeContent();
}

void CPPCodeGenerationPolicy::setVectorClassNameInclude(const QString &value) {
	m_vectorClassNameInclude = value;
	emit modifiedCodeContent();
}

/** determine if the string include is global one */
bool CPPCodeGenerationPolicy::stringIncludeIsGlobal () {
	return m_stringIncludeIsGlobal;
}

bool CPPCodeGenerationPolicy::vectorIncludeIsGlobal () {
	return m_vectorIncludeIsGlobal;
}

void CPPCodeGenerationPolicy::setStringIncludeIsGlobal(bool value) {
	m_stringIncludeIsGlobal = value;
	emit modifiedCodeContent();
}

void CPPCodeGenerationPolicy::setVectorIncludeIsGlobal(bool value) {
	m_vectorIncludeIsGlobal = value;
	emit modifiedCodeContent();
}

QString CPPCodeGenerationPolicy::getVectorMethodAppend(const QString & variableName, const QString & itemClassName) {
	QString value = m_vectorMethodAppendBase;
	if(!variableName.isEmpty())
		value.replace(QRegExp("%VARNAME%"),variableName);
	value.replace(QRegExp("%VECTORTYPENAME%"), m_vectorClassName);
	if(!itemClassName.isEmpty())
		value.replace(QRegExp("%ITEMCLASS%"),itemClassName);
        return value;
}

QString CPPCodeGenerationPolicy::getVectorMethodRemove(const QString & variableName, const QString & itemClassName) {
	QString value = m_vectorMethodRemoveBase;
        if(!variableName.isEmpty())
                value.replace(QRegExp("%VARNAME%"),variableName);
        value.replace(QRegExp("%VECTORTYPENAME%"), m_vectorClassName);
        if(!itemClassName.isEmpty())
                value.replace(QRegExp("%ITEMCLASS%"),itemClassName);
        return value;
}

QString CPPCodeGenerationPolicy::getVectorMethodInit(const QString & variableName, const QString & itemClassName) {
	QString value = m_vectorMethodInitBase;
        if(!variableName.isEmpty())
                value.replace(QRegExp("%VARNAME%"),variableName);
        value.replace(QRegExp("%VECTORTYPENAME%"), m_vectorClassName);
        if(!itemClassName.isEmpty())
                value.replace(QRegExp("%ITEMCLASS%"),itemClassName);
        return value;
}

QString CPPCodeGenerationPolicy::getObjectMethodInit(const QString & variableName, const QString & itemClassName) {
	QString value = m_objectMethodInitBase;
        if(!variableName.isEmpty())
                value.replace(QRegExp("%VARNAME%"),variableName);
        value.replace(QRegExp("%VECTORTYPENAME%"), m_vectorClassName);
        if(!itemClassName.isEmpty())
                value.replace(QRegExp("%ITEMCLASS%"),itemClassName);
        return value;
}

// Other methods
//

void CPPCodeGenerationPolicy::writeConfig ( KConfig * config )
{

	// write ONLY the CPP specific stuff
	config->setGroup("CPP Code Generation");

	config->writeEntry("commentStyle",getCommentStyle());
	config->writeEntry("autoGenEmptyConstructors",getAutoGenerateConstructors());
	config->writeEntry("autoGenAccessors",getAutoGenerateAccessors());

	CodeGenerator *codegen = UMLApp::app()->getGenerator();
	CPPCodeGenerator *cppcodegen = dynamic_cast<CPPCodeGenerator*>(codegen);
	if (cppcodegen)
		config->writeEntry("buildMakefile", cppcodegen->getCreateProjectMakefile());

	config->writeEntry("inlineAccessors",getAccessorsAreInline());
	config->writeEntry("inlineOps",getOperationsAreInline());
	config->writeEntry("virtualDestructors",getDestructorsAreVirtual());
	config->writeEntry("packageIsNamespace",getPackageIsNamespace());

	config->writeEntry("stringClassName",getStringClassName());
	config->writeEntry("stringClassNameInclude",getStringClassNameInclude());
	config->writeEntry("stringIncludeIsGlobal",stringIncludeIsGlobal());

	config->writeEntry("vectorClassName",getVectorClassName());
	config->writeEntry("vectorClassNameInclude",getVectorClassNameInclude());
	config->writeEntry("vectorIncludeIsGlobal",vectorIncludeIsGlobal());

}

void CPPCodeGenerationPolicy::setDefaults ( CodeGenerationPolicy * clone, bool emitUpdateSignal )
{

	CPPCodeGenerationPolicy * cppclone;
	if (!clone)
		return;

	// do the super class
	CodeGenerationPolicy::setDefaults(clone, false);

	// NOW block signals for cpp param setting
        blockSignals(true); // we need to do this because otherwise most of these
                           // settors below will each send the modifiedCodeContent() signal
                           // needlessly (we can just make one call at the end).


	// now do cpp-specific stuff IF our clone is also a CPPCodeGenerationPolicy object
 	if((cppclone = dynamic_cast<CPPCodeGenerationPolicy*>(clone)))
	{
		setCommentStyle(cppclone->getCommentStyle());
		setAutoGenerateConstructors(cppclone->getAutoGenerateConstructors());
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
		emit modifiedCodeContent();

}

void CPPCodeGenerationPolicy::setDefaults( KConfig * config, bool emitUpdateSignal )
{

	if(!config)
		return;

        // call the superclass to init default stuff
        CodeGenerationPolicy::setDefaults(config, false);

	// NOW block signals (because call to super-class method will leave value at "true")
        blockSignals(true); // we need to do this because otherwise most of these
                            // settors below will each send the modifiedCodeContent() signal
                            // needlessly (we can just make one call at the end).

	// now do cpp specific stuff
        config -> setGroup("CPP Code Generation");

	setCommentStyle((CPPCommentStyle)config->readNumEntry("commentStyle",DEFAULT_COMMENT));
	setAutoGenerateConstructors(config->readBoolEntry("autoGenEmptyConstructors",DEFAULT_AUTO_GEN_EMPTY_CONSTRUCTORS));
	setAutoGenerateAccessors(config->readBoolEntry("autoGenAccessors",DEFAULT_AUTO_GEN_ACCESSORS));
/**** Temporarily commented because of following endless recursion:
 #0  UMLApp::createGenerator() (this=0x841f0f8) at uml.cpp:1250
 #1  0x0818a5f9 in UMLApp::getGenerator(bool) (this=0x841f0f8, warnMissing=true) at uml.cpp:1216
 #2  0x0829c481 in CPPCodeGenerationPolicy::setDefaults(KConfig*, bool) (this=0x8508db8, config=0x83f3ac8, 
     emitUpdateSignal=false) at cppcodegenerationpolicy.cpp:391
 #3  0x0818a7ea in UMLApp::createGenerator() (this=0x841f0f8) at uml.cpp:1257
 #4  0x0818a5f9 in UMLApp::getGenerator(bool) (this=0x841f0f8, warnMissing=true) at uml.cpp:1216
 #5  0x0819fe6d in UMLDoc::addDefaultDatatypes() (this=0x8428cb0) at umldoc.cpp:2943
 #6  0x0819018e in UMLDoc::newDocument() (this=0x8428cb0) at umldoc.cpp:346

	CodeGenerator *codegen = UMLApp::app()->getGenerator();
	CPPCodeGenerator *cppcodegen = dynamic_cast<CPPCodeGenerator*>(codegen);
	if (cppcodegen) {
		bool mkmf = config->readBoolEntry("buildMakefile", CPPCodeGenerator::DEFAULT_BUILD_MAKEFILE);
		cppcodegen->setCreateProjectMakefile(mkmf);
	}
*************************************************************************************************/
	setAccessorsAreInline(config->readBoolEntry("inlineAccessors",DEFAULT_INLINE_ACCESSORS));
	setOperationsAreInline(config->readBoolEntry("inlineOps",DEFAULT_INLINE_OPERATIONS));
	setDestructorsAreVirtual(config->readBoolEntry("virtualDestructors",DEFAULT_VIRTUAL_DESTRUCTORS));
	setPackageIsNamespace(config->readBoolEntry("packageIsNamespace",DEFAULT_PACKAGE_IS_NAMESPACE));

	setStringClassName(config->readEntry("stringClassName",DEFAULT_STRING_CLASS_NAME) );
	setStringClassNameInclude(config->readEntry("stringClassNameInclude",DEFAULT_STRING_CLASS_INCLUDE ) );
	setStringIncludeIsGlobal(config->readBoolEntry("stringIncludeIsGlobal",DEFAULT_STRING_INCLUDE_GLOBAL) );

	setVectorClassName(config->readEntry("vectorClassName",DEFAULT_VECTOR_CLASS_NAME) );
	setVectorClassNameInclude(config->readEntry("vectorClassNameInclude",DEFAULT_VECTOR_CLASS_INCLUDE) );
	setVectorIncludeIsGlobal(config->readBoolEntry("vectorIncludeIsGlobal",DEFAULT_VECTOR_INCLUDE_GLOBAL) );

        blockSignals(false); // "as you were citizen"

	if(emitUpdateSignal)
		emit modifiedCodeContent();
}


/**
 * Create a new dialog interface for this object.
 * @return dialog object
 */
CodeGenerationPolicyPage * CPPCodeGenerationPolicy::createPage ( QWidget *parent, const char *name ) {
        return new CPPCodeGenerationPolicyPage ( parent, name, this );
}

void CPPCodeGenerationPolicy::init() {

	m_commentStyle = DEFAULT_COMMENT;
	m_autoGenerateConstructors = DEFAULT_AUTO_GEN_EMPTY_CONSTRUCTORS;
        m_autoGenerateAccessors = DEFAULT_AUTO_GEN_ACCESSORS;

	m_inlineAccessors = DEFAULT_INLINE_ACCESSORS;
	m_inlineOperations = DEFAULT_INLINE_OPERATIONS;
	m_virtualDestructors = DEFAULT_VIRTUAL_DESTRUCTORS;
	m_packageIsNamespace = DEFAULT_PACKAGE_IS_NAMESPACE;

	m_stringClassName = DEFAULT_STRING_CLASS_NAME;
	m_stringClassNameInclude = DEFAULT_STRING_CLASS_INCLUDE;
	m_stringIncludeIsGlobal = DEFAULT_STRING_INCLUDE_GLOBAL;

	m_vectorClassName = DEFAULT_VECTOR_CLASS_NAME;
	m_vectorClassNameInclude = DEFAULT_VECTOR_CLASS_INCLUDE;
	m_vectorIncludeIsGlobal = DEFAULT_VECTOR_INCLUDE_GLOBAL;

	m_vectorMethodAppendBase = DEFAULT_VECTOR_METHOD_APPEND;
	m_vectorMethodRemoveBase = DEFAULT_VECTOR_METHOD_REMOVE;
	m_vectorMethodInitBase = DEFAULT_VECTOR_METHOD_INIT;
	m_objectMethodInitBase = DEFAULT_OBJECT_METHOD_INIT;

}


#include "cppcodegenerationpolicy.moc"
