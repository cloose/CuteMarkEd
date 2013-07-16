#ifndef HUNSPELL_SPELLCHECKER_H
#define HUNSPELL_SPELLCHECKER_H

#include <QtCore/qstring.h>

class Hunspell;
class QTextCodec;

namespace hunspell {

class SpellChecker
{
public:
    SpellChecker();

    bool isCorrect(const QString &word);
    QStringList suggestions(const QString &word);

private:
    Hunspell *hunspellChecker;
    QTextCodec *textCodec;
};

} // namespace Hunspell

#endif // HUNSPELL_SPELLCHECKER_H
