#ifndef SNIPPETLISTMODELTEST_H
#define SNIPPETLISTMODELTEST_H

#include <QObject>

struct Snippet;
class SnippetListModel;


class SnippetListModelTest : public QObject
{
    Q_OBJECT
    
private slots:
    void acceptsNewSnippet();
    void updatesCorrectRowForSnippet();
    void removesCorrectRowForSnippet();
    void holdsSnippetsInTriggerOrder();

private:
    void assertItemMatchesSnippet(int row, const Snippet &snippet);
    QVariant itemValue(int row, int role);

private:
    SnippetListModel *model;
};

#endif // SNIPPETLISTMODELTEST_H
