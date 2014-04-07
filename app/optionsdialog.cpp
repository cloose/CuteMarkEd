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
#include "optionsdialog.h"
#include "ui_optionsdialog.h"

#include <QAbstractTableModel>
#include <QFontComboBox>
#include <QMessageBox>
#include <QSpinBox>
#include <QSettings>

#include <snippets/snippetcollection.h>
#include "options.h"

class SnippetsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SnippetsTableModel(SnippetCollection *collection, QObject *parent);
    ~SnippetsTableModel() {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QModelIndex createSnippet();
    void removeSnippet(const QModelIndex &index);

private:
    void replaceSnippet(const Snippet &snippet, const QModelIndex &index);
    bool isValidTrigger(const QString &trigger);

private:
    SnippetCollection *snippetCollection;
};


SnippetsTableModel::SnippetsTableModel(SnippetCollection *collection, QObject *parent) :
    QAbstractTableModel(parent),
    snippetCollection(collection)
{
}

int SnippetsTableModel::rowCount(const QModelIndex &) const
{
    return snippetCollection->count();
}

int SnippetsTableModel::columnCount(const QModelIndex &) const
{
    return 2;
}

Qt::ItemFlags SnippetsTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags itemFlags = QAbstractTableModel::flags(index);
    if (index.isValid()) {
        const Snippet snippet = snippetCollection->snippetAt(index.row());
        if (!snippet.builtIn) {
            itemFlags |= Qt::ItemIsEditable;
        }
    }
    return itemFlags;
}

QVariant SnippetsTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    const Snippet snippet = snippetCollection->snippetAt(index.row());

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return snippet.trigger;
        } else {
            return snippet.description + (snippet.builtIn ? " (built-in)" : "");
        }
    }

    if (role == Qt::EditRole) {
        if (index.column() == 0) {
            return snippet.trigger;
        } else {
            return snippet.description;
        }
    }

    return QVariant();
}

bool SnippetsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    Snippet snippet = snippetCollection->snippetAt(index.row());

    if (index.column() == 0) {
        const QString &s = value.toString();
        if (!isValidTrigger(s)) {
            QMessageBox::critical(0, tr("Error", "Title of error message box"), tr("Not a valid trigger."));
            if (snippet.trigger.isEmpty())
                removeSnippet(index);
            return false;
        }
        snippet.trigger = s;
    } else {
        snippet.description = value.toString();
    }

    replaceSnippet(snippet, index);
    return true;
}

QVariant SnippetsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    if (section == 0)
         return tr("Trigger");
     else
        return tr("Description");
}

QModelIndex SnippetsTableModel::createSnippet()
{
    Snippet snippet;
    beginInsertRows(QModelIndex(), 0, 0);
    int row = snippetCollection->insert(snippet);
    endInsertRows();

    return index(row, 0);
}

void SnippetsTableModel::removeSnippet(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    Snippet snippet = snippetCollection->snippetAt(index.row());
    snippetCollection->remove(snippet);
    endRemoveRows();
}

void SnippetsTableModel::replaceSnippet(const Snippet &snippet, const QModelIndex &index)
{
    const int row = index.row();

    Snippet previousSnippet = snippetCollection->snippetAt(index.row());
    snippetCollection->remove(previousSnippet);

    int insertedRow = snippetCollection->insert(snippet);

    if (index.row() == insertedRow) {
        if (index.column() == 0)
            emit dataChanged(index, index.sibling(row, 1));
        else
            emit dataChanged(index.sibling(row, 0), index);
    } else {
        if (row < insertedRow)
            beginMoveRows(QModelIndex(), row, row, QModelIndex(), insertedRow+1);
        else
            beginMoveRows(QModelIndex(), row, row, QModelIndex(), insertedRow);
        endMoveRows();
    }
}

bool SnippetsTableModel::isValidTrigger(const QString &trigger)
{
    if (trigger.isEmpty())
        return false;

    if (snippetCollection->contains(trigger))
        return false;

    for (int i = 0; i < trigger.length(); ++i) {
        if (trigger.at(i).isSpace()) {
            return false;
        }
    }

    return true;
}



OptionsDialog::OptionsDialog(Options *opt, SnippetCollection *collection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog),
    options(opt),
    snippetCollection(collection)
{
    ui->setupUi(this);

    ui->tabWidget->setIconSize(QSize(24, 24));
    ui->tabWidget->setTabIcon(0, QIcon("fa-cog.fontawesome"));
    ui->tabWidget->setTabIcon(1, QIcon("fa-file-text-o.fontawesome"));
    ui->tabWidget->setTabIcon(2, QIcon("fa-globe.fontawesome"));
    ui->tabWidget->setTabIcon(3, QIcon("fa-puzzle-piece.fontawesome"));

    ui->fontComboBox->setFontFilters(QFontComboBox::MonospacedFonts);

    foreach (int size, QFontDatabase::standardSizes()) {
        ui->sizeComboBox->addItem(QString().setNum(size));
    }

    ui->portLineEdit->setValidator(new QIntValidator(0, 65535));
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    ui->snippetTableView->setModel(new SnippetsTableModel(snippetCollection, ui->snippetTableView));
    connect(ui->snippetTableView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentSnippetChanged(QModelIndex,QModelIndex)));

    connect(ui->snippetTextEdit, SIGNAL(textChanged()),
            this, SLOT(snippetTextChanged()));

    // FIXME: remove general tab for now, if hoedown is disabled, until more converters are supported
