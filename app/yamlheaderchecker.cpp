#include <QRegularExpression>
#include "yamlheaderchecker.h"

YamlHeaderChecker::YamlHeaderChecker(const QString &text)
{
    QRegularExpression rx(QStringLiteral(R"(^---\s*\n(.*?\n)?(---|\.\.\.)\s*(\n|$))"),
                          QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch match = rx.match(text);
    if (match.hasMatch()) {
        m_header = match.captured(0);
        m_body = text.mid(m_header.length());
    } else {
        m_body = text;
    }
}

bool YamlHeaderChecker::hasHeader() const
{
    return !m_header.isEmpty();
}

QString YamlHeaderChecker::header() const
{
    return m_header;
}

QString YamlHeaderChecker::body() const
{
    return m_body;
}
