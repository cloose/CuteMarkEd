#include "actionlabel.h"

#include <QAction>

ActionLabel::ActionLabel(QWidget *parent) :
	ActiveLabel(parent),
    m_action(0)
{
}

void ActionLabel::setAction(QAction *action)
{
    // if was previously defined, disconnect
    if(m_action != NULL) {
        disconnect(m_action, &QAction::changed, this, &ActionLabel::updateFromAction);
		disconnect(this, &ActionLabel::doubleClicked, m_action, &QAction::trigger);
    }

    // set new action
    m_action = action;

    // update label using action's data
    updateFromAction();

    // action action and label to have them synced
    // whenever one of them is triggered
    connect(m_action, &QAction::changed, this, &ActionLabel::updateFromAction);
	connect(this, &ActionLabel::doubleClicked, m_action, &QAction::trigger);
}

void ActionLabel::updateFromAction()
{
    setStatusTip(m_action->statusTip());
    setToolTip(m_action->toolTip());
    setEnabled(m_action->isEnabled());

    // update text based on QAction data
    QString actionText = m_action->text();
    actionText.remove("&");

    if(m_action->isCheckable()) {
        if(m_action->isChecked())
            setText(QString("%1: %2").arg(actionText).arg(tr("on")));
        else
            setText(QString("%1: %2").arg(actionText).arg(tr("off")));
    } else {
        setText(actionText);
    }
}


