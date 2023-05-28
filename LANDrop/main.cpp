
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

#include <stdexcept>

#include <QObject>
#include <QTranslator>
#include <QApplication>
#include <QDebug>
#include "settings.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("LANDrop");
    a.setOrganizationDomain("landrop.app");
    a.setApplicationName("LANDrop");
    a.setApplicationVersion("0.4.0");


    QTranslator appTranslator;
    qDebug()<< "/home/pi/LANDrop/LANDrop/locales/" + a.applicationName() + '.' + QLocale::system().name() + ".qm";
    if (appTranslator.load( "/home/pi/LANDrop/LANDrop/locales/" + a.applicationName() + '.' + QLocale::system().name() + ".qm")){
        a.installTranslator(&appTranslator);
        qDebug()<< "installation succeed";
    }

    SettingsDialog w;
    w.show();
    return a.exec();
}
