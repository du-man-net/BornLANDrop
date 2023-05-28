/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2021, LANDrop
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "settings.h"

#include <QApplication>
#include <QDir>
#include <QSettings>
#include <QHostInfo>

QString Settings::deviceName()
{
    QString d = QHostInfo::localHostName();
    //return QSettings().value("deviceName", d).toString();
    return d;
}

QString Settings::dirBase()
{
    QString name = qgetenv("USER");
    return "/media/" + name;
}

QString Settings::diskName()
{
    return QSettings().value("diskName").toString();
}

QString Settings::projectName()
{
    return QSettings().value("projectName").toString();
}

QString Settings::downloadPath()
{
    if (QSettings().value("diskName").toString().length()>0){
        if (QSettings().value("projectName").toString().length()>0){
            QString d = Settings::dirBase();
            d += QDir::separator() + QSettings().value("diskName").toString();
            d += QDir::separator() + QSettings().value("projectName").toString();
            return d;
        }
    }
    return "";
}

bool Settings::discoverable()
{
    //return QSettings().value("discoverable", true).toBool();
    return true;
}

quint16 Settings::serverPort()
{
    return QSettings().value("serverPort", 0u).toUInt();
}

void Settings::setDiskName(const QString &diskName)
{
    QSettings().setValue("diskName", diskName);
}

void Settings::setProjectName(const QString &projectName)
{
    QSettings().setValue("projectName", projectName);
}

void Settings::setServerPort(quint16 serverPort)
{
    QSettings().setValue("serverPort", serverPort);
}
