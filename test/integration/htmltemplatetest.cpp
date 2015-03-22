/*
* Copyright 2015 Christian Loose <christian.loose@hamburg.de>
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
#include "htmltemplatetest.h"

#include <QtTest>

#include <template/htmltemplate.h>
#include "loremipsumtestdata.h"

static const QString HTML_TEMPLATE = QStringLiteral("<html><head><!--__HTML_HEADER__--></head><body><!--__HTML_CONTENT__--></body></html>");

void HtmlTemplateTest::rendersContentInsideBodyTags()
{
	HtmlTemplate htmlTemplate(HTML_TEMPLATE);

	QString html = htmlTemplate.render("<p>TEST</p>", 0);

	QCOMPARE(html, QStringLiteral("<html><head><script type=\"text/javascript\">window.onscroll = function() { synchronizer.webViewScrolled(); }; </script>\n</head><body><p>TEST</p></body></html>"));
}
