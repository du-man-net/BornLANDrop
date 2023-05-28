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

#include <QAbstractButton>
#include <QNetworkProxy>
#include <QDesktopServices>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QVersionNumber>

#include "filetransferdialog.h"
#include "ui_filetransferdialog.h"

FileTransferDialog::FileTransferDialog(QWidget *parent, FileTransferSession *session) :
    QDialog(parent), ui(new Ui::FileTransferDialog), session(session), errored(false), questionBox(this)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);

    session->setParent(this);
    connect(session, &FileTransferSession::printMessage, ui->statusLabel, &QLabel::setText);
    connect(session, &FileTransferSession::updateProgress, this, &FileTransferDialog::sessionUpdateProgress);
    connect(session, &FileTransferSession::errorOccurred, this, &FileTransferDialog::sessionErrorOccurred);
    connect(session, &FileTransferSession::ended, this, &FileTransferDialog::accept);
    session->start();
    show();
    connect(timer, &QTimer::timeout, this, &FileTransferDialog::autoClose);
    timer->start(20);
}

FileTransferDialog::~FileTransferDialog()
{
    delete ui;
}

void FileTransferDialog::autoClose()
{
    timer->stop();
    session->respond(true);
}

void FileTransferDialog::sessionUpdateProgress(double progress)
{
    ui->progressBar->setValue(ui->progressBar->maximum() * progress);
}

void FileTransferDialog::sessionErrorOccurred(const QString &msg)
{
    if (errored)
        return;
    errored = true;
    if (isVisible())
        QMessageBox::critical(this, QApplication::applicationName(), msg);
    done(Rejected);
}
