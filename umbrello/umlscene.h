/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright (C) 2002-2007                                               *
 *   Umbrello UML Modeller Authors <uml-devel@uml.sf.net>                  *
 ***************************************************************************/

#ifndef UMLSCENE_H
#define UMLSCENE_H

#include <QGraphicsScene>

//local includes
#include "umlnamespace.h"
#include "optionstate.h"
#include "umlobjectlist.h"
#include "umlwidgetlist.h"
#include "associationwidgetlist.h"
#include "messagewidgetlist.h"
#include "worktoolbar.h"

// forward declarations
class ClassOptionsPage;
class IDChangeLog;
class ListPopupMenu;
class FloatingTextWidget;
class ObjectWidget;
class UMLFolder;
class UMLApp;
class UMLDoc;
class UMLAttribute;
class UMLCanvasObject;
class UMLClassifier;
class UMLViewImageExporter;
class UMLForeignKeyConstraint;
class UMLEntity;
class UMLView;

class QPrinter;
class ToolBarState;
class ToolBarStateFactory;

/**
 * UMLScene instances represent diagrams.
 * The UMLScene class inherits from QGraphicsScene.
 */
class UMLScene : public QGraphicsScene
{
    Q_OBJECT
    public:
    friend class UMLViewImageExporterModel;

    /**
     * Constructor
     */
    UMLScene(UMLFolder *parentFolder);

    /**
     * Destructor
     */
    virtual ~UMLScene();

    // Accessors and other methods dealing with loaded/saved data

    /**
     * Return the UMLFolder in which this diagram lives.
     */
    UMLFolder *getFolder() {
        return m_pFolder;
    }

    /**
     * Set the UMLFolder in which this diagram lives.
     */
    void setFolder(UMLFolder *folder) {
        m_pFolder = folder;
    }

    /**
     * Return the documentation of the diagram.
     */
    QString getDoc() const {
        return m_Documentation;
    }

    /**
     * Set the documentation of the diagram.
     */
    void setDoc(const QString &doc) {
        m_Documentation = doc;
    }

    /**
     * Return the name of the diagram.
     */
    QString getName() const;

    /**
     * Set the name of the diagram.
     */
    void setName(const QString &name);

    /**
     * Returns the type of the diagram.
     */
    Uml::Diagram_Type getType() const {
        return m_Type;
    }

    /**
     * Set the type of diagram.
     */
    void setType(Uml::Diagram_Type type) {
        m_Type = type;
    }

    /**
     * Returns the fill color to use.
     */
    QColor getFillColor() const;

    /**
     * Returns the default brush for diagram widgets.
     */
    QBrush brush() const {
        // TODO: Remove getFillColor()
        return getFillColor();
    }

    /**
     * Set the background color.
     *
     * @param color  The color to use.
     */
    void setFillColor(const QColor &color);

    /**
     * Returns the line color to use.
     */
    QColor getLineColor() const;

    /**
     * Sets the line color.
     *
     * @param color  The color to use.
     */
    void setLineColor(const QColor &color);

    /**
     * Returns the line width to use.
     */
    uint getLineWidth() const;

    /**
     * Sets the line width.
     *
     * @param width  The width to use.
     */
    void setLineWidth(uint width);

    /**
     * Returns the ID of the diagram.
     */
    Uml::IDType getID() const {
        return m_nID;
    }

    /**
     * Sets the ID of the diagram.
     */
    void setID(Uml::IDType id) {
        m_nID = id;
    }

    /**
     * Returns height of the diagram canvas.
     */
    qreal canvasHeight() const {
        return sceneRect().height();
    }

    /**
     * Returns width of the diagram canvas.
     */
    qreal canvasWidth() const {
        return sceneRect().width();
    }

    /**
     * Return whether to use snap to grid.
     */
    bool getSnapToGrid() const {
        return m_bUseSnapToGrid;
    }

    /**
     *  Sets whether to snap to grid.
     */
    void setSnapToGrid(bool bSnap);

    /**
     * Return whether to use snap to grid for component size.
     */
    bool getSnapComponentSizeToGrid() const {
        return m_bUseSnapComponentSizeToGrid;
    }

