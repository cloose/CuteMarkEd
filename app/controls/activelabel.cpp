#include "activelabel.h"

#include <QMouseEvent>

ActiveLabel::ActiveLabel(QWidget *parent) :
    QLabel(parent)
{
}

ActiveLabel::ActiveLabel(const QString &text, QWidget *parent) :
    QLabel(text, parent)
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
