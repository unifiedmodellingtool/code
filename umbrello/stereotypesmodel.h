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

#ifndef STEREOTYPESMODEL_H
#define STEREOTYPESMODEL_H

#include "stereotype.h"
#include "uml.h"
#include "umldoc.h"

#include <KLocalizedString>

#include <QAbstractTableModel>
#include <QtDebug>

Q_DECLARE_METATYPE(UMLStereotype*);

/**
 * The StereotypesModel class provides the content of a stereotypes list
 * as a model according to the Qt model/view design pattern.
 */
class StereotypesModel : public QAbstractTableModel
{
public:
    StereotypesModel(UMLStereotypeList *stereotypes)
      : m_stereotypes(stereotypes)
    {
    }

    /**
     * reimplemented from QAbstractTableModel
     */
    int rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);
        return m_stereotypes->count();
    }

    /**
     * reimplemented from QAbstractTableModel
     */
    int columnCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);
        return 1;
    }

    /**
     * reimplemented from QAbstractTableModel
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
    {
        if (section < 0)
            return QVariant();

        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Vertical)
            return section + 1;
        if (section == 0)
            return QVariant(i18n("Name"));
        else return QVariant();
    }

    /**
     * reimplemented from QAbstractTableModel
     */
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const
    {
        if (role == Qt::UserRole && index.column() == 0) {
            QVariant v;
            v.setValue(m_stereotypes->at(index.row()));
            return v;
        }

        if (role != Qt::DisplayRole)
            return QVariant();

        int cCount = columnCount(index);
        if (index.column() >= cCount)
            return QVariant();

        UMLStereotype *s = m_stereotypes->at(index.row());
        // single column view
        if (cCount == 1) {
            QString a = s->name() + QString(QLatin1String(" (%1)")).arg(s->refCount());
            return a;
          }

        // two columns view
        if (index.column() == 0)
            return s->name();
        else
            return s->refCount();
    }

    /**
     * Add stereotype to the model.
     *
     * @param stereotype
     * @return true if stereotype has been added
     * @return false stereotype has been already added to the model
     */
    bool addStereotype(UMLStereotype *stereotype)
    {
        if (m_stereotypes->contains(stereotype))
            return false;
        int index = m_stereotypes->count();
        beginInsertRows(QModelIndex(), index, index);
        m_stereotypes->append(stereotype);
        endInsertRows();
        return true;
    }

    /**
     * Remove stereotype from the model.
     *
     * @param stereotype
     * @return true if stereotype has been removed
     * @return false stereotype is not in the model
     */
    bool removeStereotype(UMLStereotype *stereotype)
    {
        if (!m_stereotypes->contains(stereotype))
            return false;
        int index = m_stereotypes->indexOf(stereotype);
        beginRemoveRows(QModelIndex(), index, index);
        m_stereotypes->removeAll(stereotype);
        endRemoveRows();
        return true;
    }

    /**
     * Emit data changed signal for a QModelIndex.
     * @param index
     */
    void emitDataChanged(const QModelIndex &index)
    {
        emit dataChanged(index, index);
    }

    /**
     * Emit data changed signal for an index.
     * @param index
     */
    void emitDataChanged(int index)
    {
        QModelIndex mi = createIndex(index,0);
        emit dataChanged(mi, mi);
    }

    /**
     * Emit data changed signal for a stereotype instance.
     * @param instance
     */
    void emitDataChanged(UMLStereotype *stereotype)
    {
        int index = m_stereotypes->indexOf(stereotype);
        emitDataChanged(index);
    }

protected:
    UMLStereotypeList *m_stereotypes;
};

#endif // STEREOTYPESMODEL_H
