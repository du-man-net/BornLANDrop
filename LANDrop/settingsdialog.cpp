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

#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QComboBox>
#include <QVersionNumber>
#include <QNetworkProxy>
#include <QDir>

#include "settings.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "QFileSystemWatcher"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
    setWindowTitle(tr("LANDrop for RaspBerry PI"));

    //Wifi settings
    ui->wifiSSIDlineEdit->setText(Settings::deviceName());

    // prepare FS watcher to detect added USB memory
    watcher = new QFileSystemWatcher(this);
    watcher->addPath("/dev");

    connect(watcher, &QFileSystemWatcher::directoryChanged, this, &SettingsDialog::USBDeviceChanged);
    connect(ui->diskNameCombo, &QComboBox::currentTextChanged, this, &SettingsDialog::diskNameComboTextChanged);
    connect(ui->projectNameCombo, &QComboBox::currentTextChanged, this, &SettingsDialog::projectNameComboTextChanged);

    SettingsDialog::diskNameComboRefresh();

    server.start();
    discoveryService.start(server.port());
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::USBDeviceChanged()
{
    SettingsDialog::diskNameComboRefresh();
}

void SettingsDialog::diskNameComboTextChanged()
{
    SettingsDialog::projectNameComboRefresh();
    Settings::setDiskName(ui->diskNameCombo->currentText());
}

void SettingsDialog::projectNameComboTextChanged()
{
    Settings::setProjectName(ui->projectNameCombo->currentText());
}

void SettingsDialog::diskNameComboRefresh()
{
    ui->diskNameCombo->clear();
    QString d = Settings::dirBase();
    QDir dir{d};
    if (dir.exists()) {
        dir.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
        QFileInfoList list = dir.entryInfoList();
        for (QFileInfo finfo: list) {
            ui->diskNameCombo->addItem(finfo.fileName());
            if (finfo.fileName()==Settings::diskName()){
                ui->diskNameCombo->setCurrentText(finfo.fileName());
            }
        }
    }
    Settings::setDiskName(ui->diskNameCombo->currentText());
}

void SettingsDialog::projectNameComboRefresh()
{
    ui->projectNameCombo->clear();
    if (ui->diskNameCombo->count()){
        ui->projectNameCombo->addItem("LANDrop");
        QString d = Settings::dirBase();
        d += QDir::separator() + ui->diskNameCombo->currentText();
        QDir dir{d};
        if (dir.exists()) {
            dir.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
            QFileInfoList list = dir.entryInfoList();
            for (QFileInfo finfo: list) {
                ui->projectNameCombo->addItem(finfo.fileName());
                if (finfo.fileName()==Settings::projectName()){
                    ui->projectNameCombo->setCurrentText(finfo.fileName());
                }
            }
        }
    }
    Settings::setDiskName(ui->projectNameCombo->currentText());
}


