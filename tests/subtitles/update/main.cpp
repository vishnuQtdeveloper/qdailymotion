/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "subtitlesrequest.h"
#include "json.h"
#include <QCoreApplication>
#include <QStringList>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    app.setOrganizationName("QDailymotion");
    app.setApplicationName("QDailymotion");
    
    QStringList args = app.arguments();
    
    if (args.size() < 3) {
        qWarning() << "Usage: subtitles-update ID SUBTITLE";
        return 0;
    }
    
    args.removeFirst();
    
    QSettings settings;

    QDailymotion::SubtitlesRequest request;
    request.setClientId(settings.value("Authentication/clientId").toString());
    request.setClientSecret(settings.value("Authentication/clientSecret").toString());
    request.setAccessToken(settings.value("Authentication/accessToken").toString());
    request.setRefreshToken(settings.value("Authentication/refreshToken").toString());
    request.update(args.takeFirst(), QtJson::Json::parse(args.takeFirst()).toMap());
    QObject::connect(&request, SIGNAL(finished()), &app, SLOT(quit()));

    return app.exec();
}