    /**
     * Returns the x grid size.
     */
    int getSnapX() const {
        return m_nSnapX;
    }

    /**
     * Sets the x grid size.
     */
    void setSnapX(int x) {
        m_nSnapX = x;
        update();
    }

    /**
     * Returns the y grid size.
     */
    int getSnapY() const {
        return m_nSnapY;
    }

    /**
     * Sets the y grid size.
     */
    void setSnapY(int y) {
        m_nSnapY = y;
        update();
    }

    /**
     * Returns the input coordinate with possible grid-snap applied.
     */
    qreal snappedX(qreal x);

    /**
     * Returns the input coordinate with possible grid-snap applied.
     */
    qreal snappedY(qreal y);

    /**
     *  Returns whether to show snap grid or not.
     */
    bool getShowSnapGrid() const;

    /**
     * Sets whether to show snap grid.
     */
    void setShowSnapGrid(bool bShow);

    /**
     * Sets whether to snap to grid for component size.
     */
    void setSnapComponentSizeToGrid(bool bSnap);

    /**
     * Returns whether to use the fill/background color
     */
    bool getUseFillColor() const;

    /**
     * Sets whether to use the fill/background color
     */
    void setUseFillColor(bool ufc);

    /**
     * Returns the font to use
     */
    QFont getFont() const;

    /**
     * Sets the font for the view and optionally all the widgets on the view.
     */
    void setFont(QFont font, bool changeAllWidgets = false);

    /**
     * Returns whether to show operation signatures.
     */
    bool getShowOpSig() const;

    /**
     * Sets whether to show operation signatures.
     */
    void setShowOpSig(bool bShowOpSig);

    /**
     * Returns the options being used.
     */
    const Settings::OptionState& getOptionState() const {
        return m_Options;
    }

    /**
     * Sets the options to be used.
     */
    void setOptionState(const Settings::OptionState& options) {
        m_Options = options;
    }

    /**
     * Returns a reference to the association list.
     */
    AssociationWidgetList& getAssociationList() {
        return m_AssociationList;
    }

    /**
     * Returns a reference to the widget list.
     */
    UMLWidgetList& getWidgetList() {
        return m_WidgetList;
    }

    /**
     * Returns a reference to the message list.
     */
    MessageWidgetList& getMessageList() {
        return m_MessageList;
    }

    // End of accessors and methods that only deal with loaded/saved data
    ////////////////////////////////////////////////////////////////////////

    /**
     * contains the implementation for printing functionality
     */
    void print(QPrinter *pPrinter, QPainter & pPainter);

    /**
     * Sees if a message is relevant to the given widget.  If it does delete it.
     * @param w The widget to check messages against.
     */
    void checkMessages(ObjectWidget * w);

    /**
     * Finds a widget with the given ID.
     *
     * @param id The ID of the widget to find.
     *
     * @return Returns the widget found, returns 0 if no widget found.
     */
    NewUMLRectWidget* findWidget(Uml::IDType id);

    /**
     * Finds an association widget with the given ID.
     *
     * @param id The ID of the widget to find.
     *
     * @return Returns the widget found, returns 0 if no widget found.
     */
    AssociationWidget* findAssocWidget(Uml::IDType id);

    /**
     * Finds an association widget with the given type and widgets.
     *
     * @param at  The Association_Type of the widget to find.
     * @param pWidgetA Pointer to the NewUMLRectWidget of role A.
     * @param pWidgetB Pointer to the NewUMLRectWidget of role B.
     *
     * @return Returns the widget found, returns 0 if no widget found.
     */
    AssociationWidget* findAssocWidget(Uml::Association_Type at,
                                       NewUMLRectWidget *pWidgetA, NewUMLRectWidget *pWidgetB);

    /**
     * Finds an association widget with the given widgets and the given role B name.
     * Considers the following association types:
     *  at_Association, at_UniAssociation, at_Composition, at_Aggregation
     * This is used for seeking an attribute association.
     *
     * @param pWidgetA  Pointer to the NewUMLRectWidget of role A.
     * @param pWidgetB  Pointer to the NewUMLRectWidget of role B.
     * @param roleNameB Name at the B side of the association (the attribute name)
     *
     * @return Returns the widget found, returns 0 if no widget found.
     */
    AssociationWidget* findAssocWidget(NewUMLRectWidget *pWidgetA,
                                       NewUMLRectWidget *pWidgetB, const QString& roleNameB);

