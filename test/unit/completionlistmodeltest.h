#ifndef COMPLETIONLISTMODELTEST_H
#define COMPLETIONLISTMODELTEST_H

#include <QObject>

struct Snippet;
class CompletionListModel;


class CompletionListModelTest : public QObject
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
    CompletionListModel *model;
};

#endif // COMPLETIONLISTMODELTEST_H
