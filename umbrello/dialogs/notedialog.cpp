/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2006                                               *
 *   Umbrello UML Modeller Authors <uml-devel@uml.sf.net>                  *
 ***************************************************************************/

//qt includes
#include <qlayout.h>
#include <qlabel.h>
//Added by qt3to4:
#include <QVBoxLayout>
#include <QHBoxLayout>
//kde includes
#include <klocale.h>
#include <kmessagebox.h>
//app includes
#include "notedialog.h"
//qt includes
#include <qlineedit.h>
#include <q3groupbox.h>
#include <q3textedit.h>


NoteDialog::NoteDialog( QWidget * parent, NoteWidget * pNote )
    : KDialog(parent) {
    setCaption( i18n("Note Documentation") );
    setButtons( Help | Ok | Cancel );
    setDefaultButton( Ok );
    setModal( true );
    showButtonSeparator( true );

    m_pNoteWidget = pNote;
    int margin = fontMetrics().height();

    QFrame *frame = new QFrame( this );
    setMainWidget( frame );
    m_pDocGB = new Q3GroupBox(i18n("Documentation"), frame);
    QVBoxLayout * mainLayout = new QVBoxLayout(frame);
    mainLayout -> addWidget(m_pDocGB);
    mainLayout -> setSpacing(10);
    mainLayout -> setMargin(margin);

    QHBoxLayout * docLayout = new QHBoxLayout(m_pDocGB);
    docLayout -> setSpacing(10);
    docLayout -> setMargin(margin);

    m_pDocTE = new Q3TextEdit( m_pDocGB );
    m_pDocTE -> setFocus();
    docLayout -> addWidget( m_pDocTE );
    m_pDocTE -> setText( pNote -> getDoc() );
    setMinimumSize(330, 160);
}

NoteDialog::~NoteDialog() {}

void NoteDialog::slotOk() {
    m_pNoteWidget -> setDoc( m_pDocTE -> text() );
    accept();
}