    /**
     * Remove a widget from view.
     *
     * @param o  The widget to remove.
     */
    void removeWidget(NewUMLRectWidget *o);

    /**
     * Sets a widget to a selected state and adds it to a list of selected widgets.
     *
     * @param w The widget to set to selected.
     * @param me The mouse event containing the information about the selection.
     */
    void setSelected(NewUMLRectWidget *w, QGraphicsSceneMouseEvent *me);

    /**
     * Returns a list of selected widgets.
     *
     * This method walks over all the selected items, tries to cast them to
     * widget and on success adds it to widget only list.
     * Finally it returns this list.
     */
    UMLWidgetList selectedWidgets() const;

    /**
     *  Clear the selected widgets list.
     */
    void clearSelected();

    /**
     * Move all the selected widgets by a relative X and Y offset.
     *
     * @param dX The distance to move horizontally.
     * @param dY The distance to move vertically.
     */
    void moveSelectedBy(qreal dX, qreal dY);

    /**
     * Return the amount of widgets selected.
     *
     * @param filterText  When true, do NOT count floating text widgets that
     *                    belong to other widgets (i.e. only count tr_Floating.)
     *                    Default: Count all widgets.
     * @return  Number of widgets selected.
     */
    int getSelectCount(bool filterText = false) const;

    /**
     * Set the useFillColor variable to all selected widgets
     *
     * @param useFC The state to set the widget to.
     */
    void selectionUseFillColor(bool useFC);

    /**
     * Set the font for all the currently selected items.
     */
    void selectionSetFont(const QFont &font);

    /**
     * Set the line color for all the currently selected items.
     */
    void selectionSetLineColor(const QColor &color);

    /**
     * Set the line width for all the currently selected items.
     */
    void selectionSetLineWidth(uint width);

    /**
     * Set the fill color for all the currently selected items.
     */
    void selectionSetFillColor(const QColor &color);

    /**
     * Toggles the show setting sel of all selected items.
     */
    void selectionToggleShow(int sel);

    /**
     * Delete the selected widgets list and the widgets in it.
     */
    void deleteSelection();

    /**
     * Selects all widgets
     */
    void selectAll();

    /**
     * Return a unique ID for the diagram.  Used by the @ref ObjectWidget class.
     *
     * @return Return a unique ID for the diagram.
     */
    Uml::IDType getLocalID();

    /**
     * Returns whether a widget is already on the diagram.
     *
     * @param id The id of the widget to check for.
     *
     * @return Returns true if the widget is already on the diagram, false if not.
     */
    bool widgetOnDiagram(Uml::IDType id);

    /**
     * Returns true if this diagram resides in an externalized folder.
     * CHECK: It is probably cleaner to move this to the UMLListViewItem.
     */
    bool isSavedInSeparateFile();

    /**
     * Get the pos variable.  Used internally to keep track of the cursor.
     */
    QPointF & getPos() {
        return m_Pos;
    }

    /**
     * Set the pos variable.  Used internally to keep track of the cursor.
     *
     * @param _pos The position to set to.
     */
    void setPos(const QPointF &_pos) {
        m_Pos = _pos;
    }

    /**
     * Returns the active view(the view with focus) associated with this scene.
     * \note This currently simply returns the first view in the views() list as
     * multiple views are yet to be implemented.
     * \todo Implement this appropriately later.
     */
    UMLView* activeView() const;

    /**
     * Sets the popup menu to use when clicking on a diagram background
     * (rather than a widget or listView).
     */
    void setMenu();

    /**
     * Reset the toolbar.
     */
    void resetToolbar() {
        emit sigResetToolBar();
    }

    /**
     * Returns the status on whether in a paste state.
     *
     * @return Returns the status on whether in a paste state.
     */
    bool getPaste() const {
        return m_bPaste;
    }

