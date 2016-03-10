/*
 * Copyright 2013 Christian Loose <christian.loose@hamburg.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "activelabel.h"

#include <QAction>
#include <QMouseEvent>

ActiveLabel::ActiveLabel(QWidget *parent) :
    QLabel(parent),
    m_action(0)
{
}

ActiveLabel::ActiveLabel(const QString &text, QWidget *parent) :
    QLabel(text, parent),
    m_action(0)
{
}

void ActiveLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
    // double click with left mouse button?
    if (e->button() == Qt::LeftButton) {
        emit doubleClicked();
    }

    QLabel::mouseDoubleClickEvent(e);
}

void ActiveLabel::setAction(QAction *action)
{
    // if was previously defined, disconnect
    if (m_action) {
        disconnect(m_action, &QAction::changed, this, &ActiveLabel::updateFromAction);
        disconnect(this, &ActiveLabel::doubleClicked, m_action, &QAction::trigger);
    }

    // set new action
    m_action = action;

    // update label using action's data
    updateFromAction();

    // action action and label to have them synced
    // whenever one of them is triggered
    connect(m_action, &QAction::changed, this, &ActiveLabel::updateFromAction);
    connect(this, &ActiveLabel::doubleClicked, m_action, &QAction::trigger);
}

void ActiveLabel::updateFromAction()
{
    setStatusTip(m_action->statusTip());
    setToolTip(m_action->toolTip());
    setEnabled(m_action->isEnabled());

    // update text based on QAction data
    QString actionText = m_action->text();
    actionText.remove("&");

    if (m_action->isCheckable()) {
        if (m_action->isChecked())
            setText(QString("%1: %2").arg(actionText).arg(tr("on")));
        else
            setText(QString("%1: %2").arg(actionText).arg(tr("off")));
    } else {
        setText(actionText);
    }
}
