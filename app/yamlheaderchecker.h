#ifndef YAMLHEADERCHECKER_H
#define YAMLHEADERCHECKER_H

#include <QString>

class YamlHeaderChecker
{
public:
    YamlHeaderChecker(const QString &text);

    bool hasHeader() const;
    QString header() const;
    QString body() const;

private:
    QString m_header;
    QString m_body;
};

#endif // YAMLHEADERCHECKER_H
