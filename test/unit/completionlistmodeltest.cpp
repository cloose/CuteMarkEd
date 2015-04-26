#include "completionlistmodeltest.h"

#include <QtTest>

#include <snippets/snippet.h>
#include <completionlistmodel.h>


void CompletionListModelTest::acceptsNewSnippet()
{
    model = new CompletionListModel(this);

    QSignalSpy spy(model, SIGNAL(rowsInserted(QModelIndex,int,int)));

    Snippet snippet;
    snippet.trigger = "link";
    snippet.description = "Hyperlink";
    snippet.snippet = "[]()";

    model->snippetCollectionChanged(SnippetCollection::ItemAdded, snippet);

    QCOMPARE(spy.count(), 1);

    QCOMPARE(model->rowCount(), 1);
    assertItemMatchesSnippet(0, snippet);

    delete model;
}

void CompletionListModelTest::updatesCorrectRowForSnippet()
{
    model = new CompletionListModel(this);

    Snippet snippet1; snippet1.trigger = "link"; snippet1.description = "Hyperlink";
    Snippet snippet2; snippet2.trigger = "gq"; snippet2.description = "German Quotes";

    model->snippetCollectionChanged(SnippetCollection::ItemAdded, snippet1);
    model->snippetCollectionChanged(SnippetCollection::ItemAdded, snippet2);

    snippet2.description = "Changed Description";

    model->snippetCollectionChanged(SnippetCollection::ItemChanged, snippet2);

    assertItemMatchesSnippet(0, snippet2);

    delete model;
}

void CompletionListModelTest::removesCorrectRowForSnippet()
{
    model = new CompletionListModel(this);

    QSignalSpy spy(model, SIGNAL(rowsRemoved(QModelIndex,int,int)));

    Snippet snippet1; snippet1.trigger = "link"; snippet1.description = "Hyperlink";
    Snippet snippet2; snippet2.trigger = "gq"; snippet2.description = "German Quotes";

    model->snippetCollectionChanged(SnippetCollection::ItemAdded, snippet1);
    model->snippetCollectionChanged(SnippetCollection::ItemAdded, snippet2);

    model->snippetCollectionChanged(SnippetCollection::ItemDeleted, snippet2);

    QCOMPARE(spy.count(), 1);

    QCOMPARE(model->rowCount(), 1);
    assertItemMatchesSnippet(0, snippet1);

    delete model;
}

void CompletionListModelTest::holdsSnippetsInTriggerOrder()
{
    model = new CompletionListModel(this);

    Snippet snippet1; snippet1.trigger = "a";
    Snippet snippet2; snippet2.trigger = "b";
    Snippet snippet3; snippet3.trigger = "c";

    model->snippetCollectionChanged(SnippetCollection::ItemAdded, snippet2);    // b
    model->snippetCollectionChanged(SnippetCollection::ItemAdded, snippet3);    // c
    model->snippetCollectionChanged(SnippetCollection::ItemAdded, snippet1);    // a

    QCOMPARE(itemValue(0, Qt::EditRole).toString(), snippet1.trigger);    // a
    QCOMPARE(itemValue(1, Qt::EditRole).toString(), snippet2.trigger);    // b
    QCOMPARE(itemValue(2, Qt::EditRole).toString(), snippet3.trigger);    // c

    delete model;
}

void CompletionListModelTest::assertItemMatchesSnippet(int row, const Snippet &snippet)
{
    QCOMPARE(itemValue(row, Qt::EditRole).toString(), snippet.trigger);
    QVERIFY(itemValue(row, Qt::DisplayRole).toString().contains(snippet.trigger));
    QVERIFY(itemValue(row, Qt::DisplayRole).toString().contains(snippet.description));
    QCOMPARE(itemValue(row, Qt::ToolTipRole).toString(), snippet.snippet.toHtmlEscaped());
}

QVariant CompletionListModelTest::itemValue(int row, int role)
{
    return model->data(model->index(row), role);
}
