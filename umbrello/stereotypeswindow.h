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

#ifndef STEREOTYPESWINDOW_H
#define STEREOTYPESWINDOW_H

#include <QDockWidget>
#include <QModelIndex>

class QTableView;

class StereotypesWindow : public QDockWidget
{
    Q_OBJECT
public:
    explicit StereotypesWindow(QWidget *parent = 0);
    ~StereotypesWindow();

signals:

public slots:
    void modified();

protected slots:
    void slotStereotypesDoubleClicked(QModelIndex index);

protected:
    QTableView *m_stereotypesTree;
};

#endif // STEREOTYPESWINDOW_H
