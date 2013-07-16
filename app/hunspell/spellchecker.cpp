#include "spellchecker.h"
using hunspell::SpellChecker;

#include <QDebug>
#include <QDir>
#include <QTextCodec>

#include <hunspell/hunspell.hxx>

SpellChecker::SpellChecker() :
    hunspellChecker(0),
    textCodec(0)
{
    QByteArray affixFilePath = QString(QDir::currentPath() + "/dictionaries/en_US.aff").toLocal8Bit();
    QByteArray dictFilePath = QString(QDir::currentPath() + "/dictionaries/en_US.dic").toLocal8Bit();

    hunspellChecker = new Hunspell(affixFilePath, dictFilePath);

    textCodec = QTextCodec::codecForName(hunspellChecker->get_dic_encoding());
    if (!textCodec) {
        textCodec = QTextCodec::codecForName("UTF-8");
    }
    qDebug() << textCodec->name();
}

bool SpellChecker::isCorrect(const QString &word)
{
    QByteArray ba = textCodec->fromUnicode(word);
    return hunspellChecker->spell(ba) != 0;
}

QStringList SpellChecker::suggestions(const QString &word)
{
    QStringList suggestions;

    char **suggestedWords;
    QByteArray ba = textCodec->fromUnicode(word);
    int count = hunspellChecker->suggest(&suggestedWords, ba);

    for (int i = 0; i < count; ++i) {
        suggestions << textCodec->toUnicode(suggestedWords[i]);
    }

    hunspellChecker->free_list(&suggestedWords, count);

    return suggestions;
}
