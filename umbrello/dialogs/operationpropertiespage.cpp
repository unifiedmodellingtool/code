/***************************************************************************
                          operationpropertiespage.cpp
                             -------------------
    copyright            : (C) 2003 Luis De la Parra
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "operationpropertiespage.h"
#include "parameterpropertiespage.h"
#include "umbrellodialog.h"
#include "../operation.h"
#include "../attribute.h"
#include "../umldoc.h"

#include <qlineedit.h>
#include <qtextedit.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlistview.h>

#include <kstandarddirs.h>
#include <klocale.h>
#include <kdebug.h>

using Umbrello::ParameterPropertiesPage;



OperationPropertiesPage::OperationPropertiesPage(UMLOperation *c, UMLDoc *doc, QWidget *parent, const char *name)
	: OperationPropertiesBase( parent, name ),DialogPage( parent == 0 ),
	  m_umlObject(c), m_doc(doc)
{
	loadData();
	connect(m_name,SIGNAL(textChanged(const QString&)),this,SIGNAL(pageModified()));
	connect(m_type,SIGNAL(textChanged(const QString&)),this,SIGNAL(pageModified()));
	connect(m_abstract,SIGNAL(toggled(bool)),this,SIGNAL(pageModified()));
	connect(m_static,SIGNAL(toggled(bool)), this, SIGNAL(pageModified()));
	connect(m_public,SIGNAL(toggled(bool)),this,SIGNAL(pageModified()));
	connect(m_protected,SIGNAL(toggled(bool)),this,SIGNAL(pageModified()));
	connect(m_private,SIGNAL(toggled(bool)),this,SIGNAL(pageModified()));
	//parameter list

	connect(m_umlObject,SIGNAL(modified()),this,SLOT(loadData()));
	connect(this,SIGNAL(pageModified()),this,SLOT(pageContentsModified()));
}

OperationPropertiesPage::~OperationPropertiesPage() {}

void OperationPropertiesPage::apply()
{
	saveData();
}

void OperationPropertiesPage::cancel()
{
	loadData();
}

void OperationPropertiesPage::pageContentsModified()
{
	if(m_autoApply)
	{
		saveData();
	}
}


void OperationPropertiesPage::loadData()
{
	disconnect(this,SIGNAL(pageModified()),this,SLOT(pageContentsModified()));

	m_name->setText(m_umlObject->getName());
	m_type->insertStringList(m_doc->getModelTypes() );
	m_type->setCurrentText(m_umlObject->getReturnType());
	m_abstract->setChecked(m_umlObject->getAbstract());
	m_static->setChecked(m_umlObject->getStatic());
	switch(m_umlObject->getScope())
	{
		case Uml::Public:
			m_public->setChecked(true);
			break;
		case Uml::Protected:
			m_protected->setChecked(true);
			break;
		case Uml::Private:
		default:
			m_private->setChecked(true);
	}
	m_paramList.clear();
	QPtrList<UMLAttribute> *list = m_umlObject->getParmList();
	QListViewItem *item;
	UMLAttribute *copy;
	// create list view and working-copy of attributes
	for( UMLAttribute *att = list->last(); att; att = list->prev() )
	{
		copy = new UMLAttribute(this,att->getName(),att->getID(),att->getTypeName(), att->getScope(),att->getInitialValue());
		m_paramList.prepend(copy);
		item = new QListViewItem( m_parameterList, copy->getName() );
		item->setPixmap(0, (copy->getScope() == Uml::Public ? m_pixmaps.Public :
				    (copy->getScope() == Uml::Protected ? m_pixmaps.Protected :
				    m_pixmaps.Private)));
		m_paramMap[item] = copy;
	}
}

void OperationPropertiesPage::saveData()
{
	disconnect(m_umlObject,SIGNAL(modified()),this,SLOT(loadData()));

	m_umlObject->setName(m_name->text());
	m_umlObject->setReturnType(m_type->currentText());
	m_umlObject->setAbstract(m_abstract->isChecked());
	m_umlObject->setStatic(m_static->isChecked());
	if (m_public->isChecked())
		m_umlObject->setScope(Uml::Public);
	else if (m_protected->isChecked())
		m_umlObject->setScope(Uml::Protected);
	else
		m_umlObject->setScope(Uml::Private);

	///////////////////////////
	 //remove deleted attributes
	{
	QPtrList<UMLAttribute> list;
	list = *(m_umlObject->getParmList());
	list.setAutoDelete(false);
	kdDebug()<<"removing deleted atts"<<endl;
	for( UMLAttribute *att = list.first(); att ; att = list.next() )
	{kdDebug()<<"checking if "<<att->getName()<<" still exists."<<endl;
		 UMLAttribute *old(0);
		 for( old = m_paramList.first(); old ; old = m_paramList.next() )
		{
			if( old->getID() == att->getID() )
				 break;
		}
		if(!old)
		{
			 m_umlObject->removeParm( att );
		}
	}
	}
	{
	// add/update attributes
	QPtrList<UMLAttribute> *pList = m_umlObject->getParmList();
	UMLAttribute *att;
	int index,old_index;
	kdDebug()<<"updating params"<<endl;
	for( att = m_paramList.first(), index = 0; att ; att = m_paramList.next(), ++index )
	{
		UMLAttribute *old(0);
		for( old = pList->first(), old_index = 0; old ; old = pList->next(), ++old_index )
		{kdDebug()<<"testing if modified:"<<old->getName()<<endl;
			if( old->getID() == att->getID() )
				break;
		}
		if( !old )
		{//add new attribute
		kdDebug()<<"new attribute!"<<endl;
			UMLAttribute *a = new UMLAttribute( m_umlObject, att->getName(),m_doc->getUniqueID(),
                                                            att->getTypeName(),att->getScope(),att->getInitialValue());
			a->setDoc( att->getDoc() );
			m_umlObject->addParm(a,index);
		}
		else
		{//update attribute
		kdDebug()<<"updating attribute!"<<endl;
			old->setName(att->getName());
			old->setTypeName(att->getTypeName());
			old->setScope(att->getScope());
			old->setInitialValue(att->getInitialValue());
			if( old_index != index )
			{kdDebug()<<"reordering"<<endl;
				m_umlObject->removeParm(old);
				m_umlObject->addParm(old,index);
			}
		}
	}
	}
	kdDebug()<<"done"<<endl;
	//////////////////////////////
	connect(m_umlObject,SIGNAL(modified()),this,SLOT(loadData()));	
}


void OperationPropertiesPage::moveUp( )
{
	QListViewItem *item = m_parameterList->currentItem();
	int index = m_paramList.findRef(m_paramMap[item]);
	if( !item || index < 0 )
	{
		return;
	}
	QListViewItem *above = item->itemAbove( );
	if( !above )
	{
		return;
	}
	above = above->itemAbove( );
	if( above ) 
	{
		item->moveItem( above );
	}
	else
	{//we are already the second, and cannot move further up just like that, so we move the first child down instead
		m_parameterList->firstChild()->moveItem( item );
	}
	UMLAttribute *a = m_paramList.take( index );
	m_paramList.insert( --index, a );
	emit pageModified( );
}
void OperationPropertiesPage::moveDown( )
{
	QListViewItem *item = m_parameterList->currentItem();
	int index = m_paramList.findRef(m_paramMap[item]);
	if( !item || index < 0 )
	{
		return;
	}
	QListViewItem *below = item->itemBelow();
	if( !below )
	{
		return;
	}
	item->moveItem( below );
	UMLAttribute *a = m_paramList.take( index );
	m_paramList.insert( ++index, a );
	emit pageModified( );
}

void OperationPropertiesPage::createParameter( )
{
	UMLAttribute *a = new UMLAttribute(this,"new_parameter",-1);
	UmbrelloDialog dialog(this, UmbrelloDialog::Swallow, "edit_attribute", true, i18n("Attribute properties"), 
	                       UmbrelloDialog::Ok | UmbrelloDialog::Cancel );
	ParameterPropertiesPage *page = new ParameterPropertiesPage(a,&dialog,0);
	dialog.setMainWidget(page);
// 	dialog.addPage(page,i18n("Attribute Properties"));
	if( dialog.exec() )
	{
		m_paramList.append(a);
		QListViewItem *item = new QListViewItem( m_parameterList, a->getName() );
		item->setPixmap(0, (a->getScope() == Uml::Public ? m_pixmaps.Public :
				    (a->getScope() == Uml::Protected ? m_pixmaps.Protected :
			    	m_pixmaps.Private)));
		m_paramMap[item] = a;
		emit pageModified( );
	}
	else
	{
		delete a;
	}
}

void OperationPropertiesPage::editSelected( )
{
	QListViewItem *item = m_parameterList->currentItem();
	UMLAttribute *a = m_paramMap[item];
	if(!a)
		return;
	UmbrelloDialog dialog(this, UmbrelloDialog::Swallow, "edit_attribute", true, i18n("Attribute properties"), 
	                       UmbrelloDialog::Ok | UmbrelloDialog::Cancel );
	ParameterPropertiesPage *page = new ParameterPropertiesPage(a,&dialog,0);
// 	dialog.addPage(page,i18n("Attribute Properties"));
	dialog.setMainWidget(page);
	if(dialog.exec())
	{
		item->setText(0,a->getName());
		item->setPixmap(0, (a->getScope() == Uml::Public ? m_pixmaps.Public :
				    (a->getScope() == Uml::Protected ? m_pixmaps.Protected :
			    	m_pixmaps.Private)));
		emit pageModified( );
	}
	
}

void OperationPropertiesPage::deleteSelected( )
{
	QListViewItem *item = m_parameterList->currentItem();
	UMLAttribute *a = m_paramMap[item];
	if(!a)
		return;
	m_paramList.removeRef( a );
	m_paramMap.remove(item);
	delete a;
	delete item;
	emit pageModified( );
}

void OperationPropertiesPage::itemSelected(QListViewItem *item )
{
	UMLAttribute *att = m_paramMap[item];
	if( !att )
		return;
	
	//enable/disable buttons
	m_upButton->setEnabled( item->itemAbove()?true:false);
	m_downButton->setEnabled( item->itemBelow()?true:false);
}

void OperationPropertiesPage::loadPixmaps()
{
	KStandardDirs *dirs = KGlobal::dirs();
	QString dataDir = dirs -> findResourceDir( "data", "umbrello/pics/public.png" );
	dataDir += "/umbrello/pics/";

	m_pixmaps.Public.load( dataDir + "public.png" );
	m_pixmaps.Protected.load( dataDir + "protected.png" );
	m_pixmaps.Private.load( dataDir + "private.png" );

}


#include "operationpropertiespage.moc"