#ifndef ENABLE_HOEDOWN
    ui->tabWidget->removeTab(0);
#endif

    // read configuration state
    readState();
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::done(int result)
{
    if (result == QDialog::Accepted) {
        // save configuration state
        saveState();
    }

    QDialog::done(result);
}

void OptionsDialog::manualProxyRadioButtonToggled(bool checked)
{
    ui->hostLineEdit->setEnabled(checked);
    ui->portLineEdit->setEnabled(checked);
    ui->userNameLineEdit->setEnabled(checked);
    ui->passwordLineEdit->setEnabled(checked);
}

void OptionsDialog::currentSnippetChanged(const QModelIndex &current, const QModelIndex &)
{
    const Snippet snippet = snippetCollection->snippetAt(current.row());

    // update text edit for snippet content
    QString formattedSnippet(snippet.snippet);
    formattedSnippet.insert(snippet.cursorPosition, "$|");
    ui->snippetTextEdit->setPlainText(formattedSnippet);
    ui->snippetTextEdit->setReadOnly(snippet.builtIn);

    // disable remove button when built-in snippet is selected
    ui->removeSnippetButton->setEnabled(!snippet.builtIn);
}

void OptionsDialog::snippetTextChanged()
{
    const QModelIndex &modelIndex = ui->snippetTableView->selectionModel()->currentIndex();
    if (modelIndex.isValid()) {
        Snippet snippet = snippetCollection->snippetAt(modelIndex.row());
        if (!snippet.builtIn) {
            snippet.snippet = ui->snippetTextEdit->toPlainText();

            // find cursor marker
            int pos = snippet.snippet.indexOf("$|");
            if (pos >= 0) {
                snippet.cursorPosition = pos;
                snippet.snippet.remove(pos, 2);
            }

            snippetCollection->update(snippet);
        }
    }
}

void OptionsDialog::addSnippetButtonClicked()
{
    SnippetsTableModel *snippetModel = qobject_cast<SnippetsTableModel*>(ui->snippetTableView->model());

    const QModelIndex &index = snippetModel->createSnippet();

    const int row = index.row();
    QModelIndex topLeft = snippetModel->index(row, 0, QModelIndex());
    QModelIndex bottomRight = snippetModel->index(row, 1, QModelIndex());
    QItemSelection selection(topLeft, bottomRight);
    ui->snippetTableView->selectionModel()->select(selection, QItemSelectionModel::SelectCurrent);
    ui->snippetTableView->setCurrentIndex(topLeft);
    ui->snippetTableView->scrollTo(topLeft);

    ui->snippetTableView->edit(index);
}

void OptionsDialog::removeSnippetButtonClicked()
{
    const QModelIndex &modelIndex = ui->snippetTableView->selectionModel()->currentIndex();
    if (!modelIndex.isValid()) {
        QMessageBox::critical(0, tr("Error", "Title of error message box"), tr("No snippet selected."));
        return;
    }

    SnippetsTableModel *snippetModel = qobject_cast<SnippetsTableModel*>(ui->snippetTableView->model());
    snippetModel->removeSnippet(modelIndex);
}

void OptionsDialog::readState()
{
    // general settings
    ui->converterComboBox->setCurrentIndex(options->markdownConverter());

    // editor settings
    QFont font = options->editorFont();
    ui->fontComboBox->setCurrentFont(font);
    ui->sizeComboBox->setCurrentText(QString().setNum(font.pointSize()));
    ui->tabWidthSpinBox->setValue(options->tabWidth());

    // proxy settings
    switch (options->proxyMode()) {
    case Options::NoProxy:
        ui->noProxyRadioButton->setChecked(true);
        break;
    case Options::SystemProxy:
        ui->systemProxyRadioButton->setChecked(true);
        break;
    case Options::ManualProxy:
        ui->manualProxyRadioButton->setChecked(true);
        break;
    }
    ui->hostLineEdit->setText(options->proxyHost());
    ui->portLineEdit->setText(QString::number(options->proxyPort()));
    ui->userNameLineEdit->setText(options->proxyUser());
    ui->passwordLineEdit->setText(options->proxyPassword());
}

void OptionsDialog::saveState()
{
    // general settings
    options->setMarkdownConverter((Options::MarkdownConverter)ui->converterComboBox->currentIndex());

    // editor settings
    QFont font = ui->fontComboBox->currentFont();
    font.setPointSize(ui->sizeComboBox->currentText().toInt());
    options->setEditorFont(font);
    options->setTabWidth(ui->tabWidthSpinBox->value());

    // proxy settings
    if (ui->noProxyRadioButton->isChecked()) {
        options->setProxyMode(Options::NoProxy);
    } else if (ui->systemProxyRadioButton->isChecked()) {
        options->setProxyMode(Options::SystemProxy);
    } else if (ui->manualProxyRadioButton->isChecked()) {
        options->setProxyMode(Options::ManualProxy);
    }
    options->setProxyHost(ui->hostLineEdit->text());
    options->setProxyPort(ui->portLineEdit->text().toInt());
    options->setProxyUser(ui->userNameLineEdit->text());
    options->setProxyPassword(ui->passwordLineEdit->text());
    options->apply();
}


#include "optionsdialog.moc"