    /**
     * Sets the status on whether in a paste state.
     */
    void setPaste(bool paste) {
        m_bPaste = paste;
    }

    /**
     * Returns a List of all the UMLObjects(Use Cases, Concepts and Actors) in the View
     */
    UMLObjectList getUMLObjects();

    /**
     * Activate all the objects and associations after a load from the clipboard
     */
    void activate();

    /**
     * Returns a list with all the selected associations from the diagram
     */
    AssociationWidgetList getSelectedAssocs();

    /**
     * Fills the List with all the selected widgets from the diagram
     * The list can be filled with all the selected widgets, or be filtered to prevent
     * text widgets other than tr_Floating to be append.
     *
     * @param WidgetList The UMLWidgetList to fill.
     * @param filterText Don't append the text, unless their role is tr_Floating
     */
    bool getSelectedWidgets(UMLWidgetList& WidgetList, bool filterText = true);

    /**
     * Activate the view after a load a new file
     */
    void activateAfterLoad(bool bUseLog = false);

    void endPartialWidgetPaste();
    void beginPartialWidgetPaste();

    /**
     * Removes a AssociationWidget from a diagram
     * Physically deletes the AssociationWidget passed in.
     *
     * @param pAssoc  Pointer to the AssociationWidget.
     */
    void removeAssoc(AssociationWidget* pAssoc);

    /**
     * Removes all the associations related to Widget
     *
     * @param pWidget  Pointer to the widget to remove.
     */
    void removeAssociations(NewUMLRectWidget* pWidget);

    /**
     * Sets each association as selected if the widgets it associates are selected
     */
    void selectAssociations(bool bSelect);

    /**
     * Fills Associations with all the associations that includes a widget related to object
     */
    void getWidgetAssocs(UMLObject* Obj, AssociationWidgetList & Associations);

    /**
     * Removes All the associations of the diagram
     */
    void removeAllAssociations();

    /**
     * Removes All the widgets of the diagram
     */
    void removeAllWidgets();

    /**
     *  Calls the same method in the DocWindow.
     */
    void showDocumentation(UMLObject * object, bool overwrite);

    /**
     *  Calls the same method in the DocWindow.
     */
    void showDocumentation(NewUMLRectWidget * widget, bool overwrite);

    /**
     *  Calls the same method in the DocWindow.
     */
    void showDocumentation(AssociationWidget * widget, bool overwrite);

    /**
     *  Calls the same method in the DocWindow.
     */
    void updateDocumentation(bool clear);

    /**
     * Returns the PNG picture of the paste operation.
     *
     * @param rect the area of the diagram to copy
     * @param diagram the class to store PNG picture of the paste operation.
     */
    void getDiagram(const QRectF &rect, QPixmap & diagram);

    /**
     * Paint diagram to the paint device
     */
    void  getDiagram(const QRectF &area, QPainter & painter);

    /**
     * Returns the PNG picture of the paste operation.
     */
    void copyAsImage(QPixmap*& pix);

    /**
     * Returns the imageExporter used to export the view.
     *
     * @return The imageExporter used to export the view.
     */
    UMLViewImageExporter* getImageExporter();

    /**
     * Adds an association to the view from the given data.
     * Use this method when pasting.
     */
    bool addAssociation(AssociationWidget* pAssoc , bool isPasteOperation = false);

    /**
     * Removes an AssociationWidget from the association list
     * and removes the corresponding UMLAssociation from the current UMLDoc.
     */
    void removeAssocInViewAndDoc(AssociationWidget* assoc);

    /**
     * Adds a widget to the view from the given data.
     * Use this method when pasting.
     */
    bool addWidget(NewUMLRectWidget * pWidget , bool isPasteOperation = false);

    /**
     * Returns the offset point at which to place the paste from clipboard.
     * Just add the amount to your co-ords.
     * Only call this straight after the event, the value won't stay valid.
     * Should only be called by Assoc widgets at the moment. no one else needs it.
     */
    QPointF getPastePoint();

    /**
     * Reset the paste point.
     */
    void resetPastePoint();

    /**
     * Called by the view or any of its children when they start a cut
     * operation.
     */
    void setStartedCut() {
        m_bStartedCut = true;
    }

