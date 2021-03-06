/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2014                                               *
 *   Umbrello UML Modeller Authors <umbrello-devel@kde.org>                *
 ***************************************************************************/

#ifndef PARAMETERPROPERTIESDIALOG_H
#define PARAMETERPROPERTIESDIALOG_H

#include "attribute.h"

#include "singlepagedialogbase.h"
#include <klineedit.h>
#include <kcombobox.h>

class DocumentationWidget;
class UMLDoc;
class UMLStereotypeWidget;
class QGroupBox;
class QLabel;
class QRadioButton;

/**
 * Displays a dialog box that displays properties of a parameter.
 * You need to make sure that @ref UMLDoc is made to be the
 * parent.
 *
 * @short A properties dialog box for a parameter.
 * @author Paul Hensgen <phensgen@techie.com>
 * Bugs and comments to umbrello-devel@kde.org or http://bugs.kde.org
 */
class ParameterPropertiesDialog : public SinglePageDialogBase
{
    Q_OBJECT
public:

    ParameterPropertiesDialog(QWidget * parent, UMLDoc * doc, UMLAttribute * attr);
    ~ParameterPropertiesDialog();

    virtual bool apply();

protected:
    QString getName() {
        return m_pNameLE->text();
    }

    QString getInitialValue() {
        return m_pInitialLE->text();
    }

    QString getTypeName() {
        return m_pTypeCB->currentText();
    }

    Uml::ParameterDirection::Enum getParmKind();

    void insertTypesSorted(const QString& type = QString());

    bool validate();

protected slots:

    virtual void slotButtonClicked(int button);

private:
    QGroupBox * m_pParmGB;
    QGroupBox *m_pKind;
    QRadioButton * m_pIn, * m_pOut, *m_pInOut;
    QLabel * m_pTypeL, * m_pNameL, * m_pInitialL;
    KComboBox * m_pTypeCB;
    KLineEdit * m_pNameLE, * m_pInitialLE;
    DocumentationWidget * m_docWidget;
    UMLDoc * m_pUmldoc;
    UMLAttribute * m_pAtt;
    UMLStereotypeWidget *m_stereotypeWidget;
};

#endif
