
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
 *      Date   : Thu Jun 19 2003
 */

#include <kdebug.h>
#include <kconfig.h>

#include <qregexp.h>

#include "cppcodegenerator.h"
#include "cppcodedocumentation.h"
#include "cppcodegenerationpolicy.h"
#include "cppsourcecodedocument.h"
#include "cppheadercodedocument.h"

#include "codeviewerdialog.h"

const bool CPPCodeGenerator::DEFAULT_BUILD_MAKEFILE = false;

// Constructors/Destructors
//

CPPCodeGenerator::CPPCodeGenerator ( UMLDoc * parentDoc , const char * name)
    : CodeGenerator( parentDoc, name ) {

	//m_parentDoc = parentDoc; // this should be done by the call to the parent constructor?
	initAttributes();
}

CPPCodeGenerator::~CPPCodeGenerator ( ) {
	// destroy all separately owned codedocuments (e.g. header docs)
	QPtrList<CodeDocument> * list = &m_headercodedocumentVector;
	for (CodeDocument *doc = list->first(); doc; doc=list->next())
		delete doc;
}

//
// Methods
//

// Accessor methods
//

/**
 * returns "Cpp"
 */
QString CPPCodeGenerator::getLanguage() {
	return "Cpp";
}

/**
 * checks whether type is "CPPCodeGenerator"
 *
 * @param type
 */
bool CPPCodeGenerator::isType (QString & type)
{
   if(type == "CPPCodeGenerator")
	return true;
   return false;
}

/**
 * Set the value of m_createMakefile
 * @param new_var the new value of m_createMakefile
 */
void CPPCodeGenerator::setCreateProjectMakefile ( bool buildIt) {
	m_createMakefile = buildIt;
	CodeDocument * antDoc = findCodeDocumentByID(CPPMakefileCodeDocument::DOCUMENT_ID_VALUE);
	if (antDoc)
		antDoc->setWriteOutCode(buildIt);
}

/**
 * Get the value of m_createMakefile
 * @return the value of m_createMakefile
 */
bool CPPCodeGenerator::getCreateProjectMakefile ( ) {
	return m_createMakefile;
}

bool CPPCodeGenerator::addHeaderCodeDocument ( CPPHeaderCodeDocument * doc )
{

	QString tag = doc->getID();

	// assign a tag if one doesnt already exist
	if(tag.isEmpty())
	{
		tag = "cppheader"+QString::number(doc->getParentClassifier()->getID());
		doc->setID(tag);
	}

	if(m_codeDocumentDictionary.find(tag))
		return false; // return false, we already have some object with this tag in the list
	else
		m_codeDocumentDictionary.insert(tag, doc);

	m_headercodedocumentVector.append(doc);
	return true;
}

/**
 * Remove a header CodeDocument object from m_headercodedocumentVector List
 */
bool CPPCodeGenerator::removeHeaderCodeDocument ( CPPHeaderCodeDocument * remove_object ) {
	QString tag = remove_object->getID();
	if(!(tag.isEmpty()))
		m_codeDocumentDictionary.remove(tag);
	else
		return false;

	m_headercodedocumentVector.remove(remove_object);
	return true;
}

// In the C++ version, we need to make both source and header files as well
// as the makefile available.
CodeViewerDialog * CPPCodeGenerator::getCodeViewerDialog ( QWidget* parent, CodeDocument *doc,
							   Settings::CodeViewerState state)
{

	ClassifierCodeDocument * cdoc = dynamic_cast<ClassifierCodeDocument*>(doc);
	if(!cdoc)
		// bah..not a classcode document?? then just use vanilla version
		return CodeGenerator::getCodeViewerDialog(parent,doc,state);
	else {
		// build with passed (source) code document
		CodeViewerDialog *dialog;

		// use classifier to find appropriate header document
		UMLClassifier * c = cdoc->getParentClassifier();
		CPPHeaderCodeDocument * hdoc = findHeaderCodeDocumentByClassifier(c);
		if(hdoc)
		{
			// if we have a header document..build with that
			dialog = new CodeViewerDialog(parent, hdoc, state);
			dialog->addCodeDocument(doc);
		} else
			// shouldnt happen, but lets try to gracefully deliver something.
			dialog = new CodeViewerDialog(parent, doc, state);

		// add in makefile if available and desired
		if(getCreateProjectMakefile())
			dialog->addCodeDocument(findCodeDocumentByID(CPPMakefileCodeDocument::DOCUMENT_ID_VALUE));

		return dialog;
	}
}