    /**
     * Creates automatically any Associations that the given @ref NewUMLRectWidget
     * may have on any diagram.  This method is used when you just add the NewUMLRectWidget
     * to a diagram.
     */
    void createAutoAssociations(NewUMLRectWidget * widget);

    /**
     * If the m_Type of the given widget is Uml::wt_Class then
     * iterate through the class' attributes and create an
     * association to each attribute type widget that is present
     * on the current diagram.
     */
    void createAutoAttributeAssociations(NewUMLRectWidget *widget);

    void createAutoConstraintAssociations(NewUMLRectWidget* widget);


    /**
     * Refreshes containment association, i.e. removes possible old
     * containment and adds new containment association if applicable.
     *
     * @param self  Pointer to the contained object for which
     *   the association to the containing object is
     *   recomputed.
     */
    void updateContainment(UMLCanvasObject *self);


    /**
     * Shows the properties dialog for the view.
     */
    bool showPropDialog();

    /**
     * Sets some options for all the @ref ClassifierWidget on the view.
     */
    void setClassWidgetOptions(ClassOptionsPage * page);

    /**
     * Call before copying/cutting selected widgets.  This will make sure
     * any associations/message selected will make sure both the widgets
     * widgets they are connected to are selected.
     */
    void checkSelections();

    /**
     * This function checks if the currently selected items have all the same
     * type (class, interface, ...). If true, the selection is unique and true
     * will be returned.
     * If there are no items selected, the function will return always true.
     */
    bool checkUniqueSelection();

    /**
     * Asks for confirmation and clears everything on the diagram.
     * Called from menus.
     */
    void clearDiagram();

    /**
     * Changes snap to grid boolean.
     * Called from menus.
     */
    void toggleSnapToGrid();

    /**
     * Changes snap to grid for component size boolean.
     * Called from menus.
     */
    void toggleSnapComponentSizeToGrid();

    /**
     *  Changes show grid boolean.
     * Called from menus.
     */
    void toggleShowGrid();

    /**
     * Changes the zoom to the currently set level (now loaded from file)
     * Called from UMLApp::slotUpdateViews()
     */
    void fileLoaded();

    /**
     * Sets the size of the canvas to just fit on all the items
     */
    void resizeCanvasToItems();

    /**
     * The width and height of a diagram canvas in pixels.
     */
    static const qreal defaultCanvasSize;

    // Load/Save interface:

    /**
     * Creates the "diagram" tag and fills it with the contents of the diagram.
     */
    virtual void saveToXMI(QDomDocument & qDoc, QDomElement & qElement);

    /**
     * Loads the "diagram" tag.
     */
    virtual bool loadFromXMI(QDomElement & qElement);

    /**
     * Loads the "UISDiagram" tag of Unisys.IntegratePlus.2 generated files.
     */
    bool loadUISDiagram(QDomElement & qElement);

    /**
     * Loads a "widget" element from XMI, used by loadFromXMI() and the clipboard.
     */
    NewUMLRectWidget* loadWidgetFromXMI(QDomElement& widgetElement);

    /**
     * Add an object to the application, and update the view.
     */
    void addObject(UMLObject *object);

    /**
     * Selects all the widgets within an internally kept rectangle.
     */
    void selectWidgets(qreal px, qreal py, qreal qx, qreal qy);

    /**
     * Determine whether on a sequence diagram we have clicked on a line
     * of an Object.
     *
     * @return The widget thats line was clicked on.
     *  Returns 0 if no line was clicked on.
     */
    ObjectWidget * onWidgetLine(const QPointF &point) const;

    /**
     * Determine whether on a sequence diagram we have clicked on
     * the destruction box of an Object.
     *
     * @return The widget thats destruction box was clicked on.
     *  Returns 0 if no destruction box was clicked on.
     */
    ObjectWidget * onWidgetDestructionBox(const QPointF &point) const;

    /**
     * Return pointer to the first selected widget (for multi-selection)
     */
    NewUMLRectWidget* getFirstMultiSelectedWidget() const;

