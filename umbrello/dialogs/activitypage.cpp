 /*
  *  copyright (C) 2002-2004
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

#include "activitypage.h"
#include "../statewidget.h"
#include "../listpopupmenu.h"
#include "../uml.h"
#include "../inputdialog.h"

#include <klocale.h>
#include <kbuttonbox.h>
#include <kdebug.h>
#include <qlayout.h>
#include <qstringlist.h>

ActivityPage::ActivityPage( QWidget * pParent, StateWidget * pWidget ) : QWidget( pParent ) {
	m_pStateWidget = pWidget;
	m_pMenu = 0;
	setupPage();
}

ActivityPage::~ActivityPage() {}

void ActivityPage::setupPage() {
	int margin = fontMetrics().height();
	QHBoxLayout * mainLayout = new QHBoxLayout( this );
	mainLayout -> setSpacing(10);

	m_pActivityGB = new QGroupBox(i18n("Activities"), this );
	QGridLayout* activityLayout = new QGridLayout( m_pActivityGB, 2, 2 );
	m_pActivityLB = new QListBox(m_pActivityGB );
	activityLayout -> setMargin(margin);
	activityLayout -> setSpacing ( 10 );
	activityLayout -> addWidget(m_pActivityLB, 0, 0);

	QVBoxLayout * buttonLayout = new QVBoxLayout( activityLayout );
	m_pUpArrowB = new KArrowButton( m_pActivityGB );
	m_pUpArrowB -> setEnabled( false );
	buttonLayout -> addWidget( m_pUpArrowB );

	m_pDownArrowB = new KArrowButton( m_pActivityGB, Qt::DownArrow );
	m_pDownArrowB -> setEnabled( false );
	buttonLayout -> addWidget( m_pDownArrowB );

	KButtonBox* buttonBox = new KButtonBox(m_pActivityGB);
	buttonBox->addButton( i18n("New Activity..."), this, SLOT(slotNewActivity()) );
	m_pDeleteActivityButton = buttonBox->addButton( i18n("Delete"),
							  this, SLOT(slotDelete()) );
	m_pRenameButton = buttonBox->addButton( i18n("Rename"), this, SLOT(slotRename()) );
	activityLayout->addMultiCellWidget(buttonBox, 1, 1, 0, 1);

	mainLayout -> addWidget( m_pActivityGB );

	//now fill activity list box
	QStringList list = m_pStateWidget -> getActivityList();
	QStringList::Iterator end(list.end());

	for( QStringList::Iterator it(list.begin()); it != end; ++it ) {
		m_pActivityLB -> insertItem( *it );
	}

	//now setup the signals
	connect(m_pActivityLB, SIGNAL(clicked(QListBoxItem *)), this, SLOT(slotClicked(QListBoxItem *)));
	connect(m_pActivityLB, SIGNAL(rightButtonPressed(QListBoxItem *, const QPoint &)),
	        this, SLOT(slotRightButtonPressed(QListBoxItem *, const QPoint &)));

	connect(m_pActivityLB, SIGNAL(rightButtonClicked(QListBoxItem *, const QPoint &)),
	        this, SLOT(slotRightButtonClicked(QListBoxItem *, const QPoint &)));

	connect( m_pUpArrowB, SIGNAL( clicked() ), this, SLOT( slotUpClicked() ) );
	connect( m_pDownArrowB, SIGNAL( clicked() ), this, SLOT( slotDownClicked() ) );
	connect( m_pActivityLB, SIGNAL( doubleClicked( QListBoxItem* ) ), this, SLOT( slotDoubleClicked( QListBoxItem* ) ) );

	enableWidgets(false);
}

void ActivityPage::updateActivities() {
	QStringList list;
	int count = m_pActivityLB -> count();
	for( int i = 0; i < count; i++ ) {
		list.append( m_pActivityLB -> text( i ) );
	}
	m_pStateWidget -> setActivities( list );
}

void ActivityPage::slotMenuSelection( int sel ) {
	switch( sel ) {
		case ListPopupMenu::mt_New_Activity:
			slotNewActivity();
			break;

		case ListPopupMenu::mt_Delete:
			slotDelete();
			break;

		case ListPopupMenu::mt_Rename:
			slotRename();
			break;
	}
}

void ActivityPage::slotNewActivity() {
	bool ok = false;
	QString name = m_pActivityLB->currentText();
	name = KInputDialog::getText( i18n("New Activity"), i18n("Enter the name of the new activity:"),
				      i18n("new activity"), &ok, UMLApp::app() );
	if( ok && name.length() > 0 ) {
		m_pActivityLB->insertItem( name );
		m_pStateWidget->addActivity( name );
	}
}

void ActivityPage::slotDelete() {
	QString name = m_pActivityLB->currentText();
	m_pStateWidget->removeActivity(name);
	m_pActivityLB->removeItem( m_pActivityLB->currentItem() );
	slotClicked(0);
}

void ActivityPage::slotRename() {
	bool ok = false;
	QString name = m_pActivityLB -> currentText();
	QString oldName = name;
	name = KInputDialog::getText( i18n("Rename Activity"), i18n("Enter the new name of the activity:"), name, &ok, UMLApp::app() );
	if( ok && name.length() > 0 ) {
		m_pActivityLB -> changeItem( name, m_pActivityLB -> currentItem());
		m_pStateWidget -> renameActivity( oldName, name );
	}
}

void ActivityPage::slotRightButtonClicked(QListBoxItem * /*item*/, const QPoint &/* p*/) {
	if(m_pMenu) {
		m_pMenu->hide();
		disconnect(m_pMenu, SIGNAL(activated(int)), this, SLOT(slotMenuSelection(int)));
		delete m_pMenu;
		m_pMenu = 0;
	}
}