QString CPPCodeGenerator::getCPPClassName (QString name) {
	return cleanName(name);
}

CPPCodeGenerationPolicy::CPPCommentStyle CPPCodeGenerator::getCommentStyle ( )
{
	return ((CPPCodeGenerationPolicy*)getPolicy())->getCommentStyle();
}

bool CPPCodeGenerator::getAutoGenerateConstructors ( )
{
	return ((CPPCodeGenerationPolicy*)getPolicy())->getAutoGenerateConstructors();
}

bool CPPCodeGenerator::getAutoGenerateAccessors ( )
{
	return ((CPPCodeGenerationPolicy*)getPolicy())->getAutoGenerateAccessors ();
}

// Other methods
//

// CHange the following dataTypes to the ones the user really
// wants in their code. Not yet complete.
QString CPPCodeGenerator::fixTypeName(QString string)
{
// FIX!!
	string.replace(QRegExp("^[Ll]ist$"),"QPtrList");
	string.replace(QRegExp("^string$"),"QString");
	return cleanName(string);
}

// special method needed so that we write out the header code documents
void CPPCodeGenerator::saveToXMI ( QDomDocument & doc, QDomElement & root ) {
	QString langType = getLanguage();
	QDomElement docElement = doc.createElement( "codegenerator" );
	docElement.setAttribute("language",langType);

	QPtrList<CodeDocument> * docList = getCodeDocumentList();
	for (CodeDocument * codeDoc = docList->first(); codeDoc; codeDoc= docList->next())
		codeDoc->saveToXMI(doc, docElement);

	for (CodeDocument * hcodeDoc = m_headercodedocumentVector.first(); hcodeDoc; hcodeDoc=m_headercodedocumentVector.next())
		hcodeDoc->saveToXMI(doc, docElement);

	root.appendChild( docElement );
}

/**
 * Force a synchronize of this code generator, and its present contents, to that of the parent UMLDocument.
 * Need to override parent method because we have header documents to consider too.
 */
void CPPCodeGenerator::syncCodeToDocument ( ) {

	QPtrList<CodeDocument> * docList = getCodeDocumentList();

	for (CodeDocument * doc = docList->first(); doc; doc=docList->next())
		doc->synchronize();

	for (CodeDocument * hcodeDoc = m_headercodedocumentVector.first(); hcodeDoc; hcodeDoc=m_headercodedocumentVector.next())
		hcodeDoc->synchronize();

}

/**
 * Write out all code documents to file as appropriate.
 */
void CPPCodeGenerator::writeCodeToFile ( )
{
	// write all source documents (incl. Makefile)
	writeListedCodeDocsToFile(getCodeDocumentList());

	// write all header documents
	writeListedCodeDocsToFile(&m_headercodedocumentVector);

}

// overridden because we need to be able to generate code for
// both the header and source documents
void CPPCodeGenerator::writeCodeToFile ( UMLClassifierList & concepts) {
	QPtrList<CodeDocument> docs;
	docs.setAutoDelete(false);

	for (UMLClassifier *concept= concepts.first(); concept; concept= concepts.next())
	{
		CodeDocument * doc = findCodeDocumentByClassifier(concept);
		if(doc)
			docs.append(doc);
		CodeDocument * hdoc = findHeaderCodeDocumentByClassifier(concept);
		if(hdoc)
			docs.append(hdoc);
	}

	writeListedCodeDocsToFile(&docs);
}


/**
 * Find a cppheadercodedocument by the given classifier.
 * @return      CPPHeaderCodeDocument
* @param       classifier
*/
CPPHeaderCodeDocument * CPPCodeGenerator::findHeaderCodeDocumentByClassifier (UMLClassifier * classifier )
{
	CodeDocument * doc = findCodeDocumentByID("cppheader"+QString::number(classifier->getID()));
	return dynamic_cast<CPPHeaderCodeDocument*>(doc);
}

/**
 * @return	ClassifierCodeDocument
 * @param	classifier
 * @param	this This package generator object.
 */
// source document version.
CodeDocument * CPPCodeGenerator::newClassifierCodeDocument (UMLClassifier * classifier)
{
	return new CPPSourceCodeDocument(classifier, this);
}

CodeComment * CPPCodeGenerator::newCodeComment ( CodeDocument * doc) {
	return new CPPCodeDocumentation(doc);
}

