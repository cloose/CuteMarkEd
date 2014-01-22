#include "reveal/revealoptions.h"

QString RevealOptions::author() const
{
    return m_author;
}

void RevealOptions::setAuthor(const QString& author)
{
    m_author = author;
}

QString RevealOptions::description() const
{
    return m_description;
}

void RevealOptions::setDescription(const QString& description)
{
    m_description = description;
}

bool RevealOptions::showControls() const
{
    return m_showControls;
}

void RevealOptions::setShowControls(bool on)
{
    m_showControls = on;
}

bool RevealOptions::showProgress() const
{
    return m_showProgress;
}

void RevealOptions::setShowProgress(bool on)
{
    m_showProgress = on;
}

bool RevealOptions::useHistory() const
{
    return m_useHistory;
}

void RevealOptions::setUseHistory(bool on)
{
    m_useHistory = on;
}

bool RevealOptions::centerPage() const
{
    return m_centerPage;
}

void RevealOptions::setCenterPage(bool on)
{
    m_centerPage = on;
}