    /**
     * Tests the given point against all widgets and returns the
     * widget for which the point is within its bounding rectangle.
     * In case of multiple matches, returns the smallest widget.
     * Returns NULL if the point is not inside any widget.
     * Does not use or modify the m_pOnWidget member.
     */
    NewUMLRectWidget *getWidgetAt(const QPointF& p);

    /**
     * Initialize and announce a newly created widget.
     * Auxiliary to contentsMouseReleaseEvent().
     */
    void setupNewWidget(NewUMLRectWidget *w);

    /**
     * Return whether we are currently creating an object.
     */
    bool getCreateObject() const {
        return m_bCreateObject;
    }

    /**
     * Set whether we are currently creating an object.
     */
    void setCreateObject(bool bCreate) {
        m_bCreateObject = bCreate;
    }

    /**
     * Emit the sigRemovePopupMenu Qt signal.
     */
    void emitRemovePopupMenu() {
        emit sigRemovePopupMenu();
    }

    /**
     * Used for creating unique name of collaboration messages.
     */
    int generateCollaborationId();

    /**
     * Return the UMLDoc pointer
     */
    UMLDoc* getUMLDoc() {
        return m_pDoc;
    }

    void callBaseMouseMethod(QGraphicsSceneMouseEvent *event);

    bool isMouseMovingItems() const {
        return m_isMouseMovingItems;
    }

protected:

    void drawBackground(QPainter *p, const QRectF& rect);

    // Methods and members related to loading/saving

    bool loadWidgetsFromXMI(QDomElement & qElement);

    bool loadMessagesFromXMI(QDomElement & qElement);

    bool loadAssociationsFromXMI(QDomElement & qElement);

    bool loadUisDiagramPresentation(QDomElement & qElement);

    /**
     * Contains the unique ID to allocate to a widget that needs an
     * ID for the view.  @ref ObjectWidget is an example of this.
     */
    Uml::IDType m_nLocalID;

    /**
     * The ID of the view.  Allocated by @ref UMLDoc
     */
    Uml::IDType m_nID;

    /**
     * The type of diagram to represent.
     */
    Uml::Diagram_Type m_Type;

    /**
     * The name of the diagram.
     */
    QString m_Name;

    /**
     * The documentation of the diagram.
     */
    QString m_Documentation;

    /**
     * Options used by view
     */
    Settings::OptionState m_Options;

    /**
     * Contains all the message widgets on the diagram.
     */
    MessageWidgetList m_MessageList;

    /**
     * Contains all the UMLWidgets on the diagram.
     */
    UMLWidgetList m_WidgetList;

    /**
     * Contains all the AssociationWidgets on the diagram.
     */
    AssociationWidgetList m_AssociationList;

    /**
     * The snap to grid x size.
     */
    int m_nSnapX;

    /**
     * The snap to grid y size.
     */
    int m_nSnapY;

    /**
     * Determines whether to use snap to grid.  The default is off.
     */
    bool m_bUseSnapToGrid;

    /**
     * Determines whether to use snap to grid for component
     * size.  The default is off.
     */
    bool m_bUseSnapComponentSizeToGrid;

    /**
     * Determines whether to show the snap grid.  The default will be on if the grid is on.
     */
    bool m_bShowSnapGrid;

    // End of methods and members related to loading/saving
    ////////////////////////////////////////////////////////////////////////

    /**
     * Override standard method.
     */
    void dragEnterEvent(QGraphicsSceneDragDropEvent *enterEvent);

    /**
     * Override standard method.
     */
    void dragMoveEvent(QGraphicsSceneDragDropEvent *moveEvent);

    /**
     * Override standard method.
     */
    void dropEvent(QGraphicsSceneDragDropEvent *dropEvent);

    /**
     * Gets the smallest area to print.
     *
     * @return Returns the smallest area to print.
     */
    QRectF getDiagramRect();

    /**
     * Overrides the standard operation.
     * Calls the same method in the current tool bar state.
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

    /**
     * Overrides the standard operation.
     * Calls the same method in the current tool bar state.
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);

    /**
     * Override standard method.
     * Calls the same method in the current tool bar state.
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);

    /**
     * Override standard method.
     * Calls the same method in the current tool bar state.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);

    bool m_isMouseMovingItems;
    bool isArrowMode();


    /**
     * Selects all the widgets of the given association widget.
     */
    void selectWidgetsOfAssoc (AssociationWidget * a);

