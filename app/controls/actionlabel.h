#ifndef ACTIONLABEL_H
#define ACTIONLABEL_H

#include "controls/activelabel.h"

class QAction;

class ActionLabel : public ActiveLabel
{
    Q_OBJECT

public:
    explicit ActionLabel(QWidget *parent=0);

    void setAction(QAction *action);

public slots:
    void updateFromAction();

private:
    QAction *m_action;
};

#endif // ACTIONLABEL_H
