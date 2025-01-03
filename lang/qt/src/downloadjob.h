/*
    downloadjob.h

    This file is part of qgpgme, the Qt API binding for gpgme
    Copyright (c) 2004 Klarälvdalens Datakonsult AB
    Copyright (c) 2016 by Bundesamt für Sicherheit in der Informationstechnik
    Software engineering by Intevation GmbH

    QGpgME is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    QGpgME is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    In addition, as a special exception, the copyright holders give
    permission to link the code of this program with any edition of
    the Qt library by Trolltech AS, Norway (or with modified versions
    of Qt that use the same license as Qt), and distribute linked
    combinations including the two.  You must obey the GNU General
    Public License in all respects for all of the code used other than
    Qt.  If you modify this file, you may extend this exception to
    your version of the file, but you are not obligated to do so.  If
    you do not wish to do so, delete this exception statement from
    your version.
*/

#ifndef __KLEO_DOWNLOADJOB_H__
#define __KLEO_DOWNLOADJOB_H__

#include "job.h"

#include <QtCore/QByteArray>
#include <QtCore/QStringList>

#include <memory>

namespace GpgME
{
class Error;
}

class QIODevice;
class QByteArray;

namespace QGpgME
{

/**
   @short An abstract base class for asynchronous downloaders

   To use a DownloadJob, first obtain an instance from the
   CryptoBackend implementation, connect the progress() and result()
   signals to suitable slots and then start the download with a call
   to start(). This call might fail, in which case the DownloadJob
   instance will have scheduled it's own destruction with a call to
   QObject::deleteLater().

   After result() is emitted, the DownloadJob will schedule it's own
   destruction by calling QObject::deleteLater().
*/
class QGPGME_EXPORT DownloadJob : public Job
{
    Q_OBJECT
protected:
    explicit DownloadJob(QObject *parent);
public:
    ~DownloadJob();

    /**
       Starts the download operation. \a fingerprint is the
       fingerprint of the key to download. If \a fingerprint is empty,
       contains only whitespace or anything other than a fingerprint,
       the result is undefined.

       Output is written to \a keyData, if given. Otherwise, it is
       passed as the second argument of result().
    */
    virtual GpgME::Error start(const QByteArray &fingerprint,
                               const std::shared_ptr<QIODevice> &keyData) = 0;

    /**
       Starts the download operation. \a fingerprints is a list of
       fingerprints used to specify the list of keys downloaded. Empty
       patterns are ignored. If \a fingerprints is empty, contains
       only empty strings or anything other than fingerprints, the
       result is undefined.
    */
    QGPGME_DEPRECATED virtual GpgME::Error start(const QStringList &fingerprints) = 0;

Q_SIGNALS:
    void result(const GpgME::Error &result, const QByteArray &keyData, const QString &auditLogAsHtml = QString(), const GpgME::Error &auditLogError = GpgME::Error());
};

}

#endif // __KLEO_DOWNLOADJOB_H__