    /**
     * Calls setSelected on the given NewUMLRectWidget and enters
     * it into the m_SelectedList while making sure it is
     * there only once.
     */
    void makeSelected (NewUMLRectWidget * uw);

    /**
     * Updates the size of all components in this view.
     */
    void updateComponentSizes();

    /**
     * Find the maximum bounding rectangle of FloatingTextWidget widgets.
     * Auxiliary to copyAsImage().
     *
     * @param ft Poqrealer to the FloatingTextWidget widget to consider.
     * @param px  X coordinate of lower left corner. This value will be
     *            updated if the X coordinate of the lower left corner
     *            of ft is smaller than the px value passed in.
     * @param py  Y coordinate of lower left corner. This value will be
     *            updated if the Y coordinate of the lower left corner
     *            of ft is smaller than the py value passed in.
     * @param qx  X coordinate of upper right corner. This value will be
     *            updated if the X coordinate of the upper right corner
     *            of ft is larger than the qx value passed in.
     * @param qy  Y coordinate of upper right corner. This value will be
     *            updated if the Y coordinate of the upper right corner
     *            of ft is larger than the qy value passed in.
     */
    void findMaxBoundingRectangle(const FloatingTextWidget* ft,
                                  qreal& px, qreal& py, qreal& qx, qreal& qy);

    void forceUpdateWidgetFontMetrics(QPainter *painter);

    /**
     * Used for creating unique name of collaboration messages.
     */
    int m_nCollaborationId;

    QPointF m_Pos;
    bool m_bCreateObject, m_bDrawSelectedOnly, m_bPaste;
    ListPopupMenu * m_pMenu;

    /**
     *  Flag if view/children started cut operation.
     */
    bool m_bStartedCut;

private:
    /**
     * The folder in which this UMLScene is contained
     */
    UMLFolder *m_pFolder;

    /**
     * set to true when a child has used the showDocumentation method,
     * thus when one clicks on a child widget.
     * Reset to false when clicking in an empty region of the view.
     */
    bool m_bChildDisplayedDoc;

    ToolBarStateFactory* m_pToolBarStateFactory;
    ToolBarState* m_pToolBarState;

    /**
     * LocalID Changes Log for paste actions
     */
    IDChangeLog * m_pIDChangesLog;

    /**
     *
     * True if the view was activated after the serialization(load)
     */
    bool m_bActivated;

    /**
     * Status of a popupmenu on view.
     * true - a popup is on view
     */
    bool m_bPopupShowing;

    /**
     * The offset at which to paste the clipboard.
     */
    QPointF m_PastePoint;

    /**
     * Pointer to the UMLDoc
     */
    UMLDoc* m_pDoc;

    /**
     * The UMLViewImageExporter used to export the view.
     */
    UMLViewImageExporter* m_pImageExporter;

    /**
     * Create an association with the attribute attr associated with the NewUMLRectWidget
     * widget if the UMLClassifier type is present on the current diagram.
     */
    void createAutoAttributeAssociation(UMLClassifier *type,
                                        UMLAttribute *attr,
                                        NewUMLRectWidget *widget);

    void createAutoConstraintAssociation(UMLEntity* refEntity,
                                         UMLForeignKeyConstraint* fkConstraint,
                                         NewUMLRectWidget* widget);

    /**
     * Returns true if the first widget's X is smaller than second's.
     * Used for sorting the UMLWidgetList.
     *
     * @param widget1 The widget to compare.
     * @param widget2 The widget to compare with.
     */
    static bool hasWidgetSmallerX(const NewUMLRectWidget* widget1, const NewUMLRectWidget* widget2);

    /**
     * Returns true if the first widget's Y is smaller than second's.
     * Used for sorting the UMLWidgetList.
     *
     * @param widget1 The widget to compare.
     * @param widget2 The widget to compare with.
     */
    static bool hasWidgetSmallerY(const NewUMLRectWidget* widget1, const NewUMLRectWidget* widget2);

