/****************************************************************************
**
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#pragma once

#include "gui.h"
#include <QtCore/QPair>
#include <QtCore/QPoint>
#include <QMessageBox>

class QAbstractScrollArea;
class QDialog;
class QMenu;
class QWidget;

namespace qtgui {

class QTTOOLS_GUI_EXPORT QWidgetUtils
{
public:
    template<typename PARENT_WIDGET>
    static PARENT_WIDGET* findFirstParentWidget(QWidget* widget);

    template<typename PARENT_WIDGET>
    static PARENT_WIDGET* findLastParentWidget(QWidget* widget);

    static void wrapWidgetInDialog(QWidget* widget, QDialog* dialog);
    static void addContentsWidget(QWidget* containerWidget, QWidget* contentsWidget);

    static QPoint globalPos(const QWidget* widget, Qt::Corner widgetCorner);
    static void moveWidgetRightTo(QWidget* widget, const QWidget* nextTo);
    static void moveWidgetLeftTo(QWidget* widget, const QWidget* nextTo);

    static QPair<int, int> horizAndVertScrollValue(const QAbstractScrollArea* area);
    static void setHorizAndVertScrollValue(QAbstractScrollArea* area,
                                           const QPair<int, int>& values);

    static void asyncDialogExec(QDialog* dialog);
    static void asyncMenuExec(QMenu* menu, const QPoint& pos = QCursor::pos());
    static QMessageBox* asyncMsgBoxInfo(
            QWidget* parent,
            const QString& title,
            const QString& text,
            QMessageBox::StandardButtons buttons = QMessageBox::Ok);
    static QMessageBox* asyncMsgBoxWarning(
            QWidget* parent,
            const QString& title,
            const QString& text,
            QMessageBox::StandardButtons buttons = QMessageBox::Ok);
    static QMessageBox* asyncMsgBoxCritical(
            QWidget* parent,
            const QString& title,
            const QString& text,
            QMessageBox::StandardButtons buttons = QMessageBox::Ok);
};

} // namespace qtgui

// --
// -- Implementation
// --

// QtWidgets
#include <QWidget>

namespace qtgui {

//! Searches up in the direct parents of \p widget the first ancestor being of type \c PARENT_WIDGET
template<typename PARENT_WIDGET>
PARENT_WIDGET* QWidgetUtils::findFirstParentWidget(QWidget* widget)
{
    PARENT_WIDGET* foundParentWidget = NULL;
    QWidget* iteratorWidget = widget;
    while (iteratorWidget != NULL && foundParentWidget == NULL) {
        iteratorWidget = iteratorWidget->parentWidget();
        foundParentWidget = qobject_cast<PARENT_WIDGET*>(iteratorWidget);
    }
    return foundParentWidget;
}

//! Searches up in the direct parents of \p widget the last ancestor being of type \c PARENT_WIDGET
template<typename PARENT_WIDGET>
PARENT_WIDGET* QWidgetUtils::findLastParentWidget(QWidget* widget)
{
    PARENT_WIDGET* foundParentWidget = NULL;
    QWidget* iteratorWidget = widget;
    while (iteratorWidget != NULL) {
        iteratorWidget = iteratorWidget->parentWidget();
        PARENT_WIDGET* currParentWidget = qobject_cast<PARENT_WIDGET*>(iteratorWidget);
        if (currParentWidget != NULL)
            foundParentWidget = currParentWidget;
    }
    return foundParentWidget;
}

} // namespace qtgui
