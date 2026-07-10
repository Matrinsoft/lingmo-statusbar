/*
 * Copyright (C) 2024 - 2022 LingmoOS Team.
 *
 * Author:     Reion Wong <reionwong@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "lyricshelper.h"

#include <QApplication>
#include <QDebug>

LyricsHelper::LyricsHelper(QObject *parent)
    : QObject(parent)
{
    m_LyricsVisible = false;
    //寤虹珛鍒皊ession bus鐨勮繛鎺?
    QDBusConnection connection = QDBusConnection::sessionBus();
    if(!connection.registerService("org.lingmo.Statusbar"))
    {
        qDebug() << "error:" << connection.lastError().message();
    }
    if(!connection.registerObject("/Statusbar/Lyrics", this,QDBusConnection::ExportAllSlots))
    {
        qDebug() << "error:姝岃瘝瀵硅薄娉ㄥ唽澶辫触";
    }
    connect(Timer, SIGNAL(timeout()), this, SLOT(onLyricsVisibleChanged()));
}

void LyricsHelper::sendLyrics(QString text)
{
    qDebug() << "鎺ュ彈鍒版瓕璇嶄俊鍙凤紒锛侊紒";
    m_LyricsVisible = true;
    emit lyricsVisibleChanged();
    m_Lyrics = text;
    Timer->stop();
    Timer->start(20000);
    Timer->setSingleShot(true);
    emit lyricsChanged();
}

QString LyricsHelper::getLyrics()
{
    return m_Lyrics;
}

bool LyricsHelper::getLyricsVisible()
{
    return m_LyricsVisible;
}

void LyricsHelper::onLyricsVisibleChanged()
{
    m_LyricsVisible = false;
    emit lyricsVisibleChanged();
}