    /**
     * Looks for the smallest x-value of the given UMLWidgets.
     *
     * @param widgetList A list with UMLWidgets.
     */
    qreal getSmallestX(const UMLWidgetList &widgetList);

    /**
     * Looks for the smallest y-value of the given UMLWidgets.
     *
     * @param widgetList A list with UMLWidgets.
     */
    qreal getSmallestY(const UMLWidgetList &widgetList);

    /**
     * Looks for the biggest x-value of the given UMLWidgets.
     *
     * @param widgetList A list with UMLWidgets.
     */
    qreal getBiggestX(const UMLWidgetList &widgetList);

    /**
     * Looks for the biggest y-value of the given UMLWidgets.
     *
     * @param widgetList A list with UMLWidgets.
     */
    qreal getBiggestY(const UMLWidgetList &widgetList);

    /**
     * Returns the sum of the heights of the given UMLWidgets
     *
     * @param widgetList A list with UMLWidgets.
     */
    qreal getHeightsSum(const UMLWidgetList &widgetList);

    /**
     * Returns the sum of the widths of the given UMLWidgets.
     *
     * @param widgetList A list with UMLWidgets.
     */
    qreal getWidthsSum(const UMLWidgetList &widgetList);

    /**
     * Sorts the given UMLWidgetList based on the Compare function.
     * The list is cleared and all the widgets are added again in order.
     *
     * The comp function gets two const NewUMLRectWidget* params and returns
     * a boolean telling if the first widget was smaller than the second,
     * whatever the "smaller" concept is depending on the sorting to do.
     *
     * @param widgetList The list with the widgets to order.
     * @param comp The comp function to compare the widgets.
     */
    template<typename Compare>
    void sortWidgetList(UMLWidgetList &widgetList, Compare comp);

public slots:


    /**
     * Changes the current tool to the selected tool.
     * The current tool is cleaned and the selected tool initialized.
     */
    void slotToolBarChanged(int c);
    void slotObjectCreated(UMLObject * o);
    void slotObjectRemoved(UMLObject * o);

    /**
     * When a menu selection has been made on the menu
     * that this view created, this method gets called.
     */
    void slotMenuSelection(QAction* action);

    /**
     * This slot is entered when an event has occurred on the views display,
     * most likely a mouse event.  Before it sends out that mouse event everyone
     * that displays a menu on the views surface (widgets and this) thould remove any
     * menu.  This stops more then one menu bieing displayed.
     */
    void slotRemovePopupMenu();

    /**
     * makes this view the active view by asking the document to show us
     */
    void slotActivate();

    /**
     * Connects to the signal that @ref UMLApp emits when a cut operation
     * is successful.
     * If the view or a child started the operation the flag m_bStartedCut will
     * be set and we can carry out any operation that is needed, like deleting the selected
     * widgets for the cut operation.
     */
    void slotCutSuccessful();

    /**
     * Called by menu when to show the instance of the view.
     */
    void slotShowView();

    /**
     * Left Alignment
     */
    void alignLeft();

    /**
     * Right Alignment
     */
    void alignRight();

    /**
     * Top Alignment
     */
    void alignTop();

    /**
     * Bottom Alignment
     */
    void alignBottom();

    /**
     * Vertical Middle Alignment
     */
    void alignVerticalMiddle();

    /**
     * Horizontal Middle Alignment
     */
    void alignHorizontalMiddle();

    /**
     * Vertical Distribute Alignment
     */
    void alignVerticalDistribute();

    /**
     * Horizontal Distribute Alignment
     */
    void alignHorizontalDistribute();

signals:
    void sigResetToolBar();
    void sigColorChanged(Uml::IDType);
    void sigRemovePopupMenu();
    void sigClearAllSelected();
    void sigLineWidthChanged(Uml::IDType);
    void sigSnapToGridToggled(bool);
    void sigSnapComponentSizeToGridToggled(bool);
    void sigShowGridToggled(bool);

    /**
     * Emitted when an association is removed.
     */
    void sigAssociationRemoved(AssociationWidget*);

    /**
     * Emitted when a widget is removed.
     */
    void sigWidgetRemoved(NewUMLRectWidget*);
};

#endif // UMLSCENE_H