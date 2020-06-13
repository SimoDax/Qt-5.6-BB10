/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtSql module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSQL_TDS_H
#define QSQL_TDS_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtSql/qsqlresult.h>
#include <QtSql/qsqldriver.h>

#ifdef Q_OS_WIN32
#define WIN32_LEAN_AND_MEAN
#ifndef Q_USE_SYBASE
#define DBNTWIN32 // indicates 32bit windows dblib
#endif
#include <winsock2.h>
#include <QtCore/qt_windows.h>
#include <sqlfront.h>
#include <sqldb.h>
#define CS_PUBLIC
#else
#include <sybfront.h>
#include <sybdb.h>
#endif //Q_OS_WIN32

#ifdef QT_PLUGIN
#define Q_EXPORT_SQLDRIVER_TDS
#else
#define Q_EXPORT_SQLDRIVER_TDS Q_SQL_EXPORT
#endif

QT_BEGIN_NAMESPACE

class QTDSDriverPrivate;
class QTDSDriver;

class Q_EXPORT_SQLDRIVER_TDS QTDSDriver : public QSqlDriver
{
    Q_DECLARE_PRIVATE(QTDSDriver)
    Q_OBJECT
    friend class QTDSResult;
public:
    explicit QTDSDriver(QObject* parent = 0);
    QTDSDriver(LOGINREC* rec, const QString& host, const QString &db, QObject* parent = 0);
    ~QTDSDriver();
    bool hasFeature(DriverFeature f) const;
    bool open(const QString & db,
               const QString & user,
               const QString & password,
               const QString & host,
               int port,
               const QString& connOpts);
    void close();
    QStringList tables(QSql::TableType) const;
    QSqlResult *createResult() const;
    QSqlRecord record(const QString& tablename) const;
    QSqlIndex primaryIndex(const QString& tablename) const;

    QString formatValue(const QSqlField &field,
                         bool trimStrings) const;
    QVariant handle() const;

    QString escapeIdentifier(const QString &identifier, IdentifierType type) const;

protected:
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
private:
    void init();
};

QT_END_NAMESPACE

#endif // QSQL_TDS_H
