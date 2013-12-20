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
#include "embeddedmediapreprocessor.h"

#include <QString>

QRegularExpression EmbeddedMediaPreprocessor::re("@\\[(.*)\\]\\((.*)\\)");

#include <QDebug>
EmbeddedMediaPreprocessor::~EmbeddedMediaPreprocessor()
{
    qDebug() << Q_FUNC_INFO;
}

void EmbeddedMediaPreprocessor::doProcessText(QString &text)
{
//    QRegularExpression re("@\\[(.*)\\]\\((.*)\\)");
    text.replace(re, QStringLiteral("<a href=\"\\2\" class=\"embed\">\\1</a>"));
}