CPPHeaderCodeDocument * CPPCodeGenerator::newHeaderClassifierCodeDocument (UMLClassifier * classifier)
{
	return new CPPHeaderCodeDocument(classifier, this);
}

/**
 * @return	CPPMakefileCodeDocument
 * @param	this
 */
CPPMakefileCodeDocument * CPPCodeGenerator::newMakefileCodeDocument ( ) {
	return new CPPMakefileCodeDocument (this);
}


/**
 * Overloaded so that we may have both source and header documents for each
 * classifier.
 */
void CPPCodeGenerator::initFromParentDocument( ) {

	// Walk through the document converting classifiers into
	// classifier code documents as needed (e.g only if doesnt exist)
	UMLClassifierList concepts = getDocument()->getClassesAndInterfaces();
	for (UMLClassifier *c = concepts.first(); c; c = concepts.next())
	{

		// Doesnt exist? Then build one.
		CodeDocument * codeDoc = findCodeDocumentByClassifier(c);
		if (!codeDoc)
		{
			codeDoc = newClassifierCodeDocument(c);
			addCodeDocument(codeDoc); // this will also add a unique tag to the code document
		}

		CPPHeaderCodeDocument * hcodeDoc = findHeaderCodeDocumentByClassifier(c);
		if (!hcodeDoc)
		{
			hcodeDoc = new CPPHeaderCodeDocument(c,this);
			addHeaderCodeDocument(hcodeDoc); // this will also add a unique tag to the code document
		}
	}

}

// need to worry about adding both source, and header documents for each
// classifier
void CPPCodeGenerator::checkAddUMLObject (UMLObject * obj) {
	if (!obj)
		return;

	UMLClassifier * c = dynamic_cast<UMLClassifier*>(obj);
	if(c) {
		CodeDocument * cDoc = newClassifierCodeDocument(c);
		CPPHeaderCodeDocument * hcodeDoc = new CPPHeaderCodeDocument(c, this);
		addCodeDocument(cDoc);
		addHeaderCodeDocument(hcodeDoc); // this will also add a unique tag to the code document
	}
}

// need to worry about removing both source, and header documents for each
// classifier
void CPPCodeGenerator::checkRemoveUMLObject (UMLObject * obj)
{

	if (!obj)
		return;

	UMLClassifier * c = dynamic_cast<UMLClassifier*>(obj);
	if(c) {

		// source
		ClassifierCodeDocument * cDoc = (ClassifierCodeDocument*) findCodeDocumentByClassifier(c);
		if (cDoc)
			removeCodeDocument(cDoc);

		// header
		CPPHeaderCodeDocument * hcodeDoc = findHeaderCodeDocumentByClassifier(c);
		if (hcodeDoc)
			removeHeaderCodeDocument(hcodeDoc);
	}

}

void CPPCodeGenerator::initAttributes ( )
{

	setPolicy ( new CPPCodeGenerationPolicy(this, getPolicy()) );

       // load Classifier documents from parent document
	initFromParentDocument();

	// add in an Make build document
	CPPMakefileCodeDocument * buildDoc = newMakefileCodeDocument( );
	addCodeDocument(buildDoc);

	// set our 'writeout' policy for that code document
	setCreateProjectMakefile(DEFAULT_BUILD_MAKEFILE);

}

// should be 'static'
QString CPPCodeGenerator::scopeToCPPDecl(Uml::Scope scope)
{
	QString scopeString;
	switch(scope)
	{
		case Uml::Public:
			scopeString = "public";
			break;
		case Uml::Protected:
			scopeString = "protected";
			break;
		case Uml::Private:
		default:
			scopeString = "private";
			break;
	}
	return scopeString;
}

void CPPCodeGenerator::createDefaultDatatypes() {
	m_document->createDatatype("int");
	m_document->createDatatype("char");
	m_document->createDatatype("bool");
	m_document->createDatatype("float");
	m_document->createDatatype("double");
	m_document->createDatatype("long");
	m_document->createDatatype("short");
	m_document->createDatatype("string");
}

/**
 * List of reserved keywords for this code generator.
 *
 * Just add new keywords, then mark all lines and
 * pipe it through the external 'sort' program.
 */
