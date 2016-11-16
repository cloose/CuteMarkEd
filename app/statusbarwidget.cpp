#include "statusbarwidget.h"

#include <QHBoxLayout>
#include <QTextBlock>
#include <QLocale>
#include <QLabel>
#include <QActionGroup>
#include <QMenu>

#include "controls/activelabel.h"
#include "markdowneditor.h"

StatusBarWidget::StatusBarWidget(MarkdownEditor* editor) :
    m_editor(editor),
    m_lineColLabel(0),
    m_wordCountLabel(0),
    m_styleLabel(0),
    m_styleActions(0),
    m_htmlLabel(0)

{
    // main layout
    QHBoxLayout *topLayout = new QHBoxLayout(this);
    topLayout->setContentsMargins(4,0,4,0);
    topLayout->setSpacing(4);

    // line&column label
    m_lineColLabel = new QLabel;
    topLayout->addWidget(m_lineColLabel, 0);
    m_lineColLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    // word count label
    m_wordCountLabel = new QLabel;
    m_wordCountLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    topLayout->addWidget(m_wordCountLabel, 0);

    // add spacer
    topLayout->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    // styles label
    m_styleLabel = new QLabel;
    m_styleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    topLayout->addWidget(m_styleLabel, 0);

    m_styleLabel->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_styleLabel, &QLabel::customContextMenuRequested, this, &StatusBarWidget::styleContextMenu);

    // separator label
    topLayout->addWidget(new QLabel("|"), 0);

    // html preview label
    m_htmlLabel = new ActiveLabel;
    m_htmlLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    topLayout->addWidget(m_htmlLabel, 0);

    connect(m_editor, &MarkdownEditor::cursorPositionChanged, this, &StatusBarWidget::cursorPositionChanged);
    connect(m_editor, &MarkdownEditor::textChanged, this, &StatusBarWidget::textChanged);
}

StatusBarWidget::~StatusBarWidget()
{
}

void StatusBarWidget::update()
{
    cursorPositionChanged();
    textChanged();
}

void StatusBarWidget::showLineColumn(bool enabled)
{
    if (enabled)
        m_lineColLabel->show();
    else
        m_lineColLabel->hide();
}

void StatusBarWidget::setHtmlAction(QAction *action)
{   
    m_htmlLabel->setAction(action);
}

void StatusBarWidget::setStyleActions(QActionGroup *actionGroup)
{
    // if was previously defined, disconnect
    if (m_styleActions) {
        disconnect(m_styleActions, &QActionGroup::triggered, this, &StatusBarWidget::updateStyleLabel);
    }

    // set new actions group
    m_styleActions = actionGroup;
    updateStyleLabel();

    connect(m_styleActions, &QActionGroup::triggered, this, &StatusBarWidget::updateStyleLabel);
}

void StatusBarWidget::cursorPositionChanged()
{
    QTextCursor cursor = m_editor->textCursor();

    int line = cursor.blockNumber();
    int column = cursor.positionInBlock();

    m_lineColLabel->setText(tr("Line %1, Column %2 %3")
            .arg(QLocale().toString(line + 1))
            .arg(QLocale().toString(column + 1))
            .arg("|")
            );
}

void StatusBarWidget::textChanged()
{
    // update statistics
    if (m_wordCountLabel) {
        int words = m_editor->countWords();
        int lines = m_editor->document()->lineCount();
        int chars = m_editor->document()->characterCount();

        m_wordCountLabel->setText(tr("%1 words").arg(words));
        m_wordCountLabel->setToolTip(tr("Lines: %1  Words: %2  Characters: %3").arg(lines).arg(words).arg(chars));
    }
}

void StatusBarWidget::styleContextMenu(const QPoint &pos)
{
    if (m_styleActions) {
        QMenu menu;
        menu.addActions(m_styleActions->actions());
        menu.exec(m_styleLabel->mapToGlobal(pos));
    }
}

void StatusBarWidget::updateStyleLabel()
{
    QAction* action = m_styleActions->checkedAction();
    if (action)
        m_styleLabel->setText(tr("Style: %1").arg(action->text()));
}
