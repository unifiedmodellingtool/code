/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2003 Luis De la Parra <lparrab@gmx.net>                 *
 *   copyright (C) 2004-2007                                               *
 *   Umbrello UML Modeller Authors <uml-devel@uml.sf.net>                  *
 ***************************************************************************/

#ifndef REFACTORING_ASSISTANT
#define REFACTORING_ASSISTANT

#include <k3listview.h>
#include <QtGui/QPixmap>
#include <QtGui/QMenu>
#include <QtGui/QDropEvent>
#include <map>


class UMLObject;
class UMLClassifier;
class UMLClassifierListItem;
class UMLDoc;

class QPoint;

class RefactoringAssistant : public K3ListView
{
    Q_OBJECT
public:
    typedef std::map<Q3ListViewItem*, UMLObject*> UMLObjectMap;

    explicit RefactoringAssistant( UMLDoc *doc, UMLClassifier *obj = 0, QWidget *parent = 0, const char *name = 0 );
    virtual ~RefactoringAssistant();

    void refactor( UMLClassifier *obj );

public slots:

    void addBaseClassifier();
    void addDerivedClassifier();
    void addInterfaceImplementation();
    void createOperation( );
    void createAttribute( );
    void editProperties( );

    void umlObjectModified( const UMLObject *obj = 0 );

    void operationAdded( UMLClassifierListItem *o );
    void operationRemoved( UMLClassifierListItem *o );

    void attributeAdded( UMLClassifierListItem *a );
    void attributeRemoved( UMLClassifierListItem *a );

    void itemExecuted( Q3ListViewItem *item );
    void showContextMenu( K3ListView*, Q3ListViewItem*, const QPoint&);

protected:

    struct { QPixmap Public,
        Protected,
        Private,
        Implementation,
        Generalization,
        Subclass;
    } m_pixmaps;

    UMLObject* findUMLObject( const Q3ListViewItem* );
    Q3ListViewItem* findListViewItem( const UMLObject *obj );
    void editProperties( UMLObject *obj );
    void addClassifier( UMLClassifier *classifier, Q3ListViewItem *parent = 0, bool addSuper = true, bool addSub = true, bool recurse = false );
    void loadPixmaps();
    virtual bool acceptDrag(QDropEvent *event) const;
    virtual void movableDropEvent (Q3ListViewItem* parent, Q3ListViewItem* afterme);
    void setVisibilityIcon( Q3ListViewItem *item , const UMLObject *obj );

    UMLClassifier *m_umlObject;
    UMLDoc *m_doc;
    QMenu *m_menu;
    UMLObjectMap m_umlObjectMap;

private:

    QAction* createAction(const QString text, const char * method);

};


#endif