static const char *ReservedWords[] = {
	"and",
	"and_eq",
	"__asm__",
	"asm",
	"__attribute__",
	"auto",
	"bitand",
	"bitor",
	"bool",
	"break",
	"BUFSIZ",
	"case",
	"catch",
	"char",
	"CHAR_BIT",
	"CHAR_MAX",
	"CHAR_MIN",
	"class",
	"CLOCKS_PER_SEC",
	"clock_t",
	"compl",
	"__complex__",
	"complex",
	"const",
	"const_cast",
	"continue",
	"__DATE__",
	"DBL_DIG",
	"DBL_EPSILON",
	"DBL_MANT_DIG",
	"DBL_MAX",
	"DBL_MAX_10_EXP",
	"DBL_MAX_EXP",
	"DBL_MIN",
	"DBL_MIN_10_EXP",
	"DBL_MIN_EXP",
	"default",
	"delete",
	"DIR",
	"div_t",
	"do",
	"double",
	"dynamic_cast",
	"E2BIG",
	"EACCES",
	"EAGAIN",
	"EBADF",
	"EBADMSG",
	"EBUSY",
	"ECANCELED",
	"ECHILD",
	"EDEADLK",
	"EDOM",
	"EEXIST",
	"EFAULT",
	"EFBIG",
	"EILSEQ",
	"EINPROGRESS",
	"EINTR",
	"EINVAL",
	"EIO",
	"EISDIR",
	"else",
	"EMFILE",
	"EMLINK",
	"EMSGSIZE",
	"ENAMETOOLONG",
	"ENFILE",
	"ENODEV",
	"ENOENT",
	"ENOEXEC",
	"ENOLCK",
	"ENOMEM",
	"ENOSPC",
	"ENOSYS",
	"ENOTDIR",
	"ENOTEMPTY",
	"ENOTSUP",
	"ENOTTY",
	"enum",
	"ENXIO",
	"EOF",
	"EPERM",
	"EPIPE",
	"ERANGE",
	"EROFS",
	"ESPIPE",
	"ESRCH",
	"ETIMEDOUT",
	"EXDEV",
	"EXIT_FAILURE",
	"EXIT_SUCCESS",
	"explicit",
	"export",
	"extern",
	"false",
	"__FILE__",
	"FILE",
	"FILENAME_MAX",
	"float",
	"FLT_DIG",
	"FLT_EPSILON",
	"FLT_MANT_DIG",
	"FLT_MAX",
	"FLT_MAX_10_EXP",
	"FLT_MAX_EXP",
	"FLT_MIN",
	"FLT_MIN_10_EXP",
	"FLT_MIN_EXP",
	"FLT_RADIX",
	"FLT_ROUNDS",
	"FOPEN_MAX",
	"for",
	"fpos_t",
	"friend",
	"__FUNCTION__",
	"__GNUC__",
	"goto",
	"HUGE_VAL",
	"if",
	"__imag__",
	"inline",
	"int",
	"INT16_MAX",
	"INT16_MIN",
	"int16_t",
	"INT32_MAX",
	"INT32_MIN",
	"int32_t",
	"INT64_MAX",
	"INT64_MIN",
	"int64_t",
	"INT8_MAX",
	"INT8_MIN",
	"int8_t",
	"INT_FAST16_MAX",
	"INT_FAST16_MIN",
	"int_fast16_t",
	"INT_FAST32_MAX",
	"INT_FAST32_MIN",
	"int_fast32_t",
	"INT_FAST64_MAX",
	"INT_FAST64_MIN",
	"int_fast64_t",
	"INT_FAST8_MAX",
	"INT_FAST8_MIN",
	"int_fast8_t",
	"INT_LEAST16_MAX",
	"INT_LEAST16_MIN",
	"int_least16_t",
	"INT_LEAST32_MAX",
	"INT_LEAST32_MIN",
	"int_least32_t",
	"INT_LEAST64_MAX",
	"INT_LEAST64_MIN",
	"int_least64_t",
	"INT_LEAST8_MAX",
	"INT_LEAST8_MIN",
	"int_least8_t",
	"INT_MAX",
	"INTMAX_MAX",
	"INTMAX_MIN",
	"intmax_t",
	"INT_MIN",
	"INTPTR_MAX",
	"INTPTR_MIN",
	"intptr_t",
	"_IOFBF",
	"_IOLBF",
	"_IONBF",
	"jmp_buf",
	"__label__",
	"LC_ALL",
	"LC_COLLATE",
	"LC_CTYPE",
	"LC_MONETARY",
	"LC_NUMERIC",
	"LC_TIME",
	"LDBL_DIG",
	"LDBL_EPSILON",
	"LDBL_MANT_DIG",
	"LDBL_MAX",
	"LDBL_MAX_10_EXP",
	"LDBL_MAX_EXP",
	"LDBL_MIN",
	"LDBL_MIN_10_EXP",
	"LDBL_MIN_EXP",
	"ldiv_t",
	"__LINE__",
	"LLONG_MAX",
	"long",
	"LONG_MAX",
	"LONG_MIN",
	"L_tmpnam",
	"M_1_PI",
	"M_2_PI",
	"M_2_SQRTPI",
	"MB_CUR_MAX",
	"MB_LEN_MAX",
	"mbstate_t",
	"M_E",
	"M_LN10",
	"M_LN2",
	"M_LOG10E",
	"M_LOG2E",
	"M_PI",
	"M_PI_2",
	"M_PI_4",
	"M_SQRT1_2",
	"M_SQRT2",
	"mutable",
	"namespace",
	"new",
	"not",
	"not_eq",
	"NPOS",
	"NULL",
	"operator",
	"or",
	"or_eq",
	"__PRETTY_FUNCTION__",
	"private",
	"protected",
	"PTRDIFF_MAX",
	"PTRDIFF_MIN",
	"ptrdiff_t",
	"public",
	"RAND_MAX",
	"__real__",
	"register",
	"reinterpret_cast",
	"restrict",
	"return",
	"SCHAR_MAX",
	"SCHAR_MIN",
	"SEEK_CUR",
	"SEEK_END",
	"SEEK_SET",
	"short",
	"SHRT_MAX",
	"SHRT_MIN",
	"SIGABRT",
	"SIGALRM",
	"SIG_ATOMIC_MAX",
	"SIG_ATOMIC_MIN",
	"sig_atomic_t",
	"SIGCHLD",
	"SIGCONT",
	"SIG_DFL",
	"SIG_ERR",
	"SIGFPE",
	"SIGHUP",
	"SIG_IGN",
	"SIGILL",
	"SIGINT",
	"SIGKILL",
	"signed",
	"SIGPIPE",
	"SIGQUIT",
	"SIGSEGV",
	"SIGSTOP",
	"SIGTERM",
	"SIGTRAP",
	"SIGTSTP",
	"SIGTTIN",
	"SIGTTOU",
	"SIGUSR1",
	"SIGUSR2",
	"SINT_MAX",
	"SINT_MIN",
	"SIZE_MAX",
	"sizeof",
	"size_t",
	"SLONG_MAX",
	"SLONG_MIN",
	"SSHRT_MAX",
	"SSHRT_MIN",
	"ssize_t",
	"static",
	"static_cast",
	"__STDC__",
	"__STDC_VERSION__",
	"stderr",
	"stdin",
	"stdout",
	"struct",
	"switch",
	"template",
	"this",
	"throw",
	"__TIME__",
	"time_t",
	"TMP_MAX",
	"true",
	"try",
	"typedef",
	"typeid",
	"typename",
	"typeof",
	"UCHAR_MAX",
	"UINT16_MAX",
	"uint16_t",
	"UINT32_MAX",
	"uint32_t",
	"UINT64_MAX",
	"uint64_t",
	"UINT8_MAX",
	"uint8_t",
	"UINT_FAST16_MAX",
	"uint_fast16_t",
	"UINT_FAST32_MAX",
	"uint_fast32_t",
	"UINT_FAST64_MAX",
	"uint_fast64_t",
	"UINT_FAST8_MAX",
	"uint_fast8_t",
	"UINT_LEAST16_MAX",
	"uint_least16_t",
	"UINT_LEAST32_MAX",
	"uint_least32_t",
	"UINT_LEAST64_MAX",
	"uint_least64_t",
	"UINT_LEAST8_MAX",
	"uint_least8_t",
	"UINT_MAX",
	"UINTMAX_MAX",
	"uintmax_t",
	"UINTPTR_MAX",
	"uintptr_t",
	"ULLONG_MAX",
	"ULONG_MAX",
	"union",
	"unsigned",
	"USHRT_MAX",
	"using",
	"va_list",
	"virtual",
	"void",
	"__volatile__",
	"volatile",
	"WCHAR_MAX",
	"WCHAR_MIN",
	"wchar_t",
	"wctrans_t",
	"wctype_t",
	"WEOF",
	"while",
	"WINT_MAX",
	"WINT_MIN",
	"wint_t",
	"xor",
	"xor_eq",
  NULL
};

/**
 * get list of reserved keywords
 */
const char **
CPPCodeGenerator::getReservedKeywords() {
  return ReservedWords;
}

#include "cppcodegenerator.moc"

