/*
    Copyright 2015  Ralf Habacker <ralf.habacker@freenet.de>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy
    defined in Section 14 of version 3 of the license.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stereotypeswindow.h"
#include "stereotypesmodel.h"

#include "stereotype.h"
#include "uml.h"
#include "umldoc.h"
#include "umllistview.h"
#include "umlobject.h"

#include <KLocalizedString>

#include <QHeaderView>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QtDebug>

//#include "tests/modeltest.h"

StereotypesWindow::StereotypesWindow(QWidget *parent)
    : QDockWidget(i18n("&Stereotypes"), parent)
{
    setObjectName(QLatin1String("StereotypesWindow"));

    QSortFilterProxyModel *proxy = new QSortFilterProxyModel;
    proxy->setSourceModel(UMLApp::app()->document()->stereotypesModel());
    proxy->setSortCaseSensitivity(Qt::CaseInsensitive);
    m_stereotypesTree = new QTableView;
    m_stereotypesTree->setModel(proxy);
    m_stereotypesTree->setSortingEnabled(true);
    m_stereotypesTree->verticalHeader()->setDefaultSectionSize(20);
    m_stereotypesTree->verticalHeader()->setVisible(false);
    m_stereotypesTree->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    m_stereotypesTree->setShowGrid(false);
    setWidget(m_stereotypesTree);

    connect(m_stereotypesTree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotStereotypesDoubleClicked(QModelIndex)));
}

StereotypesWindow::~StereotypesWindow()
{
    delete m_stereotypesTree;
}

void StereotypesWindow::modified()
{
    UMLStereotype *o = static_cast<UMLStereotype*>(QObject::sender());
    if (!o)
        return;
    int index = UMLApp::app()->document()->stereotypes().indexOf(o);
    UMLApp::app()->document()->stereotypesModel()->emitDataChanged(index);
}

void StereotypesWindow::slotStereotypesDoubleClicked(QModelIndex index)
{
    QVariant v = UMLApp::app()->document()->stereotypesModel()->data(index, Qt::UserRole);
    if (v.canConvert<UMLStereotype*>()) {
        UMLStereotype *s = v.value<UMLStereotype*>();
        s->showPropertiesDialog(this);
    }
}