void ActivityPage::slotRightButtonPressed(QListBoxItem * item, const QPoint & p)
{
	ListPopupMenu::Menu_Type type = ListPopupMenu::mt_Undefined;
	if( item ) { //pressed on an item
		type = ListPopupMenu::mt_Activity_Selected;
	} else { //pressed into fresh air
		type = ListPopupMenu::mt_New_Activity;
	}

	if(m_pMenu) {
		m_pMenu -> hide();
		disconnect(m_pMenu, SIGNAL(activated(int)), this, SLOT(slotMenuSelection(int)));
		delete m_pMenu;
		m_pMenu = 0;
	}
	m_pMenu = new ListPopupMenu(this, type);
	m_pMenu->popup(p);
	connect(m_pMenu, SIGNAL(activated(int)), this, SLOT(slotMenuSelection(int)));
}

void ActivityPage::slotUpClicked() {
	int count = m_pActivityLB -> count();
	int index = m_pActivityLB -> currentItem();
	//shouldn't occur, but just in case
	if( count <= 1 || index <= 0 ) {
		return;
	}

	//swap the text around ( meaning attributes )
	QString aboveString = m_pActivityLB -> text( index - 1 );
	QString currentString = m_pActivityLB -> text( index );
	m_pActivityLB -> changeItem( currentString, index -1 );
	m_pActivityLB -> changeItem( aboveString, index );
	//set the moved atttribute selected
	QListBoxItem * item = m_pActivityLB -> item( index - 1 );
	m_pActivityLB -> setSelected( item, true );
	slotClicked(item);
}

void ActivityPage::slotDownClicked() {
	int count = m_pActivityLB -> count();
	int index = m_pActivityLB -> currentItem();
	//shouldn't occur, but just in case
	if( count <= 1 || index >= count - 1 ) {
		return;
	}

	//swap the text around ( meaning attributes )
	QString belowString = m_pActivityLB -> text( index + 1 );
	QString currentString = m_pActivityLB -> text( index );
	m_pActivityLB -> changeItem( currentString, index + 1 );
	m_pActivityLB -> changeItem( belowString, index );
	//set the moved atttribute selected
	QListBoxItem * item = m_pActivityLB -> item( index + 1 );
	m_pActivityLB -> setSelected( item, true );
	slotClicked(item);
}

void ActivityPage::slotClicked(QListBoxItem *item) {
	//make sure clicked on an item
	if(!item) {
		enableWidgets(false);
		m_pActivityLB -> clearSelection();
	} else {
		enableWidgets(true);
	}
}

void ActivityPage::slotDoubleClicked(QListBoxItem* item) {
	if (item) {
		slotRename();
	}
}

void ActivityPage::enableWidgets(bool state) {
	if( !state ) {
		m_pUpArrowB->setEnabled( false );
		m_pDownArrowB->setEnabled( false );
		m_pDeleteActivityButton->setEnabled(false);
		m_pRenameButton->setEnabled(false);
		return;
	}
	/*now check the order buttons.
		Double check an item is selected
	   If only one att. in list make sure there disabled.
		If at top item,only allow down arrow to be enabled.
		If at bottom item. only allow up arrow to be enabled.
	*/
	int index = m_pActivityLB->currentItem();
	if( m_pActivityLB->count() == 1 || index == -1 ) {
		m_pUpArrowB->setEnabled(false);
		m_pDownArrowB->setEnabled(false);
	} else if( index == 0 ) {
		m_pUpArrowB->setEnabled(false);
		m_pDownArrowB->setEnabled(true);
	} else if( index == (int)m_pActivityLB->count() - 1 ) {
		m_pUpArrowB->setEnabled(true);
		m_pDownArrowB->setEnabled(false);
	} else {
		m_pUpArrowB->setEnabled(true);
		m_pDownArrowB->setEnabled(true);
	}
	m_pDeleteActivityButton->setEnabled(true);
	m_pRenameButton->setEnabled(true);
}


#include "activitypage.moc"
